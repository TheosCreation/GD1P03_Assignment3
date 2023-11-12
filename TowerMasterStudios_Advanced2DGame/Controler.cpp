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

bool Controler::SelectObj(sf::Vector2u _GridMousePos)
{
    m_Moved = false;
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
            m_Moved = true;
            
        }
        else {
            m_HasSelected = false;
        }
    }
    return m_Moved;
    
}

void Controler::Destroy()
{
    if(m_ObjectSelected!= nullptr){
     m_ObjectSelected->m_TilePos.x = -1;
     m_ObjectSelected->m_TilePos.y = -1;
     m_ObjectSelected->m_ObjShape.setPosition(-1,-1);
     m_ObjectSelected->m_ObjShape.setSize(sf::Vector2f(0,0));
    }
}
void Controler::Treasure(int _Treasure)
{
    m_Treasure += _Treasure;
}

void Controler::LoadFromFile(std::string _fileName)
{
    std::ifstream ObjFile(_fileName);

    if (!ObjFile) {
        std::cout << "File not found" << std::endl;
        return;
    }

    int x = 0;
    int y = 0;
    int ArrayPos = 0;
    char Type;
    bool Ally = true;
    Object* NewObject = nullptr;

    while (ObjFile >> Type) {
        if (Type == 'a') {
            std::cerr << "a: " << "\n";
            continue;
        }
        if (Type == 'e') {
            std::cerr << "e: " << "\n";
            Ally = false;
            ArrayPos = 0;
            continue;
        }

        ObjFile >> x >> y;
        if (Ally) {
            switch (Type)
            {
            case 'c':

                std::cerr << "c: " << x << " " << y << "\n";

                NewObject = new Object(Type_AllyPiece, Type_Cruise, sf::Vector2f(x, y), 64.0f);
                break;
            case 'j':
                std::cerr << "j: " << x << " " << y << "\n";
                NewObject = new Object(Type_AllyPiece, Type_JetSki, sf::Vector2f(x, y), 64.0f);
                break;
            case 'p':
                std::cerr << "p: " << x << " " << y << "\n";
                NewObject = new Object(Type_AllyPiece, Type_PirateShip, sf::Vector2f(x, y), 64.0f);
                break;
            default:
                std::cerr << "Unknown object type: " << Type << std::endl;
                continue; // Skip to the next iteration of the loop
            }
        
            std::cerr << ArrayPos << "\n";
            AllyObjArray[ArrayPos++] = NewObject;
        }
        else {
            switch (Type)
            {
            case 'c':

                std::cerr << "c: " << x << " " << y << "\n";

                NewObject = new Object(Type_EnemyPiece, Type_Cruise, sf::Vector2f(x, y), 64.0f);
                break;
            case 'j':
                std::cerr << "j: " << x << " " << y << "\n";
                NewObject = new Object(Type_EnemyPiece, Type_JetSki, sf::Vector2f(x, y), 64.0f);
                break;
            case 'p':
                std::cerr << "p: " << x << " " << y << "\n";
                NewObject = new Object(Type_EnemyPiece, Type_PirateShip, sf::Vector2f(x, y), 64.0f);
                break;
            default:
                std::cerr << "Unknown object type: " << Type << std::endl;
                continue; // Skip to the next iteration of the loop
            }

            std::cerr << ArrayPos << "\n";
            EnemyObjArray[ArrayPos++] = NewObject;
        }
        
    }
    for (int i = 0; i < 10; i++)
    {
      //  std::cout << EnemyObjArray[i] << std::endl;
    }
    
}