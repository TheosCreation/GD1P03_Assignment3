#include "Controler.h"

void Controler::InstObjects()
{
    int ArrayPos = 0;
    for (int i = 1; i < 3; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            Object* NewObject = new Object(Type_AllyPiece, sf::Vector2f(j, i + 10), 100.0f);
            //init an object
            AllyObjArray[ArrayPos] =NewObject;
            //assign object to this
            ArrayPos++;

        }
    }
}

void Controler::SelectObj(sf::Vector2u _GridMousePos)
{
    for (Object* obj : AllyObjArray) {
        if (_GridMousePos == sf::Vector2u(obj->m_TilePos.x, obj->m_TilePos.y)) {
             m_IsSelected = true;
             m_ObjectSelected = obj;
             obj->IsSelected = true;

            
        }
        else {
            obj->IsSelected = false;
        }
    }
    
}
