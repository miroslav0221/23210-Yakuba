#include <iostream>
#include "View.h"


View::View(Model & new_model) : model(new_model) {};


void View::image_field() {
    for (size_t i = 0; i < this->model.get_weight(); i++) {
        for (size_t j = 0; j < this->model.get_height(); j++) {
            if ((this->model.get_field())[i][j]) {
                std::cout << '0';
                continue;
            }
            std::cout << '#';
        }
        std::cout << std::endl;
    }
}
