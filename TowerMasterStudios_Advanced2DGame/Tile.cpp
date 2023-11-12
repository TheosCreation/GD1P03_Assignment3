#include "Tile.h"

void Tile::ObjInTile(Controler* _ObjHandler, EnemyControler* _EnemyHandler)
{
	if (_ObjHandler->m_MovedToTile == sf::Vector2f(m_Pos.x, m_Pos.y))
	{
		switch (m_TileType)
		{
		case Type_Mine:
			if (Active) {
				_ObjHandler->Destroy();
				Active = false;
		/*		SetSprite("Assets/Sprites/Water.png");
				m_TileType = Type_Water;
				SetNeighbours();*/
			}
			break;
		case Type_Treasure:
			if (Active) {
				_ObjHandler->Treasure(1);
				Active = false;
			/*	SetSprite("Assets/Sprites/Water.png");
				m_TileType = Type_Water;
				SetNeighbours();*/
			}
			break;
		case Type_Water:

			m_Explored = true;
			SetSprite((  std::string("Assets/Sprites/WaterExplored").append(std::to_string(m_MineCount))  ).append(".png"));
			break;
		default:
			break;
		}

		
	}	if (_EnemyHandler->m_MovedToTile == sf::Vector2f(m_Pos.x, m_Pos.y))
	{
		switch (m_TileType)
		{
		case Type_Mine:
			if (Active) {
				_EnemyHandler->Destroy();
				Active = false;
		/*		SetSprite("Assets/Sprites/Water.png");
				m_TileType = Type_Water;
				SetNeighbours();*/
			}
			break;
		case Type_Treasure:
			if (Active) {
				_EnemyHandler->Treasure(1);
				Active = false;
			/*	SetSprite("Assets/Sprites/Water.png");
				m_TileType = Type_Water;
				SetNeighbours();*/
			}
			break;
		case Type_Water:

			m_Explored = true;
			SetSprite((  std::string("Assets/Sprites/WaterExplored").append(std::to_string(m_MineCount))  ).append(".png"));
			break;
		default:
			break;
		}

		
	}
	
}

void Tile::SetSprite(sf::String _Path)
{
	m_TileTexture.loadFromFile(_Path);
	m_TileSprite.setTexture(m_TileTexture);
}

void Tile::SetNeighbours()
{
	m_MineCount = 0;
	m_TresureCount = 0;
	for (int i = 0; i < 8; i++)
	{
		if (m_Neighbours[i] != NULL) {
			if (m_Neighbours[i]->m_TileType == Type_Mine) {
				m_MineCount++;
			}
			if (m_Neighbours[i]->m_TileType == Type_Treasure) {
				m_TresureCount++;
			}
		}
	}

}

void Tile::Update(int _showingMine)
{
	
	if (_showingMine > 100 && _showingMine < 200) {
		SetSprite((std::string("Assets/Sprites/WaterExploredTreasure").append(std::to_string(m_TresureCount))).append(".png"));
	}
	else {
		SetSprite((std::string("Assets/Sprites/WaterExplored").append(std::to_string(m_MineCount))).append(".png"));
	}
	
}
