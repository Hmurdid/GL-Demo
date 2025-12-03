#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window() {}; 

Window::~Window() {
    if(window) {glfwDestroyWindow(window); glfwTerminate();}
};

int Window::initWindow() {
    if (!glfwInit()) return -1;

    // Giveng current version to GLFW: 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(800, 600, " ", NULL, NULL);
    /* Creating window with:
    width: 800;
    heigh: 600;
    window mane: " ";
    window type: NULL; (winwowed)
    window shader sharing: NULL;
    */

    if (!window) {glfwTerminate(); return -1;}
    glfwMakeContextCurrent(window); // Fixing our window to OpenGL


    // If OpenGL wasnt initialized via GLAD: Return -1.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    glViewport(0, 0, 800, 600);
    return 0;
};

GLFWwindow* Window::getWindow() {
    return window;
};

