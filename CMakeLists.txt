cmake_minimum_required(VERSION 3.20)
project(GLdemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp"
    "src/*.c"
    "src/*.h"
)

file(GLOB_RECURSE IMGUI_SOURCES CONFIGURE_DEPENDS 
    "lib/imgui/*.cpp"
    "lib/imgui/*.h"
    "lib/imgui/backends/*.cpp"
    "lib/imgui/backends/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends
)

target_link_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        glfw3 
        opengl32 
        gdi32 
        user32 
        shell32 
        imm32
    )
else()
    message(FATAL_ERROR "This shit doesnt work on Linux currently. Im so tired")
endif()