#include "GameOverScreen.h"
#include "GameState.h"
#include "LobbyScreen.h"
#include "AudioManager.h"
#include <iostream>
#include <cstdio>

// STB_IMAGE_IMPLEMENTATION은 LobbyScreen.cpp에서 이미 정의됨
#include "stb_image.h"

bool GameOverScreen::isInGameOver = false;
int GameOverScreen::finalScore = 0;
int GameOverScreen::finalTime = 0;
GLuint GameOverScreen::backgroundTexture = 0;  // 배경 텍스처 초기화

// 버튼 크기
const float GameOverScreen::BUTTON_WIDTH = 400.0f;
const float GameOverScreen::BUTTON_HEIGHT = 80.0f;

// 버튼 위치는 동적으로 계산됨
const float GameOverScreen::RESTART_BTN_X = 0.0f;  // draw()에서 계산
const float GameOverScreen::RESTART_BTN_Y = 0.0f;
const float GameOverScreen::MENU_BTN_X = 0.0f;
const float GameOverScreen::MENU_BTN_Y = 0.0f;

void GameOverScreen::init(int score, int time)
{
    isInGameOver = true;
    finalScore = score;
    finalTime = time;
    
    // 게임 오버 배경 이미지 로드
    loadTexture("gameover.png");
    
    std::cout << "Game Over Screen initialized" << std::endl;
    std::cout << "Final Score: " << finalScore << std::endl;
    std::cout << "Final Time: " << finalTime << " seconds" << std::endl;
}

bool GameOverScreen::loadTexture(const char* filename)
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

    return true;
}

void GameOverScreen::draw()
{
    // 셰이더 프로그램 비활성화 (2D UI 그리기 전에 필수!)
    glUseProgram(0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 버튼 위치를 화면 중앙 기준으로 동적 계산
    float restartBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
    float restartBtnY = windowHeight / 2.0f - 50.0f;
    float menuBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
    float menuBtnY = windowHeight / 2.0f - 150.0f;

    // 2D 직교 투영 설정
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
    glLoadIdentity();

    // 배경 이미지 그리기 (약간 크게 표시하여 화면을 완전히 채움)
    if (backgroundTexture != 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);

        glColor3f(1.0f, 1.0f, 1.0f);
        
        // 이미지를 약간 더 크게 표시 (5% 오버스캔)
        float overscan = 0.05f;  // 5% 더 크게
        float extraWidth = windowWidth * overscan;
        float extraHeight = windowHeight * overscan;
     
   glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-extraWidth, -extraHeight);  // 좌하단
   glTexCoord2f(1.0f, 1.0f); glVertex2f((float)windowWidth + extraWidth, -extraHeight);  // 우하단
        glTexCoord2f(1.0f, 0.0f); glVertex2f((float)windowWidth + extraWidth, (float)windowHeight + extraHeight);  // 우상단
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-extraWidth, (float)windowHeight + extraHeight);  // 좌상단
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
    else
  {
  // 배경 이미지 로드 실패 시 어두운 회색 배경
   glDisable(GL_BLEND);
    glColor3f(0.1f, 0.1f, 0.1f);
      glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f((float)windowWidth, 0);
        glVertex2f((float)windowWidth, (float)windowHeight);
        glVertex2f(0, (float)windowHeight);
        glEnd();
    }

    // 블렌딩 활성화 (텍스트와 버튼 그리기)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // "GAME OVER" 텍스트
  glColor3f(1.0f, 0.0f, 0.0f);
    float titleX = windowWidth / 2.0f - 80.0f;
    float titleY = windowHeight / 2.0f + 150.0f;
    drawText(titleX, titleY, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);

    // 점수 및 시간 표시
    char scoreText[100];
    sprintf(scoreText, "Score: %d", finalScore);
    glColor3f(1.0f, 1.0f, 1.0f);
    float scoreX = windowWidth / 2.0f - 80.0f;
    float scoreY = windowHeight / 2.0f + 80.0f;
    drawText(scoreX, scoreY, scoreText, GLUT_BITMAP_HELVETICA_18);

    char timeText[100];
    sprintf(timeText, "Time: %d seconds", finalTime);
    float timeX = windowWidth / 2.0f - 100.0f;
    float timeY = windowHeight / 2.0f + 50.0f;
    drawText(timeX, timeY, timeText, GLUT_BITMAP_HELVETICA_18);

    // 버튼 그리기
    drawButton(restartBtnX, restartBtnY, BUTTON_WIDTH, BUTTON_HEIGHT, "Restart Game");
    drawButton(menuBtnX, menuBtnY, BUTTON_WIDTH, BUTTON_HEIGHT, "Main Menu");

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

void GameOverScreen::drawButton(float x, float y, float width, float height, const char* text)
{
    // 버튼 배경 (완전 불투명)
    glColor4f(0.8f, 0.2f, 0.2f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 버튼 테두리
    glColor3f(1.0f, 1.0f, 0.0f); // 노란색
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
    glEnd();

    // 버튼 텍스트
    glColor3f(1.0f, 1.0f, 1.0f);
    float textX = x + width / 2.0f - 70.0f;
    float textY = y + height / 2.0f - 10.0f;
    drawText(textX, textY, text, GLUT_BITMAP_HELVETICA_18);
}

bool GameOverScreen::isMouseInButton(int mouseX, int mouseY, float btnX, float btnY, float btnWidth, float btnHeight)
{
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    // OpenGL 좌표계로 변환 (Y축 반전)
    int glMouseY = windowHeight - mouseY;

    return (mouseX >= btnX && mouseX <= btnX + btnWidth &&
        glMouseY >= btnY && glMouseY <= btnY + btnHeight);
}

void GameOverScreen::drawText(float x, float y, const char* text, void* font)
{
  glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
 }
}

void GameOverScreen::handleMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
 {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
      int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        // 버튼 위치 재계산 (draw()와 동일하게)
      float restartBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
        float restartBtnY = windowHeight / 2.0f - 50.0f;
     float menuBtnX = (windowWidth - BUTTON_WIDTH) / 2.0f;
   float menuBtnY = windowHeight / 2.0f - 150.0f;

        // Restart Game 버튼 클릭
        if (isMouseInButton(x, y, restartBtnX, restartBtnY, BUTTON_WIDTH, BUTTON_HEIGHT))
  {
            std::cout << "Restart Game clicked!" << std::endl;
            isInGameOver = false;
            
          // 게임 재시작
            GameState::initGame();

            // 게임 음악 재생
            AudioManager::playBackgroundMusicSimple(L"game.wav");
      
            glutPostRedisplay();
        }
      // Main Menu 버튼 클릭
        else if (isMouseInButton(x, y, menuBtnX, menuBtnY, BUTTON_WIDTH, BUTTON_HEIGHT))
        {
   std::cout << "Main Menu clicked!" << std::endl;
isInGameOver = false;
     LobbyScreen::isInLobby = true;
            
// 로비 음악 재생
            AudioManager::playBackgroundMusicSimple(L"lobby.wav");

        glutPostRedisplay();
      }
    }
}

void GameOverScreen::cleanup()
{
    if (backgroundTexture != 0)
    {
        glDeleteTextures(1, &backgroundTexture);
        backgroundTexture = 0;
    }
    
    isInGameOver = false;
    finalScore = 0;
    finalTime = 0;
}
