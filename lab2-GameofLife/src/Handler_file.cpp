#include "Handler_file.h"
#include "Field.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

Handler_file::Handler_file(Model & model_) : model(model_) {}

std::vector<size_t> convert_str_to_vector(const std::string & str) {
    std::vector<size_t> vector;
    for (const char number : str) {
        vector.push_back(static_cast<size_t>(number) -
            static_cast<size_t>('0'));
    }
    return vector;
}

void Handler_file::read_file(const std::string & filename) const {
    std::fstream fs;
    fs.open(filename);
    if (!fs.is_open()) {
        throw std::ios_base::failure("Не удалось открыть файл: " + filename);
    }
    std::string current_str;
    int count_str = 0;
    Field & field = model.get_field();
    while(std::getline(fs, current_str)) {
        count_str++;
        int index_1 = 0, index_2 = 0, weight = 0, height = 0;
        std::string name_universe = "Standard name";
        if (count_str == 1) {
            if (current_str.find("#Life") == std::string::npos) {
                throw std::invalid_argument("Неверный формат файла. Файл должен быть формы .life");
            }
            continue;
        }
        if (count_str == 2) {
            index_1 = static_cast<int>(current_str.find("#N"));
            if (index_1 == std::string::npos) {
                std::cout << "-----------------------" << std::endl
                        << "Нет названия вселенной" << std::endl
                        << "-----------------------" << std::endl;
            }
            else {
                name_universe = current_str.substr(index_1 + 3);
            }
            model.change_name_universe(name_universe);
            continue;
        }
        if(count_str == 3) {
            index_1 = static_cast<int>(current_str.find('B'));
            index_2 = static_cast<int>(current_str.find('S'));
            {
                const std::string str_born = current_str.substr(index_1 + 1, index_2 - index_1 - 2);
                const std::string str_survive = current_str.substr(index_2 + 1);
                auto born = convert_str_to_vector(str_born);
                auto survive = convert_str_to_vector(str_survive);

                model.change_rules(born, survive);
            }
            continue;
        }
        if (count_str == 4) {
            index_1 = static_cast<int>(current_str.find('W'));
            index_2 = static_cast<int>(current_str.find('H'));
            {
                const std::string str_height = current_str.substr(index_2 + 1, index_1 - 2 - index_2);
                const std::string str_weight = current_str.substr(index_1 + 1);
                height = std::stoi(str_height);
                weight = std::stoi(str_weight);
                field.set_size(weight, height);
                field.init_field();
            }
            continue;
        }
        int x, y;
        std::istringstream stream(current_str);
        stream >> x >> y;
        if (x >= field.get_weight()) {
            continue;
        }
        if (x < 0) {
            x = (x + static_cast<int>(model.get_field().get_weight())) %
                static_cast<int>(model.get_field().get_weight());
        }
        if (y >= field.get_height()) {
            continue;;
        }
        if (y < 0) {
            y = (y + static_cast<int>(model.get_field().get_height())) %
                static_cast<int>(model.get_field().get_height());
        }
        field.set_cell(x, y, Field::alive);
    }
}

void Handler_file::write_file(const std::string & filename) const {
    std::fstream fs;
    fs.open(filename, std::ios::out | std::ios::trunc);
    if (!fs.is_open()) {
        throw std::ios_base::failure("Не удалось открыть файл.");
    }
    fs.write("#Life 1.06\n", 11);
    std::string name_universe = model.get_name_universe();
    fs.write("#N ", 3);
    fs.write(name_universe.c_str(), static_cast<int>(name_universe.length()));
    fs << '\n';
    fs.write("#R B", 4);
    std::pair<std::vector<size_t>, std::vector<size_t>> rules =
        model.get_rules();
    for (const size_t & num:rules.first) {
        fs << num;
    }
    fs << "/S";
    for (const size_t & num:rules.second) {
        fs << num;
    }
    fs << '\n';
    fs.write("#SIZE H", 7);
    Field & field = model.get_field();

    fs << field.get_height() << "/W" << field.get_weight() << '\n';
    for (int i = 0; i < field.get_height(); i++) {
        for (int j = 0; j < field.get_weight(); j++) {
            if (field.get_cell(j, i) == Field::alive) { //
                fs << j << ' ' << i << '\n';
            }
        }
    }
}