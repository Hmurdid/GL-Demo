#include "physic.hpp"
#include <cmath>

void updatePhysic(std::vector<body> &bodies, float dt) {
    float g = 0.00001f;
    for(auto& body : bodies) {
        body.fx = body.fy = body.fz = 0;
    }

    for(int i = 0; i < bodies.size(); i++) {
        for(int j = i+1; j < bodies.size(); j++) {
            float dx = bodies[i].x - bodies[j].x;
            float dy = bodies[i].y - bodies[j].y;
            float dz = bodies[i].z - bodies[j].z;
        
            float r = sqrt(dx*dx + dy*dy + dz*dz);
            float F = g * bodies[i].mass * bodies[j].mass / (r*r);
            float Fx = F * (dx / r);
            float Fy = F * (dy / r);
            float Fz = F * (dz / r);

            bodies[i].fx -= Fx; 
            bodies[i].fy -= Fy;
            bodies[i].fz -= Fz;

            bodies[j].fx += Fx;
            bodies[j].fy += Fy;
            bodies[j].fz += Fz;
        }
    }

    for(int i = 0; i < bodies.size(); i++) {
        bodies[i].vx = bodies[i].vx + (bodies[i].fx / bodies[i].mass) * dt;
        bodies[i].vy = bodies[i].vy + (bodies[i].fy / bodies[i].mass) * dt;
        bodies[i].vz = bodies[i].vz + (bodies[i].fz / bodies[i].mass) * dt;

        bodies[i].x = bodies[i].x + bodies[i].vx * dt;
        bodies[i].y = bodies[i].y + bodies[i].vy * dt;
        bodies[i].z = bodies[i].z + bodies[i].vz * dt;
    }
}
