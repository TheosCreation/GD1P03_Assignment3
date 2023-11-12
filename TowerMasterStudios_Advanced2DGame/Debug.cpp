#include "Debug.h"

Debug::Debug(sf::Vector2f _UpButtonPos, sf::Vector2f _DownButtonPos, sf::Vector2f _ButtonSize, sf::Font& _Font, sf::Vector2f _TitleTextPos, sf::Vector2f _UpTextPos, sf::Vector2f _DownTextPos, float _TextSize)
{
    // up button visual
    m_ButtonUpVisual.setPosition(_UpButtonPos);
    m_ButtonUpVisual.setSize(_ButtonSize);
    m_ButtonUpVisual.setOutlineColor(sf::Color::White);
    m_ButtonUpVisual.setFillColor(sf::Color::Transparent);
    m_ButtonUpVisual.setOutlineThickness(2);

    // down button visual
    m_ButtonDownVisual.setPosition(_DownButtonPos);
    m_ButtonDownVisual.setSize(_ButtonSize);
    m_ButtonDownVisual.setOutlineColor(sf::Color::White);
    m_ButtonDownVisual.setFillColor(sf::Color::Transparent);
    m_ButtonDownVisual.setOutlineThickness(2);

    // up button text
    m_ButtonUpText.setFont(_Font);
    m_ButtonUpText.setCharacterSize(_TextSize);
    m_ButtonUpText.setFillColor(sf::Color::White);
    m_ButtonUpText.setPosition(_UpTextPos);

    // down button text
    m_ButtonDownText.setFont(_Font);
    m_ButtonDownText.setCharacterSize(_TextSize);
    m_ButtonDownText.setFillColor(sf::Color::White);
    m_ButtonDownText.setPosition(_DownTextPos);

    // title text
    m_TitleText.setFont(_Font);
    m_TitleText.setCharacterSize(_TextSize);
    m_TitleText.setFillColor(sf::Color::White);
    m_TitleText.setPosition(_TitleTextPos);
}

Debug::~Debug()
{
}

void Debug::Draw(sf::RenderWindow* _Window)
{
    _Window->draw(m_TitleText);
    _Window->draw(m_ButtonUpVisual);
    _Window->draw(m_ButtonUpText);
    _Window->draw(m_ButtonDownVisual);
    _Window->draw(m_ButtonDownText);
}
