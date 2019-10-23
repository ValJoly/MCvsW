#ifndef _BOUTON_HPP_
#define _BOUTON_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Bouton : public sf::Drawable, public sf::Transformable {

private:

sf::Vector2f position;  //deux coordonées pour la position du bouton
sf::Vector2f size;   //deux coordonées pour la taille du bouton
sf::Text name;   //le nom du bouton
sf::RectangleShape rect;   //contour autour du bouton
sf::Font font;   //police de caractère du bouton
sf::Texture texture;   //texture utilisé pour le bouton
sf::Sprite sprite;   //sprite utilisé pour le bouton
bool textureBT;   //On vérifie si le bouton a une texture (true) ou non (false)


public:

//Différents constructeur pour nos boutons
Bouton();
Bouton(sf::Vector2f, sf::Vector2f, sf::Color, sf::String&);
Bouton(sf::Vector2f, sf::Vector2f, sf::String, sf::String);

//Méthode permettant de savoir si le bouton en question est cliqué.
bool isPressed(float, float, bool&, sf::RenderWindow&);

//Méthode permettant l'affichage du bouton
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

//Ensemble des methodes get() et set() classique.
void setPosition(sf::Vector2f);
sf::Vector2f getPosition();

void setSize(sf::Vector2f);
sf::Vector2f getSize();

void setName(sf::Text);
sf::Text getName();

};

#endif
