#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <SFML/System/Vector2.hpp>

class FileManager
{
public:
	FileManager();
	~FileManager();

	void LoadValuesFromFile(const std::string& _filename, bool& _VSync, bool& _Debug, sf::Vector2f& WindowSize);
};

