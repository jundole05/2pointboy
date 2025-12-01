#pragma once

class InputHandler {
public:
    static void Keyboard(unsigned char key, int x, int y);
    
private:
    static void handleRotation(unsigned char key);
    static void handleMovement(unsigned char key);
    static void handleView(unsigned char key);
 static void handleHardDrop();
};
