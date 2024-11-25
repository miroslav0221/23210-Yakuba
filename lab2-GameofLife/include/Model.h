#ifndef MODEL_H
#define MODEL_H
#include <iostream>

class Model {
private:
    size_t weight;
    size_t height;
    std::vector<size_t> count_for_survive;
    std::vector<size_t> count_for_born;
    std::vector<std::vector<bool>> field;
    std::string name_universe;

public:

    void change_name_universe(const std::string & new_name_universe);

    void change_rules(const std::vector<size_t> & born, const std::vector<size_t> & survive);

    void change_size(const size_t & weight, const size_t & height);

    void init_field();

    void add_life_cell(int x, int y);

    size_t & get_weight();

    size_t & get_height();

    std::vector<std::vector<bool>> & get_field();

};

#endif