#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <vector>
#include <chrono>
#include "particle.hpp"
#include <random>
#include "lightparticle.hpp"
#include "heavyparticle.hpp"
#include "graphics.hpp"
#include <cstdlib>
class SimulationWindow;

class System {
    std::vector<Particle*> particles;
    int start_l, start_h;
    SimulationWindow* window;
public:
    System(int seed, int num_l_particles, int num_h_particles, SimulationWindow* win);
    System(const System& other);
    System& operator=(const System& other);

    void addParticle_l();
    void addParticle_h();
    void delete_particle_l();
    void delete_particle_h();
    void step();
    void draw();

    SimulationWindow* get_window();
    Particle* get_overlapping_particle(Particle* particle, std::vector<Particle*>::size_type index);
    Particle* get_particle(std::vector<Particle*>::size_type n);

    int get_amount();
    void set_num_steps(); 
    int& get_num_steps();
    void erase();
    bool is_overlap(const Particle* new_particle, int index);

    ~System();
};
#endif // SYSTEM_HPP
