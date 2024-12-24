#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <Field.h>
class Model {

private:
    Field & field_;
    std::array<int, 9> count_for_survive;
    std::array<int, 9> count_for_born;
    std::string name_universe;

public:
    explicit Model(Field & field);

    void change_name_universe(const std::string & new_name_universe);

    void change_rules(const std::array<int, 9> & born, const std::array<int, 9> & survive);


    // std::pair<std::vector<size_t>, std::vector<size_t>> get_rules();

    std::array<int, 9> get_born();

    std::array<int, 9> get_survive();

    std::string & get_name_universe();

    Field & get_field() const;

    int calc_alive_cells(int i, int j) const;

    void evolution_world();

};

#endif