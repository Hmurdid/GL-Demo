#include "render.hpp"
#include <iostream>

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

void Render::createTriangleBuffer(const float* vertices, size_t count, GLenum usage) {
    this-> vertexCount = count / 7;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, usage);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
};

void Render::setupShaders() {

    const char* vertex_shader_source = 
        "#version 330 core\n"
        "layout(location = 0) in vec3 pos;\n"
        "layout(location = 1) in vec4 col;\n"
        "out vec4 vertexColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 1.0);\n"
        "    vertexColor = col;\n"
        "}\n";

    const char* fragment_shader_source = 
        "#version 330 core\n"
        "in vec4 vertexColor;\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vertexColor;\n"
        "}\n";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
} 

void Render::beginFrame() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
}

void Render::endFrame() {
    // Empty for now. Sosal
}

void Render::drawTriangle() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

