#ifndef LIGHTPARTICLE_HPP
#define LIGHTPARTICLE_HPP
#include <cmath>
#include <iostream>
#include <vector>
#include "particle.hpp"
#include "graphics.hpp"
class SimulationWindow;
class LightParticle : public Particle {
    static double mass;
    static double radius;
public:
    LightParticle(double x, double y, double vx, double vy); 
    LightParticle(int seed, SimulationWindow* win);

    double get_mass() const;
    double get_radius() const;
};


#endif // LIGHTPARTICLE_HPP
