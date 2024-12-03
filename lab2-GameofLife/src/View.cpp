#include <iostream>
#include "View.h"
#include "Model.h"
#include "Field.h"
View::View(Model & new_model) : model(new_model) {};


void View::image_field() const {
    Field field = model.get_field();
    const size_t height = field.get_height();
    const size_t weight = field.get_weight();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < weight; j++) {
            if (field.get_field()[i][j] == Field::alive) {
                std::cout << '0';
                continue;
            }
            std::cout << '#';
        }
        std::cout << std::endl;
    }
}
// #include <SFML/Graphics.hpp>
// #include "View.h"
// #include "Model.h"

// const int CELL_SIZE = 20;  // Размер одной клетки на экране в пикселях
//
// View::View(Model &new_model) : model(new_model) {}
//
// // Метод для отображения игрового поля с использованием SFML
// void View::image_field() const {
//     // Определяем размеры окна в зависимости от размеров поля
//     unsigned int window_width = model.get_weight() * CELL_SIZE;
//     unsigned int window_height = model.get_height() * CELL_SIZE;
//
//     // Создаем окно с нужными размерами
//     sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Game of Life");
//
//     // Главный цикл окна
//     while (window.isOpen()) {
//         sf::Event event;  // Инициализация события
//         // Обрабатываем события окна (например, закрытие)
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();  // Закрытие окна при событии закрытия
//             }
//         }
//
//         // Очищаем экран перед отрисовкой следующего кадра
//         window.clear(sf::Color::Black);
//
//         // Рисуем игровое поле
//         for (size_t i = 0; i < model.get_height(); i++) {
//             for (size_t j = 0; j < model.get_weight(); j++) {
//                 // Создаем квадрат для каждой клетки
//                 sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));  // -1 для отступов между клетками
//                 cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);  // Позиционируем клетку
//
//                 // Устанавливаем цвет клетки в зависимости от её состояния
//                 if (model.get_field()[i][j] == Model::alive) {
//                     cell.setFillColor(sf::Color::Green);  // Живая клетка — зеленая
//                 } else {
//                     cell.setFillColor(sf::Color::White);  // Мертвая клетка — белая
//                 }
//
//                 // Рисуем клетку на экране
//                 window.draw(cell);
//             }
//         }
//
//         // Отображаем все нарисованные клетки на экране
//         window.display();
//     }
// }

