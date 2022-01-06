#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "main.h"
#include "Cell.h"


class Field {

public:
    enum class State { LOST, BASIC, HP, WON };

    Field(int rows, int cols);

    Cell *get_cell(int row, int col);

    void flag(int row, int col);
    void dig(int row, int col);
    void display(sf::RenderWindow &window);

private:
    std::vector<Cell> matrix;  // matrix_i,j = matrix[i*COLUMNS+j]
    State state;

    bool first_digging;
    int discovered;

    void init_mines(int row, int col);
    bool surroundings(int row, int col, int random_row, int random_col);
    void init_mines_around();

    void cout_func();

};
