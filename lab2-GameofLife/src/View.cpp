#include <iostream>
#include "View.h"
#include "Model.h"
#include "Field.h"
View::View(Model & new_model) : model(new_model) {};


void View::image_field() const {
    Field field = model.get_field();
    const size_t height = field.get_height();
    const size_t weight = field.get_weight();
    std::vector<std::vector<Field::field_cells>> field_current = field.get_field();

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < weight; j++) {
            if (field_current[i][j] == Field::alive) {
                std::cout << '0';
                continue;
            }
            std::cout << '#';
        }
        std::cout << std::endl;
    }
}

