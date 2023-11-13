#include "EnemyControler.h"
EnemyControler::EnemyControler()
{
  
    
}
EnemyControler::~EnemyControler()
{
}
void EnemyControler::InstObjects(Controler _ControlerRef)
{
    m_AllyControlerRef = &_ControlerRef;

    for (int i = 0; i < 10; i++) {
        m_EnemyObjArray[i] = m_AllyControlerRef->EnemyObjArray[i];
    }
}

void EnemyControler::MoveTile(bool _Move)
{
    if ( _Move) {
        int random = rand() % ArraySize;
        int maxMove = m_EnemyObjArray[random]->m_MaxMoveDistance;
        m_MovedObj = m_EnemyObjArray[random];
     //   maxMove = 1;
        bool ableToSet = false;

        int newPosX;
        int newPosY;
        std::vector<int> oldPosX;
        std::vector<int> oldPosY;
        int MaxWhile = 0;
        while (!ableToSet && MaxWhile<8) {
            MaxWhile++;
            bool work = true;;
            int MaxWhileX = 0;
            int MaxWhileY = 0;
            do{
             newPosX = (rand() % (maxMove * 2) - maxMove) * 64
            + m_EnemyObjArray[random]->m_Pos.x;
             MaxWhileX++;
            }
            while (std::find(oldPosX.begin(), oldPosX.end(), newPosX) != oldPosX.end()||int(newPosX/64)>20 || int(newPosX / 64) < 0&& MaxWhileX <8);
            do {
                newPosY = (rand() % (maxMove * 2) - maxMove) * 64
                    + m_EnemyObjArray[random]->m_Pos.y;
                MaxWhileY++;
            }
            while (std::find(oldPosY.begin(), oldPosY.end(), newPosY) != oldPosY.end()||int(newPosY/64)>19 || int(newPosY / 64) < 1&& MaxWhile<8);
   
            for (int i = 0; i < 10; i++)
            {
                if (m_EnemyObjArray[random]->m_ObjShape.getPosition() == sf::Vector2f(newPosX, newPosY)) {
                    oldPosX.push_back(newPosX);
                    oldPosY.push_back(newPosY);
                    work = false;
                    break;
                }      
            }
            if (work) {
                m_EnemyObjArray[random]->m_ObjShape.setPosition(newPosX, newPosY);
                ableToSet = true;
            }
        }
        m_MovedToTile = sf::Vector2f(int(newPosX/64) , int(newPosY/64));
    }
}
void EnemyControler::Destroy()
{
    m_Health--;
    if (m_MovedObj != nullptr) {
        m_MovedObj->m_TilePos.x = -1;
        m_MovedObj->m_TilePos.y = -1;
        m_MovedObj->m_ObjShape.setPosition(-1, -1);
        m_MovedObj->m_ObjShape.setSize(sf::Vector2f(0, 0));
    }
}
void EnemyControler::Treasure(int _Treasure)
{
    m_Treasure += _Treasure;
}

void EnemyControler::save()
{
    std::ofstream SavedEnemies("Assets/Saved/Enemies.txt");
    SavedEnemies << "e" << std::endl;
    char type = ' ';
    for (int i = 0; i < 10; i++) {
        switch (m_EnemyObjArray[i]->m_UnitType)
        {
        case Type_Cruise:
            type = 'c';
            break;
        case Type_JetSki:
            type = 'j';
            break;
        case Type_PirateShip:
            type = 'p';
            break;
        default:
            break;
        }
    
        SavedEnemies << type << " " << m_EnemyObjArray[i]->m_TilePos.x << " " << m_EnemyObjArray[i]->m_TilePos.y << std::endl;
    }
    SavedEnemies.close();
    
}
void EnemyControler::LoadFromFile(std::string _fileName)
{
    std::ifstream ObjFile(_fileName);

    if (!ObjFile) {
        std::cerr << "File not found" + _fileName << std::endl;
        ObjFile.close();
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
            continue;
        }
        if (Type == 'e') {
            Ally = false;
            ArrayPos = 0;
            continue;
        }

        ObjFile >> x >> y;
        
        if(!Ally){
            switch (Type)
            {
            case 'c':
                NewObject = new Object(Type_EnemyPiece, Type_Cruise, sf::Vector2f(x, y), 64.0f);
                break;
            case 'j':
                NewObject = new Object(Type_EnemyPiece, Type_JetSki, sf::Vector2f(x, y), 64.0f);
                break;
            case 'p':
                NewObject = new Object(Type_EnemyPiece, Type_PirateShip, sf::Vector2f(x, y), 64.0f);
                break;
            default:
                std::cerr << "Unknown object type: " << Type << std::endl;
                continue; // Skip to the next iteration of the loop
            }
            m_EnemyObjArray[ArrayPos] = NewObject;
            ArrayPos++;
            std::cout << ArrayPos << std::endl;
        }

    }
 
    ObjFile.close();
}