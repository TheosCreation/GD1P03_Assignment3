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
	}
	
}

void Tile::SetSprite(sf::String _Path)
{
	m_TileTexture.loadFromFile(_Path);
	m_TileSprite.setTexture(m_TileTexture);
}
