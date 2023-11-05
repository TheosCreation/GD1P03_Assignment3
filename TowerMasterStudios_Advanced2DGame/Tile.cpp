#include "Tile.h"

void Tile::ObjInTile(Controler _ObjHandler)
{
	if (_ObjHandler.m_MovedToTile == sf::Vector2f(m_Pos.x, m_Pos.y) )
	{
		switch (m_TileType)
		{
		case Type_Mine:
			_ObjHandler.Damage(10);
			break;
		case Type_Treasure:
			_ObjHandler.Treasure(10);
			break;
		case Type_Water:
			
			break;
		default:
			break;
		}
	}
	
}
