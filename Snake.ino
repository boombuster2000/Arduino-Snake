// Uses the MD_MAX72XX library to communicate with the MD_MAX72XX display. https://github.com/MajicDesigns/MD_MAX72XX


#include "MD_MAX72xx.h"

#define DEBUG 0
#define DEBUG_LOG(message) if (DEBUG) Serial.println(message)

// Defining hardware, size, and output pins
#define HARDWARE_TYPE MD_MAX72XX::moduleType_t::FC16_HW
#define MAX_DEVICES 1 // no. of screens
#define CS_PIN 9
#define DATA_PIN 11
#define CLK_PIN 13

// Defining joystick pins
#define VRX_PIN A0 // Arduino pin connected to VRX pin
#define VRY_PIN A1 // Arduino pin connected to VRY pin

// Defining joystick threshholds to reduce sensitivity
#define LEFT_THRESHOLD 400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD 800
#define DOWN_THRESHOLD 400

// Defining joystick commands
#define COMMAND_NONE 0x00
#define COMMAND_LEFT 0x01
#define COMMAND_RIGHT 0x02
#define COMMAND_UP 0x04
#define COMMAND_DOWN 0x08

struct Vector2
// Struct to group X and Y values
{
    int x = 0, y = 0;
};

Vector2 joystickInput = {}; // To store value of the X axis and Y axis of joystick
Vector2 playerCoords = {};  // Stores coordinates of the player
int command = COMMAND_NONE; // Will store the commands for the joystick

// Create a new instance of the MD_MAX72XX class with hardware SPI connection
MD_MAX72XX display = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup()
// This function is required to setup the pins and display.
{
    if (DEBUG) Serial.begin(9600);

    // Intialize the object
    display.begin();

    // Set the intensity (brightness) of the display (0-15)
    display.control(MD_MAX72XX::controlRequest_t::INTENSITY, 0);
}

int getCommand(Vector2 joystickInput)
// This function converts the analog joystick input to commands. Each bit represents a command.
{
    // Reset commands
    int command = COMMAND_NONE;

    // Check left/right commands
    if (joystickInput.x < LEFT_THRESHOLD) command |= COMMAND_LEFT;
    else if (joystickInput.x > RIGHT_THRESHOLD) command |= COMMAND_RIGHT;

    // Check up/down commands
    if (joystickInput.y > UP_THRESHOLD) command |= COMMAND_UP;
    else if (joystickInput.y < DOWN_THRESHOLD) command |= COMMAND_DOWN;

    return command;
}

void loop()
// Main program will run forever here.
{
    display.clear();
    display.setPoint(playerCoords.x, playerCoords.y, true);

    // Read analog X and Y analog values of joystick
    joystickInput.x = analogRead(VRX_PIN);
    joystickInput.y = analogRead(VRY_PIN);

    // Converts the analog value to commands
    command = getCommand(joystickInput); // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS

    // Print command to serial and process command
    if (command & COMMAND_LEFT)
    {
        DEBUG_LOG("COMMAND LEFT");
        if (0 < playerCoords.x)
        {
            playerCoords.x--;
        }
    }

    if (command & COMMAND_RIGHT)
    {
        DEBUG_LOG("COMMAND RIGHT");
        if (playerCoords.x < display.getColumnCount() - 1)
        {
            playerCoords.x++;
        }
    }

    if (command & COMMAND_UP)
    {
        DEBUG_LOG("COMMAND UP");
        if (0 < playerCoords.y)
        {
            playerCoords.y--;
        }
    }

    if (command & COMMAND_DOWN)
    {
        DEBUG_LOG("COMMAND DOWN");
        if (playerCoords.y < display.getColumnCount() - 1)
        {
            playerCoords.y++;
        }
    }

    delay(100);
}