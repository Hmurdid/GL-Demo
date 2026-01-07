#include "render.hpp"

Render::Render() {};
Render::~Render() {};

bool Render::init() {
    glGenVertexArrays(1 ,&VAO);
    glGenBuffers(1, &VBO);
    
    if(VAO == 0 || VBO == 0) return false;
    return true;
};      

void Render::cleanUp() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
};

void Render::createLineBuffer(const float* vertices, size_t count, GLenum usage) {

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, usage);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Render::bindLineBuffer() {
    glBindVertexArray(VAO);
}

void Render::unbindLineBuffer() {
    glBindVertexArray(0);
}

void Render::setupShaders() {
    
}