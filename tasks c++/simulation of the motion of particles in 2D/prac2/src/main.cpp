#include "graphics.hpp"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <seed> <light_particles> <heavy_particles>\n";
        return 1;
    }

    int seed = std::stoi(argv[1]);
    int light_particles = std::stoi(argv[2]);
    int heavy_particles = std::stoi(argv[3]);

    SimulationWindow *win = new SimulationWindow(1120, 820, "Simulation");
    System* system = new System(seed, light_particles, heavy_particles, win);
   
    win->set_sys(system);
    win->show();
    return Fl::run();

}
