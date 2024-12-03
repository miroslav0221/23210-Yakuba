#include "Model.h"
#include <iostream>

Model::Model() : weight(0), height(0) {};


void Model::change_name_universe(const std::string & new_name_universe) {
    name_universe = new_name_universe;
}

void Model::change_rules(const std::vector<size_t> & born, const std::vector<size_t> & survive ) {
    count_for_born = born;
    count_for_survive = survive;
}

void Model::change_size(const size_t & weight_new, const size_t & height_new) {
    weight = weight_new;
    height = height_new;
}

void Model::add_life_cell(int x, int y) {
    field[x][y] = alive;
}

void Model::init_field() {
    std::vector<std::vector<field_cells>> field_new(height, std::vector<field_cells>(weight, die));
    field = field_new;
}

size_t & Model::get_weight() {
    return weight;
}

size_t & Model::get_height() {
    return height;
}

std::vector<std::vector<Model::field_cells>> & Model::get_field() {
    return field;
}

std::string & Model::get_name_universe() {
    return name_universe;
}

std::pair<std::vector<size_t>, std::vector<size_t>>  Model::get_rules() {
    std::pair<std::vector<size_t>, std::vector<size_t>> rules(count_for_born, count_for_survive);
    return rules;
}

void Model::change_field(const std::vector<std::vector<field_cells> > & new_field) {
    field = new_field;
}

