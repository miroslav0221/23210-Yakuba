#include "Controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Model.h>

void help() {
    std::cout << "Функционал игры:" << std::endl <<
        "1. dump <filename> - сохранить вселенную в файл \n"
        "2. tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат. \n"
        "3. exit – завершить игру \n"
        "4. help – распечатать справку о командах" << std::endl;
}

Controller::Controller(Model & model_new, View & view_new) : model(model_new), view(view_new) {};

std::vector<size_t> convert_str_to_vector(const std::string & str) {
    std::vector<size_t> vector;
    for (const char number : str) {
        vector.push_back(static_cast<size_t>(number) -
            static_cast<size_t>('0'));
    }
    return vector;
}


void Controller::read_file(const std::string & filename) const {
    std::fstream fs;
    fs.open(filename);
    if (!fs.is_open()) {
        throw std::ios_base::failure("Не удалось открыть файл: " + filename);
    }
    std::string current_str;
    int count_str = 0;
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
        if(count_str == 2) {
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
                model.change_size(weight, height);
                model.init_field();
            }
            continue;
        }
        int x, y;
        std::istringstream stream(current_str);
        stream >> x >> y;
        if (x >= model.get_weight()) {
            continue;
        }
        if (x < 0) {
            x = (x + weight) % weight;
        }
        if (y >= model.get_height()) {
            continue;;
        }
        if (y < 0) {
            y = (y + height) % height;
        }
        model.add_life_cell(x, y);
    }
}

void Controller::write_file(const std::string & filename) const {
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
    fs << model.get_height() << "/W" << model.get_weight() << '\n';
    std::vector<std::vector<Model::field_cells>> field = model.get_field();
    for (size_t i = 0; i < model.get_weight(); i++) {
        for (size_t j = 0; j < model.get_height(); j++) {
            if (field[i][j] == Model::alive) {
                fs << i << ' ' << j << '\n';
            }
        }
    }
}

int calc_alive_cells(const size_t i, const size_t j, const size_t weight, const size_t height,
                     const std::vector<std::vector<Model::field_cells>> & field) {
    int count_alive_cells = 0;
    constexpr int shift_j[] {-1, -1, -1, 0, 0, 1, 1, 1};
    constexpr int shift_i[] {1, 0, -1, 1, -1, 1, 0, -1};
    for (int k = 0; k < 8; k++) {
        const size_t new_i = (i + shift_i[k] + height) % height;
        const size_t new_j = (j + shift_j[k] + weight) % weight;
        if (field[new_i][new_j] == Model::alive) {
            count_alive_cells++;
        }
    }
    return count_alive_cells;
}

void Controller::change_field_by_rules(const int count_tick) const {
    std::vector<size_t> born = model.get_rules().first;
    std::vector<size_t> survive = model.get_rules().second;

    const size_t weight = model.get_weight();
    const size_t height = model.get_height();
    std::vector<std::vector<Model::field_cells>> current_field = model.get_field();

    int count_alive_cells = 0;
    for (int tick = 0; tick < count_tick; tick++) {
        std::vector field_new(height,
        std::vector(weight, Model::die));
        for(size_t i = 0; i < height; ++i) {
            for(size_t j = 0; j < weight; ++j) {
                const Model::field_cells status = current_field[i][j];
                count_alive_cells = calc_alive_cells(i, j, weight, height, current_field);
                if (status == Model::die and std::find(begin(born),
                    end(born), count_alive_cells) != end(born)) {
                    field_new[i][j] = Model::alive;
                    continue;
                    } // born
                if (status == Model::alive) {
                    if (std::find(begin(survive),
                    end(survive), count_alive_cells) != end(survive)) {
                        field_new[i][j] = Model::alive;
                        continue;
                    }
                    field_new[i][j] = Model::die;
                } // survive
            }
        }
        current_field = field_new;
        model.change_field(current_field);
        view.image_field();
        std::cout << "----------" << std::endl;
    }

}

void Controller::offline_mode(int count_iter, const std::string & out_file) const {
    change_field_by_rules(count_iter);
    write_file(out_file);

}

void Controller::play() const {
    help();
    while(true) {
        std::string answer;
        std::cout << "Команда: " << std::endl;
        std::getline(std::cin, answer);
        std::string count_ticks_str;
        int count_ticks = 1;
        auto res = answer.find("t ");
        if (res != std::string::npos) {
            count_ticks_str = answer.substr(res + 2);
            if (!count_ticks_str.empty()) {
                count_ticks = std::stoi(count_ticks_str);;
            }
            change_field_by_rules(count_ticks);
            continue;
        }
        auto res_ = answer.find("tick");
        if (res_ != std::string::npos) {
            count_ticks_str = answer.substr(res + 5);
            if (!count_ticks_str.empty()) {
                count_ticks = std::stoi(count_ticks_str);;
            }
            change_field_by_rules(count_ticks);
            continue;
        }

        res = answer.find("dump");
        if (res != std::string::npos) {
            std::string name_out_file = answer.substr(res + 5);
            if (name_out_file.empty()) {
                name_out_file = "output.life";
            }
            write_file(name_out_file);
            continue;
        }
        if (answer == "exit") {
            return;
        }
        if (answer == "help") {
            help();
            continue;
        }
        std::cout << "Нет такой команды. Введите команду "
                            "help для просмотра списка команд" << std::endl;
        help();
    }
}