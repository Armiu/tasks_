#include "graphics.hpp"
void callback_timeout(void* s);

void add_callback(Fl_Widget* butt, void* s) {
    (void) butt;
    Fl_Window *adder = new Fl_Window(450,150 , "Выберите тип частицы");
    Fl_Button *light = new Fl_Button(50, 40, 150, 75, "Лёгкая частица");
    light->callback(add_particle_l, s);
    Fl_Button *heavy = new Fl_Button(250, 40, 150, 75, "Тяжёлая частица");
    heavy->callback(add_particle_h, s);

    adder->show();
    Fl::run();
}

void remove_callback(Fl_Widget* butt, void* s) {
    (void) butt;
    Fl_Window *adder = new Fl_Window(450,150 , "Выберите тип частицы");
    Fl_Button *light = new Fl_Button(50, 40, 150, 75, "Лёгкая частица");
    light->callback(delete_particle_l, s);
    Fl_Button *heavy = new Fl_Button(250, 40, 150, 75, "Тяжёлая частица");
    heavy->callback(delete_particle_h, s);

    adder->show();
    Fl::run();
}

void step_callback(Fl_Widget* butt, void* s) {
    (void) butt;
    System* system = (System*)s;
    SimulationWindow* window = system->get_window(); 
    const char* input_text = window->get_input_value();
    if (strlen(input_text) == 0) {
        return;
    }

    Fl_Window* dialog = new Fl_Window(720, 200, "Dialog");
    Fl_Box* box = new Fl_Box(10, 40, 700, 100, "Дальше будут мигать частицы, эпилептикам быть осторожнее!");
    box->box(FL_UP_BOX);
    box->color(FL_WHITE);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labelsize(20);

    Fl_Button* continueButton = new Fl_Button(290, 150, 130, 30, "Продолжить");
    continueButton->color(FL_WHITE);
    continueButton->labelsize(20);
    continueButton->callback([](Fl_Widget* w, void* v) { (void) w; Fl_Window* win = (Fl_Window*)v; win->hide();}, dialog);
    dialog->end();
    dialog->show();

    while (dialog->shown()) Fl::wait();

    delete continueButton;
    delete box;
    delete dialog;

    system->set_num_steps();
    Fl::add_timeout(0.5, ::callback_timeout, s); 
}

void SimulationWindow::set_value() {
    const char* input_text = input->value();
    num_steps = std::stoi(input_text);
}

int& SimulationWindow::get_value() {
    return num_steps;
}

int SimulationWindow::get_num_steps() {
    return std::stoi(input->value());
}

const char* SimulationWindow::get_input_value() {
    return input->value();
}

void SimulationWindow::erase() {
    input->value("");
}

void callback_timeout(void* sys){
    ((System*)sys)->step();
    --((System*)sys)->get_num_steps();
    if(((System*)sys)->get_num_steps()) {
        Fl::repeat_timeout(0.05, callback_timeout, sys);
    }
    else {
        ((System*)sys)->erase();
    }
}

void add_particle_l(Fl_Widget* butt, void* s) {
    (void) butt;
    ((System*)s)->addParticle_l();
}
void add_particle_h(Fl_Widget* butt, void* s) {
    (void) butt;
    ((System*)s)->addParticle_h();
}
void delete_particle_l(Fl_Widget* butt, void* s) {
    (void) butt;
    ((System*)s)->delete_particle_l();
}
void delete_particle_h(Fl_Widget* butt, void* s) {
    (void) butt;
    ((System*)s)->delete_particle_h();
}

SimulationWindow::SimulationWindow(int width, int height, const char* title)
    : Fl_Window(width, height, title) {
    addButton = new Fl_Button(210, 30, 140, 30, "Добавить частицу");
    addButton->color(FL_WHITE);
    stepButton = new Fl_Button(50, 30, 140, 30, "Сделать шаги");
    stepButton->color(FL_WHITE);
    removeButton = new Fl_Button(370, 30, 140, 30, "Удалить частицу");
    removeButton->color(FL_WHITE);
    input = new Fl_Int_Input(530, 30, 140, 30);
}

void SimulationWindow::set_sys(System* s) {
    system = s;
    addButton->callback(add_callback, system);
    stepButton->callback(step_callback, system);
    removeButton->callback(remove_callback, system); 
}

void SimulationWindow::draw() {
    Fl_Window::draw();
    fl_color(FL_BLACK); 
    fl_rect(50, 80, 1050, 720); 
    fl_color(FL_WHITE);
    fl_rectf(51, 81, 1048, 718);
    system->draw();
    Fl::check();
}

SimulationWindow::~SimulationWindow() {
    delete addButton;
    delete stepButton;
    delete removeButton;
    delete input;
}
