#pragma once
#include "Cell.h"
#include "Field.h"


// Constantes
constexpr int CELL_SIZE = 60;  // ne pas changer

constexpr int ROWS = 9;
constexpr int COLUMNS = 9;
constexpr int MINES = 10;

constexpr int RECT_WIDTH = ROWS * CELL_SIZE;
constexpr int RECT_HEIGHT = 80;

constexpr int TEXT_SIZE = 60;
constexpr int MARGIN_X = 10;
constexpr int MARGIN_Y = 20;

constexpr int MARC_MARGIN_X = 15;
constexpr int MARC_MARGIN_Y = 10;

constexpr int WIN_WIDTH = ROWS * CELL_SIZE;
constexpr int WIN_HEIGHT = COLUMNS * CELL_SIZE + RECT_HEIGHT;
