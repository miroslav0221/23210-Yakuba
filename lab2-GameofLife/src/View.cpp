#include <iostream>
#include "View.h"
#include "Model.h"

View::View(Model & new_model) : model(new_model) {};


void View::image_field() {
    //std::cout<< this->model.get_name_universe() << std::endl;
    for (size_t i = 0; i < model.get_height(); i++) {
        for (size_t j = 0; j < model.get_weight(); j++) {
            if (model.get_field()[i][j] == Model::alive) {
                std::cout << '0';
                continue;
            }
            std::cout << '#';
        }
        std::cout << std::endl;
    }
}