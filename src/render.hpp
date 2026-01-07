/*

Абстракція над абстракціями — це і є айсберг програмування. Неможливо їхати машиною, 
самостійно підливаючи паливо та запалюючи свічу.

*/

#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Render {
public:
    Render();
    ~Render();

    bool init();
    void cleanUp();

    void createLineBuffer(const float* vertices, size_t count, GLenum usage = GL_STATIC_DRAW);
    void bindLineBuffer();
    void unbindLineBuffer();

    void setupShaders();    
    void compileShaders();
    void createShaderProgram();

    void beginFrame();
    void endFrame();
    
    void setColor();
    void setProjection();
    void updateBufferData();

private:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    float projectionMatrix[16];
    float x, y, z;
    float r, g, b, a; 
};