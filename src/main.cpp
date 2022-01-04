// LET'S JUST DO A 9X9 MINESWEEPER TO BEGIN WITH ALRIGHT

#include "main.h"


int main() {

    // Création de la fenêtre immuable.
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), L"MinesweeperSFML", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {

        // Event loop.
        sf::Event event;
        while (window.pollEvent(event)) {

            // Fermer la fenêtre quand on appuie sur la croix ou autre event de type close.
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        // Affichage.
        window.clear(sf::Color::White);
        window.display();

    }

    return 0;
}
