#include <iostream>
#include "View.h"
#include "Model.h"
#include "Field.h"

View::View(Model & new_model) : model(new_model) {};


void View::image_field() const {
    Field & field = model.get_field();
    const size_t height = field.get_height();
    const size_t weight = field.get_weight();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            if (field.get_cell(j, i) == Field::alive) {
                std::cout << '0';
                continue;
            }
            std::cout << '#';
        }
        std::cout << std::endl;
    }
    std::cout << "----------" << std::endl;
}

