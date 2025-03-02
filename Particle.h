//
// Created by Carl Gombert on 2/28/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>


class Particle {

    public:
        Particle();
        Particle(float pX, float pY, float vX, float vY, float radius);
        void update(float deltaT);

        void draw();

    private:
        const int NUM_SEGMENTS = 100;
        const float GRAVITY = 0;
        const int WIDTH = 800;
        const int HEIGHT = 600;
        int air_time;
        float radius;
        float density;
        float mass = 1;
        std::vector<float> color = {0.0, 1.0, 0.0};
        std::vector<float> position;
        std::vector<float> velocity;
        void collision();
        float timeElapsed();

};

#endif //PARTICLE_H
