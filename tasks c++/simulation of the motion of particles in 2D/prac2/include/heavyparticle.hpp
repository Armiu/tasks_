#ifndef HEAVYPARTICLE_HPP
#define HEAVYPARTICLE_HPP
#include <cmath>
#include <iostream>
#include <vector>
#include "particle.hpp"
#include "graphics.hpp"

class SimulationWindow;
class HeavyParticle : public Particle {
    double mass;
    double radius;
public:
    HeavyParticle(double mass, double radius, double x, double y, double vx, double vy);
    HeavyParticle(int seed, SimulationWindow* win);

    double get_mass() const override;
    double get_radius() const override;
};

#endif // HEAVYPARTICLE_HPP
