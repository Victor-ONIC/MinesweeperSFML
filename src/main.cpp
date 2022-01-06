#include "main.h"

int main() {

    // Création de la fenêtre immuable.
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), L"MinesweeperSFML", sf::Style::Titlebar | sf::Style::Close);

    // Create Field object called field.
    Field field(ROWS, COLUMNS);

    //
    bool game_over = false;

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

            if (field.get_state() == Field::State::GOING) {

                // Clic gauche -> creuser.
                // Clic droit -> drapeau.
                if (event.type == sf::Event::MouseButtonPressed) {
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

        }  // end of event loop

        if (!game_over) {

            if (field.get_discovered() == ROWS * COLUMNS - MINES) {
            field.set_state(Field::State::WON);
            }

            if (field.get_state() == Field::State::LOST) {
                game_over = true;
                std::cout << "Perdu !\n";
                // Afficher le jeu perdu.
                // Ne pas pouvoir recommencer (pour l'instant).
            }
            else if (field.get_state() == Field::State::WON) {
                game_over = true;
                std::cout << "Gagné !\n";
            }
        }

        // Affichage.
        window.clear(sf::Color::Black);

        field.display(window);

        window.display();

    }

    return 0;
}
