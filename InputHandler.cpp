#include "InputHandler.h"
#include "GameState.h"
#include "Renderer.h"
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LobbyScreen.h"

// 정적 변수 초기화 추가
bool InputHandler::isDragging = false;
int InputHandler::lastMouseX = 0;
int InputHandler::lastMouseY = 0;

// 마우스 버튼 콜백
void InputHandler::Mouse(int button, int state, int x, int y)
{
    // 로비 화면에서는 로비 클릭 처리
    if (LobbyScreen::isInLobby)
    {
        LobbyScreen::handleMouseClick(button, state, x, y);
        return;
    }

    // 게임 화면에서는 카메라 회전 처리
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP)
        {
            isDragging = false;
        }
    }
}

// 마우스 드래그 콜백
void InputHandler::Motion(int x, int y)
{
    if (isDragging)
    {
        // 마우스 이동량 계산
        int deltaX = x - lastMouseX;
        int deltaY = y - lastMouseY;

        // 카메라 회전 각도 업데이트 (감도 조절)
        float sensitivity = 0.5f;
        Renderer::cameraYaw -= deltaX * sensitivity;
        Renderer::cameraPitch += deltaY * sensitivity;

        // Pitch 각도 제한 (위아래 회전 제한)
        if (Renderer::cameraPitch > 89.0f)
            Renderer::cameraPitch = 89.0f;
        if (Renderer::cameraPitch < -89.0f)
            Renderer::cameraPitch = -89.0f;

        // 카메라 업데이트
        Renderer::updateCamera();

        // 마지막 마우스 위치 업데이트
        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }

}

void InputHandler::Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'O':
    case 'o':
    case 'P':
    case 'p':
        handleView(key);
     break;
    case 'j':
    case 'J':
    case 'k':
    case 'K':
    case 'l':
    case 'L':
        handleRotation(key);
        break;
    case 'w':
  case 'W':
    case 's':
  case 'S':
    case 'a':
    case 'A':
    case 'd':
    case 'D':
        handleMovement(key);
 break;
    case 32: // Space
        handleHardDrop();
        break;
    case 27: // Esc
        GameState::quit = 1;
        break;
    case '0':
      GameState::cheat *= -1;
        break;
    }
    glutPostRedisplay();
}

void InputHandler::handleView(unsigned char key)
{
    if (key == 'O' || key == 'o')
    {
        if (GameState::lookdown == 0)
        {
            Renderer::rot = glm::mat4(1.0f);
 Renderer::rot = glm::rotate(Renderer::rot, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GameState::current_rot = (GameState::current_rot + 1) % 4;
      Renderer::model = Renderer::model * Renderer::rot;
        }
}
  else if (key == 'P' || key == 'p')
    {
        int temp = GameState::current_rot;
 for (int i = 0; i < temp; ++i)
        {
       Renderer::rot = glm::mat4(1.0f);
 Renderer::rot = glm::rotate(Renderer::rot, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GameState::current_rot -= 1;
Renderer::model = Renderer::model * Renderer::rot;
        }
 
        if (GameState::lookdown == 0)
 {
            Renderer::rot = glm::mat4(1.0f);
            Renderer::rot = glm::rotate(Renderer::rot, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            Renderer::model = Renderer::model * Renderer::rot;
 GameState::lookdown = 1;
        }
        else
   {
         Renderer::rot = glm::mat4(1.0f);
   Renderer::rot = glm::rotate(Renderer::rot, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      Renderer::model = Renderer::model * Renderer::rot;
          GameState::lookdown = 0;
        }
    }
}

void InputHandler::handleRotation(unsigned char key)
{
    if (key == 'j' || key == 'J')
    {
  if (GameState::myY < 0) GameState::myY = 0;
        if (GameState::myZ < 0) GameState::myZ = 0;
  if (GameState::myY > 9) GameState::myY = 9;
      if (GameState::myZ > 9) GameState::myZ = 9;
        GameState::myRotX = (GameState::myRotX + 1) % 4;
    }
    else if (key == 'k' || key == 'K')
    {
        if (GameState::myX < 0) GameState::myX = 0;
        if (GameState::myZ < 0) GameState::myZ = 0;
        if (GameState::myX > 9) GameState::myX = 9;
   if (GameState::myZ > 9) GameState::myZ = 9;
        GameState::myRotY = (GameState::myRotY + 1) % 4;
    }
    else if (key == 'l' || key == 'L')
    {
        if (GameState::myY < 0) GameState::myY = 0;
        if (GameState::myX < 0) GameState::myX = 0;
      if (GameState::myY > 9) GameState::myY = 9;
        if (GameState::myX > 9) GameState::myX = 9;
        GameState::myRotZ = (GameState::myRotZ + 1) % 4;
    }
}

void InputHandler::handleMovement(unsigned char key)
{
    int dir = 0;
    
    if (key == 'w' || key == 'W')
    {
     if (GameState::current_rot == 0)
        {
       dir = 1;
    if (GameState::collides(dir) == 0) GameState::myY -= 1;
      }
        else if (GameState::current_rot == 1)
{
          dir = 3;
     if (GameState::collides(dir) == 0) GameState::myX -= 1;
 }
        else if (GameState::current_rot == 2)
        {
         dir = 2;
        if (GameState::collides(dir) == 0) GameState::myY += 1;
        }
        else if (GameState::current_rot == 3)
        {
            dir = 4;
            if (GameState::collides(dir) == 0) GameState::myX += 1;
        }
    }
    else if (key == 's' || key == 'S')
    {
        if (GameState::current_rot == 0)
        {
       dir = 2;
         if (GameState::collides(dir) == 0) GameState::myY += 1;
        }
        else if (GameState::current_rot == 1)
        {
            dir = 4;
     if (GameState::collides(dir) == 0) GameState::myX += 1;
  }
        else if (GameState::current_rot == 2)
        {
            dir = 1;
     if (GameState::collides(dir) == 0) GameState::myY -= 1;
        }
    else if (GameState::current_rot == 3)
     {
       dir = 3;
            if (GameState::collides(dir) == 0) GameState::myX -= 1;
        }
    }
    else if (key == 'a' || key == 'A')
    {
 if (GameState::current_rot == 0)
        {
            dir = 3;
   if (GameState::collides(dir) == 0) GameState::myX -= 1;
        }
        else if (GameState::current_rot == 1)
        {
     dir = 2;
            if (GameState::collides(dir) == 0) GameState::myY += 1;
}
        else if (GameState::current_rot == 2)
        {
   dir = 4;
    if (GameState::collides(dir) == 0) GameState::myX += 1;
   }
        else if (GameState::current_rot == 3)
        {
    dir = 1;
    if (GameState::collides(dir) == 0) GameState::myY -= 1;
        }
    }
    else if (key == 'd' || key == 'D')
    {
if (GameState::current_rot == 0)
      {
            dir = 4;
        if (GameState::collides(dir) == 0) GameState::myX += 1;
   }
        else if (GameState::current_rot == 1)
        {
  dir = 1;
            if (GameState::collides(dir) == 0) GameState::myY -= 1;
        }
        else if (GameState::current_rot == 2)
        {
    dir = 3;
  if (GameState::collides(dir) == 0) GameState::myX -= 1;
        }
        else if (GameState::current_rot == 3)
        {
        dir = 2;
        if (GameState::collides(dir) == 0) GameState::myY += 1;
        }
    }
}

void InputHandler::handleHardDrop()
{
    while (GameState::isEnded() == 0)
    {
     GameState::myZ -= 1;
    }
    
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
    for (int k = 0; k < 3; ++k)
     {
          GameState::tempSpace[GameState::myX + i][GameState::myY + j][GameState::myZ + k] += 
       GameState::myBlock[i][j][k];
            }
        }
    }
 
    GameState::spawnNewBlock();
    
    if (GameState::isGameOver() == 1)
    {
  GameState::quit = 1;
    }
}
