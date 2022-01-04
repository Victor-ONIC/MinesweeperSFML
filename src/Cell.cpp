#include "Cell.h"


// Constructeur: initialise position.
Cell::Cell(int row, int col) : position(sf::Vector2i(row, col)), state(Cell::State::BASE) {}

// Obtenir la valeur de position.
sf::Vector2i Cell::get_position() {
    return position;
}

// Obtenir la valeur de state.
Cell::State Cell::get_state() {
    return state;
}
// Définir la valeur de state.
void Cell::set_state(Cell::State new_state) {
    state = new_state;
}

