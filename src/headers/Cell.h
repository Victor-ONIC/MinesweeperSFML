#pragma once
#include <SFML/Graphics.hpp>

class Cell {

public:
    enum class State { BASE, DUG, MINE, FLAG, BOOM };

    Cell(int row, int col);

    sf::Vector2i get_position();
    State get_state();

    void set_state(State state);

private:
    sf::Vector2i position;
    State state;

};
