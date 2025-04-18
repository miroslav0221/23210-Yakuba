#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "View.h"
#include "Handler_file.h"
class Controller {
private:
    Model & model;
    View & view;
public:
    Controller(Model & model_new, View & view);

   // void read_file(const std::string & filename) const;

    void write_file(const std::string & filename) const;

    void change_field_by_rules(int count_tick) const;

    void offline_mode(int count_iter, const std::string & out_file) const;

    void play() const;

    int calc_alive_cells(size_t i, size_t j) const;
};
#endif