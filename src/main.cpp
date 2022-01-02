#include "main.h"

// Classe "Menu" pour afficher:
// _ un logo
// _ demander le mode de jeu
// _ demander la taille
// _ demander la difficulté
class Menu {

};


int main() {

    // Création de la fenêtre.
    sf::RenderWindow window;
    window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), L"Démineur", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {

        // Event loop
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

        }

        // Affichage à l'écran.
        window.clear(sf::Color::Black);
        window.display();

    }

    return 0;
}