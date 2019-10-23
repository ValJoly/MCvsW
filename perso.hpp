#ifndef _PERSO_HPP_
#define _PERSO_HPP_

#include <vector>
#include <string>
#include <random>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "loot.hpp"

class Perso : public sf::Drawable, public sf::Transformable /*On fait heriter notre classe de 2 presente dans la SFML*/ {
private:

std::string name; //Nom du personnage (tirer aléatoirement dans le constructeur)
int food;         //Niveau d'alimentation du personnage
int life;         //Niveau de vie
int fatigue;      //Niveau de fatigue
int fear;         //Niveau de peur
int time;         //Temps passer a survivre

std::vector<Loot> stuff; //Vector de notre classe objet "Loot" qui correspond a l'inventaire
int stuffSize;           //Taille maximum de l'inventair du personnage

bool play; //Booléen qui permet de savoir si le personnage est mort ou non

public:

//Constructeur pour le personnage
Perso();

//Méthode get() et set() classique
int getFood();
int getLife();
int getFatigue();
int getFear();
int getTime();
int getStuffSize();
std::string getName();
std::vector<Loot> getStuff();

void setFood(int);
void setLife(int);
void setFatigue(int);
void setFear(int);
void setTime(int);
void setStuffSize(int);

//Méthode permettant de mettre en jour l'inventaire du personnage
void eraseStuff(int);
void setStuff(Loot);

//Draw remplace l'ancienne show() et permet d'afficher notre personnage
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//Test si notre personnage est encore en vie ou non
bool isPlay();
};

#endif
