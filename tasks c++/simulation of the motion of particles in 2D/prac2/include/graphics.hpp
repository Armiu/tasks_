#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <vector>
#include <FL/Fl_Int_Input.H>
#include <FL/fl_draw.H>
#include <cmath>
#include <FL/Fl_Box.H>
#include "system.hpp"

class System;
class SimulationWindow : public Fl_Window {
public:
    SimulationWindow(int width, int height, const char* title);
    void set_sys(System* s);
    void draw();
    ~SimulationWindow();

    void erase();
    void set_value();
    int& get_value();
    int get_num_steps();
    const char* get_input_value();
private:
    System* system;
    int num_steps;
    Fl_Box* box; 
    Fl_Int_Input* input;
    Fl_Button* addButton;
    Fl_Button* stepButton;
    Fl_Button* removeButton;
};

void add_callback(Fl_Widget* butt, void* s);
void remove_callback(Fl_Widget* butt, void* s);
void step_callback(Fl_Widget* butt, void* s);

void add_particle_l(Fl_Widget* butt, void* s);
void add_particle_h(Fl_Widget* butt, void* s);
void delete_particle_l(Fl_Widget* butt, void* s);
void delete_particle_h(Fl_Widget* butt, void* s);
#endif // GRAPHICS_HPP
