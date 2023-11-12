#pragma once
#include "Tile.h"
#include <cstdlib>  // Include the <cstdlib> header for the rand() function
#include <ctime>    // Include the <ctime> header for seed initialization
#include <fstream>
#include <iostream>
class TileMap
{

	float gridSizeF = 0;
	
	int fromX = 0;
	int toX = 0;
	int fromY = 0;
	int toY = 0; 
	int ShowingMine = 0;
	sf::Texture* BombTexture;
	

public:
	std::vector<std::vector<Tile>> tileMap;
	int mapSize = 0;
	TileMap(int _mapSize, float _gridSizeF);
	void draw(sf::RenderWindow* _window);
	void update(sf::View _view, Controler* _ctrl, EnemyControler* _ectrl);
	void save(std::string _FileName);
};

