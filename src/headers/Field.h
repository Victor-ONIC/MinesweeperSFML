#pragma once
#include "Cell.h"

// Classe "Field" pour la matrice du jeu. ////////////////////////////////
class Field {

private:
    enum Game_State { LOST, BASIC, HP, WON };

    Game_State state;
    int nb_row;
    int nb_col;
    Cell **matrix;

    Cell **create_matrix();

public:
    Field(int rows, int cols);
    ~Field();

    void set_state(Game_State new_state);

    void init_matrix();

}; ///////////////////////////////////////////////////////////////////////
// Field game(nb_row, nb_col);
// game.init_matrix();
// game