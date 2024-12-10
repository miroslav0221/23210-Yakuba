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

int Model::calc_alive_cells(int i, int j) const{
    int count_alive_cells = 0;
    Field field = get_field();
    size_t height = field.get_height();
    size_t weight = field.get_weight();

    const int shift_j[] {-1, -1, -1, 0, 0, 1, 1, 1};
    const int shift_i[] {1, 0, -1, 1, -1, 1, 0, -1};
    for (int k = 0; k < 8; k++) {
        const size_t new_i = (i + shift_i[k] + height) % height;
        const size_t new_j = (j + shift_j[k] + weight) % weight;
        if (field.get_cell(static_cast<int>(new_i),
            static_cast<int>(new_j)) == Field::alive) {
            count_alive_cells++;
            }
    }
    return count_alive_cells;
}


void Model::evolution_world() {
    std::vector<size_t> born = get_rules().first;
    std::vector<size_t> survive = get_rules().second;
    Field & field = get_field();
    const size_t weight = field.get_weight();
    const size_t height = field.get_height();

    int count_alive_cells = 0;
    std::vector<Field::field_cells> field_new(height*weight, Field::die);
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < weight; ++j) {
            const Field::field_cells status = field.get_cell(j, i);
            count_alive_cells = calc_alive_cells(i, j);
            if (status == Field::die and std::find(begin(born),
                end(born), count_alive_cells) != end(born)) {
                field_new[i*weight + j] = Field::alive;
                continue;
                } // born
            if (status == Field::alive) {
                if (std::find(begin(survive),
                end(survive), count_alive_cells) != end(survive)) {
                    field_new[i*weight + j] = Field::alive;
                    continue;
                }
                field_new[i*weight + j] = Field::die;
            } // survive
        }
    }
    field.change_field(field_new);
    //view.image_field();
    //std::cout << "----------" << std::endl;
}
