#include <iostream>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "Particle.h"

int startTime = 0;

const int WIDTH = 800;
const int HEIGHT = 600;

std::vector<Particle*> particles(1);

float timeElapsed() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    int time = duration.count();

    int deltaT = time - startTime;
    //startTime = time;
    //std::cout << "Seconds since epoch: " << timer << std::endl;
    //std::cout << "Seconds since start: " << startTime << std::endl;
    //std::cout << "deltaT: " << deltaT << std::endl;
    return (float)deltaT;
}

int main()
{
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    int time = duration.count();
    startTime = time;

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::cout << particles.size() << std::endl;
    for (unsigned int i = 0; i < particles.size(); i++) {
        //Particle *particle = new Particle(350 + (float) i*10, 0, i, i*10, 7.5);
        Particle *particle = new Particle(400-i, 0+i, 10+i, 10+i, 7.5);
        particles[i] = particle;
    }
    std::cout << particles.size() << std::endl;

    float deltaT = 0;
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        int time = duration.count();

        if(time - startTime > 500) {
            startTime = time;
            deltaT += 1;
        }

        for (unsigned int i = 0; i < particles.size(); i++) {
            particles[i]->update(deltaT);
            particles[i]->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
