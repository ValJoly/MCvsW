#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "classeBlockDeText.hpp"


class Events : public sf::Drawable, public sf::Transformable {

private:

std::string title;          //titre de l'evenement
std::string description;    //sa description

//caracteristique du premier choix
int food1;            //valeur d'alimentation
int life1;            //valeur de vie
int fatigue1;         //valeur d'epuisement
int fear1;            //valeur de fatigue
int time1;            //valeur de temps
std::string title1;   //intitulé du choix
std::string loot1;    //chemin d'accès vers un objet
std::string next1;    //chemin d'accès vers un evenement imbriqué

//caracteristique du second choix
int food2;            //valeur d'alimentation
int life2;            //valeur de vie
int fatigue2;         //valeur d'epuisement
int fear2;            //valeur de fatigue
int time2;            //valeur de temps
std::string title2;   //intitulé du choix
std::string loot2;    //chemin d'accès vers un objet
std::string next2;    //chemin d'accès vers un evenement imbriqué
sf::RenderWindow* window;
Zonedetext descriptionZone, choix1Zone, choix2Zone;


public:

Events(sf::RenderWindow&); //constructeur qui initialise les paramètres à O (pour les int) ou ensemble vide (pour les string)

//methode qui lit un fichier évènement puis remplit les caractéristiques de celui-ci
void fill(std::string);

//méthodes get classique, nous n'utilisons pas de set qui est remplacé par fill()
std::string getTitle();
std::string getDescription();

int getFood1();
int getLife1();
int getFatigue1();
int getFear1();
int getTime1();
std::string getTitle1();
std::string getLoot1();
std::string getNext1();

int getFood2();
int getLife2();
int getFatigue2();
int getFear2();
int getTime2();
std::string getTitle2();
std::string getLoot2();
std::string getNext2();

Zonedetext getDescriptionZone();
Zonedetext getChoix1Zone();
Zonedetext getChoix2Zone();
//Méthode permettant l'affichage de l'évènement
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif
