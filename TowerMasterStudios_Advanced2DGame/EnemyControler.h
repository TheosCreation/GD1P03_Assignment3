#pragma once
#include "Controler.h"
class EnemyControler
{
public:
	
	Controler* m_AllyControlerRef;
	const static int ArraySize = 10;
	Object* EnemyObjArray[ArraySize];
	int m_Treasure = 0;
	bool m_HasSelected = false;
	EnemyControler(Controler _ControlerRef);
	~EnemyControler();
	void InstObjects();
	void MoveTile();
	void Destroy();
	void Treasure(int _Treasure);
};

