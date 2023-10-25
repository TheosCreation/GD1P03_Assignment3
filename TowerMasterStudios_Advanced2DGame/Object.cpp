#include "Object.h"


Object::Object(ObjectType _Type, sf::Vector2f _Position, float _gridSizeF) // constructor. Each object has a type and position. 
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_TilePos = _Position;
	m_Pos = sf::Vector2f(_Position.x * _gridSizeF, _Position.y * _gridSizeF);
	m_ObjShape.setPosition(m_Pos);

	// this switch statement allows us to change the colour based on the object type, which is part of the object constructor, above. 
	switch (_Type)
	{
	case Type_AllyPiece:
		break;
	case Type_EnemyPiece:
		break;
	default:
		break;
	}
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Input()
{
	m_ObjSpeed = sf::Vector2f(0.5, 0);

	m_ObjShape.move(m_ObjSpeed);
}
