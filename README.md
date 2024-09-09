# RaylibClockProject
This repository contains two C programs for implementing a digital clock using the Raylib library. Both programs offer different versions of a digital clock, which can be compiled and run using the steps below.

## Files

1. **Clock-dev7.c**: 
   - A basic digital clock implementation using Raylib. This program displays the current time in a simple interface.
   
2. **DigitalC.c**:
   - An extended version of the digital clock with additional features and customization options.

## Compilation and Usage
To compile and run either of the programs, use the following commands (assuming you have Raylib installed):

```bash
# For Clock-dev7.c
gcc -o Clock-dev7 Clock-dev7.c -L/opt/homebrew/lib -lraylib

# For DigitalC.c
gcc -o DigitalC DigitalC.c -L/opt/homebrew/lib -lraylib
