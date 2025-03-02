//
// Created by Carl Gombert on 2/28/25.
//

#include "Particle.h"

#include <iostream>
#include <ostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <chrono>
#include <algorithm>



Particle::Particle() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    int time = duration.count();
    air_time = time;
    position = {0, 0};
    velocity = {0, 0};
    this->radius = 7.5;
}

Particle::Particle(float pX, float pY, float vX, float vY, float radius) {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    int time = duration.count();
    air_time = time;
    position = {pX, pY};
    velocity = {vX, vY};
    this->radius = radius;
}

void Particle::update(float deltaT) {
    velocity[1] += GRAVITY * deltaT;
    position[1] += velocity[1];
    position[0] += velocity[0];
    float velocityMag = sqrt(velocity[0]*velocity[0] + velocity[1]*velocity[1]);

    float colorValue = std::min(20.0f, velocityMag)/20.0f;

    color[0] = colorValue;
    color[1] = 1.0-colorValue;
    color[2] = 1.0-colorValue;
    collision();
}

void Particle::draw() {
    float cx = position[0];
    float cy = position[1];
    float r = this->radius;
    std::vector<float> c = color;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of the circle
    for (int i = 0; i <= NUM_SEGMENTS; i++) {
        float theta = 2.0f * M_PI * float(i) / float(NUM_SEGMENTS);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glColor3f(c[0], c[1], c[2]);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void Particle::collision() {
    if(position[0] + radius > WIDTH || position[0] - radius < 0) {
        velocity[0] *= -0.5;
        if(position[0] + radius > WIDTH) {
            position[0] = WIDTH - radius;
            std::cout << "far right" << std::endl;
        }
        else if(position[0] - radius < 0) {
            position[0] = 0 + radius;
            std::cout << "far left" << std::endl;
        }
    }
    if(position[1] + radius > HEIGHT || position[1] - radius < 0) {
        velocity[1] *= -0.5;
        if(position[1] + radius > HEIGHT) {
            position[1] = HEIGHT - radius;
        }
        else if (position[1] - radius < 0) {
            position[1] = 0 + radius;
        }
    }
}

float Particle::timeElapsed() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    int time = duration.count();

    int deltaT = time - air_time;
    return (float)deltaT;
}

