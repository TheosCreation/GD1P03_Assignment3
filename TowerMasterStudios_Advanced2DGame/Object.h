#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
enum ObjectType {
	Type_AllyPiece,
	Type_EnemyPiece
};

enum UnitType {
	Type_Cruise,
	Type_JetSki,
	Type_PirateShip
};

class Object
{
private:

	sf::Vector2f m_ObjSpeed;
public:
	sf::Vector2f m_Pos;
	sf::RectangleShape m_ObjShape;
	ObjectType m_ObjType;
	UnitType m_UnitType;
	
	sf::Vector2f m_TilePos;
	bool IsSelected = false;
	int m_MaxMoveDistance = 1;
	sf::Color m_Color;
	Object(ObjectType _ObjType, UnitType _UnitType, sf::Vector2f _Position, float _gridSizeF);
	~Object();

	void Update();
	void Input();
	void draw(sf::RenderWindow* _window);

};

