#include "Tile.h"

void Tile::ObjInTile(Controler* _ObjHandler)
{
	if (_ObjHandler->m_MovedToTile == sf::Vector2f(m_Pos.x, m_Pos.y) )
	{
		switch (m_TileType)
		{
		case Type_Mine:
			if (Active) {
				_ObjHandler->Damage(10);
				Active = false;
			}
			break;
		case Type_Treasure:
			if (Active) {
				_ObjHandler->Treasure(10);
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