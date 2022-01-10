#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "main.h"


class Field {

public:
    enum class State { LOST, GOING, WON };
    enum class Feeling { IDLE, SCARED, DEAD, PROUD };

    Field(sf::Font &font);
    void reset();

    Cell *get_cell(int row, int col);
    State get_state() const;
    int get_discovered() const;

    void over();
    void set_state(State);
    void set_Marc(Feeling feeling);
    void flag(int row, int col);
    void dig(int row, int col);
    void draw(sf::RenderWindow &window);

private:
    std::vector<Cell> matrix;
    State state;
    sf::Text text;
    Feeling marc_state;

    bool first_digging;
    int discovered;
    int flags;

    void init_mines(int row, int col);
    bool surroundings(int row, int col, int random_row, int random_col);
    void init_mines_around();
    void update_text(sf::Text &text);

};
