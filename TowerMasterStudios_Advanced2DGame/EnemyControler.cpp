#include "EnemyControler.h"
EnemyControler::EnemyControler(Controler _ControlerRef)
{
  
    m_AllyControlerRef = &_ControlerRef;
    
    for (int i = 0; i < 10; i++) {
        m_EnemyObjArray[i] =  m_AllyControlerRef->EnemyObjArray[i];
    }
    std::cout << "x: " << m_AllyControlerRef->m_Moved << std::endl;
}
EnemyControler::~EnemyControler()
{
}
void EnemyControler::InstObjects()
{
    /*int ArrayPos = 0;
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
    }*/
    
    for (int i = 0; i < 10; i++) {
       //m_EnemyObjArray.push_back( m_AllyControlerRef->EnemyObjArray[i]);
       //m_EnemyObjArray.push_back( m_AllyControlerRef->EnemyObjArray[i]);
      std::cout << m_EnemyObjArray[i] <<std::endl;
    }
}

void EnemyControler::MoveTile(bool _Move)
{
   
    
    if (m_AllyControlerRef->m_HasSelected&& m_AllyControlerRef->m_Moved  && _Move) {
        
        int random = rand() % ArraySize;
        int maxMove = m_EnemyObjArray[random]->m_MaxMoveDistance;
        maxMove = 1;
        bool ableToSet = false;
       // std::cout << rand() % maxMove << std::endl;

        int newPosX;
        int newPosY;
        std::vector<int> oldPosX;
        std::vector<int> oldPosY;

        while (!ableToSet) {
            bool work = true;;
            do{
             newPosX = (rand() % (maxMove * 2) - maxMove) * 64
            + m_EnemyObjArray[random]->m_Pos.x;
            }
            while (std::find(oldPosX.begin(), oldPosX.end(), newPosX) != oldPosX.end());
            do {
                newPosY = (rand() % (maxMove * 2) - maxMove) * 64
                    + m_EnemyObjArray[random]->m_Pos.y;

            } while (std::find(oldPosY.begin(), oldPosY.end(), newPosY) != oldPosY.end());

   
            for (int i = 0; i < 10; i++)
            {
                if (m_EnemyObjArray[random]->m_ObjShape.getPosition() == sf::Vector2f(newPosX, newPosY)) {
                    oldPosX.push_back(newPosX);
                    oldPosY.push_back(newPosY);
                    work = false;
                    break;
                }      
            }
            if(work){
             m_EnemyObjArray[random]->m_ObjShape.setPosition(newPosX, newPosY);
             ableToSet = true;
            }

        }
            
        for (int i = 0; i < 10; i++) {
         /*   std::cout << i << std::endl;
            std::cout <<"X: " << m_EnemyObjArray[i]->m_ObjShape.getPosition().x << std::endl;
            std::cout <<"Y: " << m_EnemyObjArray[i]->m_ObjShape.getPosition().y << std::endl;
            */
        }
    }
}
