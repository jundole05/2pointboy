#include "Block.h"

int Block::block1[3][3][3] = // S
{
    {{0,0,0},
    {0,0,0},
    {0,0,0}},

    {{0,0,0},
    {0,2,2},
    {2,2,0}},

    {{0,0,0},
    {0,0,0},
    {0,0,0}}
};

int Block::block2[3][3][3] = // L
{
    {{0,0,0},
    {0,0,0},
    {0,0,0}},

    {{0,1,0},
    {0,1,0},
    {0,1,1}},

    {{0,0,0},
    {0,0,0},
    {0,0,0}}
};

int Block::block3[3][3][3] = // I
{
    {{0,0,0},
    {0,0,0},
    {0,0,0}},

    {{0,3,0},
    {0,3,0},
    {0,3,0}},

    {{0,0,0},
    {0,0,0},
    {0,0,0}}
};

int Block::block4[3][3][3] = // T
{
    {{0,0,0},
    {0,0,0},
    {0,0,0}},

    {{0,0,0},
    {5,5,5},
    {0,5,0}},

    {{0,0,0},
    {0,0,0},
    {0,0,0}}
};

int Block::block5[3][3][3] = // O
{
    {{0,0,0},
    {0,0,0},
    {0,0,0}},

    {{0,0,0},
    {0,4,4},
    {0,4,4}},

    {{0,0,0},
    {0,0,0},
{0,0,0}}
};

void Block::initializeBlocks()
{
    // 이미 정적으로 초기화됨
}

void Block::copyBlock(int source[3][3][3], int dest[3][3][3])
{
    for (int i = 0; i < 3; ++i)
    {
for (int j = 0; j < 3; ++j)
  {
         for (int k = 0; k < 3; ++k)
            {
           dest[i][j][k] = source[i][j][k];
       }
        }
    }
}

void Block::rotateBlockX(int block[3][3][3])
{
    for (int x = 0; x < 3; ++x)
    {
        for (int i = 0; i < 2; ++i)
        {
            int temp00 = block[x][0][0];
     block[x][0][0] = block[x][1][0];
    block[x][1][0] = block[x][2][0];
   block[x][2][0] = block[x][2][1];
  block[x][2][1] = block[x][2][2];
            block[x][2][2] = block[x][1][2];
     block[x][1][2] = block[x][0][2];
            block[x][0][2] = block[x][0][1];
            block[x][0][1] = temp00;
     }
}
}

void Block::rotateBlockY(int block[3][3][3])
{
    for (int y = 0; y < 3; ++y)
    {
      for (int i = 0; i < 2; ++i)
        {
 int temp = block[0][y][0];
     block[0][y][0] = block[1][y][0];
            block[1][y][0] = block[2][y][0];
            block[2][y][0] = block[2][y][1];
            block[2][y][1] = block[2][y][2];
        block[2][y][2] = block[1][y][2];
     block[1][y][2] = block[0][y][2];
 block[0][y][2] = block[0][y][1];
            block[0][y][1] = temp;
     }
    }
}

void Block::rotateBlockZ(int block[3][3][3])
{
    for (int z = 0; z < 3; ++z)
    {
        for (int i = 0; i < 2; ++i)
        {
            int temp = block[0][0][z];
         block[0][0][z] = block[1][0][z];
  block[1][0][z] = block[2][0][z];
   block[2][0][z] = block[2][1][z];
  block[2][1][z] = block[2][2][z];
    block[2][2][z] = block[1][2][z];
            block[1][2][z] = block[0][2][z];
            block[0][2][z] = block[0][1][z];
            block[0][1][z] = temp;
   }
    }
}

// 블럭 가져오기 함수
int (*Block::getBlockByID(int blockID))[3][3]
{
    switch (blockID)
    {
        case 1: return block1;
        case 2: return block2;
        case 3: return block3;
        case 4: return block4;
        case 5: return block5;
        default: return block1;
    }
}
