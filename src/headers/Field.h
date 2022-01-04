#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "main.h"
#include "Cell.h"


class Field {

public:
    enum class State { LOST, BASIC, HP, WON };

    Field(int rows, int cols);

    void display(sf::RenderWindow &window);

private:
    std::vector<Cell> matrix;  // matrix_i,j = matrix[i*COLUMNS+j]
    State state;

};
