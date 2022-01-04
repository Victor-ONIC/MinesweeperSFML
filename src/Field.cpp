#include "Field.h"


// Constructeur.
Field::Field(int rows, int cols) : state(Field::State::BASIC) {

    for (int i_row = 0; i_row < rows; i_row++) {
        for (int i_col = 0; i_col < cols; i_col++) {
            Cell cell(i_row, i_col);
            matrix.push_back(cell);
        }
    }

}

void Field::display(sf::RenderWindow &window) {

    sf::RectangleShape cellule(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    cellule.setFillColor(sf::Color(0xC175FFFF));
    cellule.setOutlineColor(sf::Color(0xB042FFFF));
    cellule.setOutlineThickness(-3.0f);

    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {
            float posX = matrix[i_row * COLUMNS + i_col].get_position().x * CELL_SIZE;
            float posY = matrix[i_row * COLUMNS + i_col].get_position().y * CELL_SIZE;
            cellule.setPosition(posX, posY);
            window.draw(cellule);
        }
    }

}