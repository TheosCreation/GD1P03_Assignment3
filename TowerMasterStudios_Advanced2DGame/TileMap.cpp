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
            tileMap[x][y].m_Tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].m_Tile.setOutlineThickness(1.0f);
            tileMap[x][y].m_Tile.setOutlineColor(sf::Color::Black);
            tileMap[x][y].m_Pos = sf::Vector2i(x, y);
            tileMap[x][y].m_Tile.setPosition(x * gridSizeF, y * gridSizeF);
            int Seed = rand() % 100;
            if (Seed % 5 == 0) {
                tileMap[x][y].m_TileType = TileType(rand() % 2);
            }
            //summons tilemap tiles? i think
 
            switch (tileMap[x][y].m_TileType)
            {
                //defines property of tiles 
            case Type_Water:
                tileMap[x][y].m_Tile.setFillColor(sf::Color::Blue);
                break;
            case Type_Mine:
                tileMap[x][y].m_Tile.setTexture(BombTexture);
                break;
            case Type_Treasure:
                tileMap[x][y].m_Tile.setFillColor(sf::Color::Yellow);
                break;
            default:
                break;
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
            _window->draw(tileMap[x][y].m_Tile);
        }
    }
}

void TileMap::update(sf::View _view, Controler* _ctrl)
{
    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].ObjInTile(_ctrl);
        }
    }
    
    // tile map position x updates
    fromX = _view.getCenter().x / gridSizeF - 10;
    toX = _view.getCenter().x / gridSizeF + 11;

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
    fromY = _view.getCenter().y / gridSizeF - 6;
    toY = _view.getCenter().y / gridSizeF + 7;

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
