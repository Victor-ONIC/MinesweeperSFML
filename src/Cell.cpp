#include "Cell.h"


// Constructeur: initialise les variables.
Cell::Cell(int row, int col) : position(coord{row, col}), state(Cell::State::BASE), mines_around(0)
{
}

// Obtenir la valeur de position.
Cell::coord Cell::get_position() const {
    return position;
}

// Obtenir la valeur de state.
Cell::State Cell::get_state() const {
    return state;
}
// Définir la valeur de state.
void Cell::set_state(Cell::State new_state) {
    state = new_state;
}

int Cell::get_mines_around() const {
    return mines_around;
}
void Cell::set_mines_around(int number) {
    mines_around = number;
}