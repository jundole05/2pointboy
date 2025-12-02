#pragma once
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>

class Renderer {
public:
    // VAO, VBO
    static GLuint VAO[12][12][12];
    static GLuint VBO_position[12][12][12];
    static GLuint VBO_color[12][12][12];
    static GLuint VAO_bg, VBO_bg, VBO_bgColor;
    static GLuint VAO_preview, VBO_top, VBO_bottom, VBO_pvColor;
    static GLuint VAO_out[12][12][12];
    static GLuint VBO_out[12][12][12];
    static GLuint VBO_outColor[12][12][12];
    
    // Shader
    static GLuint shaderID;
    static GLuint MatrixID;
    
    // 정점 데이터
    static GLfloat background[24][3];
    static GLfloat bgColor[24][3];
    static GLfloat squarePosition[24][3];
    static GLfloat square[24][3];
    static GLfloat squareColor[24][3];
    static GLfloat originColor[24][3];
    static GLfloat outPosition[24][3];
    static GLfloat outColor[24][3];
    static GLfloat top[4][3];
    static GLfloat bottom[4][3];
    static GLfloat pvColor[4][3];
    static GLfloat pvTarget[4][3];
    
    // 변환 행렬
    static glm::mat4 proj;
    static glm::mat4 camera;
    static glm::mat4 model;
    static glm::mat4 trans;
    static glm::mat4 rot;
    


    // 추가뷰포트용 변수
    static glm::mat4 topDownCamera;
    static glm::mat4 topDownProj;
    static glm::mat4 topDownTrans;
    static void drawTopDownViewport(int windowWidth, int windowHeight);

    // 추가: lookdown 뷰포트용
    static glm::mat4 lookdownCamera;
    static glm::mat4 lookdownProj;
    static glm::mat4 lookdownTrans;
    static glm::mat4 lookdownFixedCamera;
    static void drawLookdownViewport(int windowWidth, int windowHeight);
    
    static void InitBuffer();
    static void drawScene();
    static void Reshape(int w, int h);

    // 텍스트 렌더링 함수
    static void drawText(float x, float y, const char* text);
    static void drawGameInfo();

    // 카메라 회전 관련
    static float cameraYaw;    // 좌우 회전 (Y축)
    static float cameraPitch;  // 상하 회전 (X축)
    static float cameraDistance; // 카메라 거리
    static void updateCamera();
    
private:
    static void drawBackground();
    static void drawGameSpace();
    static void drawPreview();
    static void drawOutBlocks();
};
