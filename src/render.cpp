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

void Render::createLineBuffers() {
    
};