#include "LobbyScreen.h"
#include "GameState.h"
#include "AudioManager.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool LobbyScreen::isInLobby = true;
GLuint LobbyScreen::backgroundTexture = 0;

// 버튼 크기
const float LobbyScreen::BUTTON_WIDTH = 400.0f;
const float LobbyScreen::BUTTON_HEIGHT = 80.0f;

// 버튼 위치는 동적으로 계산됨
const float LobbyScreen::START_BTN_X = 0.0f;  // draw()에서 계산
const float LobbyScreen::START_BTN_Y = 0.0f;
const float LobbyScreen::EXIT_BTN_X = 0.0f;
const float LobbyScreen::EXIT_BTN_Y = 0.0f;

void LobbyScreen::init()
{
    isInLobby = true;
    loadTexture("mainscreen.png");
    
    // 로비 배경음악 재생
    std::cout << "Initializing lobby screen and playing music..." << std::endl;
    AudioManager::playBackgroundMusicSimple(L"lobby.wav");
}

bool LobbyScreen::loadTexture(const char* filename)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);

    if (!image)
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    std::cout << "Texture loaded successfully: " << filename << std::endl;
    return true;
}

void LobbyScreen::draw()
{
    // 셰이더 프로그램 비활성화 (2D UI 그리기 전에 필수!)
    glUseProgram(0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    std::cout << "LobbyScreen draw - Window: " << windowWidth << "x" << windowHeight << std::endl;

    // 버튼 위치를 화면 중앙 기준으로 동적 계산
    float startBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
    float startBtnY = windowHeight / 2.0f - 50.0f;
    float exitBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
    float exitBtnY = windowHeight / 2.0f - 150.0f;

  std::cout << "Start button: (" << startBtnX << ", " << startBtnY << ")" << std::endl;
    std::cout << "Exit button: (" << exitBtnX << ", " << exitBtnY << ")" << std::endl;

    // 2D 직교 투영 설정
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 배경 이미지 그리기
    if (backgroundTexture != 0)
    {
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
        glTexCoord2f(1.0f, 0.0f); glVertex2f((float)windowWidth, 0);
     glTexCoord2f(1.0f, 1.0f); glVertex2f((float)windowWidth, (float)windowHeight);
  glTexCoord2f(0.0f, 1.0f); glVertex2f(0, (float)windowHeight);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    else
    {
     // 배경 이미지 로드 실패 시 검은 배경
        std::cout << "No background texture, using black background" << std::endl;
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // 블렌딩 활성화 (버튼 그리기 전)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 버튼 그리기
    std::cout << "Drawing buttons..." << std::endl;
    drawButton(startBtnX, startBtnY, BUTTON_WIDTH, BUTTON_HEIGHT, "Start Game");
    drawButton(exitBtnX, exitBtnY, BUTTON_WIDTH, BUTTON_HEIGHT, "Exit Game");

    // 블렌딩 비활성화
    glDisable(GL_BLEND);

    // 원래 상태로 복원
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void LobbyScreen::drawButton(float x, float y, float width, float height, const char* text)
{
    std::cout << "LobbyScreen::drawButton called: pos=(" << x << ", " << y << ") size=(" << width << ", " << height << ")" << std::endl;

    // 버튼 배경 (완전 불투명)
    glColor4f(0.2f, 0.5f, 0.8f, 1.0f); // 완전 불투명으로 변경
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 버튼 테두리 (더 두껍고 눈에 띄게)
    glColor3f(1.0f, 1.0f, 0.0f); // 노란색으로 변경
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 버튼 텍스트
    glColor3f(1.0f, 1.0f, 1.0f);
    float textX = x + width / 2.0f - 60.0f;
    float textY = y + height / 2.0f - 10.0f;
    glRasterPos2f(textX, textY);

    for (const char* c = text; *c != '\0'; c++)
    {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

bool LobbyScreen::isMouseInButton(int mouseX, int mouseY, float btnX, float btnY, float btnWidth, float btnHeight)
{
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    // OpenGL 좌표계로 변환 (Y축 반전)
    int glMouseY = windowHeight - mouseY;

    return (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        glMouseY >= btnY && glMouseY <= btnY + btnHeight);
}

void LobbyScreen::handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

     // 버튼 위치 재계산 (draw()와 동일하게)
        float startBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
        float startBtnY = windowHeight / 2.0f - 50.0f;
  float exitBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
float exitBtnY = windowHeight / 2.0f - 150.0f;

        // Start Game 버튼 클릭
     if (isMouseInButton(x, y, startBtnX, startBtnY, BUTTON_WIDTH, BUTTON_HEIGHT))
     {
        std::cout << "Start Game clicked!" << std::endl;
    isInLobby = false;
     
            // 게임 배경 음악 재생
     AudioManager::playBackgroundMusicSimple(L"game.wav");
         
            GameState::initGame();
    glutPostRedisplay();
        }
        // Exit Game 버튼 클릭
     else if (isMouseInButton(x, y, exitBtnX, exitBtnY, BUTTON_WIDTH, BUTTON_HEIGHT))
        {
    std::cout << "Exit Game clicked!" << std::endl;
            cleanup();
 AudioManager::cleanup();
     exit(0);
  }
    }
}

void LobbyScreen::cleanup()
{
    if (backgroundTexture != 0)
    {
        glDeleteTextures(1, &backgroundTexture);
        backgroundTexture = 0;
    }
}