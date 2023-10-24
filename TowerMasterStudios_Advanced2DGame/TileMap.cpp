#include "TileMap.h"

TileMap::TileMap(int _mapSize, float _gridSizeF)
{
    gridSizeF = _gridSizeF;
    mapSize = _mapSize;
    tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

    for (int x = 0; x < mapSize; x++)
    {
        tileMap[x].resize(mapSize, sf::RectangleShape());
        for (int y = 0; y < mapSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(1.0f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
        }
    }
}

void TileMap::draw(sf::RenderWindow* _window)
{
    for (int x = fromX; x < toX; x++)
    {
        for (int y = fromY; y < toY; y++)
        {
            _window->draw(tileMap[x][y]);
        }
    }
}

void TileMap::update(sf::View _view)
{
    
    // tile map position x updates
    fromX = _view.getCenter().x / gridSizeF - 5;
    toX = _view.getCenter().x / gridSizeF + 6;

    if (fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize;

    if (toX < 0)
        toX = 0;
    else if (toX >= mapSize)
        toX = mapSize;

    // tile map position y updates
    fromY = _view.getCenter().y / gridSizeF - 5;
    toY = _view.getCenter().y / gridSizeF + 6;

    if (fromY < 0)
        fromY = 0;
    else if (fromY >= mapSize)
        fromY = mapSize;

    if (toY < 0)
        toY = 0;
    else if (toY >= mapSize)
        toY = mapSize;
}
