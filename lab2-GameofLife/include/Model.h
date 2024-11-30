#ifndef MODEL_H
#define MODEL_H
#include <iostream>



class Model {
public:
    enum field_cells {
        alive,
        die
    };
private:
    size_t  weight;
    size_t  height;
    std::vector<size_t> count_for_survive;
    std::vector<size_t> count_for_born;
    std::vector<std::vector<field_cells>> field;
    std::string name_universe;

public:

    void change_name_universe(const std::string & new_name_universe);

    void change_rules(const std::vector<size_t> & born, const std::vector<size_t> & survive);

    void change_size(const size_t & weight_new, const size_t & height_new);

    void init_field();

    void change_field(const std::vector<std::vector<field_cells>> & new_field);

    void add_life_cell(int x, int y);

    std::pair<std::vector<size_t>, std::vector<size_t>> get_rules();

    size_t & get_weight();

    size_t & get_height();

    std::string & get_name_universe();

    std::vector<std::vector<field_cells>> & get_field();

};

#endif