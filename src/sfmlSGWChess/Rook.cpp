#include "pch.h"

Rook::Rook(COLOR color, Cell* cell) : Piece(color, cell) {
	_symbol = 'r';
}

Rook::~Rook() {

}
void Rook::SetAccesibleCellsToPlayable(Board* board) {
	//lets go up first
	int offset = 1;
	Cell* target = board->GetCellAt(_posCell->pos.x, _posCell->pos.y - offset);
	while(target != nullptr){
		if (target->occupedBy != nullptr) {
			if (target->occupedBy->_color != _color) {
				target->playable = true;
			}
			target = nullptr;
		}
		else {
			target->playable = true;
			++offset;
			target = board->GetCellAt(_posCell->pos.x, _posCell->pos.y + offset);
		}
	}

	// down
	offset = 1;
	target = board->GetCellAt(_posCell->pos.x, _posCell->pos.y + offset);
	while (target != nullptr) {
		if (target->occupedBy != nullptr) {
			if (target->occupedBy->_color != _color) {
				target->playable = true;
			}
			target = nullptr;
		}
		else {
			target->playable = true;
			++offset;
			target = board->GetCellAt(_posCell->pos.x, _posCell->pos.y + offset);
		}
	}

	// right
	offset = 1;
	target = board->GetCellAt(_posCell->pos.x + offset, _posCell->pos.y);
	while (target != nullptr) {
		if (target->occupedBy != nullptr) {
			if (target->occupedBy->_color != _color) {
				target->playable = true;
			}
			target = nullptr;
		}
		else {
			target->playable = true;
			++offset;
			target = board->GetCellAt(_posCell->pos.x + offset, _posCell->pos.y);
		}
	}

	// left
	offset = 1;
	target = board->GetCellAt(_posCell->pos.x - offset, _posCell->pos.y);
	while (target != nullptr) {
		if (target->occupedBy != nullptr) {
			if (target->occupedBy->_color != _color) {
				target->playable = true;
			}
			target = nullptr;
		}
		else {
			target->playable = true;
			++offset;
			target = board->GetCellAt(_posCell->pos.x + offset, _posCell->pos.y);
		}
	}
}