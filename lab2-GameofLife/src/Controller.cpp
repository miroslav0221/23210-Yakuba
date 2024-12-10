#include "Controller.h"
#include "Handler_file.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Model.h>

void help() {
    std::cout << "Функционал игры:" << std::endl <<
        "1. dump <filename> - сохранить вселенную в файл \n"
        "2. tick <n=1> (и сокращенно t <n=1>) - рассчитать n (по умолчанию 1) итераций и напечатать результат. \n"
        "3. exit – завершить игру \n"
        "4. help – распечатать справку о командах" << std::endl;
}

Controller::Controller(Model & model_, View & view_new) : model(model_),
view(view_new) {};



void Controller::write_file(const std::string & filename) const {
    Handler_file handler(model);
    handler.write_file(filename);
}

void Controller::change_field_by_rules(int count_tick) const {
    for (int i = 0; i < count_tick; i++) {
        model.evolution_world();
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