#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "bouton.hpp"

//Nous créeons un deuxieme constructeur "par defaut" uniquement pour les objets dans l'inventaire
Bouton::Bouton(){
        this->position = sf::Vector2f(0, 0);
        this->size = sf::Vector2f(150, 75);
        this->rect.setPosition(position); //On applique la position au bouton
        this->rect.setSize(size);     //On applique la taille du bouton

        //Colorisation du RectangleShapetangle de fond
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(5);

        //on charge une police d'écriture
        this->font.loadFromFile(("./Assets/crackin.ttf"));

        //Mise en forme du texte du bouton; police taille des caractère, couleur ...
        this->name.setFont(font);
        sf::String tmp("Def_name");
        this->name.setString(tmp);
        this->name.setCharacterSize(40);
        this->name.setPosition(sf::Vector2f(position.x, position.y + size.y));
        this->name.setFillColor(sf::Color::White);
        this->textureBT = false;
}


Bouton::Bouton(sf::Vector2f p_position, sf::Vector2f p_size, sf::Color p_color, sf::String &p_name){
        //Meme principe que le constructeur du dessus mais en appliquant les parametre et non des valeurs par defaut
        this->position = p_position;
        this->size = p_size;
        this->rect.setPosition(position);
        this->rect.setSize(size);

        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(5);

        this->font.loadFromFile(("./Assets/crackin.ttf"));

        this->name.setFont(font);
        this->name.setString(p_name);
        this->name.setCharacterSize(size.y - (p_name.getSize() * 4));
        this->name.setPosition(sf::Vector2f(position.x + size.x/2 - this->name.getLocalBounds().width/2, position.y + size.y/2 - this->name.getLocalBounds().height/2));
        this->name.setFillColor(p_color);
        this->textureBT = false;

}


//On affiche les sprites avec ce constructeur
Bouton::Bouton(sf::Vector2f p_position, sf::Vector2f p_size, sf::String p_path, sf::String p_name){
        this->position = p_position;
        this->size = p_size;
        //Au lieu de modifier le rectangle, le bouton a ici une texture que l'on charge avec :
        if (!texture.loadFromFile(p_path)) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        //Puis comme précédement
        this->sprite.setPosition(position);
        this->sprite.setTexture(texture);


        this->font.loadFromFile(("./Assets/crackin.ttf"));

        this->name.setFont(font);
        this->name.setString(p_name);
        this->name.setCharacterSize(size.y);
        this->name.setPosition(sf::Vector2f(position.x, position.y - 20));
        this->textureBT = true; //le bouton a une texture dans ce constructeur
}

bool Bouton::isPressed(float x, float y, bool& click, sf::RenderWindow& window){
        if (x < (this->position.x + this->size.x) && x > this->position.x && y < (this->position.y + this->size.y) && y > this->position.y) /*On regarde si la souris se situe dans la zone du bouton en fonction de sa taille et de sa position*/ {
                if (click == true) {
                        click = false;
                        return true;
                }
        }
        return false;
}

void Bouton::draw(sf::RenderTarget& target, sf::RenderStates states) const /*Permet d'afficher le Bouton*/ {
        states.transform *= getTransform(); //On applique les transformations necessaires
        if (textureBT == false) /*On regarde quel type de bouton on veut afficher*/ {
                target.draw(rect, states); //ici c'est un rectangle
        }
        else /*Sinon il s'agit du sprite à afficher*/ {
                target.draw(sprite, states);
        }
        target.draw(name, states); //Puis le nom dans tous les cas
}





//méthodes get et set classique
void Bouton::setPosition(sf::Vector2f p_position){
        this->position = p_position;
}

sf::Vector2f Bouton::getPosition(){
        return position;
}

void Bouton::setSize(sf::Vector2f p_size){
        this->size = p_size;
}
sf::Vector2f Bouton::getSize(){
        return size;
}

void Bouton::setName(sf::Text p_name){
        this->name = p_name;
}
sf::Text Bouton::getName(){
        return name;
}
