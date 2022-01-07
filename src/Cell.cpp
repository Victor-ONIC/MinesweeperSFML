#include "Cell.h"


// Constructeur.
Cell::Cell(int row, int col) : position(coord{row, col}), state(State::BASE), mines_around(0)
{
}

// Réinitialise les valeurs d'une case.
void Cell::reset() {
    state = State::BASE;
    mines_around = 0;
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

// Obtenir le nombre de mines autour de cette case.
int Cell::get_mines_around() const {
    return mines_around;
}
// Augmente le nombre de mines autour de number, par défaut 1.
void Cell::increment_mines_around(int number) {
    mines_around += number;
}
