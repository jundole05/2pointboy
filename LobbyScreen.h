#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>

class LobbyScreen
{
public:
    static bool isInLobby;
    static GLuint backgroundTexture;

    static void init();
    static void draw();
    static void handleMouseClick(int button, int state, int x, int y);
    static void cleanup();

private:
    static bool loadTexture(const char* filename);
    static void drawButton(float x, float y, float width, float height, const char* text);
    static bool isMouseInButton(int mouseX, int mouseY, float btnX, float btnY, float btnWidth, float btnHeight);

    // 버튼 위치 및 크기 (화면 중앙 기준)
    static const float START_BTN_X;
    static const float START_BTN_Y;
    static const float EXIT_BTN_X;
    static const float EXIT_BTN_Y;
    static const float BUTTON_WIDTH;
    static const float BUTTON_HEIGHT;
};
