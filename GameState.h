#pragma once
#include <gl/glew.h>

class GameState {
public:
    static const int GRID_SIZE = 12;
    
    // 게임 공간
    static GLint GameSpace[12][12][12];
    static GLint tempSpace[12][12][12];
    static GLint blockSpace[12][12][12];
    static GLint previewSpace[12][12][12];
    static int outSpace[12][12][12];
    static int out[12];

 // 현재 블록 상태
    static int myBlockID;
    static int myBlock[3][3][3];
    static int myRotX, myRotY, myRotZ;
    static int myX, myY, myZ;

 // 다음 블록 상태
    static int nextBlockID;
    static int nextBlock[3][3][3];
    
  // 게임 상태 변수
    static int quit, bye;
    static int cheat;
    static int frameCount;
    static int frames_needed;
    static int fCount;
    static int fneed;
    static int current_rot;
    static int lookdown;

    // 시간과 점수 변수
    static int gameTime; // 게임 플레이 시간 (초)
    static int score;    // 점수
    static int timeFrameCount;

    static void initGame();
    static void spawnNewBlock();
    static void updateGame();
    static void killBlock();
    static void preview();
    static void goout();
 
    static int isEnded();
    static int collides(int dir);
    static int isGameOver();
    
    
    static void resetRotation();
};
