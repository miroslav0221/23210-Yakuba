#include "Model.h"
#include <iostream>

void Model::change_name_universe(const std::string & new_name_universe) {
    this->name_universe = new_name_universe;
}

void Model::change_rules(const std::vector<size_t> & born, const std::vector<size_t> & survive ) {
    (this->count_for_born) = born;
    (this->count_for_survive) = survive;
}

void Model::change_size(const size_t & weight, const size_t & height) {
    (this->weight) = weight;
    (this->height) = height;
}

void Model::add_life_cell(int x, int y) {
    (this->field)[x][y] = true;
}

void Model::init_field() {
    std::vector<std::vector<bool>> field_new(height, std::vector<bool>(weight, false));
    this->field = field_new;
}

size_t & Model::get_weight() {
    return this->weight;
}

size_t & Model::get_height() {
    return this->height;
}

std::vector<std::vector<bool>> & Model::get_field() {
    return this->field;
}