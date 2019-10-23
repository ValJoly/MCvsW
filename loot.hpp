#ifndef _LOOT_HPP_
#define _LOOT_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "bouton.hpp"

class Loot : public sf::Drawable, public sf::Transformable {
private:
std::string name; //nom de l'objet
std::string pathImage; //chemin d'accès vers l'image de l'objet

int food;         //valeur d'alimentation
int life;         //valeur de la vie
int fatigue;      //valeur de la fatigue
int fear;         //valeur de peur
int addStuff;     //valeur d'ajout d'emplacement dans l'inventaire


sf::Vector2f position; //coordonées du bouton qui indique sa position
Bouton lootBt; //insance de Bouton qui permet de créer un loot cliquable, et donc utilisable

public:

//Constructeur de la classe
Loot(std::string, sf::Vector2f);

//Ensemble des get() et set() classique
std::string getName();

int getFood();
int getLife();
int getFatigue();
int getFear();
int getAddStuff();
sf::Vector2f getPosition();
Bouton getLootBt();

void setName(std::string);
void setFood(int);
void setLife(int);
void setFatigue(int);
void setFear(int);
void setAddStuff(int);
void setPosition(sf::Vector2f);

//Méthode permettant l'affichage d'un objet
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
