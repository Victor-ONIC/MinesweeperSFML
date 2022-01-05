#pragma once
#include <SFML/Graphics.hpp>

class Cell {

public:
    enum class State { BASE, DUG, MINE, FLAG };

    struct coord {
        int row;
        int col;
    };

    Cell(int row, int col);

    coord get_position() const;
    State get_state() const;
    int get_mines_around() const;

    void set_state(State state);
    void set_mines_around(int number);

private:
    coord position;
    State state;
    int mines_around;

};
