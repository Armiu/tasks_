#include "particle.hpp"
Particle::Particle(double, double, double x, double y, double vx, double vy)
    : x(x), y(y), vx(vx), vy(vy) {}

Particle::Particle(){}

double Particle::get_x() const {
    return x;
}

double Particle::get_y() const {
    return y;
}
double Particle::get_vx() const {
    return vx;
}
double Particle::get_vy() const {
    return vy;
}
void Particle::set_vx(double vx) {
    this->vx = vx;
}
void Particle::set_vy(double vy) {
    this->vy = vy;
}
void Particle::set_x(double x) {
    this->x = x;
}
void Particle::set_y(double y) {
    this->y = y;
}

double Particle::distance_to(const Particle* a) const {
    return sqrt((x - a->get_x())*(x - a->get_x()) + (y - a->get_y())*(y - a->get_y()));
}
bool Particle::check_collision(const Particle* other) const {
    return distance_to(other) < (get_radius() + other->get_radius());
}

void Particle::check_handle_wall_collision() {
    if (x - get_radius() < 50) {
        x = 50 + get_radius();
        vx = -vx;
    } else if (x + get_radius() > 1100) {
        x = 1100 - get_radius();
        vx = -vx;
    }

    if (y - get_radius() < 80) {
        y = 80 + get_radius();
        vy = -vy;
    } else if (y + get_radius() > 800) {
        y = 800 - get_radius();
        vy = -vy;
    }
}
void Particle::handle_collision(Particle* p) {
    double dx = p->get_x() - get_x();
    double dy = p->get_y() - get_y();
    double distance = sqrt(dx*dx + dy*dy);
    double direction_x = dx / distance;
    double direction_y = dy / distance;
    double overlap = get_radius() + p->get_radius() - distance;

    if (overlap > 0) {
        double correction_x = direction_x * overlap;
        double correction_y = direction_y * overlap;
        set_x(get_x() - correction_x * (get_mass() / (get_mass() + p->get_mass())));
        set_y(get_y() - correction_y * (get_mass() / (get_mass() + p->get_mass())));
        p->set_x(p->get_x() + correction_x * (p->get_mass() / (get_mass() + p->get_mass())));
        p->set_y(p->get_y() + correction_y * (p->get_mass() / (get_mass() + p->get_mass())));

        double normal_x = direction_x;
        double normal_y = direction_y;
        double vx1 = get_vx();
        double vy1 = get_vy();
        double vx2 = p->get_vx();
        double vy2 = p->get_vy();
        double m1 = get_mass();
        double m2 = p->get_mass();

        double v1n = vx1 * normal_x + vy1 * normal_y;
        double v2n = vx2 * normal_x + vy2 * normal_y;
        double v1nAfter = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
        double v2nAfter = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);
        set_vx(vx1 + (v1nAfter - v1n) * normal_x);
        set_vy(vy1 + (v1nAfter - v1n) * normal_y);
        p->set_vx(vx2 + (v2nAfter - v2n) * normal_x);
        p->set_vy(vy2 + (v2nAfter - v2n) * normal_y);
    }
}

void Particle::update_position(double dt) {
    x += vx * dt;
    y += vy * dt;
    check_handle_wall_collision();    
}



