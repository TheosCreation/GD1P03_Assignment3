#include "TileMap.h"

TileMap::TileMap(int _mapSize, float _gridSizeF)
{
    if (BombTexture) {
        BombTexture->loadFromFile("Assets/Sprites/Bomb.png");
    }
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    gridSizeF = _gridSizeF;
    mapSize = _mapSize;
    tileMap.resize(mapSize);

    for (int x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize);
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].m_TileSprite.setPosition(x * gridSizeF, y * gridSizeF);
            tileMap[x][y].m_Pos = sf::Vector2i(x, y);
           
       
            int Seed = rand() % 100;
            if (Seed % 4 == 0) {
                tileMap[x][y].m_TileType = TileType(rand() % 2);
            }
            //summons tilemap tiles? i think
            if (x == 1 && y == 1) {
                tileMap[x][y].m_TileType = Type_Mine;
            }

            tileMap[x][y].SetSprite("Assets/Sprites/Water.png");
            //switch (tileMap[x][y].m_TileType)
            //{
            ////defines property of tiles 
            //case Type_Water:
            //    tileMap[x][y].SetSprite("Assets/Sprites/Water.png");
            //    break;
            //case Type_Mine:
            //    tileMap[x][y].SetSprite("Assets/Sprites/Bomb.png");
            //    break;
            //case Type_Treasure:
            //    tileMap[x][y].SetSprite("Assets/Sprites/Treasure.png");
            //    break;
            //default:
            //    break;
            //}
        }
    }
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            int NeighbourCount = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {

                    if (i != 0 || j != 0) {

                        int newX = x + i;
                        int newY = y + j;

                        if (newX >= 0 && newX < mapSize && newY >= 0 && newY < mapSize)
                        {
                            tileMap[x][y].m_Neighbours[NeighbourCount] = &tileMap[newX][newY];
                            NeighbourCount++;
                            
                        }
                    }
                }
            }
        }
    }
}

void TileMap::draw(sf::RenderWindow* _window)
{
    for (int x = fromX; x < toX; x++)
    {
        for (int y = fromY; y < toY; y++)
        {
            _window->draw(tileMap[x][y].m_TileSprite);
        }
    }
}

void TileMap::update(sf::View _view, Controler* _ctrl, EnemyControler* _ectrl)
{
    ShowingMine = ShowingMine < 200 ? ShowingMine + 1 : 0;
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].ObjInTile(_ctrl, _ectrl);
            if (tileMap[x][y].m_Explored) {
                tileMap[x][y].Update(ShowingMine);
            }
            
        }
    }
    
    // tile map position x updates
    fromX = _view.getCenter().x / gridSizeF - 15;
    toX = _view.getCenter().x / gridSizeF + 16;

    if (fromX < 0)
    {
        fromX = 0;
    }
    else if (fromX >= mapSize)
    {
        fromX = mapSize;
    }

    if (toX < 0){
        toX = 0;
    }
    else if (toX >= mapSize) {
        toX = mapSize;
    }
    // tile map position y updates
    fromY = _view.getCenter().y / gridSizeF - 10;
    toY = _view.getCenter().y / gridSizeF + 11;

    if (fromY < 0)
    {
        fromY = 0;
    }
    else if (fromY >= mapSize)
    {
        fromY = mapSize;
    }

    if (toY < 0)
    {
        toY = 0;
    }
    else if (toY >= mapSize)
    {
        toY = mapSize;
    }   
    
}

void TileMap::save(std::string _FileName)
{

    std::ofstream SavedGame("Assets/Saved/"+_FileName + ".txt");
    for (int y = 0; y < mapSize; y++)
    {

        for (int x = 0; x < mapSize; x++)
        {
            SavedGame << " t " << std::to_string(tileMap[x][y].m_TileType) << " " << std::to_string(tileMap[x][y].m_Explored)
                << " " << std::to_string(tileMap[x][y].Active) << " " <<
                std::to_string(tileMap[x][y].m_TresureCount) << " " << std::to_string(tileMap[x][y].m_MineCount) << " g ";
        }
        SavedGame << '\n';
    }
    SavedGame.close();

}

void TileMap::load(std::string _FileName)
{
    std::ifstream ObjFile(_FileName);
    
    if (!ObjFile) {
        std::cerr << "File not found" + _FileName << std::endl;
        ObjFile.close();
        return;
    }

 
    int ArrayPos = 0;
    char t;
    char Type;
    char Explored;
    char Act;
    bool Ally = true;
    Object* NewObject = nullptr;  
    tileMap.resize(mapSize);
    
    
    int y = 0;
    int a = 0;
    for (std::string line; std::getline(ObjFile, line); )
    {
        int x = -1;
        if (x <= mapSize && y <= mapSize) {
           
            int switcher = 0;
            for (char ch : line) {
                
                
                switch (ch) {
                case 't':
                    switcher = 0;
                    x++;
                    break;
                case ' ':
                    break;
                case 'g':
                    tileMap[x][y].m_TileSprite.setPosition(x * gridSizeF, y * gridSizeF);
                    tileMap[x][y].m_Pos = sf::Vector2i(x, y);
                    
                     tileMap[x][y].SetSprite("Assets/Sprites/Water.png");
                    break;
                default:
                    switcher++;
                    switch (switcher) {
                    case 1:
                        tileMap[x][y].m_TileType = TileType(ch - '0');
                        break;
                    case 2:
                        tileMap[x][y].m_Explored = bool(ch - '0');
                        break;
                    case 3:
                        tileMap[x][y].Active = bool(ch - '0');
                        break;
                    case 4:
                        tileMap[x][y].m_TresureCount = int(ch - '0');
                        break;
                    case 5:
                        tileMap[x][y].m_MineCount = int(ch - '0');
                        break;
                    default:
                        std::cout << "aaaa";
                        break;
                    }
                    break;
                }
            }
            y++;
        }
    }
  
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].SetNeighbours();
        }
    }
    ObjFile.close();
}
