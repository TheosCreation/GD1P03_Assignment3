#include "Controler.h"
#include "EnemyControler.h"
#include "TileMap.h"
#include "Debug.h"
#include "FileManager.h"
#include <SFML/Audio.hpp>
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
    // Loaded Variables
    bool _VSync = false;
    bool _Debug = false;
    int Volume = false;
    sf::Vector2f WindowSize(1700, 1080);

    FileManager fileManager;
    fileManager.LoadValuesFromFile("Assets/Config.txt", _VSync, _Debug, WindowSize, Volume);

    // game variables
    float _dt = 0.0f;
    sf::Clock dtClock;

    // grid variables
    float gridSizeF = 64.0f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    Controler ObjHandler;

    bool testvar = true;

    // Window Creation
    sf::RenderWindow Window(sf::VideoMode(WindowSize.x, WindowSize.y), "Pirate Minesweeper");
    Window.setVerticalSyncEnabled(_VSync);
    Window.setFramerateLimit(60);

    // Viewport Creation
    float viewSpeed = 300.0f;
    sf::View view;
    view.setSize(WindowSize);

    // Music Creation
    sf::Music music;

    // Change some parameters
    music.openFromFile("Assets/Sounds/Music.ogg");
    music.setVolume(Volume);
    music.setLoop(true);
    music.play();

    // Mouse variables
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;    
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    // Font Creation
    sf::Font font;
    font.loadFromFile("Assets/Fonts/HWYGOTH.TTF");

    // Debug
    sf::Text DebugText;
    DebugText.setCharacterSize(16);
    DebugText.setFillColor(sf::Color::Green);
    DebugText.setFont(font);
    DebugText.setPosition(20.0f, 20.0f);


    //Debug Window
    sf::RenderWindow DebugWindow(sf::VideoMode(WindowSize.x/4, WindowSize.y/4), "Debug Window");
    DebugWindow.setPosition(sf::Vector2i(Window.getPosition().x - (400 + 50), Window.getPosition().y));
    DebugWindow.setFramerateLimit(60);
    DebugWindow.setVisible(_Debug);

    // Debuging Entry for Gravity
    Debug g_ViewSpeed(sf::Vector2f(320, 10), sf::Vector2f(360, 10), sf::Vector2f(20, 20), font, sf::Vector2f(10, 10),
        sf::Vector2f(325, 10), sf::Vector2f(365, 10), 15);
    g_ViewSpeed.m_TitleText.setString("ViewSpeed");
    g_ViewSpeed.m_ButtonUpText.setString("+");
    g_ViewSpeed.m_ButtonDownText.setString("-");
    Debug g_Save(sf::Vector2f(320, 50), sf::Vector2f(360, 50), sf::Vector2f(20, 20), font, sf::Vector2f(10, 50),
        sf::Vector2f(325, 50), sf::Vector2f(365, 50), 15);
    g_Save.m_TitleText.setString("Save");
    g_Save.m_ButtonUpText.setString("+");
    g_Save.m_ButtonDownText.setString("-");

    // controler
    ObjHandler.LoadFromFile("Assets/Battles/Battle3.txt");
    EnemyControler EnemyHandler;
    EnemyHandler.InstObjects(ObjHandler);

    // tilemap
    int mapsize = 20;
    TileMap tileMap(mapsize, gridSizeF);

    int tilemapcenter = (mapsize * gridSizeF) / 2 - 1;

    //sets the initial start position of the view
    view.setCenter(tilemapcenter, tilemapcenter);

    // tile selector
    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.0f);
    tileSelector.setOutlineColor(sf::Color::Green);

    for (int x = 0; x < tileMap.mapSize; x++)
    {
  
        for (int y = 0; y < tileMap.mapSize; y++)
        {
            tileMap.tileMap[x][y].SetNeighbours();
        }

    }
    
    while (Window.isOpen())
    {
        // update dt
        _dt = dtClock.restart().asSeconds();
        //play music
        

        // update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(Window);
        Window.setView(view);
        mousePosView = Window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.0f){
            mousePosGrid.x = mousePosView.x / gridSizeU;
        }
        if (mousePosView.y >= 0.0f) {
            mousePosGrid.y = mousePosView.y / gridSizeU;
        }
        // update game
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        // update ui
        int DisplayMineCount = -1;
        int DisplayTreasureCount= -1;
        if (mousePosGrid.x < tileMap.mapSize && mousePosGrid.y < tileMap.mapSize ) {
            if(tileMap.tileMap[mousePosGrid.x][mousePosGrid.y].m_Explored){
                DisplayMineCount = tileMap.tileMap[mousePosGrid.x][mousePosGrid.y].m_MineCount;
                DisplayTreasureCount = tileMap.tileMap[mousePosGrid.x][mousePosGrid.y].m_TresureCount;
            }
            else {
                DisplayMineCount = -1;
                DisplayTreasureCount = -1;
            }
        }
       
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
            << "Treasure: " << ObjHandler.m_Treasure << "\n"
            << "Nearby Mines: " << DisplayMineCount << "\n"
            << "Nearby Treasure: " << DisplayTreasureCount << "\n";

        DebugText.setString(ss.str());

        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                
                
                EnemyHandler.MoveTile(ObjHandler.SelectObj(mousePosGrid));
            }
            
        }
        sf::Event DebugEvent;
        while (DebugWindow.pollEvent(DebugEvent))
        {
            // Exit and close the Debug window
            if (DebugEvent.type == sf::Event::Closed)
            {
                DebugWindow.setVisible(false);
            }
            // Checks mouse pressed
            if (DebugEvent.type == sf::Event::MouseButtonPressed)
            {

                // View Speed Increase
                if (g_ViewSpeed.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    viewSpeed += 100.0f;
                    g_ViewSpeed.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                   
                }
                // View Speed decrease
                if (g_ViewSpeed.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    viewSpeed -= 100.0f;
                    g_ViewSpeed.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                } 
                if (g_Save.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    tileMap.save("SavedGame");
                    EnemyHandler.save();
                    ObjHandler.save();
                    g_Save.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                   
                }
                // View Speed decrease
                if (g_Save.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    //delete &ObjHandler;
                    ObjHandler = Controler();
                    ObjHandler.LoadFromFile("Assets/Saved/SavedBattle.txt");
                    EnemyHandler.InstObjects(ObjHandler);
                    g_Save.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                }
            }
            if (DebugEvent.type == sf::Event::MouseButtonReleased) {
                g_ViewSpeed.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_ViewSpeed.m_ButtonDownVisual.setFillColor(sf::Color::Transparent); 
                g_Save.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_Save.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
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
        tileMap.update(view, &ObjHandler, &EnemyHandler);

        // draw
        Window.clear();
        Window.setView(view);

        // draw game
        tileMap.draw(&Window);

        // update and draw objects
        for (Object* obj : ObjHandler.AllyObjArray)
        {
            obj->Update();
            obj->draw(&Window);
        }  
      
        for (Object* obj : ObjHandler.EnemyObjArray)
        {
            obj->Update();
            obj->draw(&Window);
        }
        Window.draw(tileSelector);

        Window.setView(Window.getDefaultView());

        // draw debug
        Window.draw(DebugText);

        Window.display();
        
        // if debug is true in file update and draw to debug window
        if (_Debug) {
            DebugWindow.clear();
            g_ViewSpeed.Draw(&DebugWindow);
            g_Save.Draw(&DebugWindow);
            DebugWindow.display();
        }
    }

    return 0;
}