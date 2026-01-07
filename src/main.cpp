/*  Diary (Vernacular)
        Вернувся після місяця вигорання та вирішив почати щоденник. Це офіційно пиздець.                     |   01.01.2026
        Я ніхуя не розумію, пробую осмимлити все через написання коментарів.
        Ні документації, нічого. Гавно яке придумали 30 років тому. Ненавиджу програмування.

        Також було додано glm та imgui в проект. Навчання проходить разом з ШІ в ролі вчителя і 
        сьогодні я отримав гарний досвід з ним. Під час інтеграції imgui в проект, виникла 
        проблема що imgui використовував особистий графічний API та на відріз відмовлявся сприймати
        мій GLAD, навіть коли додавав аргументи в task.json чи ставив його нижче GLAD в include списку.
        Граний досвід полягає в тому, що я вперше, хоч і з ШІ, почав дебажити ЧУЖИЙ код, інтегруючи 
        чужі бібліотеки в свій код. Це було важливо тому що я розумію, що 90% роботи програміста - це не
        робота зі своїм кодом, але чужим. 

        Далі по планам є створення CMAKE, підтримка task.json припиняється, а також скоро проект чекає
        рефакторинг, оскільки main файл вже доволі сильно розрісся тимчасовим сміттям



        Написав CMake. Поки що лише для Windows. Колись зайду зі свого дистро і подивлюсь                   | 02.01.2026
        як там варто робити під Linux. MacOS соячки не чекайте CMake на свою систему ближчим часом.
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "window.hpp"
#include "render.hpp"

int main() {
    Window win;
    Render render;
    if (win.initWindow() != 0) return -1;
    GLFWwindow* window = win.getWindow();
    render.init();

    // Все що повязано з ImGui було додано ШІ для швидкого тестування.
    // Також цей коміт це початок рефакторингу проекту.
    // ========== ImGui Setup ==========
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Увімкнути docking
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // ========== Тестові змінні для UI ==========
    float gravity = 9.81f;
    float mass = 1.0f;
    bool showDemo = false;
    float color[3] = {1.0f, 1.0f, 1.0f};

    // Тимчасовий код:
    // Псевдо-рандом
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // Зазначення вершин обєкта
    float line_vertices[9] = {
    0.98f, -0.10f, 0.0f,
    -0.37f, -0.59f, 0.0f,
    0.41f,  0.23f, 0.0f
    };

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Та сама умовність
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char* vertex_shader_source =
        "#version 330 core\n"
        "layout(location = 0) in vec2 pos;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 0.0, 1.0);\n"
        "}\n";

    const char* fragment_shader_source = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec3 lineColor;\n"
        "void main() {\n"
        "    FragColor = vec4(lineColor, 1.0);\n"
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

    // Створюємо і лінкуємо шейдерну програму
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader Program Linking Failed\n" << infoLog << std::endl;
    }

    // Видаляємо шейдери (вони вже в програмі)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Головний цикл
    while (!glfwWindowShouldClose(window)) {

         // ===== ImGui New Frame =====
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ===== ImGui UI =====
        ImGui::Begin("Simulation Settings:");
        ImGui::Text("FPS: %.1f", io.Framerate);
        ImGui::Separator();
        
        ImGui::SliderFloat("Gravitaion", &gravity, 0.0f, 20.0f);
        ImGui::SliderFloat("Mass", &mass, 0.1f, 10.0f);
        ImGui::ColorEdit3("Line Color", color);
        
        ImGui::Separator();
        ImGui::Checkbox("Show Demo window", &showDemo);
        
        if (ImGui::Button("Reset variables")) {
            gravity = 9.81f;
            mass = 1.0f;
            color[0] = color[1] = color[2] = 1.0f;
        }
        
        ImGui::End();

        // Demo вікно (опціонально)
        if (showDemo) {
            ImGui::ShowDemoWindow(&showDemo);
        }

        // Очистка екрану (темно-синій колір)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Передаємо колір з UI в шейдер
        int colorLoc = glGetUniformLocation(shaderProgram, "lineColor");
        glUniform3fv(colorLoc, 1, color);



        // Рандомайзер вершини на швидку руку
        float r = dist(rng);
        float r2 = dist(rng);
        line_vertices[1] = r;
        line_vertices[4] = r2;
        glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_DYNAMIC_DRAW);

        // Виконання всього цього гівна яке я написав за межами циклу
        glBindVertexArray(line_VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);


        // ===== ImGui Render =====
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // Обмін буферів і обробка подій
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // ========== Cleanup ==========
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glDeleteVertexArrays(1, &line_VAO);
    glDeleteBuffers(1, &line_VBO);
    glDeleteProgram(shaderProgram);
    


    glfwTerminate();
    return 0;
}