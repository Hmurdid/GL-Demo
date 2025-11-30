#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();
    int initWindow();
    GLFWwindow* getWindow();

private: 
    GLFWwindow* window;
};
#endif