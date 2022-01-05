#include "Field.h"


// Constructeur.
Field::Field(int rows, int cols) : state(Field::State::BASIC), first_digging(false) {

    for (int i_row = 0; i_row < rows; i_row++) {
        for (int i_col = 0; i_col < cols; i_col++) {
            Cell cell(i_row, i_col);
            matrix.push_back(cell);
        }
    }

}

// Renvoie la Cell à l'emplacement [row,col] du jeu.
Cell *Field::get_cell(int row, int col) {
    return &matrix[row * COLUMNS + col];
}

// Pose un drapeau s'il n'y en a pas. Le retire s'il y en a déjà un.
void Field::flag(int row, int col) {

    if (get_cell(row, col)->get_state() == Cell::State::BASE || get_cell(row, col)->get_state() == Cell::State::MINE) {
        get_cell(row, col)->set_state(Cell::State::FLAG);
    }
    else if (get_cell(row, col)->get_state() == Cell::State::FLAG) {
        get_cell(row, col)->set_state(Cell::State::BASE);
    }

}

// Creuse.
void Field::dig(int row, int col) {

    if (!first_digging) {
        first_digging = true;
        init_mines(row, col);
        init_mines_around();
    }

    // Si la cellule n'est pas d'état BASE ou MINE, alors on ne peut pas creuser.
    if (!(get_cell(row, col)->get_state() == Cell::State::BASE || get_cell(row, col)->get_state() == Cell::State::MINE)) {
        return;
    }

    if (get_cell(row, col)->get_state() == Cell::State::MINE) {
        std::cout << "PERDU!\n";
        // Perdu.
    }

    get_cell(row, col)->set_state(Cell::State::DUG);
    // creuser récursif s'il n'a pas de mines autour. //TODO

}

// Crée MINES mines placées aléatoirement.
void Field::init_mines(int row, int col) {
    srand(time(NULL));
    int random_row = rand() % ROWS;
    int random_col = rand() % COLUMNS;

    for (int i_mines = 0; i_mines < MINES; i_mines++) {

        // Si la case hasard est déjà une mine, ou si elle est autour de la première case creusée, on recommence.
        while (get_cell(random_row, random_col)->get_state() == Cell::State::MINE || surroundings(row, col, random_row, random_col)) {
            random_row = rand() % ROWS;
            random_col = rand() % COLUMNS;
        }

        get_cell(random_row, random_col)->set_state(Cell::State::MINE);

    }

}

// Renvoie true si la case [random_row, random_col] est dans un carré 3x3 autour de la case [row,col].
bool Field::surroundings(int row, int col, int random_row, int random_col) {
    bool condition = (
        (random_row >= row - 1) && (random_row <= row + 1) &&
        (random_col >= col - 1) && (random_col <= col + 1)
    );
    return condition;
}

// Pour chaque case, on calcule le nombre de mines dans son entourage.
void Field::init_mines_around() {

    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {

            // Si la case contient une mine, on met mines_around à -1.
            if (get_cell(i_row, i_col)->get_state() == Cell::State::MINE) {
                get_cell(i_row, i_col)->set_mines_around(-1);
            }

            get_cell(i_row, i_col)->set_mines_around(1);

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
            switch (get_cell(i_row, i_col)->get_state()) {  // PATH
            
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
                
                case Cell::State::FLAG:
                    if (!texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(120, 0, 60, 60))) {
                        std::cout << "------ ERROR: CAN'T LOAD TEXTURE ------";
                    }
                    cellule.setTexture(texture);
                    break;
                
                case Cell::State::MINE:
                    if (!texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(180, 0, 60, 60))) {
                        std::cout << "------ ERROR: CAN'T LOAD TEXTURE ------";
                    }
                    cellule.setTexture(texture);
                    break;

            }

            // Positionner le rectangle.
            // Les colonnes sont l'unité horizontale.
            // Les lignes sont l'unité verticale.
            float sprite_position_X = get_cell(i_row, i_col)->get_position().col * CELL_SIZE;
            float sprite_position_Y = get_cell(i_row, i_col)->get_position().row * CELL_SIZE;
            cellule.setPosition(sprite_position_X, sprite_position_Y);

            window.draw(cellule);
        }
    }

}
