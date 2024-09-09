#include"raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void drawHourHand(int cx, int cy, int radius, int h, int m, int s){
    Vector2 startV, endV;
    double theta = (h*60*60+m*60+s)*2*PI/(12*60*60);
    double phi = PI/2-theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.70*radius*cos(phi)+cx;
    endV.y = -0.70*radius*sin(phi)+cy;
    DrawLineEx(startV, endV, 10, BLACK);
}

void drawMinHand(int cx, int cy, int radius, int m, int s){
    Vector2 startV, endV;
    double theta = (m*60+s)*2*PI/(60*60);
    double phi = PI/2-theta;
    startV.x = cx; startV.y = cy;
    endV.x = 0.85*radius*cos(phi)+cx;
    endV.y = -0.85*radius*sin(phi)+cy;
    DrawLineEx(startV, endV, 7, BLACK);
}
void drawSecHand(int cx, int cy, int radius, int s) {
    Vector2 startV, endV;
    double theta = s * 2 * PI / 60;
    double phi = PI / 2 - theta;
    startV.x = cx;
    startV.y = cy;
    endV.x = 0.95 * radius * cos(phi) + cx;
    endV.y = -0.95 * radius * sin(phi) + cy;
    DrawLineEx(startV, endV, 2, BLACK);

    Rectangle rect = { cx, cy, 15, 15 };
    Color color = RED;
    float rotation = s * 6;

    DrawRectanglePro(rect, (Vector2){ 7.5, 7.5 }, rotation, color);
    DrawLineEx(startV, endV, 4, RED);
}

void drawClockFace(int cx, int cy, int radius, int rx, int ry, int rw, int rh){
    Rectangle rect = { rx /2 - rw /2 , ry /2 - rh /2, rw, rh};
    DrawRectangle(cx-radius, cy-radius, radius*2, radius*2, RAYWHITE);
    float roundness = 0.2f;
    int segments = 0;
    Color color = BEIGE; 
    for (int i=0; i<60; i++){
        double theta = i*2*PI/60;
        float phi  = i*6;
        int thickness = 1;

        if(i%5==0){
            thickness = 4;
        }
        if((phi>45) &&(phi<=135)){
            float alpha = phi* PI/180.0;
            Vector2 line_pos = (Vector2){cx +radius/tan(alpha), cy + -1*radius};
            DrawLineEx((Vector2){cx,cy} , line_pos , thickness , BLUE);
        }else if((phi>135) && (phi<=225)){
            float alpha = phi* PI/180.0;
            Vector2 line_pos = (Vector2){cx +radius, cy + radius*tan(alpha)};
            DrawLineEx((Vector2){cx,cy} , line_pos , thickness , BLUE);
        }else if((phi>225) && (phi<=315)){
            float alpha = phi* PI/180.0;
            Vector2 line_pos = (Vector2){cx + -1*radius/tan(alpha), cy + radius};
            DrawLineEx((Vector2){cx,cy} , line_pos , thickness , BLUE);
        }else if((phi<=45) || (phi>315)) {
            float alpha = phi* PI/180.0;
            Vector2 line_pos = (Vector2){cx + -1*radius, cy + -1*radius*tan(alpha)};
            DrawLineEx((Vector2){cx,cy} , line_pos , thickness , BLUE);
        }


    }
    DrawRectangleRounded(rect, roundness, segments, color);
}

void drawhands(int cx, int cy, int radius){
    time_t tt = time(NULL);
    struct tm *t= localtime(&tt);
    drawHourHand(cx, cy, radius, t->tm_hour, t->tm_min, t->tm_sec);
    drawMinHand(cx, cy, radius, t->tm_min, t->tm_sec);
    drawSecHand(cx, cy, radius, t->tm_sec);
}

char* getCurrentTime(void){
    time_t tt = time(NULL);
    struct tm *t= localtime(&tt);
    int hour = t->tm_hour;
    int minute = t->tm_min;
    int second = t->tm_sec;
    char* timeString = (char*)malloc(sizeof(char) * 9);
    snprintf(timeString, 9, "%02d:%02d:%02d", hour, minute, second);
    return timeString;
}

void drawTimeString(const char* timeString, int radius){
    int fontSize = 30;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), timeString, fontSize, 1);
    double textX = GetScreenWidth() / 2 - textSize.x / 2;
    double textY = GetScreenHeight() / 2 - textSize.y / 2;
    DrawText(timeString, (GetScreenWidth() / 2 - textSize.x / 2) , (GetScreenHeight() / 2 - textSize.y / 2) + radius / 2, fontSize, BLUE);
}

int main(void){
    const int screenWidth = 450;
    const int screenHight = 450;
    const int clockRadius = 200;
    int widthRec = 350;
    int heightRec = 350;
    InitWindow(screenWidth, screenHight, "raylib Analog Clock");

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        if (IsKeyPressed(KEY_ESCAPE)) {
            break; // Exit the loop if the ESC key is pressed
        }
        char* timeString = getCurrentTime();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawClockFace(screenWidth/2, screenHight/2, clockRadius, screenWidth, screenHight, widthRec, heightRec);

            //drawTimeString(timeString, clockRadius);
            drawhands(screenWidth/2, screenHight/2, clockRadius);



        EndDrawing();
        free(timeString);
    }
    CloseWindow();
    return 0;
}


