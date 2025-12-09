#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"
#include "render.hpp"

int main() {
    Window win;
    Render render;

    if (win.initWindow() != 0) return -1;
    GLFWwindow* window = win.getWindow();

    render.init();


    // Головний цикл
    while (!glfwWindowShouldClose(window)) {
        // Очистка екрану (темно-синій колір)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Обмін буферів і обробка подій
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Очистка ресурсів
    glfwTerminate();
    return 0;
}