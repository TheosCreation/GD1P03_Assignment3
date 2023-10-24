#pragma once
#include <SFML/Graphics.hpp>

class TileMap
{
	int mapSize = 0;
	float gridSizeF = 0;
	std::vector<std::vector<sf::RectangleShape>> tileMap;
	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0;
public:
	TileMap(int _mapSize, float _gridSizeF);
	void draw(sf::RenderWindow* _window);
	void update(sf::View _view);
};

