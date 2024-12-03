#ifndef FIELD_H
#define FIELD_H
#include <iostream>
class Field {
public:
    enum field_cells {
        alive,
        die
    };
private:
    size_t weight;
    size_t height;
    std::vector<std::vector<field_cells>> field;
public:
    Field();

    void change_size(const size_t & weight_new, const size_t & height_new);

    void init_field();

    void change_field(const std::vector<std::vector<field_cells>> & new_field);

    void add_life_cell(int x, int y);

    size_t & get_weight();

    size_t & get_height();

    std::vector<std::vector<field_cells>> & get_field();

};


#endif
