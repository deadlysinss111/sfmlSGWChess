#include "pch.h"

SFMLHandler::SFMLHandler(sf::RenderWindow* wnd, Board* board) {
	_wnd = wnd;
	_board = board;
}

SFMLHandler::~SFMLHandler() {

}

void SFMLHandler::Init() {
	InitTextures();
}

void SFMLHandler::InitTextures() {
	std::pair<sf::Texture, sf::Texture> pair;
	sf::Texture texture;
	_texDict = new std::map <const char, std::pair<sf::Texture, sf::Texture>>;

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_pawn.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_pawn.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('c', pair));

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_king.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_king.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('K', pair));

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_queen.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_queen.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('q', pair));

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_knight.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_knight.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('k', pair));

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_rook.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_rook.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('r', pair));

	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\black_pawn.png");
	pair.first = texture;
	texture.loadFromFile("..\\..\\..\\src\\sfmlSGWChess\\white_pawn.png");
	pair.second = texture;
	_texDict->insert(std::pair<char, std::pair<sf::Texture, sf::Texture>>('p', pair));

	//_texDict = texDict;
}

void SFMLHandler::Update() {
	_wnd->clear();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Cell* target = _board->GetCellAt(i, j);

			sf::RectangleShape shape(sf::Vector2f{ 40,40 });
			shape.setPosition(sf::Vector2f{ float(i * 40),float(j * 40) });
			shape.setFillColor(((i + j) % 2 == 0 ? sf::Color::Red : sf::Color::Black));

			if(target->playable)
				shape.setFillColor((sf::Color::Cyan));
			if (target->occupedBy != nullptr) {
				if (target->occupedBy->_color == WHITE)
					shape.setTexture(&((*_texDict)[target->occupedBy->_symbol]).second);
				else
					shape.setTexture(&((*_texDict)[target->occupedBy->_symbol]).first);
			}

			_wnd->draw(shape);
		}
	}
	_wnd->display();
}