#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>


#include "window.hpp"
#include "render.hpp"

int main() {
    Window win;
    Render render;
    if (win.initWindow() != 0) return -1;
    GLFWwindow* window = win.getWindow();
    render.init();

    // Тимчасовий код:
    // Псевдо-рандом
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // Зазначення вершин обєкта
    float line_vertices[4];
    line_vertices[0] = 0.0;
    line_vertices[1] = 0.0;
    
    line_vertices[2] = 1.0;
    line_vertices[3] = 1.0;

    // Ініціалізація VAO, VBO (VAO - інструкції для читання буферу. VBO - буфер вершин)
    // Бінд VAO, VBO
    // Запис в VAO, VBO
    // Стверджуємо робочий слот VAO для GPU
    // Відвязка GPU від VAO, VBO (Умовність)
    unsigned int line_VAO, line_VBO;
    glGenVertexArrays(1, &line_VAO);
    glGenBuffers(1, &line_VBO);

    glBindVertexArray(line_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Та сама умовність
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    // Це пиздець. Я ніхуя не розумію, пробую осмимлити все через коменти.                     |   01.01.2026
    // Ні документації, нічого. Гавно яке придумали 30 років тому. Ненавиджу програмування.
    

    const char* vertex_shader_source =
        "#version 330 core\n"
        "layout(location = 0) in vec2 pos;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 0.0, 1.0);\n"
        "}\n";

    const char* fragment_shader_source = 
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragmentShader);

    // Створюємо і лінкуємо шейдерну програму
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Видаляємо шейдери (вони вже в програмі)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);




    // Головний цикл
    while (!glfwWindowShouldClose(window)) {
        // Очистка екрану (темно-синій колір)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // Рандомайзер вершини на швидку руку
        float r = dist(rng);
        float r2 = dist(rng);
        line_vertices[2] = r;
        line_vertices[3] = r2;
        glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_DYNAMIC_DRAW);

        // Виконання всього цього гівна яке я написав за межами циклу
        glUseProgram(shaderProgram);
        glBindVertexArray(line_VAO);
        glDrawArrays(GL_LINES, 0, 2);

        // Обмін буферів і обробка подій
        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    
    // Очистка ресурсів
    glfwTerminate();
    return 0;
}