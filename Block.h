#pragma once

class Block {
public:
    static const int BLOCK_SIZE = 3;
    
// 블록 타입 정의
    enum BlockType {
        BLOCK_S = 1,
        BLOCK_L = 2,
        BLOCK_I = 3,
        BLOCK_T = 4,
        BLOCK_O = 5
    };

    // 블록 데이터
    static int block1[3][3][3]; // S
    static int block2[3][3][3]; // L
    static int block3[3][3][3]; // I
    static int block4[3][3][3]; // T
    static int block5[3][3][3]; // O

    static void initializeBlocks();
    static void copyBlock(int source[3][3][3], int dest[3][3][3]);
    static void rotateBlockX(int block[3][3][3]);
    static void rotateBlockY(int block[3][3][3]);
    static void rotateBlockZ(int block[3][3][3]);

    // 추가: 블럭 ID로 블럭 데이터 가져오기
    static int (*getBlockByID(int blockID))[3][3];

};
