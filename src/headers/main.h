#pragma once
#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "Field.h"


// Constantes
int const ROWS = 9;
int const COLUMNS = 9;
int const MINES = 10;
float const CELL_SIZE = 60;

// Dimensions de la fenêtre
int const WIN_WIDTH = ROWS * CELL_SIZE;
int const WIN_HEIGHT = COLUMNS * CELL_SIZE;
