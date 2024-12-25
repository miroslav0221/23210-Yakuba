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
    std::vector<field_cells> field;
public:
    Field();

    void set_size(const size_t & weight, const size_t & height);

    void init_field();

    void change_field(const std::vector<field_cells> & new_field);

    void set_cell(int x, int y, field_cells);

    Field::field_cells get_cell(int x, int y) const;

    size_t & get_weight();

    size_t & get_height();
};


#endif
