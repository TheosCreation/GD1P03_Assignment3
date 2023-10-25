#include <sstream>
#include "Object.h"
#include "TileMap.h"


// ALWAYS BUILD IN RELEASE, AT LEAST ONCE A DAY. 

int main()
{
    // game variables
    float _dt = 0.0f;
    sf::Clock dtClock;

    // grid variables
    float gridSizeF = 100.0f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);

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

    // window stuff
    sf::Vector2f WindowSize(1920, 1080);

    sf::RenderWindow window(sf::VideoMode(WindowSize.x, WindowSize.y), "Chess Tower Masters");
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

        // update ui
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

        text.setString(ss.str());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
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
        tileMap.update(view);

        // draw
        window.clear();
        window.setView(view);

        // draw game
        tileMap.draw(&window);

        window.draw(tileSelector);

        window.setView(window.getDefaultView());

        // draw ui
        window.draw(text);

        window.display();
    }

    return 0;
}