#include "Controler.h"

void Controler::InstObjects()
{
    int ArrayPos = 0;
    for (int i = 1; i < 2; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            Object* NewObject = new Object(Type_AllyPiece, Type_Cruise, sf::Vector2f(j, i + 10), 64.0f);
            //init an object
            AllyObjArray[ArrayPos] =NewObject;
            //assign object to this
            ArrayPos++;

        }
    }
}

void Controler::SelectObj(sf::Vector2u _GridMousePos)
{
    bool ObjectHasBeenSelected = false;
    for (Object* obj : AllyObjArray) {
        if (_GridMousePos == sf::Vector2u(obj->m_TilePos.x, obj->m_TilePos.y)) {
             m_HasSelected = true;
             m_ObjectSelected = obj;
             obj->IsSelected = true;
             ObjectHasBeenSelected = true;
        }
        else {
            obj->IsSelected = false;
        }
    }
    if(!ObjectHasBeenSelected&& m_HasSelected){
        //moves ovject
        sf::Vector2f MoveDistance = sf::Vector2f(abs(m_ObjectSelected->m_TilePos.x - _GridMousePos.x), abs(m_ObjectSelected->m_TilePos.y - _GridMousePos.y));
        if (MoveDistance.x <= m_ObjectSelected->m_MaxMoveDistance && MoveDistance.y <= m_ObjectSelected->m_MaxMoveDistance) {

            m_ObjectSelected->m_TilePos = sf::Vector2f(_GridMousePos.x, _GridMousePos.y);
            m_ObjectSelected->m_ObjShape.setPosition(m_ObjectSelected->m_TilePos.x * 64 + 19.2, m_ObjectSelected->m_TilePos.y * 64 + 19.2);
            m_HasSelected = false;
            m_MovedToTile = sf::Vector2f(_GridMousePos.x, _GridMousePos.y);
        
            
        }
        else {
            m_HasSelected = false;
        }
    }
    
}

void Controler::Destroy()
{
    m_ObjectSelected->m_TilePos.x = -1;
    m_ObjectSelected->m_TilePos.y = -1;
    m_ObjectSelected->m_ObjShape.setPosition(-1,-1);
    m_ObjectSelected->m_ObjShape.setSize(sf::Vector2f(0,0));
}
void Controler::Treasure(int _Treasure)
{
    m_Treasure += _Treasure;
}
