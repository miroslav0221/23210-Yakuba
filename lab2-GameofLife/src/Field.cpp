#include "Field.h"
#include <iostream>

Field::Field() : weight(0),height(0) {};

void Field::set_size(const size_t & weight_, const size_t & height_) {
    weight = weight_;
    height = height_;
}


void Field::set_cell(int x, int y, field_cells status) {
    field[(y * weight + x) % (weight*height) ] = status;
}

void Field::init_field() {
    std::vector<field_cells> field_(height*weight, die);
    field = field_;
}

Field::field_cells Field::get_cell(int x, int y) const {
    return field[(y * weight + x) % (weight*height)];
}


size_t & Field::get_weight() {
    return weight;
}

size_t & Field::get_height() {
    return height;
}


void Field::change_field(const std::vector<Field::field_cells> & new_field) {
    field = new_field;
}