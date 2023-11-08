#pragma once
#include "Object.h"
class Controler 
{
public:
	Object *AllyObjArray[10];
	Object* m_ObjectSelected;
	sf::Vector2f m_MovedToTile;

	int m_Treasure = 0;
	bool m_HasSelected = false;

	void InstObjects();
	void SelectObj(sf::Vector2u _GridMousePos);
	void Destroy();
	void Treasure(int _Treasure);
};

