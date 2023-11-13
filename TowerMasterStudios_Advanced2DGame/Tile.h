#pragma once
#include <SFML/Graphics.hpp>
#include "Controler.h"
#include "EnemyControler.h"

enum TileType {
	Type_Mine,
	Type_Treasure,
	Type_Water

};
class Tile
{
public:
	bool m_Explored = false;
	TileType m_TileType = Type_Water;
	sf::RectangleShape m_Tile; 
	sf::Vector2i m_Pos = { 0,0 };
	sf::Texture m_TileTexture;
	sf::Sprite m_TileSprite;
	Tile *m_Neighbours[8];
	unsigned int ShowingMine = 0;
	bool Active = true;
	void ObjInTile(Controler* _ObjHandler, EnemyControler* _EnemyHandler);
	void ShowTile();
	void SetSprite(sf::String _Path);
	void SetNeighbours();
	int m_MineCount = 0;
	int m_TresureCount = 0;
	void Update(int _showingMine);
};

