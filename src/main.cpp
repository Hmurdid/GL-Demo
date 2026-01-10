#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "window.hpp"
#include "render.hpp"
#include "physic.hpp"

int main() {
    Window win;
    Render render;

    if(win.initWindow() != 0) return 1;
    GLFWwindow* window = win.getWindow();
    render.init();



    // Тимчасовий код:
    std::vector<body> bodies {
        {0.3f, 0.4f, 0.0f,      0.5f, 0.5f, 0.5f, 1.0f,     0.2f,     0,0,0,0,0,0}, // XYZ, RGBA, Mass, V(3 coordinates) F(3 coordinates)
        {-0.6f, -0.2f, 0.0f,    0.5f, 0.5f, 0.5f, 1.0f,     0.07f,    0,0,0,0,0,0},
        {0.1f, -0.5f, 0.0f,     0.5f, 0.5f, 0.5f, 1.0f,     0.117f,   0,0,0,0,0,0}
    };

    int vertices_count = 21;
    render.setupShaders();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // КОСТИЛЬ! ВИПРАВИТИ ПІСЛЯ ТЕСТІВ!
    glLineWidth(2.0f);                          // ЦЕ ТАКОЖ!


    while(!glfwWindowShouldClose(window)) {

        float dt = 0.016f;
        updatePhysic(bodies, dt);
        std::cout << "Body 0: " << bodies[0].x << " " << bodies[0].y << std::endl;

        float vertices[] = {
        bodies[0].x, bodies[0].y, bodies[0].z, bodies[0].r, bodies[0].g, bodies[0].b, bodies[0].a,
        bodies[1].x, bodies[1].y, bodies[1].z, bodies[1].r, bodies[1].g, bodies[1].b, bodies[1].a,
        bodies[2].x, bodies[2].y, bodies[2].z, bodies[2].r, bodies[2].g, bodies[2].b, bodies[2].a
        };

        render.beginFrame();
        render.createTriangleBuffer(vertices, vertices_count, GL_DYNAMIC_DRAW);
        render.drawTriangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    render.cleanUp();
}