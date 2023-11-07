#include <sstream>
#include "Controler.h"
#include "TileMap.h"

#include <iostream>
// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 
/*
minesweeper pirate game
walk around, find tresure using mindsweeper strats and avoid mines 
its a vs game a competition
\ai just moves randomly (haha they are stupid)
*/
int main()
{
    // game variables
    float _dt = 0.0f;
    sf::Clock dtClock;

    // grid variables
    float gridSizeF = 64.0f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    Controler ObjHandler;
    // object variables 
  /*  Object EnemyObjArray[20];
    int ArrayPos = 0;
    for (int i = 1; i < 3; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            
         
            EnemyObjArray[ArrayPos].initObject(Type_EnemyPiece, sf::Vector2f(j, i), 100.0f);
            ArrayPos++;
           
        }
    }*/
    bool testvar = true;
  
    // mouse variables
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;    
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    // ui variables
    sf::Font font;
    font.loadFromFile("Assets/Fonts/HWYGOTH.TTF");

    sf::Text text;
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Green);
    text.setFont(font);
    text.setPosition(20.0f, 20.0f);

    //controler
    ObjHandler.InstObjects();

    // window stuff
    sf::Vector2f WindowSize(1920, 1080);

    sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Pirate Minesweeper");
    window.setFramerateLimit(60);

    // viewport stff
    sf::View view;
    view.setSize(WindowSize);
    
    //view.setCenter(window.getSize().x/2.0f, window.getSize().y / 2.0f);
    float viewSpeed = 300.0f;

    // game objects

    // tilemap
    int mapsize = 20;
    TileMap tileMap(mapsize, gridSizeF);

    int tilemapcenter = (mapsize * gridSizeF) / 2 - 1;

    //set the initial start position of the view
    view.setCenter(tilemapcenter, tilemapcenter);

    // tile selector
    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.0f);
    tileSelector.setOutlineColor(sf::Color::Green);
    int a = 0;
    while (window.isOpen())
    {
        // update dt
        _dt = dtClock.restart().asSeconds();


        // update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.0f){
            mousePosGrid.x = mousePosView.x / gridSizeU;
        }
        if (mousePosView.y >= 0.0f) {
            mousePosGrid.y = mousePosView.y / gridSizeU;
        }
        // update game
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
    /*
        if(testvar){
        for (int i = 0; i < 8; i++)
        {

            if(tileMap.tileMap[12][6].m_Neighbours[i]!=NULL){
            std::cout << tileMap.tileMap[2][2].m_Neighbours << std::endl;
            }
        }
        testvar = false;
        }
*/
        // update ui
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
            << "Treasure: " << ObjHandler.m_Treasure << "\n";

        text.setString(ss.str());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                ObjHandler.SelectObj(mousePosGrid);
            }
        }

        //Update
        

        //Update Input
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(-viewSpeed * _dt, 0.0f);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(viewSpeed * _dt, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0.0f, -viewSpeed * _dt);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0.0f, viewSpeed * _dt);
        }

        // tilemap update
        tileMap.update(view, &ObjHandler);

        // draw
        window.clear();
        window.setView(view);

        // draw game
        tileMap.draw(&window);
 
     /*   for (Object obj : EnemyObjArray)
        {
            
          
            obj.draw(&window);
        } 
    */
        for (Object* obj : ObjHandler.AllyObjArray)
        {
            obj->Update();
            obj->draw(&window);
        }
        window.draw(tileSelector);

        window.setView(window.getDefaultView());

        // draw ui
        window.draw(text);

        window.display();
    }

    return 0;
}