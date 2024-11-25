#include "Controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Controller::Controller(Model & model_new) : model(model_new) {};

std::vector<size_t> convert_born(const std::string & str_born) {
    std::vector<size_t> born;
    for (auto number = str_born.begin(); number != str_born.end(); ++number) {
        born.push_back(static_cast<size_t>(*number) -
            static_cast<size_t>('0'));
    }
    return born;
}

std::vector<size_t> convert_survive(const std::string & str_survive) {
    std::vector<size_t> survive;
    for (auto number = str_survive.begin(); number != str_survive.end(); ++number) {
        survive.push_back(static_cast<size_t>(*number) -
            static_cast<size_t>('0'));
    }
    return survive;
}


void Controller::read_file(const std::string & filename) {
    std::fstream fs;
    fs.open(filename);
    std::string current_str;
    int count_str = 0;
    if (fs.is_open()) {
        while(std::getline(fs, current_str)) {
            count_str++;
            int index_1 = 0, index_2 = 0, weight = 0, height = 0;

            switch (count_str) {
                case 1:
                    if (current_str.find("#Life") == std::string::npos) {
                        throw std::invalid_argument("Неверный формат файла. Файл должен быть формы .life");
                    }
                    break;

                case 2:
                    index_1 = static_cast<int>(current_str.find("#N"));
                    if (index_1 == std::string::npos) {
                        std::cout << "-----------------------" << std::endl
                                  << "Нет названия вселенной" << std::endl
                                  << "-----------------------" << std::endl;
                    }
                    {
                        const std::string name_universe = current_str.substr(index_1 + 2);
                        (this->model).change_name_universe(name_universe);
                    }
                    break;

                case 3:
                    index_1 = static_cast<int>(current_str.find('B'));
                    index_2 = static_cast<int>(current_str.find('S'));
                    {
                        const std::string str_born = current_str.substr(index_1 + 1, index_2 - 1 - index_1);
                        const std::string str_survive = current_str.substr(index_2);
                        auto born = convert_born(str_born);
                        auto survive = convert_born(str_survive);

                        (this->model).change_rules(born, survive);
                    }
                    break;

                case 4:
                    index_1 = static_cast<int>(current_str.find('W'));
                    index_2 = static_cast<int>(current_str.find('H'));
                    {
                        const std::string str_height = current_str.substr(index_2 + 1, index_1 - 2 - index_2);
                        const std::string str_weight = current_str.substr(index_1 + 1);
                        height = std::stoi(str_height);
                        weight = std::stoi(str_weight);
                        (this->model).change_size(weight, height);
                        (this->model).init_field();
                    }
                    break;

                default:
                    int x, y;
                    std::istringstream stream(current_str);
                    stream >> x >> y;
                    if (x >= this->model.get_weight()) {
                        break;
                    }
                    if (x < 0) {
                        x = (x + weight) % weight;
                    }
                    if (y >= this->model.get_height()) {
                        break;
                    }
                    if (y < 0) {
                        y = (y + height) % height;
                    }
                    (this->model).add_life_cell(x, y);
                    break;
            }

        }
    }
    else {
        std::cout << "Не удалось открыть файл" << std::endl;
    }
}
