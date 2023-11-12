#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Debug
{
public:
    sf::RectangleShape m_ButtonUpVisual;
    sf::RectangleShape m_ButtonDownVisual;
    sf::Text m_TitleText;
    sf::Text m_ButtonUpText;
    sf::Text m_ButtonDownText;

    Debug(sf::Vector2f _UpButtonPos, sf::Vector2f _DownButtonPos, sf::Vector2f _ButtonSize, sf::Font& _Font, sf::Vector2f _TitleTextPos,
        sf::Vector2f _UpTextPos, sf::Vector2f _DownTextPos, float _TextSize);
    ~Debug();

    void Draw(sf::RenderWindow* _Window);
};

