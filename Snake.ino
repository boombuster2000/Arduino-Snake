#include "MD_MAX72xx.h"

// Defining hardware, size, and output pins
#define HARDWARE_TYPE MD_MAX72XX::moduleType_t::FC16_HW
#define MAX_DEVICES 1 // no. of screens
#define CS_PIN 9
#define DATA_PIN 11
#define CLK_PIN 13

// Defining joystick pins
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

// Defining joystick threshholds to reduce sensitivity
#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    800
#define DOWN_THRESHOLD  400

// Defining joystick commands
#define COMMAND_NONE   0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

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
{

}


void loop()
{

}