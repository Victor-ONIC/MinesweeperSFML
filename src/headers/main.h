#pragma once
#include "Cell.h"
#include "Field.h"


// Constantes.
const int CELL_SIZE = 60;

const int ROWS = 9;
const int COLUMNS = 9;
const int MINES = 10;

const int RECT_WIDTH = ROWS * CELL_SIZE;
const int RECT_HEIGHT = 80;

const int TEXT_SIZE = 60;
const int MARGIN_X = 10;
const int MARGIN_Y = 20;

const int MARC_MARGIN_X = 15;
const int MARC_MARGIN_Y = 10;

const int WIN_WIDTH = ROWS * CELL_SIZE;
const int WIN_HEIGHT = COLUMNS * CELL_SIZE + RECT_HEIGHT;
