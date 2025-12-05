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
    void beginFrame();
    void endFrame();
    void setColor();
    void setupShaders();    
    void compileShaders();
    void createShaderProgram();
    void setProjection();
    void createLineBuffers();
    void updateBufferData();
    void drawLine();

private:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    float projectionMatrix[16];
    float r, g, b;
};