#pragma once
#include "Object.h"
#include <fstream>
#include <sstream>
class Controler 
{
private: 
	
public:
	Object *AllyObjArray[10];
	Object *EnemyObjArray[10];
	Object* m_ObjectSelected = nullptr;
	sf::Vector2f m_MovedToTile = sf::Vector2f(-1, -1);
	bool m_Moved = false;
	int m_Treasure = 0;
	bool m_HasSelected = false;
	int m_Health = 10;
	void InstObjects();
	bool SelectObj(sf::Vector2u _GridMousePos);
	void Destroy();
	void Treasure(int _Treasure);
	void LoadFromFile(std::string _fileName);
	void save();
};

