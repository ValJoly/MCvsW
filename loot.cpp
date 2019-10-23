#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "loot.hpp"
#include "bouton.hpp"

#define _RED "\x1B[31m"
#define _YELLOW "\x1b[33m"
#define _BLUE "\x1B[34m"
#define _WHITE "\x1B[37m"
#define _PURPLE "\x1B[35m"
#define _GREEN "\x1B[32m"
#define _DEFAULT "\x1B[0m"

Loot::Loot(std::string path, sf::Vector2f p_position){
        name = "";
        pathImage = "Default.png"; //on charge une image par défault qui sera remplacé si l'objet en possède une
        food = 0;
        life = 0;
        fatigue = 0;
        fear = 0;
        addStuff = 0;
        position = p_position;



        //creation d'un flux vers le fichier passé en paramètre
        std::ifstream fichier(path, std::ios::in);
        std::string Lu;

        if(fichier) {


                while (getline(fichier, Lu, '\n')) /*On lit le fichier ouvert tant qu'il y a des caractères*/ {

                        std::string delimiter = ":"; //On definit un caractère delimiteur de nos fichiers
                        std::string token = Lu.substr(0, Lu.find(delimiter));

                        //On remplit les différentes valeurs relative aux attributs en fonction de la chaine de caractère lu
                        if(token == "Nom_Item") {
                                this->name = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Val_Item_Alimentation") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->food;
                        }
                        if(token == "Val_Item_Vie") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->life;
                        }
                        if(token == "Val_Item_Epuisement") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fatigue;
                        }
                        if(token == "Val_Item_Peur") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fear;
                        }
                        if(token == "Add_Stuff") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->addStuff;
                        }
                        if(token == "pathImage") {
                                this->pathImage = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                }


                fichier.close();
        }
        else{
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;


                sf::String tmp = this->name; //on convertit notre std::String en sf::String
                //créé le bouton lié a l'objet, pour pouvoir l'utiliser
                lootBt = Bouton(this->position, sf::Vector2f(75, 75), "Loots/Assets/" + pathImage, "");

        }
}

//methodes get et set classique
std::string Loot::getName(){
        return name;
}
int Loot::getFood(){
        return food;
}
int Loot::getLife(){
        return life;
}
int Loot::getFatigue(){
        return fatigue;
}
int Loot::getFear(){
        return fear;
}
int Loot::getAddStuff(){
        return addStuff;
}
sf::Vector2f Loot::getPosition(){
        return position;
}

Bouton Loot::getLootBt(){
        return lootBt;
}


void Loot::setName(std::string p_name){
        name = p_name;
}
void Loot::setFood(int p_food){
        food = p_food;
}
void Loot::setLife(int p_life){
        life = p_life;
}
void Loot::setFatigue(int p_fatigue){
        fatigue = p_fatigue;
}
void Loot::setFear(int p_fear){
        fear = p_fear;
}
void Loot::setAddStuff(int p_addStuff){
        addStuff = p_addStuff;
}
void Loot::setPosition(sf::Vector2f p_position){
        position = p_position;
        lootBt.setPosition(position); //On n'oublie pas d'assigner la position du bouton
}





void Loot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        //Création de variables pour afficher le nom du bouton
        sf::String affichage = name;
        sf::Text DescriptionTxt;
        sf::Font font;

        //On charge la police pour le texte
        font.loadFromFile(("./Assets/crackin.ttf"));

        //On met en forme le texte
        DescriptionTxt.setString(affichage);
        DescriptionTxt.setFont(font);
        DescriptionTxt.setCharacterSize(40);
        DescriptionTxt.setPosition(position.x + 75, position.y);


        Bouton TmpBt(this->position, sf::Vector2f(75, 75), "Loots/Assets/" + pathImage, ""); //On créé un bouton équivalent pour l' aficher
        target.draw(TmpBt, states);   //On affiche le bouton
        target.draw(DescriptionTxt, states);  //Puison affiche le texte sur le coté

}
