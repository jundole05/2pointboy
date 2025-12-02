#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <stdio.h>
#include "filein.h"
#include "Block.h"
#include "GameState.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "ShaderManager.h"

using namespace std;

GLvoid GameLoop(int value);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("project");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
std::cerr << "GLEW 초기화 불가능" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
  std::cout << "GLEW가 초기화됨\n";
  
    printf("Key        Function (액션)               비고\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("W / w      현재 블록을 위쪽(Y축 -) 방향으로 이동          current_rot에 따라 달라짐\n");
    printf("S / s      현재 블록을 아래쪽(Y축 +) 방향으로 이동\n");
    printf("A / a      현재 블록을 왼쪽(X축 -) 방향으로 이동\n");
    printf("D / d      현재 블록을 오른쪽(X축 +) 방향으로 이동\n");
    printf("J / j      현재 블록을 X축 기준 90도 회전 (myRotX 증가)\n");
    printf("K / k      현재 블록을 Y축 기준 90도 회전 (myRotY 증가)\n");
    printf("L / l      현재 블록을 Z축 기준 90도 회전 (myRotZ 증가)\n");
    printf("Space(32)  하드 드롭 - 바닥까지 즉시 떨어뜨리고 다음 블록 생성   가장 빠르게 착지\n");
    printf("O / o      전체 뷰를 Y축 기준 왼쪽으로 90도 회전       카메라/월드 회전\n");
    printf("P / p      1) O로 돌린 횟수만큼 되돌리기\n");
    printf("        2) 위에서 내려다보는 뷰(lookdown) 토글           두 번 누르면 위/아래 전환\n");
    printf("Esc(27)    게임 오버 처리 → 게임 재시작             quit = 1\n");
    printf("0       치트 토글 (cheat -1 ↔ 1)   I블록 고정 (디버그용)\n");

    glutDisplayFunc(Renderer::drawScene);
    glutReshapeFunc(Renderer::Reshape);
    glutKeyboardFunc(InputHandler::Keyboard);
    glutTimerFunc(30, GameLoop, 1);
    
    ShaderManager::vertexShaderSource = filetobuf("vertex1.glsl");
    ShaderManager::fragmentShaderSource = filetobuf("fragment1.glsl");

    ShaderManager::make_vertexShaders();
 ShaderManager::make_fragmentShaders();
    Renderer::shaderID = ShaderManager::make_shaderProgram();
    
    Block::initializeBlocks();
    Renderer::InitBuffer();
    GameState::initGame();
    
    glutMainLoop();
}

GLvoid GameLoop(int value)
{
   GameState::updateGame();
   GameState::killBlock();
    
   GameState::fCount += 1;
   if (GameState::fCount == GameState::fneed)
     {
        GameState::goout();
        GameState::fCount = 0;
     }
   // 시간 계산 (30프레임당 1초)
  GameState::timeFrameCount++;
  if (GameState::timeFrameCount >= 30)
  {
      GameState::gameTime++;
      GameState::timeFrameCount = 0;
  }

    glutPostRedisplay();
    
    if (GameState::quit == 1)
    {
        GameState::initGame();
  }
    if (GameState::bye == 1)
    {
        PostQuitMessage(0);
    }
    
    glutTimerFunc(30, GameLoop, 1);
}