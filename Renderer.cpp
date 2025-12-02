#include "Renderer.h"
#include "GameState.h"
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 정적 변수 초기화
GLuint Renderer::VAO[12][12][12];
GLuint Renderer::VBO_position[12][12][12];
GLuint Renderer::VBO_color[12][12][12];
GLuint Renderer::VAO_bg = 0;
GLuint Renderer::VBO_bg = 0;
GLuint Renderer::VBO_bgColor = 0;
GLuint Renderer::VAO_preview = 0;
GLuint Renderer::VBO_top = 0;
GLuint Renderer::VBO_bottom = 0;
GLuint Renderer::VBO_pvColor = 0;
GLuint Renderer::VAO_out[12][12][12];
GLuint Renderer::VBO_out[12][12][12];
GLuint Renderer::VBO_outColor[12][12][12];

GLuint Renderer::shaderID = 0;
GLuint Renderer::MatrixID = 0;

GLfloat Renderer::background[24][3] =
{
    {-6,-6,-6},
    {6,-6,-6},
    {6,6,-6},
    {-6,6,-6},

    {-6,-6,-6},
    {6,-6,-6},
    {6,-6,6},
    {-6,-6,6},

    {-6,-6,-6},
    {-6,6,-6},
    {-6,6,6},
  {-6,-6,6},

    {-6,-6,6},
    {6,-6,6},
    {6,6,6},
    {-6,6,6},

    {6,-6,6},
    {6,-6,-6},
    {6,6,-6},
    {6,6,6},

    {-6,6,-6},
    {6,6,-6},
    {6,6,6},
    {-6,6,6}
};

GLfloat Renderer::bgColor[24][3] =
{
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1},
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1},
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1},
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1},
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1},
    {1,1,1}, {1,1,1}, {1,1,1}, {1,1,1}
};

GLfloat Renderer::squarePosition[24][3] =
{
    {0.5,0.5,0.5}, {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {0.5,0.5,-0.5},
    {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5},
    {0.5,0.5,0.5}, {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,0.5,0.5},
    {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,0.5,-0.5},
    {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,-0.5,0.5},
    {0.5,0.5,0.5}, {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,-0.5,0.5}
};

GLfloat Renderer::square[24][3] =
{
    {0.5,0.5,0.5}, {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {0.5,0.5,-0.5},
    {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5},
    {0.5,0.5,0.5}, {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,0.5,0.5},
    {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,0.5,-0.5},
    {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,-0.5,0.5},
    {0.5,0.5,0.5}, {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,-0.5,0.5}
};

GLfloat Renderer::squareColor[24][3] = { 0 };
GLfloat Renderer::originColor[24][3] = { 0 };

GLfloat Renderer::outPosition[24][3] =
{
    {0.5,0.5,0.5}, {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {0.5,0.5,-0.5},
    {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,-0.5,-0.5}, {0.5,-0.5,-0.5},
    {0.5,0.5,0.5}, {0.5,-0.5,0.5}, {-0.5,-0.5,0.5}, {-0.5,0.5,0.5},
    {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,0.5,-0.5},
    {-0.5,0.5,0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,-0.5}, {-0.5,-0.5,0.5},
    {0.5,0.5,0.5}, {0.5,0.5,-0.5}, {0.5,-0.5,-0.5}, {0.5,-0.5,0.5}
};

GLfloat Renderer::outColor[24][3] = { 0 };

GLfloat Renderer::top[4][3] =
{
    {0.5,0.55,0.5},
    {-0.5,0.55,0.5},
    {-0.5,0.55,-0.5},
    {0.5,0.55,-0.5}
};

GLfloat Renderer::bottom[4][3] =
{
    {0.5,-0.5,0.5},
    {-0.5,-0.5,0.5},
    {-0.5,-0.5,-0.5},
    {0.5,-0.5,-0.5}
};

GLfloat Renderer::pvColor[4][3] =
{
    {1,1,1},
    {1,1,1},
  {1,1,1},
    {1,1,1}
};

GLfloat Renderer::pvTarget[4][3];

glm::mat4 Renderer::proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 Renderer::camera = glm::lookAt(glm::vec3(12, 12, 24), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
glm::mat4 Renderer::model = glm::mat4(1.0f);
glm::mat4 Renderer::trans;
glm::mat4 Renderer::rot = glm::mat4(1.0f);

// 뷰포트용 추가
glm::mat4 Renderer::topDownCamera = glm::lookAt(
    glm::vec3(0, 20, 0), // 위에서 아래로 보는 위치
    glm::vec3(0, 0, 0), // 중심점
    glm::vec3(0, 0, -1) // Up벡터
);
glm::mat4 Renderer::topDownProj = glm::ortho(-8.0f, 8.0f, -8.0f, 8.0f, 0.1f, 100.0f);

glm::mat4 Renderer::topDownTrans;

void Renderer::InitBuffer()
{
    glGenVertexArrays(1, &VAO_preview);
    glGenBuffers(1, &VBO_top);
    glGenBuffers(1, &VBO_bottom);
    glGenBuffers(1, &VBO_pvColor);

    glBindVertexArray(VAO_preview);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_top);
    glBufferData(GL_ARRAY_BUFFER, sizeof(top), top, GL_STATIC_DRAW);

    GLint pAttribute3 = glGetAttribLocation(shaderID, "vPos");
    glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(pAttribute3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_bottom);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bottom), bottom, GL_STATIC_DRAW);

    GLint pAttribute4 = glGetAttribLocation(shaderID, "vPos");
    glVertexAttribPointer(pAttribute4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(pAttribute4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_pvColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pvColor), pvColor, GL_STATIC_DRAW);

    GLint cAttribute3 = glGetAttribLocation(shaderID, "vColor");
    glVertexAttribPointer(cAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(cAttribute3);

  glGenVertexArrays(1, &VAO_bg);
    glGenBuffers(1, &VBO_bg);
    glGenBuffers(1, &VBO_bgColor);

    glBindVertexArray(VAO_bg);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
    glBufferData(GL_ARRAY_BUFFER, sizeof(background), background, GL_STATIC_DRAW);

    GLint pAttribute2 = glGetAttribLocation(shaderID, "vPos");
    glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
 glEnableVertexAttribArray(pAttribute2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_bgColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgColor), bgColor, GL_STATIC_DRAW);

    GLint cAttribute2 = glGetAttribLocation(shaderID, "vColor");
    glVertexAttribPointer(cAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(cAttribute2);

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
   {
    for (int k = 0; k < 12; ++k)
            {
     glGenVertexArrays(1, &VAO[i][j][k]);
           glGenBuffers(1, &VBO_position[i][j][k]);
  glGenBuffers(1, &VBO_color[i][j][k]);

         glBindVertexArray(VAO[i][j][k]);

           glBindBuffer(GL_ARRAY_BUFFER, VBO_position[i][j][k]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(squarePosition), squarePosition, GL_STATIC_DRAW);

                GLint pAttribute1 = glGetAttribLocation(shaderID, "vPos");
     glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
     glEnableVertexAttribArray(pAttribute1);

         glBindBuffer(GL_ARRAY_BUFFER, VBO_color[i][j][k]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(squareColor), squareColor, GL_STATIC_DRAW);

           GLint cAttribute1 = glGetAttribLocation(shaderID, "vColor");
        glVertexAttribPointer(cAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
   glEnableVertexAttribArray(cAttribute1);

                glGenVertexArrays(1, &VAO_out[i][j][k]);
      glGenBuffers(1, &VBO_out[i][j][k]);
     glGenBuffers(1, &VBO_outColor[i][j][k]);

     glBindVertexArray(VAO_out[i][j][k]);

   glBindBuffer(GL_ARRAY_BUFFER, VBO_out[i][j][k]);
     glBufferData(GL_ARRAY_BUFFER, sizeof(outPosition), outPosition, GL_STATIC_DRAW);

        GLint pAttribute2 = glGetAttribLocation(shaderID, "vPos");
    glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
      glEnableVertexAttribArray(pAttribute2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_outColor[i][j][k]);
           glBufferData(GL_ARRAY_BUFFER, sizeof(outColor), outColor, GL_STATIC_DRAW);

     GLint cAttribute2 = glGetAttribLocation(shaderID, "vColor");
                glVertexAttribPointer(cAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
           glEnableVertexAttribArray(cAttribute2);
    }
        }
    }
}

void Renderer::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(shaderID);

    //기본뷰포트
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, windowWidth, windowHeight);

    trans = proj * camera * model;
    MatrixID = glGetUniformLocation(shaderID, "trans");
    glUniformMatrix4fv(MatrixID, 1, FALSE, glm::value_ptr(trans));

    drawBackground();
    drawGameSpace();
    drawPreview();
    drawOutBlocks();
    
    // 추가 뷰포트
    drawTopDownViewport(windowWidth, windowHeight);

    glutSwapBuffers();
}

void Renderer::drawTopDownViewport(int windowWidth, int windowHeight)
{
    // 오른쪽 위 1/4 크기 뷰포트 설정
    int vpWidth = windowWidth / 4;
    int vpHeight = windowHeight / 4;
    int vpX = windowWidth - vpWidth - 10;  // 오른쪽에서 10px 여백
    int vpY = windowHeight - vpHeight - 10; // 위에서 10px 여백

    glViewport(vpX, vpY, vpWidth, vpHeight);

    // Top-down 카메라로 변환 행렬 설정
    topDownTrans = topDownProj * topDownCamera;
    glUniformMatrix4fv(MatrixID, 1, FALSE, glm::value_ptr(topDownTrans));

    // 뷰포트 테두리 그리기 (선택사항)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 씬 다시 그리기
    drawBackground();
    drawGameSpace();
    drawPreview();
    drawOutBlocks();

    // 원래 폴리곤 모드로 복원
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::drawBackground()
{
    glBindVertexArray(VAO_bg);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
    glBufferData(GL_ARRAY_BUFFER, sizeof(background), background, GL_STATIC_DRAW);

    GLint pAttribute2 = glGetAttribLocation(shaderID, "vPos");
    glVertexAttribPointer(pAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(pAttribute2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_bgColor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgColor), bgColor, GL_STATIC_DRAW);

    GLint cAttribute2 = glGetAttribLocation(shaderID, "vColor");
    glVertexAttribPointer(cAttribute2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(cAttribute2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawArrays(GL_QUADS, 0, 24);
}

void Renderer::drawGameSpace()
{
    for (int x = 0; x < 12; ++x)
    {
        for (int y = 0; y < 12; ++y)
        {
            for (int z = 0; z < 12; ++z)
        {
      glBindVertexArray(VAO[x][y][z]);
  switch (GameState::GameSpace[x][z][y])
            {
            case 1:
  for (int i = 0; i < 24; ++i)
     {
       squarePosition[i][0] = square[i][0] + (float)x - 5.5f;
             squarePosition[i][1] = square[i][1] + (float)y - 5.5f;
          squarePosition[i][2] = square[i][2] + (float)z - 5.5f;

    squareColor[i][0] = 0.8;
              squareColor[i][1] = 0.4;
  squareColor[i][2] = 0.4;
        }
          break;
           case 2:
    for (int i = 0; i < 24; ++i)
      {
  squarePosition[i][0] = square[i][0] + (float)x - 5.5f;
               squarePosition[i][1] = square[i][1] + (float)y - 5.5f;
  squarePosition[i][2] = square[i][2] + (float)z - 5.5f;

         squareColor[i][0] = 0.0;
          squareColor[i][1] = 1.0;
squareColor[i][2] = 0.0;
   }
     break;
   case 3:
      for (int i = 0; i < 24; ++i)
            {
          squarePosition[i][0] = square[i][0] + (float)x - 5.5f;
       squarePosition[i][1] = square[i][1] + (float)y - 5.5f;
               squarePosition[i][2] = square[i][2] + (float)z - 5.5f;

      squareColor[i][0] = 0.0;
            squareColor[i][1] = 0.5;
           squareColor[i][2] = 1.0;
        }
            break;
     case 4:
       for (int i = 0; i < 24; ++i)
       {
               squarePosition[i][0] = square[i][0] + (float)x - 5.5f;
          squarePosition[i][1] = square[i][1] + (float)y - 5.5f;
    squarePosition[i][2] = square[i][2] + (float)z - 5.5f;

         squareColor[i][0] = 1.0;
    squareColor[i][1] = 1.0;
squareColor[i][2] = 0.0;
   }
         break;
              case 5:
           for (int i = 0; i < 24; ++i)
         {
        squarePosition[i][0] = square[i][0] + (float)x - 5.5f;
   squarePosition[i][1] = square[i][1] + (float)y - 5.5f;
                 squarePosition[i][2] = square[i][2] + (float)z - 5.5f;

   squareColor[i][0] = 1.0;
    squareColor[i][1] = 0.0;
       squareColor[i][2] = 1.0;
  }
            break;
                }

                if (GameState::GameSpace[x][z][y] > 0)
         {
         glBindBuffer(GL_ARRAY_BUFFER, VBO_position[x][y][z]);
         glBufferData(GL_ARRAY_BUFFER, sizeof(squarePosition), squarePosition, GL_STATIC_DRAW);

     GLint pAttribute1 = glGetAttribLocation(shaderID, "vPos");
      glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
       glEnableVertexAttribArray(pAttribute1);

   glBindBuffer(GL_ARRAY_BUFFER, VBO_color[x][y][z]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(squareColor), squareColor, GL_STATIC_DRAW);

         GLint cAttribute1 = glGetAttribLocation(shaderID, "vColor");
            glVertexAttribPointer(cAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
                    glEnableVertexAttribArray(cAttribute1);

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          glDrawArrays(GL_QUADS, 0, 24);

     for (int i = 0; i < 24; ++i)
  {
               for (int j = 0; j < 3; ++j)
      {
           squareColor[i][j] = 0;
    }
          }

    glBindBuffer(GL_ARRAY_BUFFER, VBO_position[x][y][z]);
           glBufferData(GL_ARRAY_BUFFER, sizeof(squarePosition), squarePosition, GL_STATIC_DRAW);

     pAttribute1 = glGetAttribLocation(shaderID, "vPos");
   glVertexAttribPointer(pAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
              glEnableVertexAttribArray(pAttribute1);

                    glBindBuffer(GL_ARRAY_BUFFER, VBO_color[x][y][z]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(squareColor), squareColor, GL_STATIC_DRAW);

          cAttribute1 = glGetAttribLocation(shaderID, "vColor");
           glVertexAttribPointer(cAttribute1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(cAttribute1);

 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
           glDrawArrays(GL_QUADS, 0, 24);
      }

 for (int i = 0; i < 24; ++i)
     {
          for (int j = 0; j < 3; ++j)
          {
  squarePosition[i][j] = square[i][j];
          squareColor[i][j] = originColor[i][j];
   }
     }
       }
}
    }
}

void Renderer::drawPreview()
{
  for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
       for (int k = 0; k < 12; ++k)
            {
            if (GameState::previewSpace[i][j][k] == 1)
    {
      for (int t = 0; t < 4; ++t)
        {
  pvTarget[t][0] = top[t][0] + i - 5.5f;
      pvTarget[t][1] = top[t][1] + k - 5.5f;
        pvTarget[t][2] = top[t][2] + j - 5.5f;
       }
               glBindVertexArray(VAO_preview);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_top);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pvTarget), pvTarget, GL_STATIC_DRAW);

         GLint pAttribute3 = glGetAttribLocation(shaderID, "vPos");
  glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
      glEnableVertexAttribArray(pAttribute3);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_pvColor);
   glBufferData(GL_ARRAY_BUFFER, sizeof(pvColor), pvColor, GL_STATIC_DRAW);

         GLint cAttribute3 = glGetAttribLocation(shaderID, "vColor");
           glVertexAttribPointer(cAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
              glEnableVertexAttribArray(cAttribute3);

         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
           glDrawArrays(GL_QUADS, 0, 4);
    }
 else if (GameState::previewSpace[i][j][k] == -1)
           {
        for (int t = 0; t < 4; ++t)
        {
              pvTarget[t][0] = bottom[t][0] + i - 5.5f;
                  pvTarget[t][1] = bottom[t][1] + k - 5.5f;
            pvTarget[t][2] = bottom[t][2] + j - 5.5f;
            }
   glBindVertexArray(VAO_preview);

             glBindBuffer(GL_ARRAY_BUFFER, VBO_bottom);
              glBufferData(GL_ARRAY_BUFFER, sizeof(pvTarget), pvTarget, GL_STATIC_DRAW);

  GLint pAttribute3 = glGetAttribLocation(shaderID, "vPos");
   glVertexAttribPointer(pAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
         glEnableVertexAttribArray(pAttribute3);

         glBindBuffer(GL_ARRAY_BUFFER, VBO_pvColor);
     glBufferData(GL_ARRAY_BUFFER, sizeof(pvColor), pvColor, GL_STATIC_DRAW);

          GLint cAttribute3 = glGetAttribLocation(shaderID, "vColor");
         glVertexAttribPointer(cAttribute3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
             glEnableVertexAttribArray(cAttribute3);

          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glDrawArrays(GL_QUADS, 0, 4);
          }
         }
        }
    }
}

void Renderer::drawOutBlocks()
{
    for (int z = 0; z < 12; ++z)
    {
if (GameState::out[z] > 0)
        {
      for (int x = 0; x < 12; ++x)
   {
       for (int y = 0; y < 12; ++y)
         {
        switch (GameState::outSpace[x][z][y])
        {
            case 1:
   for (int i = 0; i < 24; ++i)
      {
       outPosition[i][0] = square[i][0] + (float)x - 5.5f + (float)GameState::out[z];
         outPosition[i][2] = square[i][2] + (float)y - 5.5f;
  outPosition[i][1] = square[i][1] + (float)z - 5.5f;

     outColor[i][0] = 0.8;
        outColor[i][1] = 0.4;
         outColor[i][2] = 0.4;
      }
 break;
     case 2:
  for (int i = 0; i < 24; ++i)
          {
      outPosition[i][0] = square[i][0] + (float)x - 5.5f + (float)GameState::out[z];
      outPosition[i][2] = square[i][2] + (float)y - 5.5f;
       outPosition[i][1] = square[i][1] + (float)z - 5.5f;

            outColor[i][0] = 0.0;
    outColor[i][1] = 1.0;
         outColor[i][2] = 0.0;
    }
    break;
       case 3:
     for (int i = 0; i < 24; ++i)
       {
          outPosition[i][0] = square[i][0] + (float)x - 5.5f + (float)GameState::out[z];
   outPosition[i][2] = square[i][2] + (float)y - 5.5f;
    outPosition[i][1] = square[i][1] + (float)z - 5.5f;

    outColor[i][0] = 0.0;
        outColor[i][1] = 0.5;
    outColor[i][2] = 1.0;
      }
      break;
         case 4:
       for (int i = 0; i < 24; ++i)
         {
   outPosition[i][0] = square[i][0] + (float)x - 5.5f + (float)GameState::out[z];
    outPosition[i][2] = square[i][2] + (float)y - 5.5f;
     outPosition[i][1] = square[i][1] + (float)z - 5.5f;

    outColor[i][0] = 1.0;
        outColor[i][1] = 1.0;
             outColor[i][2] = 0.0;
         }
     break;
    case 5:
            for (int i = 0; i < 24; ++i)
  {
      outPosition[i][0] = square[i][0] + (float)x - 5.5f + (float)GameState::out[z];
                outPosition[i][2] = square[i][2] + (float)y - 5.5f;
      outPosition[i][1] = square[i][1] + (float)z - 5.5f;

        outColor[i][0] = 1.0;
       outColor[i][1] = 0.0;
           outColor[i][2] = 1.0;
     }
          break;
                 }

  if (GameState::outSpace[x][z][y] > 0)
         {
           glBindVertexArray(VAO_out[x][y][z]);

       glBindBuffer(GL_ARRAY_BUFFER, VBO_out[x][y][z]);
              glBufferData(GL_ARRAY_BUFFER, sizeof(outPosition), outPosition, GL_STATIC_DRAW);

      GLint pAttribute4 = glGetAttribLocation(shaderID, "vPos");
         glVertexAttribPointer(pAttribute4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
          glEnableVertexAttribArray(pAttribute4);

              glBindBuffer(GL_ARRAY_BUFFER, VBO_outColor[x][y][z]);
 glBufferData(GL_ARRAY_BUFFER, sizeof(outColor), outColor, GL_STATIC_DRAW);

         GLint cAttribute4 = glGetAttribLocation(shaderID, "vColor");
                glVertexAttribPointer(cAttribute4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(cAttribute4);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
           glDrawArrays(GL_QUADS, 0, 24);
    }

      for (int i = 0; i < 24; ++i)
      {
      for (int j = 0; j < 3; ++j)
 {
         outPosition[i][j] = square[i][j];
         outColor[i][j] = originColor[i][j];
  }
            }
        }
}
}
    }
}

void Renderer::Reshape(int w, int h)
{
glViewport(0, 0, w, h);
// 메인 프로젝션 업데이트
proj = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);

// Top-down 프로젝션도 비율에 맞게 업데이트 (선택사항)
float aspect = (float)w / (float)h;
topDownProj = glm::ortho(-8.0f * aspect, 8.0f * aspect, -8.0f, 8.0f, 0.1f, 100.0f);
}
