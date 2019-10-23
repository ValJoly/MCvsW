#ifndef _CLASSEBLOCKDETEXTE_HPP_
#define _CLASSEBLOCKDETEXTE_HPP_


#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



class Zonedetext {

private:

//attribut
//aucun attribut en private car pas besoin vue l'echelle du truc //si il y a des attribut en private il faut cr�e des accesseur
sf::Vector2f taillefenetreorigine;      //largeur hauteur fenetre d'origine //taille de la fenetre a l'instanciation
std::string texteaaff;      //le text a afficher
sf::RectangleShape blockdorigine;     //taille du rect d'origine pour faire des rezize
sf::RectangleShape blockdetext;     //block de text pour la couleur de fond
sf::Color couleurbackground;     //sauvegarde de la couleur de fond
sf::Text text;     //text a init avec font
sf::Font font;     // a init avec arial .ttf // a chang�
sf::RenderWindow* window;     // a init //permet de recuperer la taille de la fenetre et d'afficher
float ratiox;     // peut etre utile // val temp pas vrament utile  //pour le resize
float ratioy;     // peut etre utile // val temp pas vrament utile //pour le resize

public:

//constructeur

Zonedetext();

Zonedetext(sf::RenderWindow& window);

Zonedetext(float posx,float posy,float largeur,float hauteur,sf::RenderWindow& window);

//methode

void setTexteaaf(std::string line);

void setFont(std::string path);

void setCharacterSize(int caracSize);

void wrapText();

void setBgColor(sf::Color color);

void recalculedetaille(sf::Event event);

void setTextColor(sf::Color color);

};

#endif
