#pragma once
#include <vector>

struct body {
    float x, y, z;
    float r, g, b, a;
    float mass;
    float vx, vy, vz;
    float fx, fy, fz;
};

void updatePhysic(std::vector<body> &bodies, float dt);