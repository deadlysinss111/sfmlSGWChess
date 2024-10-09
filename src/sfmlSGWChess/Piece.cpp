#include "pch.h"

Piece::Piece(COLOR color, Cell* cell) {
	_color = color;
	_posCell = cell;
	_didMove = false;
}

Piece::~Piece() {
	
}

void Piece::MoveTo(Cell* dest) {
	dest->occupedBy = this;
	_posCell->occupedBy = nullptr;
	_posCell = dest;
	_didMove = true;
}
