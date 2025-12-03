#include "GameOverScreen.h"
#include "GameState.h"
#include "LobbyScreen.h"
#include "AudioManager.h"
#include <iostream>
#include <cstdio>

bool GameOverScreen::isInGameOver = false;
int GameOverScreen::finalScore = 0;
int GameOverScreen::finalTime = 0;

// 버튼 위치 (화면 중앙)
const float GameOverScreen::RESTART_BTN_X = 400.0f;
const float GameOverScreen::RESTART_BTN_Y = 350.0f;
const float GameOverScreen::MENU_BTN_X = 400.0f;
const float GameOverScreen::MENU_BTN_Y = 250.0f;
const float GameOverScreen::BUTTON_WIDTH = 400.0f;
const float GameOverScreen::BUTTON_HEIGHT = 80.0f;

void GameOverScreen::init(int score, int time)
{
    isInGameOver = true;
    finalScore = score;
    finalTime = time;
    
    std::cout << "Game Over Screen initialized" << std::endl;
    std::cout << "Final Score: " << finalScore << std::endl;
    std::cout << "Final Time: " << finalTime << " seconds" << std::endl;
}

void GameOverScreen::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 2D 직교 투영 설정
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 반투명 검은 배경
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();
    glDisable(GL_BLEND);

    // "GAME OVER" 텍스트
    glColor3f(1.0f, 0.0f, 0.0f);
    float titleX = windowWidth / 2 - 120;
    float titleY = windowHeight / 2 + 150;
    drawText(titleX, titleY, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);

    // 점수 및 시간 표시
    char scoreText[100];
    sprintf(scoreText, "Score: %d", finalScore);
    glColor3f(1.0f, 1.0f, 1.0f);
    float scoreX = windowWidth / 2 - 80;
    float scoreY = windowHeight / 2 + 80;
    drawText(scoreX, scoreY, scoreText, GLUT_BITMAP_HELVETICA_18);

    char timeText[100];
    sprintf(timeText, "Time: %d seconds", finalTime);
float timeX = windowWidth / 2 - 100;
    float timeY = windowHeight / 2 + 50;
    drawText(timeX, timeY, timeText, GLUT_BITMAP_HELVETICA_18);

    // 버튼 그리기
    drawButton(RESTART_BTN_X, RESTART_BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Restart Game");
    drawButton(MENU_BTN_X, MENU_BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Main Menu");

// 원래 상태로 복원
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

void GameOverScreen::drawButton(float x, float y, float width, float height, const char* text)
{
    // 버튼 배경
    glColor4f(0.8f, 0.2f, 0.2f, 0.8f); // 빨간색 반투명
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 버튼 테두리
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // 버튼 텍스트
    glColor3f(1.0f, 1.0f, 1.0f);
    float textX = x + width / 2 - 70; // 텍스트 중앙 정렬 (대략)
    float textY = y + height / 2 - 10;
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
        // Restart Game 버튼 클릭
        if (isMouseInButton(x, y, RESTART_BTN_X, RESTART_BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT))
        {
  std::cout << "Restart Game clicked!" << std::endl;
   isInGameOver = false;
    
            // 게임 재시작
     GameState::initGame();
 
  // 게임 음악 재생
 AudioManager::playBackgroundMusicSimple(L"C:\\3dp\\2pointboy\\game.wav");
 
      glutPostRedisplay();
        }
        // Main Menu 버튼 클릭
        else if (isMouseInButton(x, y, MENU_BTN_X, MENU_BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT))
     {
  std::cout << "Main Menu clicked!" << std::endl;
 isInGameOver = false;
            LobbyScreen::isInLobby = true;
            
            // 로비 음악 재생
       AudioManager::playBackgroundMusicSimple(L"C:\\3dp\\2pointboy\\lobby.wav");
          
        glutPostRedisplay();
        }
    }
}

void GameOverScreen::cleanup()
{
isInGameOver = false;
    finalScore = 0;
    finalTime = 0;
}
