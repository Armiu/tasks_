#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include<FL/Fl.H>
#include<FL/fl_draw.H>
#include<random>
#include <math.h>

class Particle {
protected:    
    double x, y; 
    double vx, vy;
public:
    Particle();
    Particle(double, double, double x, double y, double vx, double vy);
    virtual void update_position(double dt);
    virtual void handle_collision(Particle* other);
    virtual bool check_collision(const Particle* other) const;
    virtual double distance_to(const Particle* a) const;
    virtual void check_handle_wall_collision();

    double get_x() const;
    double get_y() const;
    double get_vx() const;
    double get_vy() const;
    virtual double get_mass() const = 0;
    virtual double get_radius() const = 0;
    virtual void set_vx(double vx);
    virtual void set_vy(double vy);
    virtual void set_x(double x);
    virtual void set_y(double y);
    virtual ~Particle() {}
};

#endif // PARTICLE_HPP
