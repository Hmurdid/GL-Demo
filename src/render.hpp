/*

Абстракція над абстракціями — це і є айсберг програмування. Неможливо їхати машиною, 
самостійно підливаючи паливо та запалюючи свічу.

*/

#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Render {
public:
    Render(); //
    ~Render(); //

    bool init(); //
    void cleanUp(); //
    void createTriangleBuffer(const float* vertices, size_t count, GLenum usage = GL_STATIC_DRAW);  //
    void setupShaders(); //

    void beginFrame();
    void endFrame();
    
    void drawTriangle();
    void drawLine(const float* vertices, size_t count);
    void drawParticle(const float* vertices, size_t count);

    //void setColor(float r, float g, float b, float a);
    void setProjection();
    void updateBufferData();

private:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    float projectionMatrix[16];
    float x, y, z;
    float r, g, b, a;

    size_t vertexCount;
    //int ColorLocation;
};