#pragma once
#include "Object.h"
class Controler 
{
public:
	Object *AllyObjArray[20];
	Object* m_ObjectSelected;
	sf::Vector2f m_MovedToTile;

	int m_Health = 50;
	int m_Money = 0;
	bool m_HasSelected = false;

	void InstObjects();
	void SelectObj(sf::Vector2u _GridMousePos);
	void Damage(int _Damage);
	void Treasure(int _Money);
};

