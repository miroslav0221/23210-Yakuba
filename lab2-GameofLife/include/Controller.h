#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "View.h"

class Controller {
private:
    Model & model;
    View & view;
public:
    explicit Controller(Model & model_new, View & view);
    //~Controller();
    void read_file(const std::string & filename) const;
    void write_file(const std::string & filename);
    void change_field_by_rules(const int count_tick) const;
    void play();
};
#endif