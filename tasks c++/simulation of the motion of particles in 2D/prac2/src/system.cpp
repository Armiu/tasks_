#include "system.hpp"

System::System(const System& other)
    : start_l(other.start_l), start_h(other.start_h), window(other.window)
{
    for (Particle* particle : other.particles) {
        if (LightParticle* lp = dynamic_cast<LightParticle*>(particle)) {
            particles.push_back(new LightParticle(*lp));
        } else if (HeavyParticle* hp = dynamic_cast<HeavyParticle*>(particle)) {
            particles.push_back(new HeavyParticle(*hp));
        }
    }
}

void System::draw() {
    for(int i = 0; i < get_amount();++i)
    {    
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        double x = get_particle(i)->get_x();
        double y = get_particle(i)->get_y();
        double radius = get_particle(i)->get_radius();
        if(dynamic_cast<LightParticle*>(get_particle(i))) {
            Fl::set_color(FL_FREE_COLOR, 206, 172, 240);
            fl_color(FL_FREE_COLOR);
        } 
        else {
            fl_color(dis(gen), dis(gen), dis(gen));
        }
        fl_pie(x - radius, y - radius, 2 * radius, 2 * radius, 0.0, 360.0);
    }
}

System& System::operator=(const System& other) {
    if (this != &other) { 
        
        for (Particle* particle : particles) {
            delete particle;
        }
        particles.clear(); 

        start_l = other.start_l;
        start_h = other.start_h;
        window = other.window;

        for (Particle* particle : other.particles) {
            if (LightParticle* lp = dynamic_cast<LightParticle*>(particle)) {
                particles.push_back(new LightParticle(*lp));
            } else if (HeavyParticle* hp = dynamic_cast<HeavyParticle*>(particle)) {
                particles.push_back(new HeavyParticle(*hp));
            }
        }
    }

    return *this;
}
int& System::get_num_steps() {
    return window->get_value();
}
void System::set_num_steps() {
    return window->set_value();
}

void System::addParticle_l() {
    bool isOverlapping;
    Particle* newParticle;

    do {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        newParticle = new LightParticle(static_cast<int>(seed), window);

        isOverlapping = is_overlap(newParticle, particles.size());
        if (isOverlapping) {
            delete newParticle;
        }
    } while (isOverlapping);

    particles.push_back(newParticle);
    window->redraw();
}

void System::addParticle_h() {
    bool isOverlapping;
    Particle* newParticle;

    do {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        newParticle = new HeavyParticle(static_cast<int>(seed), window);

        isOverlapping = is_overlap(newParticle, particles.size());
        if (isOverlapping) {
            delete newParticle;
        }
    } while (isOverlapping);

    particles.push_back(newParticle);
    window->redraw();
}

void System::delete_particle_l() {
    for (int i = particles.size() - 1; i >= 0; --i) {
        LightParticle* lp = dynamic_cast<LightParticle*>(particles[i]);
        if (lp != nullptr) {
            Particle* a = particles[i];
            particles.erase(particles.begin() + i);
            delete a;
            window->redraw();
            break;
        }
    }
}
void System::delete_particle_h() {
    for (int i = particles.size() - 1; i >= 0; --i) {
        HeavyParticle* lp = dynamic_cast<HeavyParticle*>(particles[i]);
        if (lp != nullptr) {
            Particle* a = particles[i];
            particles.erase(particles.begin() + i);
            delete a;
            window->redraw();
            break;
        }
    }
}

Particle* System::get_overlapping_particle(Particle* particle, std::vector<Particle*>::size_type index) {
    for (std::vector<Particle*>::size_type i = 0; i < particles.size(); ++i) {
        if (i != index) {
            Particle* otherParticle = particles[i];
            double dx = particle->get_x() - otherParticle->get_x();
            double dy = particle->get_y() - otherParticle->get_y();
            double distance = sqrt(dx*dx + dy*dy);
            if (distance < particle->get_radius() + otherParticle->get_radius()) {
                return otherParticle;
            }
        }
    }
    return nullptr;
}


System::System(int seed, int num_l_particles, int num_h_particles, SimulationWindow* win):start_l(num_l_particles), start_h(num_h_particles), window(win){
 
    for (int i = 0; i < num_l_particles; ++i)
    {
        particles.push_back(new LightParticle((seed+i*100), win));
        int f = 0;
        while(is_overlap(particles[particles.size()-1], particles.size()-1)){
            Particle* overlappingParticle = get_overlapping_particle(particles[particles.size()-1], particles.size()-1);

            double dx = particles[particles.size()-1]->get_x() - overlappingParticle->get_x();
            double dy = particles[particles.size()-1]->get_y() - overlappingParticle->get_y();
            double distance = sqrt(dx*dx + dy*dy);
            double moveDistance = particles[particles.size()-1]->get_radius() + overlappingParticle->get_radius() - distance + 1; // Add 1 to ensure they are not touching

            double moveDirectionX = dx / distance;
            double moveDirectionY = dy / distance;

            particles[particles.size()-1]->set_x(particles[particles.size()-1]->get_x() +  moveDirectionX * moveDistance);
            particles[particles.size()-1]->set_y(particles[particles.size()-1]->get_y() +  moveDirectionY * moveDistance);

            f++;
        }
    }
    
    for (int i = 0; i < num_h_particles; ++i)
    {
        particles.push_back(new HeavyParticle((seed+i*100), win));
        int f = 0;
        while(is_overlap(particles[particles.size()-1], particles.size()-1)){
            Particle* overlappingParticle = get_overlapping_particle(particles[particles.size()-1], particles.size()-1);

            double dx = particles[particles.size()-1]->get_x() - overlappingParticle->get_x();
            double dy = particles[particles.size()-1]->get_y() - overlappingParticle->get_y();
            double distance = sqrt(dx*dx + dy*dy);
            double moveDistance = particles[particles.size()-1]->get_radius() + overlappingParticle->get_radius() - distance + 1; // Add 1 to ensure they are not touching

            double moveDirectionX = dx / distance;
            double moveDirectionY = dy / distance;

            particles[particles.size()-1]->set_x(particles[particles.size()-1]->get_x() +  moveDirectionX * moveDistance);
            particles[particles.size()-1]->set_y(particles[particles.size()-1]->get_y() +  moveDirectionY * moveDistance);

            f++;
        }
    }
    window->show();
}

void System::step() {
    for (auto it = particles.begin(); it != particles.end(); ++it) {
        (*it)->update_position(0.05);
        for (auto other = std::next(it); other != particles.end(); ++other) {
            if ((*it)->check_collision(*other)) {
                (*it)->handle_collision(*other);
            }
        }
    }
    window->redraw();
}

void System::erase() {
    window->erase();
}

bool System::is_overlap(const Particle* new_particle, int index) {
    for (int i = 0; i < index; ++i) {
        if (particles[i]->distance_to(new_particle) < (particles[i]->get_radius() + new_particle->get_radius())) {
            return true;
        }
    }
    return false;
}

Particle* System::get_particle(std::vector<Particle*>::size_type n) {
    if (n < particles.size()) {
        return particles[n];
    } else {
        return nullptr;
    }
}
int System::get_amount() {
    return particles.size();
}

SimulationWindow* System::get_window() {
    return window;
}

System::~System() {
    for (Particle* p : particles) {
        delete p;
    }
}
