#pragma once

class SFMLHandler {
public:
	SFMLHandler(sf::RenderWindow* wnd, Board* board);
	~SFMLHandler();

	void Init();
	void InitTextures();

	void Update();

private:
	std::map <const char, std::pair<sf::Texture, sf::Texture>>* _texDict;
	sf::Texture tex;
	sf::RenderWindow* _wnd;
	Board* _board;
};