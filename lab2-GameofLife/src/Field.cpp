#include "Field.h"
#include <iostream>

Field::Field() : weight(0),height(0) {};

void Field::change_size(const size_t & weight_new, const size_t & height_new) {
    weight = weight_new;
    height = height_new;
}

void Field::add_life_cell(int x, int y) {
    field[x][y] = alive;
}

void Field::init_field() {
    std::vector<std::vector<field_cells>> field_new(height, std::vector<field_cells>(weight, die));
    field = field_new;
}

size_t & Field::get_weight() {
    return weight;
}

size_t & Field::get_height() {
    return height;
}

std::vector<std::vector<Field::field_cells>> & Field::get_field() {
    return field;
}

void Field::change_field(const std::vector<std::vector<field_cells> > & new_field) {
    field = new_field;
}