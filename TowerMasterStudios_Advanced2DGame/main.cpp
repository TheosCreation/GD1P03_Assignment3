#include "Controler.h"
#include "EnemyControler.h"
#include "TileMap.h"
#include "Button.h"
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
    view.setSize(sf::Vector2f(WindowSize.x/1.6, WindowSize.y/1.6));

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
    
    // Ui For Treasure
    sf::Text Ui;
    Ui.setCharacterSize(64);
    Ui.setFillColor(sf::Color::Green);
    Ui.setFont(font);
    Ui.setPosition(100.0f, 20.0f);


    //Debug Window
    sf::RenderWindow DebugWindow(sf::VideoMode(WindowSize.x/4, WindowSize.y/4), "Debug Window");
    DebugWindow.setPosition(sf::Vector2i(Window.getPosition().x - (400 + 50), Window.getPosition().y));
    DebugWindow.setFramerateLimit(60);
    DebugWindow.setVisible(_Debug);
    
    // Win and Lose Screens
    sf::RenderWindow WinScreen(sf::VideoMode(WindowSize.x, WindowSize.y), "You Win");
    WinScreen.setPosition(sf::Vector2i(Window.getPosition().x, Window.getPosition().y));
    WinScreen.setFramerateLimit(60);
    WinScreen.setVisible(false);
    
    sf::RenderWindow LoseScreen(sf::VideoMode(WindowSize.x, WindowSize.y), "You Lose");
    LoseScreen.setPosition(sf::Vector2i(Window.getPosition().x, Window.getPosition().y));
    LoseScreen.setFramerateLimit(60);
    LoseScreen.setVisible(false);

    //Menu Buttons
    Button g_PlayAgain(sf::Vector2f(800, 800), sf::Vector2f(230, 70), font, sf::Vector2f(805, 800), 50);
    g_PlayAgain.m_ButtonUpText.setString("Play Again");

    //Debug Buttons
    Button g_ViewSpeed(sf::Vector2f(320, 10), sf::Vector2f(360, 10), sf::Vector2f(20, 20), font, sf::Vector2f(10, 10),
        sf::Vector2f(325, 10), sf::Vector2f(365, 10), 15);
    g_ViewSpeed.m_TitleText.setString("ViewSpeed");
    g_ViewSpeed.m_ButtonUpText.setString("+");
    g_ViewSpeed.m_ButtonDownText.setString("-");
    
    Button g_Save(sf::Vector2f(310, 50), sf::Vector2f(360, 50), sf::Vector2f(40, 20), font, sf::Vector2f(10, 50),
        sf::Vector2f(315, 50), sf::Vector2f(365, 50), 15);
    g_Save.m_TitleText.setString("Saving/Loading");
    g_Save.m_ButtonUpText.setString("Save");
    g_Save.m_ButtonDownText.setString("Load");
    
    Button g_VSync(sf::Vector2f(295, 80), sf::Vector2f(360, 80), sf::Vector2f(55, 20), font, sf::Vector2f(10, 80),
        sf::Vector2f(300, 80), sf::Vector2f(365, 80), 15);
    g_VSync.m_TitleText.setString("VSync");
    g_VSync.m_ButtonUpText.setString("Enable");
    g_VSync.m_ButtonDownText.setString("Disable");

    Button g_Volume(sf::Vector2f(320, 110), sf::Vector2f(360, 110), sf::Vector2f(20, 20), font, sf::Vector2f(10, 110),
        sf::Vector2f(325, 110), sf::Vector2f(365, 110), 15);
    g_Volume.m_TitleText.setString("Volume");
    g_Volume.m_ButtonUpText.setString("+");
    g_Volume.m_ButtonDownText.setString("-");
    
    Button g_GameOver(sf::Vector2f(295, 140), sf::Vector2f(360, 140), sf::Vector2f(55, 20), font, sf::Vector2f(10, 140),
        sf::Vector2f(300, 140), sf::Vector2f(365, 140), 15);
    g_GameOver.m_TitleText.setString("Game Over");
    g_GameOver.m_ButtonUpText.setString("Enable");
    g_GameOver.m_ButtonDownText.setString("Disable");
    
    Button g_GameWin(sf::Vector2f(295, 170), sf::Vector2f(360, 170), sf::Vector2f(55, 20), font, sf::Vector2f(10, 170),
        sf::Vector2f(300, 170), sf::Vector2f(365, 170), 15);
    g_GameWin.m_TitleText.setString("Game Win");
    g_GameWin.m_ButtonUpText.setString("Enable");
    g_GameWin.m_ButtonDownText.setString("Disable");

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
        
        // update volume
        music.setVolume(Volume);

        // update mouse positions
        Window.setView(view);
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(Window);
        
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
       
        std::stringstream Treasure;
        Treasure << "Treasure: " << ObjHandler.m_Treasure << "\n"
            << "Enemy Treasure: " << EnemyHandler.m_Treasure << "\n";
        Ui.setString(Treasure.str());

        std::stringstream ss;
        if (_Debug) {
            ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
                << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
                << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
                << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
                << "Treasure: " << ObjHandler.m_Treasure << "\n"
                << "Nearby Mines: " << DisplayMineCount << "\n"
                << "Nearby Treasure: " << DisplayTreasureCount << "\n";
        }
        
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
            if (_Debug && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tilde)
            {
                DebugWindow.setVisible(true);
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
                    std::cerr << viewSpeed << std::endl;
                   
                }
                // View Speed decrease
                if (g_ViewSpeed.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    viewSpeed -= 100.0f;
                    g_ViewSpeed.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << viewSpeed << std::endl;
                } 

                // Save game
                if (g_Save.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    tileMap.save("SavedGame");
                    EnemyHandler.save();
                    ObjHandler.save();
                    g_Save.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << "Saved Game" << std::endl;
                   
                }
                // Load Game
                if (g_Save.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    //delete &ObjHandler;
                    tileMap.load("Assets/Saved/SavedGame.txt");
                    ObjHandler = Controler();
                    ObjHandler.LoadFromFile("Assets/Saved/SavedBattle.txt");
                    EnemyHandler.InstObjects(ObjHandler);
                    g_Save.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << "Loaded Game" << std::endl;
                }
                
                // VSync Enable
                if (g_VSync.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    _VSync = true;
                    g_VSync.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << _VSync << std::endl;
                }
                // VSync Disable
                if (g_VSync.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    _VSync = false;
                    g_VSync.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << _VSync << std::endl;
                }

                // Volume up
                if (g_Volume.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    if (Volume < 100) {
                        Volume += 10;
                    }
                    g_Volume.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << Volume << "%" << std::endl;
                }
                // Volume down
                if (g_Volume.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    if (Volume > 0) {
                        Volume -= 10;
                    }
                    g_Volume.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << Volume << "%" << std::endl;
                }

                // GameWin Enable
                if (g_GameWin.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    ObjHandler.GameWin = true;
                    g_GameWin.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << ObjHandler.GameWin << std::endl;
                }
                // GameWin Disable
                if (g_GameWin.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    ObjHandler.GameWin = false;
                    g_GameWin.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << ObjHandler.GameWin << std::endl;
                }
                
                // GameOver Enable
                if (g_GameOver.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    ObjHandler.GameOver = true;
                    g_GameOver.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << ObjHandler.GameOver << std::endl;
                }
                // GameOver Disable
                if (g_GameOver.m_ButtonDownVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(DebugWindow))))
                {
                    ObjHandler.GameOver = false;
                    g_GameOver.m_ButtonDownVisual.setFillColor(sf::Color::Green);
                    std::cerr << ObjHandler.GameOver << std::endl;
                }
            }
            if (DebugEvent.type == sf::Event::MouseButtonReleased) {
                g_ViewSpeed.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_ViewSpeed.m_ButtonDownVisual.setFillColor(sf::Color::Transparent); 
                g_Save.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_Save.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
                g_VSync.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_VSync.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
                g_Volume.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_Volume.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
                g_GameWin.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_GameWin.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
                g_GameOver.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_GameOver.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
            }
        }
        if (ObjHandler.GameWin) {
            WinScreen.setVisible(true);
        }
        else {
            WinScreen.setVisible(false);
        }
        sf::Event WinScreenEvent;
        while (WinScreen.pollEvent(WinScreenEvent))
        {
            if (WinScreenEvent.type == sf::Event::MouseButtonPressed)
            {
                if (g_PlayAgain.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(WinScreen))))
                {
                    g_PlayAgain.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << "Play Again Selected" << std::endl;
                    DebugWindow.close();
                    Window.close();
                    WinScreen.close();
                    LoseScreen.close();
                    main();
                }
            }
            if (WinScreenEvent.type == sf::Event::MouseButtonReleased) {
                g_PlayAgain.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_PlayAgain.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
            }
        }

        if (ObjHandler.GameOver) {
            LoseScreen.setVisible(true);
        }
        else {
            LoseScreen.setVisible(false);
        }
        sf::Event LoseScreenEvent;
        while (LoseScreen.pollEvent(LoseScreenEvent))
        {
            if (LoseScreenEvent.type == sf::Event::MouseButtonPressed)
            {
                if (g_PlayAgain.m_ButtonUpVisual.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(LoseScreen))))
                {
                    main();
                    g_PlayAgain.m_ButtonUpVisual.setFillColor(sf::Color::Green);
                    std::cerr << "Play Again Selected" << std::endl;
                }
            }
            if (LoseScreenEvent.type == sf::Event::MouseButtonReleased) {
                g_PlayAgain.m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
                g_PlayAgain.m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
            }
        }
        
        //Update Input
        sf::Vector2f topLeft = Window.mapPixelToCoords(sf::Vector2i(0, 0));
        sf::Vector2f bottomRight = topLeft + view.getSize();
        int MoveAmount = 1;
        if (topLeft.x < 0) {
            view.move(MoveAmount, 0);
        }
        else if (topLeft.y < 0) {
            view.move(0, MoveAmount);
        }
        else if (bottomRight.x > 1280) {
            view.move(-MoveAmount, 0);
        }
        else if (bottomRight.y > 1280) {
            view.move(0, -MoveAmount);
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view.move(-viewSpeed * _dt, 0.0f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(viewSpeed * _dt, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                view.move(0.0f, -viewSpeed * _dt);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(0.0f, viewSpeed * _dt);
            }
        }
       

        // tilemap update
        tileMap.update(view, &ObjHandler, &EnemyHandler);

        // draw
        //Window.clear();
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

        //draw Ui
        Window.draw(Ui);

        Window.display();
        
        // if debug is true in file update and draw to debug window
        if (_Debug) {
            DebugWindow.clear();
            g_ViewSpeed.Draw(&DebugWindow);
            g_Save.Draw(&DebugWindow);
            g_VSync.Draw(&DebugWindow);
            g_Volume.Draw(&DebugWindow);
            g_GameWin.Draw(&DebugWindow);
            g_GameOver.Draw(&DebugWindow);
            DebugWindow.display();
        }
        if (ObjHandler.GameWin) {
            WinScreen.clear();
            g_PlayAgain.Draw(&WinScreen);
            WinScreen.display();
        }
        if (ObjHandler.GameOver) {
            LoseScreen.clear();
            g_PlayAgain.Draw(&LoseScreen);
            LoseScreen.display();
        }
    }

    return 0;
}