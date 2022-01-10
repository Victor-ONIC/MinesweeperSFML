#include "Field.h"


// Constructeur.
Field::Field(sf::Font &font) : state(State::GOING), marc_state(Feeling::IDLE), first_digging(false), discovered(0), flags(0) {

    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {
            Cell cell(i_row, i_col);
            matrix.push_back(cell);
        }
    }

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(TEXT_SIZE);
    text.setString("Mines:" + std::to_string(MINES));
    text.setPosition(MARGIN_X, WIN_HEIGHT - (MARGIN_Y + TEXT_SIZE));

}

// Réinitialise les valeurs du jeu.
void Field::reset() {

    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {
            get_cell(i_row, i_col)->reset();
        }
    }

    discovered = 0;
    flags = 0;
    first_digging = false;
    state = State::GOING;
    marc_state = Feeling::IDLE;

    update_text(text);

}

// Renvoie la Cell à l'emplacement [row,col] du jeu.
Cell *Field::get_cell(int row, int col) {
    return &matrix[row * COLUMNS + col];
}

// Obtenir la valeur de state.
Field::State Field::get_state() const {
    return state;
}
// Définir la valeur de state.
void Field::set_state(Field::State new_state) {
    state = new_state;
}

// Obtenir la valeur de discovered.
int Field::get_discovered() const {
    return discovered;
}

// Définir l'état de Marc.
void Field::set_Marc(Feeling feeling) {
    marc_state = feeling;
}

// Pose un drapeau s'il n'y en a pas. Le retire s'il y en a déjà un.
void Field::flag(int row, int col) {

    switch (get_cell(row, col)->get_state()) {

        case Cell::State::BASE:
            get_cell(row, col)->set_state(Cell::State::FLAG_BASE);
            flags++;
            update_text(text);
            break;

        case Cell::State::MINE:
            get_cell(row, col)->set_state(Cell::State::FLAG_MINE);
            flags++;
            update_text(text);
            break;
            
        case Cell::State::FLAG_BASE:
            get_cell(row, col)->set_state(Cell::State::BASE);
            flags--;
            update_text(text);
            break;
            
        case Cell::State::FLAG_MINE:
            get_cell(row, col)->set_state(Cell::State::MINE);
            flags--;
            update_text(text);
            break;   
    }
}

// Mettre à jour le texte.
void Field::update_text(sf::Text &text) {
    text.setString("Mines:" + std::to_string(MINES - flags));
}

// Creuser.
void Field::dig(int row, int col) {

    // Ne générer les mines qu'après la première creusée.
    if (!first_digging) {
        first_digging = true;
        init_mines(row, col);
        init_mines_around();
    }

    // Si la cellule n'est pas d'état BASE ou MINE, alors on ne peut pas creuser.
    if (!(get_cell(row, col)->get_state() == Cell::State::BASE || get_cell(row, col)->get_state() == Cell::State::MINE)) {
        return;
    }

    // Si la case creusée est une mine, la partie est perdue.
    if (get_cell(row, col)->get_state() == Cell::State::MINE) {
        get_cell(row, col)->set_state(Cell::State::BOOM);
        set_state(Field::State::LOST);
        set_Marc(Feeling::DEAD);
        return;
    }

    get_cell(row, col)->set_state(Cell::State::DUG);
    discovered++;

    // Creusée récursive s'il n'a pas de mines autour.
    if (get_cell(row, col)->get_mines_around() == 0) {

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                
                // Si la case est out of bounds, on ne la creuse pas.
                if ((i == 0 && j == 0) || row + i < 0 || row + i >= ROWS || col + j < 0 || col + j >= COLUMNS) {
                    continue;
                }

                // Si la case est déjà creusée, one ne la creuse pas.
                if (get_cell(row + i, col + j)->get_state() == Cell::State::DUG) {
                    continue;
                }

                dig(row + i, col + j);

            }
        }

    }

}

// Crée MINES mines placées aléatoirement.
void Field::init_mines(int row, int col) {
    srand(time(NULL));
    int random_row = rand() % ROWS;
    int random_col = rand() % COLUMNS;

    for (int i_mines = 0; i_mines < MINES; i_mines++) {

        // Si la case hasard est déjà une mine, ou si elle est autour de la première case creusée, on change hasard.
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
                get_cell(i_row, i_col)->increment_mines_around(-1);
            }
            else {
                // Compter les mines autour de la case [i_row,i_col].
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {

                        // Si la case [i_row + i, i_col + j] est out of bounds on l'ignore.
                        // On ignore aussi la case [i_row,i_col] elle-même.
                        if ((i == 0 && j == 0) ||
                            i_row + i < 0 || i_row + i >= ROWS ||
                            i_col + j < 0 || i_col + j >= COLUMNS)
                        {
                            continue;
                        }

                        // Si la case est une mine, on incrémente mines_around.
                        if (get_cell(i_row + i, i_col + j)->get_state() == Cell::State::MINE) {
                            get_cell(i_row, i_col)->increment_mines_around();
                        }

                    }
                }
            }
        }
    }

}

// Display.
void Field::draw(sf::RenderWindow &window) {

    // La matrice du jeu.
    sf::Texture texture;
    sf::Sprite cellule;

    // On déplace le même rectangle pour chaque case, puis on dessine.
    for (int i_row = 0; i_row < ROWS; i_row++) {
        for (int i_col = 0; i_col < COLUMNS; i_col++) {

            // Texture de la cellule selon l'état de la case.
            switch (get_cell(i_row, i_col)->get_state()) {

                case Cell::State::BASE:
                    texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(0, 0, 60, 60));
                    cellule.setTexture(texture);
                    break;

                case Cell::State::MINE:
                    if (state == Field::State::LOST) {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(720, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    }
                    else if (state == Field::State::WON) {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(120, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    }
                    else {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(0, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    }

                case Cell::State::FLAG_BASE:
                    if (state != Field::State::GOING) {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(780, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    }
                    texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(120, 0, 60, 60));
                    cellule.setTexture(texture);
                    break;

                case Cell::State::FLAG_MINE:
                    texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(120, 0, 60, 60));
                    cellule.setTexture(texture);
                    break;
                
                case Cell::State::BOOM:
                    texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(660, 0, 60, 60));
                    cellule.setTexture(texture);
                    break;

                case Cell::State::DUG:
                    int number = get_cell(i_row, i_col)->get_mines_around();

                    if (number == 0) {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(60, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    }
                    else {
                        texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(120 + number * 60, 0, 60, 60));
                        cellule.setTexture(texture);
                        break;
                    } 
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

    // Le texte.
    if (state == Field::State::WON) {
        text.setString("Mines:0");
    }
    window.draw(text);

    // Marc.
    sf::Texture Marc_texture;
    sf::Sprite Marc;

    // Texture de Marc selon son état.
    switch (marc_state) {

        case Feeling::IDLE:
            Marc_texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(840, 0, 60, 60));
            Marc.setTexture(Marc_texture);
            break;

        case Feeling::SCARED:
            Marc_texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(900, 0, 60, 60));
            Marc.setTexture(Marc_texture);
            break;

        case Feeling::PROUD:
            Marc_texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(960, 0, 60, 60));
            Marc.setTexture(Marc_texture);
            break;

        case Feeling::DEAD:
            Marc_texture.loadFromFile("src/res/sprites60x60.png", sf::IntRect(1020, 0, 60, 60));
            Marc.setTexture(Marc_texture);
            break;
    }

    // Positionnement de Marc.
    float Marc_position_X = WIN_WIDTH - (CELL_SIZE + MARC_MARGIN_X);
    float Marc_position_Y = WIN_HEIGHT - (CELL_SIZE + MARC_MARGIN_Y);
    Marc.setPosition(Marc_position_X, Marc_position_Y);

    window.draw(Marc);

}
