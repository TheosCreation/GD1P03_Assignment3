#include "EnemyControler.h"
EnemyControler::EnemyControler(Controler _ControlerRef)
{
    m_AllyControlerRef = &_ControlerRef;

}
EnemyControler::~EnemyControler()
{
}
void EnemyControler::InstObjects()
{
    int ArrayPos = 0;
    for (int i = 1; i < 2; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            
            Object* NewObject = new Object(Type_EnemyPiece, Type_JetSki, sf::Vector2f(j, i + 9), 64.0f);
            //init an object
            EnemyObjArray[ArrayPos] = NewObject;
            //assign object to this
            ArrayPos++;

        }
    }
}

void EnemyControler::MoveTile()
{
    if (m_AllyControlerRef->m_HasSelected) {
        
        int random = rand() % ArraySize;
        int maxMove = EnemyObjArray[random]->m_MaxMoveDistance;

        std::cout << rand() % maxMove << std::endl;

        EnemyObjArray[random]->
            m_ObjShape.setPosition
            ((((rand() % maxMove * 2) - maxMove)*64) + EnemyObjArray[random]->m_Pos.x),
                (((rand() % maxMove * 2) - maxMove)*64) + EnemyObjArray[random]->m_Pos.y));

    }
}
