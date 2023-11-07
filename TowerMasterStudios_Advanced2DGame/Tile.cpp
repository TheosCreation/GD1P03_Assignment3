#include "Tile.h"

void Tile::ObjInTile(Controler* _ObjHandler)
{
	if (_ObjHandler->m_MovedToTile == sf::Vector2f(m_Pos.x, m_Pos.y) )
	{
		switch (m_TileType)
		{
		case Type_Mine:
			if (Active) {
				_ObjHandler->Destroy();
				Active = false;
			}
			break;
		case Type_Treasure:
			if (Active) {
				_ObjHandler->Treasure(1);
				Active = false;
			}
			break;
		case Type_Water:
			// Does nothing
			break;
		default:
			break;
		}
		m_MineCount = 0;
		m_TresureCount = 0;
		for (int i = 0; i < 8; i++)
		{
			if(m_Neighbours[i]!=NULL){
				if (m_Neighbours[i]->m_TileType == Type_Mine) {
					m_MineCount++;
				}			
				if (m_Neighbours[i]->m_TileType == Type_Treasure) {
					m_TresureCount++;
				}
			}
		}
		std::cout << m_MineCount << std::endl;

	}
	
}

void Tile::SetSprite(sf::String _Path)
{
	m_TileTexture.loadFromFile(_Path);
	m_TileSprite.setTexture(m_TileTexture);
}
