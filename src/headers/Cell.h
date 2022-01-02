#pragma once

// Classe "Cell" pour les cases du jeu. //////////////////////////////////
class Cell {

private:
    enum Cell_State { BASE, DUG, MINE, FLAG, BOOM };

    Cell_State state;
    int mines_around;

public:
    Cell();
    void set_state(Cell_State new_state);

}; ///////////////////////////////////////////////////////////////////////