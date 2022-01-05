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

// Displays the game matrix to the window.
void Field::display(sf::RenderWindow &window) {

    sf::Texture texture;
    sf::Sprite cellule;

    // On déplace le même rectangle pour chaque case, puis on dessine.
    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {

            // Texture de la cellule.
            switch (matrix[i_row * COLUMNS + i_col].get_state()) {
            
                case Cell::State::BASE:
                    if (!texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(0, 0, 60, 60))) {
                        std::cout << "------ ERROR: CAN'T LOAD TEXTURE ------";
                    }
                    cellule.setTexture(texture);
                    break;

                case Cell::State::DUG:
                    if (!texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(60, 0, 60, 60))) {
                        std::cout << "------ ERROR: CAN'T LOAD TEXTURE ------";
                    }
                    cellule.setTexture(texture);
                    break;

            }

            // Positionner le rectangle.
            float posX = matrix[i_row * COLUMNS + i_col].get_position().x * CELL_SIZE;
            float posY = matrix[i_row * COLUMNS + i_col].get_position().y * CELL_SIZE;
            cellule.setPosition(posX, posY);

            window.draw(cellule);
        }
    }

}
