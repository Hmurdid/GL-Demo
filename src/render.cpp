#include "render.hpp"

Render::Render() {};
Render::~Render() {};

bool Render::init() {
    glGenVertexArrays(1 ,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    if(VAO == 0 || VBO == 0 || EBO == 0) return false;
    return true;
};      

void Render::cleanUp() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
};

void Render::createLineBuffers() {
    float verticesForFun[] = {
        0.0f, 1.0f,
        1.0f, 0.0f
    };
    unsigned int indices[] {
        0, 1
    };

    
};