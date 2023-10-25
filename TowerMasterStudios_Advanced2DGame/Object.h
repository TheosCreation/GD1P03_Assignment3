#pragma once
#include <SFML/Graphics.hpp>

enum ObjectType {
	Type_AllyPiece,
	Type_EnemyPiece
};

class Object
{

public:

	sf::RectangleShape m_ObjShape;
	ObjectType m_ObjType;
	sf::Vector2f m_ObjSpeed;
	sf::Vector2f m_TilePos;
	sf::Vector2f m_Pos;

	Object(ObjectType _Type, sf::Vector2f _Position, float _gridSizeF);
	~Object();

	void Update();
	void Input();
};

