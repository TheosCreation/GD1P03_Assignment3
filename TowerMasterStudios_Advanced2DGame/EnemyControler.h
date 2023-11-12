#pragma once
#include "Controler.h"
#include <vector>
class EnemyControler
{
public:
	
	Controler* m_AllyControlerRef;
	const static int ArraySize = 10;
	Object *m_EnemyObjArray[10];
	Object* m_MovedObj;
	int m_Treasure = 0;
	sf::Vector2f m_MovedToTile;
	bool m_HasSelected = false;
	EnemyControler(Controler _ControlerRef);
	~EnemyControler();
	void InstObjects();
	void MoveTile(bool _Move);
	void Destroy();
	void Treasure(int _Treasure);
};

