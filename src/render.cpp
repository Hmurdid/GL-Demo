#include "render.hpp"

Render::Render() {};
Render::~Render() {};

bool Render::init() {
    VAO = 0;
    VBO = 0;
    shaderProgram = 0;
    r = g = b = 0.0f;
    return true;
};

