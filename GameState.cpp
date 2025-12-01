#include "GameState.h"
#include "Block.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

// 정적 변수 초기화
GLint GameState::GameSpace[12][12][12] = { 0 };
GLint GameState::tempSpace[12][12][12] = { 0 };
GLint GameState::blockSpace[12][12][12] = { 0 };
GLint GameState::previewSpace[12][12][12] = { 0 };
int GameState::outSpace[12][12][12] = { 0 };
int GameState::out[12] = { 0 };

int GameState::myBlockID = 0;
int GameState::myBlock[3][3][3] = { 0 };
int GameState::myRotX = 0;
int GameState::myRotY = 0;
int GameState::myRotZ = 0;
int GameState::myX = 5;
int GameState::myY = 5;
int GameState::myZ = 9;

int GameState::quit = 0;
int GameState::bye = 0;
int GameState::cheat = -1;
int GameState::frameCount = 0;
int GameState::frames_needed = 33;
int GameState::fCount = 0;
int GameState::fneed = 2;
int GameState::current_rot = 0;
int GameState::lookdown = 0;

void GameState::initGame()
{
    // 게임 공간 지우기
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
   for (int k = 0; k < 12; ++k)
    {
                GameSpace[i][j][k] = 0;
        tempSpace[i][j][k] = 0;
     blockSpace[i][j][k] = 0;
      previewSpace[i][j][k] = 0;
       outSpace[i][j][k] = 0;
            }
     }
        out[i] = 0;
    }

    srand((unsigned int)time(NULL));
    int bound = rand() % 2;
    for (int z = 2; z >= 0; --z)
    {
        for (int tx = -bound; tx < bound; ++tx)
{
          int x = tx;
            if (x < 0)
            {
      x += 12;
            }
            for (int ty = 0; ty < 12; ++ty)
            {
    tempSpace[x][ty][z] = z + 1;
    tempSpace[ty][x][z] = z + 1;
       }
        }
 bound += rand() % 2 + 1;
    }
    
  quit = 0;
    bye = 0;
    myBlockID = rand() % 5 + 1;
    myRotX = 0;
    myRotY = 0;
 myRotZ = 0;
    myX = 5;
    myY = 5;
    myZ = 9;
    cheat = -1;
}

void GameState::spawnNewBlock()
{
    myBlockID = (rand() % 5) + 1;
    if (cheat > 0)
    {
        myBlockID = 3;
  }
    myRotX = 0;
    myRotY = 0;
    myRotZ = 0;
    myZ = 9;
    if (myX > 9)
    {
        myX = 9;
    }
    if (myX < 0)
    {
        myX = 0;
    }
    if (myY > 9)
    {
        myY = 9;
    }
    if (myY < 0)
    {
  myY = 0;
    }
}

void GameState::updateGame()
{
    // 블록 타입에 따라 데이터 복사
    switch (myBlockID)
    {
    case 1:
        Block::copyBlock(Block::block1, myBlock);
   break;
    case 2:
        Block::copyBlock(Block::block2, myBlock);
        break;
    case 3:
        Block::copyBlock(Block::block3, myBlock);
        break;
    case 4:
        Block::copyBlock(Block::block4, myBlock);
        break;
    case 5:
        Block::copyBlock(Block::block5, myBlock);
        break;
    }

    // X축 회전
    for (int n = 0; n < myRotX; ++n)
    {
   Block::rotateBlockX(myBlock);
    }

    // Y축 회전
    for (int n = 0; n < myRotY; ++n)
    {
        Block::rotateBlockY(myBlock);
    }

    // Z축 회전
    for (int n = 0; n < myRotZ; ++n)
    {
     Block::rotateBlockZ(myBlock);
    }

 // 임시공간 비우기
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            for (int k = 0; k < 12; ++k)
   {
      blockSpace[i][j][k] = 0;
           previewSpace[i][j][k] = 0;
          }
        }
    }

    // 현재 떨구고 있는 블록만 임시공간에 대입
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
 for (int k = 0; k < 3; ++k)
            {
       if ((myX + i <= 11 && myY + j <= 11 && myZ + k <= 11) && 
 (myX + i >= 0 && myY + j >= 0 && myZ + k >= 0))
     blockSpace[myX + i][myY + j][myZ + k] = myBlock[i][j][k];
  }
        }
    }

    // 임시공간에 처리 완료 후 게임공간에 대입
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            for (int k = 0; k < 12; ++k)
          {
   GameSpace[i][j][k] = tempSpace[i][j][k] + blockSpace[i][j][k];
            }
    }
    }
    
    preview();

    if (cheat < 0)
    {
        frameCount += 1;
        if (frameCount == frames_needed)
        {
            if (isEnded() == 0)
            {
       myZ -= 1;
     }
  else
         {
        for (int i = 0; i < 3; ++i)
      {
         for (int j = 0; j < 3; ++j)
   {
          for (int k = 0; k < 3; ++k)
           {
       tempSpace[myX + i][myY + j][myZ + k] += myBlock[i][j][k];
             }
          }
        }
       spawnNewBlock();
    if (isGameOver() == 1)
         {
  quit = 1;
       }
            }
       frameCount = 0;
        }
    }
}

void GameState::killBlock()
{
    int target = -1;
    int t = 1;
    for (int z = 0; z < 12; ++z)
    {
        t = 1;
      for (int x = 0; x < 12; ++x)
    {
       for (int y = 0; y < 12; ++y)
       {
          if (tempSpace[x][y][z] == 0)
                {
            t = 0;
          }
            }
        }
        if (t)
        {
        target = z;
  break;
}
  }
    
    if (target != -1)
    {
        out[target] = 1;
        for (int x = 0; x < 12; ++x)
   {
  for (int y = 0; y < 12; ++y)
    {
       outSpace[x][target][y] = tempSpace[x][y][target];
            printf("%d ", outSpace[x][y][target]);
 }
         printf("\n");
        }

        for (int z = target; z < 11; ++z)
      {
   for (int x = 0; x < 12; ++x)
        {
        for (int y = 0; y < 12; ++y)
          {
 int temp;
     temp = tempSpace[x][y][z];
              tempSpace[x][y][z] = tempSpace[x][y][z + 1];
       tempSpace[x][y][z + 1] = temp;
      }
         }
        }
        
        for (int x = 0; x < 12; ++x)
        {
    for (int y = 0; y < 12; ++y)
            {
    tempSpace[x][y][11] = 0;
    }
     }
        
        if (frames_needed > 15)
      frames_needed -= 1;
  }
}

void GameState::preview()
{
    for (int z = 0; z < 12; ++z)
    {
     for (int x = 0; x < 12; ++x)
        {
          for (int y = 0; y < 12; ++y)
            {
      if (blockSpace[x][y][z] > 0)
       {
       int exists = 0;
        for (int tz = z; tz >= 0; --tz)
    {
     if (tempSpace[x][y][tz] > 0)
         {
                   previewSpace[x][y][tz] = 1;
       exists = 1;
       break;
           }
          }
if (exists == 0)
        {
 previewSpace[x][y][0] = -1;
    }
          }
        }
        }
    }
}

int GameState::isEnded()
{
    int ended = 0;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
     for (int z = 0; z < 3; ++z)
            {
                if (myBlock[x][y][z] > 0)
    {
            if (myZ + z > 0)
        {
   if (tempSpace[myX + x][myY + y][myZ + z - 1] > 0)
          {
           ended = 1;
      }
 }
            else if (myZ + z == 0)
         {
       ended = 1;
   }
    }
        }
        }
    }
    return ended;
}

int GameState::collides(int direction)
{
    int collide = 0;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            for (int z = 0; z < 3; ++z)
        {
          if (direction == 1) // up
        {
        if (myBlock[x][y][z] > 0)
   {
  if (myY + y > 0)
     {
        if (tempSpace[myX + x][myY - 1 + y][myZ + z] > 0)
   {
   collide = 1;
      }
         }
      else
    {
       collide = 1;
        }
  }
  }
         else if (direction == 2) // down
     {
          if (myBlock[x][y][z] > 0)
      {
      if (myY + y < 11)
      {
      if (tempSpace[myX + x][myY + 1 + y][myZ + z] > 0)
              {
                     collide = 1;
                }
       }
       else
       {
    collide = 1;
        }
               }
    }
                else if (direction == 3) // left
     {
           if (myBlock[x][y][z] > 0)
        {
      if (myX + x > 0)
             {
             if (tempSpace[myX + x - 1][myY + y][myZ + z] > 0)
          {
         collide = 1;
       }
         }
              else
   {
   collide = 1;
              }
    }
 }
     else if (direction == 4) // right
      {
  if (myBlock[x][y][z] > 0)
    {
             if (myX + x < 11)
     {
  if (tempSpace[myX + x + 1][myY + y][myZ + z] > 0)
 {
     collide = 1;
     }
     }
                 else
        {
         collide = 1;
         }
     }
     }
        }
        }
    }
    return collide;
}

int GameState::isGameOver()
{
    int over = 0;
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            for (int z = 0; z < 3; ++z)
            {
    if (myBlock[x][y][z] > 0)
     {
        if (tempSpace[myX + x][myY + y][myZ + z] > 0)
     {
over = 1;
     }
   }
    }
        }
    }
    return over;
}

void GameState::goout()
{
    for (int z = 0; z < 12; ++z)
 {
  if (out[z] > 0)
      {
            if (out[z] > 13)
     {
            out[z] = 0;
 for (int x = 0; x < 12; ++x)
  {
             for (int y = 0; y < 12; ++y)
                    {
       outSpace[x][y][z] = 0;
         }
        }
            }
            else
            {
                out[z] += 1;
}
        }
    }
}
