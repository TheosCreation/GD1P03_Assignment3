#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
enum ObjectType {
	Type_AllyPiece,
	Type_EnemyPiece
};

class Object
{
private:
	sf::Vector2f m_Pos;
	sf::Vector2f m_ObjSpeed;
public:

	sf::RectangleShape m_ObjShape;
	ObjectType m_ObjType;
	
	sf::Vector2f m_TilePos; // change to set spots 
	bool IsSelected = false;

	Object();
	~Object();

	void Update();
	void Update(sf::Vector2u _GridMousePos, float _gridSizeF);
	void Input();
	void initObject(ObjectType _Type, sf::Vector2f _Position, float _gridSizeF);
	void draw(sf::RenderWindow* _window);
	void move(sf::Vector2f _ToPosition);
};

