// Démineur - Victor ONIC
//
// Contrôles:
// Clic gauche: creuser
// Clic droit: drapeau
// Échap: fermer
// Entrée: rejouer

#include "main.h"

int main() {

    // Création de la fenêtre immuable.
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "MinesweeperSFML", sf::Style::Titlebar | sf::Style::Close);

    // Police du texte.
    sf::Font font;
    font.loadFromFile("src/res/VT323-Regular.ttf");

    // Création de field.
    Field field(font);

    // Rectangle de fond.
    sf::RectangleShape rectangle(sf::Vector2f(RECT_WIDTH, RECT_HEIGHT));
    rectangle.setPosition(0, WIN_HEIGHT - RECT_HEIGHT);
    rectangle.setFillColor(sf::Color(0x1A1A1AFF));
    

    while (window.isOpen()) {

        // Event loop.
        sf::Event event;
        while (window.pollEvent(event)) {

            // Fermer la fenêtre quand on appuie sur la croix ou autre event de type close.
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {

                switch (event.key.code) {

                    // Fermer la fenêtre quand on appuie sur Échap.
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    
                    // Redémarrer la partie avec Entrée.
                    case sf::Keyboard::Enter:
                        field.reset();
                        break;
                }
            }

            if (field.get_state() == Field::State::GOING) {

                // Clic gauche -> creuser.
                // Clic droit -> drapeau.
                if (event.type == sf::Event::MouseButtonPressed) {
                    field.set_Marc(Field::Feeling::SCARED);

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
                else if (event.type == sf::Event::MouseButtonReleased) {
                    field.set_Marc(Field::Feeling::IDLE);
                }
            }

        }  // end of event loop.

        // Condition de victoire.
        if (field.get_discovered() == ROWS * COLUMNS - MINES) {
            field.set_state(Field::State::WON);
            field.set_Marc(Field::Feeling::PROUD);
        }

        // Affichage.
        window.clear(sf::Color::Black);

        window.draw(rectangle);
        field.draw(window);

        window.display();

    }

    return 0;
}
