#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>

class GameOverScreen
{
public:
    static bool isInGameOver;
    static int finalScore;
    static int finalTime;

    static void init(int score, int time);
    static void draw();
    static void handleMouseClick(int button, int state, int x, int y);
    static void cleanup();

private:
    static void drawButton(float x, float y, float width, float height, const char* text);
    static bool isMouseInButton(int mouseX, int mouseY, float btnX, float btnY, float btnWidth, float btnHeight);
    static void drawText(float x, float y, const char* text, void* font);

    // 버튼 위치 및 크기
    static const float RESTART_BTN_X;
    static const float RESTART_BTN_Y;
    static const float MENU_BTN_X;
    static const float MENU_BTN_Y;
    static const float BUTTON_WIDTH;
    static const float BUTTON_HEIGHT;
};
