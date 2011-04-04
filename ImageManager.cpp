#include <iostream>

#include "ImageManager.h"


ImageManager gImageManager;

sf::Image* ImageManager::load( const std::string& strId ) {
    sf::Image* image = new sf::Image();
    if( !image->LoadFromFile( strId ) ) {
        std::cout << "[WARN] ImageManager failed to load: " << strId << std::endl;
        delete image;
        image = NULL;
    }
    image->SetSmooth(false);
    return image;
}