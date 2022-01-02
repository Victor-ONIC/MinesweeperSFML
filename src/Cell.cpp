#include "Cell.h"


Cell::Cell() : state(BASE), mines_around(0) {}

void Cell::set_state(Cell_State new_state) { state = new_state; }