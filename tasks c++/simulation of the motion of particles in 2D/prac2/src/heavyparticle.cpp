#include "heavyparticle.hpp"

HeavyParticle::HeavyParticle(double mass, double radius, double x, double y, double vx, double vy)
    : Particle(mass, radius, x, y, vx, vy) {}
    
double HeavyParticle::get_mass() const {
    return mass;
}
double HeavyParticle::get_radius() const {
    return radius;
}

HeavyParticle::HeavyParticle(int seed, SimulationWindow* win) {   
    (void) win;
    std::mt19937 generator(seed);
    std::uniform_real_distribution<double> distribution_radius(10, 40);
    std::uniform_real_distribution<double> distribution_x(100, 1050);
    std::uniform_real_distribution<double> distribution_y(150, 720);
    std::uniform_real_distribution<double> distribution_vx(10, 61);
    std::uniform_real_distribution<double> distribution_vy(10, 26);
    std::uniform_real_distribution<double> distribution_mass(5, 15);

    radius = distribution_radius(generator);
    x = distribution_x(generator);
    y = distribution_y(generator);
    vx = distribution_vx(generator);
    vy = distribution_vy(generator);
    mass = distribution_mass(generator);
}


