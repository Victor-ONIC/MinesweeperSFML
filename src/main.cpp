// LET'S JUST DO A 9X9 MINESWEEPER TO BEGIN WITH ALRIGHT
// Remove all "debug" marked lines.
// Check all "PATH" marked lines.

#include "main.h"


int main() {

    // Création de la fenêtre immuable.
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), L"MinesweeperSFML", sf::Style::Titlebar | sf::Style::Close);

    // Create Field object called field.
    Field field(ROWS, COLUMNS);

    while (window.isOpen()) {

        // Event loop.
        sf::Event event;
        while (window.pollEvent(event)) {

            // Fermer la fenêtre quand on appuie sur la croix ou autre event de type close.
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Fermer la fenêtre quand on appuie sur Échap.
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }

            // Lorsque le clic GAUCHE est relaché, on creuse.
            // Seulement si la case est Cell::State::BASE, sinon ne rien faire.

            if (event.type == sf::Event::MouseButtonReleased) {
                int cell_position_row = event.mouseButton.y / CELL_SIZE;
                int cell_position_col = event.mouseButton.x / CELL_SIZE;

                switch (event.mouseButton.button) {

                    case sf::Mouse::Left:
                        field.dig(cell_position_row, cell_position_col);
                        break;

                    case sf::Mouse::Right:
                        field.flag(cell_position_row, cell_position_col);
                        break;

                }

            }
        }

        // Affichage.
        window.clear(sf::Color::Black);

        field.display(window);

        window.display();

    }

    return 0;
}
