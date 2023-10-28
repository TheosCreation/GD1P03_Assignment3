#include "Object.h"


Object::Object() // constructor. Each object has a type and position. 
{
	
}

Object::~Object()
{
}





void Object::Input()
{
	m_ObjSpeed = sf::Vector2f(0.5, 0);

	m_ObjShape.move(m_ObjSpeed);
}
void Object::initObject(ObjectType _Type, sf::Vector2f _Position, float _gridSizeF)
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_TilePos = _Position;
	m_Pos = sf::Vector2f(_Position.x * _gridSizeF + 35, _Position.y * _gridSizeF + 35);
	m_ObjShape.setPosition(m_Pos);

	// this switch statement allows us to change the colour based on the object type, which is part of the object constructor, above. 

	m_ObjShape.setOutlineThickness(5.0f);
	m_ObjShape.setOutlineColor(sf::Color::Black);
	m_ObjType = _Type;
	switch (m_ObjType)
	{
	case Type_AllyPiece:
		m_ObjShape.setFillColor(sf::Color::Green);
		break;
	case Type_EnemyPiece:
		m_ObjShape.setFillColor(sf::Color::Red);
		break;
	default:
		break;
	}
}
void Object::draw(sf::RenderWindow* _window)
{
	_window->draw(m_ObjShape);
}
void Object::Update(sf::Vector2u _GridMousePos)
{
	if (m_ObjType == Type_AllyPiece) {

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (_GridMousePos == sf::Vector2u(m_TilePos.x, m_TilePos.y)) {
				//select this as player

				IsSelected = true;
			}
			else {
				IsSelected = false;
			}
		}	
		if (IsSelected) {
			m_ObjShape.setFillColor(sf::Color::Yellow);
			m_ObjShape.setSize(sf::Vector2f(100, 100));
			
		}
		else {
			
			m_ObjShape.setFillColor(sf::Color::Green);
			m_ObjShape.setSize(sf::Vector2f(30, 30));
		}

	}
}