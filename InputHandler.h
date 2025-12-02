#pragma once

class InputHandler {
public:
    static void Keyboard(unsigned char key, int x, int y);
    
    // 추가: 마우스 콜백 함수들
    static void Mouse(int button, int state, int x, int y);
    static void Motion(int x, int y);
private:
    static void handleRotation(unsigned char key);
    static void handleMovement(unsigned char key);
    static void handleView(unsigned char key);
    static void handleHardDrop();

    // 추가: 마우스 상태 변수
    static bool isDragging;
    static int lastMouseX;
    static int lastMouseY;
};
