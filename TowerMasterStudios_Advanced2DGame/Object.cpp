#include "Object.h"

Object::Object(ObjectType _ObjType, UnitType _UnitType, sf::Vector2f _Position, float _gridSizeF) // constructor. Each object has a type and position. 
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_TilePos = _Position;
	m_Pos = sf::Vector2f(_Position.x * _gridSizeF + 19.2, _Position.y * _gridSizeF + 19.2);
	m_ObjShape.setPosition(m_Pos);

	// this switch statement allows us to change the colour based on the object type, which is part of the object constructor, above. 

	sf::Color Purple(142, 22, 166, 128);
	sf::Color Blue(22, 56, 166, 128);
	sf::Color GreenA(79, 174, 54, 128);


	sf::Color Red(255, 0, 0, 128);
	sf::Color Green(0, 255, 0, 128);


	

	
	
	m_ObjType = _ObjType;
	m_UnitType = _UnitType;
	switch (m_ObjType)
	{
	case Type_AllyPiece:
		m_ObjShape.setOutlineThickness(5.0f);
		m_ObjShape.setOutlineColor(Green);
		break;
	case Type_EnemyPiece:
		m_ObjShape.setOutlineThickness(5.0f);
		m_ObjShape.setOutlineColor(Red);
		break;
	default:
		break;
	}

	switch (_UnitType)
	{
	case Type_Cruise:
		m_MaxMoveDistance = 1;
		m_ObjShape.setFillColor(Purple);
		m_Color = Purple;
		break;
	case Type_JetSki:
		m_MaxMoveDistance = 2;
		m_ObjShape.setFillColor(Blue);
		m_Color =  Blue;
	
	case Type_PirateShip:
		m_MaxMoveDistance = 3;
		m_ObjShape.setFillColor(GreenA);
		m_Color = GreenA;
		
		break;
	default:
		break;
	}
}

Object::~Object()
{
}





void Object::Input()
{
	m_ObjSpeed = sf::Vector2f(0.5, 0);

	m_ObjShape.move(m_ObjSpeed);
}
//void Object::initObject(ObjectType _Type, sf::Vector2f _Position, float _gridSizeF)
//{
//	
//}
void Object::draw(sf::RenderWindow* _window)
{
	_window->draw(m_ObjShape);
}
void Object::Update()
{	
	if (IsSelected) {
		m_ObjShape.setFillColor(sf::Color::Yellow);
		
	}
	else {
		m_ObjShape.setFillColor(m_Color);
	}
}