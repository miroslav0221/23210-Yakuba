#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"


class Controller {
private:
    Model & model;
public:
    explicit Controller(Model & model_new);
    //~Controller();
    void read_file(const std::string & filename);
    void write_file();
};
#endif