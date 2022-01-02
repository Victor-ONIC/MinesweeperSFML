#include "Field.h"


Field::Field(int rows, int cols) : nb_col(cols), nb_row(rows) {}

Field::~Field() {
    for (int i_row = 0; i_row < nb_row; i_row++) {
        delete[] matrix[i_row];
    }
    delete[] matrix;
}

void Field::set_state(Game_State new_state) { state = new_state; }

void Field::init_matrix() {
    matrix = create_matrix();
}


Cell **Field::create_matrix() {
    Cell **matrix = new Cell *[nb_row];

    for (int i_row = 0; i_row < nb_row; i_row++) {
        matrix[i_row] = new Cell[nb_col];
    }
    return matrix;
}