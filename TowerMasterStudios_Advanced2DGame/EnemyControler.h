#pragma once
#include "Controler.h"
#include <vector>
#include <fstream>
#include <iostream>
class EnemyControler
{
public:
	
	Controler* m_AllyControlerRef;
	const static int ArraySize = 10;
	Object *m_EnemyObjArray[10];
	Object* m_MovedObj;
	int m_Treasure = 0;
	int m_Health = 10;
	sf::Vector2f m_MovedToTile;
	bool m_HasSelected = false;
	EnemyControler();
	~EnemyControler();
	void InstObjects(Controler _ControlerRef);
	void MoveTile(bool _Move);
	void Destroy();
	void Treasure(int _Treasure);
	void save();
	void LoadFromFile(std::string _fileName);
};

