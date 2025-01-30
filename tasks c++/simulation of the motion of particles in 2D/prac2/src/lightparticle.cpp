#include "lightparticle.hpp"
double LightParticle::mass = 4;
double LightParticle::radius = 20;

LightParticle::LightParticle(double x, double y, double vx, double vy)
        : Particle(mass, radius, x, y, vx, vy) {} 

double LightParticle::get_mass() const {
    return mass;
}
double LightParticle::get_radius() const {
    return radius;
}

LightParticle::LightParticle(int seed, SimulationWindow* win) {  
    (void) win;
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution_x(100, 1050);
    std::uniform_real_distribution<double> distribution_y(150, 720);
    std::uniform_real_distribution<double> distribution_vx(10, 61);
    std::uniform_real_distribution<double> distribution_vy(10, 34);

    x = distribution_x(generator);
    y = distribution_y(generator);
    vx = distribution_vx(generator);
    vy = distribution_vy(generator);
}


