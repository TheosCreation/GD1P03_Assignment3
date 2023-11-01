#pragma once
#include "Object.h"
class Controler
{
public:
	Object *AllyObjArray[20];
	Object* m_ObjectSelected;
	bool m_HasSelected = false;

	void InstObjects();
	void SelectObj(sf::Vector2u _GridMousePos);
};

