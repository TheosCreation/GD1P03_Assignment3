#include "FileManager.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::LoadValuesFromFile(const std::string& _filename, bool& _VSync, bool& _Debug, sf::Vector2f& WindowSize)
{
    std::ifstream file(_filename);

    if (!file) {
        std::cout << "File not found" << std::endl;
        return;
    }

    std::string key;
    int Count = 1;
    while (file >> key) {
        if (key == "#") {
            // Skip the comment line
            std::getline(file, key);
            continue;
        }
        switch (Count)
        {
        case 1:
            _VSync = stoi(key);
        case 2:
            _Debug = stoi(key);
        case 3:
            WindowSize.x = stoi(key);
        case 4:
            WindowSize.y = stoi(key);
        }
        Count++;
    }
    file.close();
}
