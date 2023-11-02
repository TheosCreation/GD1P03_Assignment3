#pragma once
#include <SFML/Graphics.hpp>
#include "Controler.h"

enum TileType {
	Type_Mine,
	Type_Treasure,
	Type_Water

};
class Tile
{
public:
	TileType m_TileType = Type_Water;
	sf::RectangleShape m_Tile; 
	sf::Vector2i m_Pos = { 0,0 };
	void ObjInTile(Controler _ObjHandler);
};

