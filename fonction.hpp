#ifndef _FONCTION_HPP_
#define _FONCTION_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


std::string randomEvent(int);
int testScore(int);
int elements();
void Dynamicresize(sf::Event event, sf::RenderWindow& renderWindow);


#endif
