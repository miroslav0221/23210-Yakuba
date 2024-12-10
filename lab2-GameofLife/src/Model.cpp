#include "Model.h"
#include <iostream>

Model::Model(Field & field) : field_(field) {};

Field & Model::get_field() const{
    return field_;
}

void Model::change_name_universe(const std::string & new_name_universe) {
    name_universe = new_name_universe;
}

void Model::change_rules(const std::vector<size_t> & born, const std::vector<size_t> & survive ) {
    count_for_born = born;
    count_for_survive = survive;
}



std::string & Model::get_name_universe() {
    return name_universe;
}

std::pair<std::vector<size_t>, std::vector<size_t>>  Model::get_rules() {
    std::pair<std::vector<size_t>, std::vector<size_t>> rules(count_for_born, count_for_survive);
    return rules;
}
