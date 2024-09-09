#include <stdlib.h>
#include"raylib.h"
#include <stdio.h>
#include <time.h>
   char* getCurrentTime(void){
    // Get the current time in seconds since the Unix epoch (January 1, 1970)
    time_t currentTime = time(NULL);
    
    // Convert the Unix time to a local time struct representing the current time
    struct tm* localTime = localtime(&currentTime);

    // Extract the hour, minute, and second values from the local time struct
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    // Allocate memory on the heap for a string containing the formatted time
    char* timeString = (char*)malloc(sizeof(char) * 9);

    // Use snprintf() to format the time string as "HH:MM:SS" and store it in the allocated memory
    snprintf(timeString, 9, "%02d:%02d:%02d", hour, minute, second);

    // Return the formatted time string
    return timeString;
}


void drawTimeString(const char* timeString)
{
    // Set the font size to 50
    int fontSize = 100;

    // Measure the size of the time string using the MeasureTextEx() function
    Vector2 textSize = MeasureTextEx(GetFontDefault(), timeString, fontSize, 1);

    // Draw the time string in the center of the window using the DrawText() function
    // The x-coordinate is set to the center of the screen minus half the width of the time string
    // The y-coordinate is set to the center of the screen minus half the height of the font
    
	// Calculate the x-coordinate of the text to center it horizontally
    double textX = GetScreenWidth() / 2 - textSize.x / 2;

    // Calculate the y-coordinate of the text to center it vertically
    double textY = GetScreenHeight() / 2 - textSize.y / 2;

	//printf("textX = %f, textY = %f\n", textX, textY);
	//printf("textSize.x = %f, textSize.y = %f\n", textSize.x, textSize.y);

	DrawText(timeString, (GetScreenWidth() / 2 - textSize.x / 2) - 30 , GetScreenHeight() / 2 - textSize.y / 2, fontSize, BLUE);
}




int main(void){
    //Initailizationn
    //-------------------------------
    const int screenWidth = 800;
    const int screenHight = 450;
    
    InitWindow(screenWidth, screenHight, "raylib Digital Clock");

    SetTargetFPS(60);
    //--------------------------------

    //Main game loop
    while (!WindowShouldClose()){
        // Get the current time string
        char* timeString = getCurrentTime();

        // Clear the screen and draw the time string in the center of the window
        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawTimeString(timeString);
		EndDrawing();

        // Release the memory used by the time string
        free(timeString);
    }
   
    CloseWindow();    //Close window and OpenGL context
    //----------------------------------
    return 0;
}

