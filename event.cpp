#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "classeBlockDeText.hpp"
#include "event.hpp"

#define _RED "\x1B[31m"
#define _YELLOW "\x1b[33m"
#define _BLUE "\x1B[34m"
#define _WHITE "\x1B[37m"
#define _PURPLE "\x1B[35m"
#define _GREEN "\x1B[32m"
#define _DEFAULT "\x1B[0m"

#define MAX_STAT 20

Events::Events(sf::RenderWindow& window){
        title = "";
        description = "";

        food1 = 0;
        life1 = 0;
        fatigue1 = 0;
        fear1 = 0;
        time1 = 0;
        title1 = "";
        loot1 = "";
        next1 = "";

        food2 = 0;
        life2 = 0;
        fatigue2 = 0;
        fear2 = 0;
        time2 = 0;
        title2 = "";
        loot2 = "";
        next2 = "";

        this->window = &window;
        descriptionZone = Zonedetext(440, 200, 420, 200, window);


}

void Events::fill(std::string path){

        //On crée un flux en lecture pour lire les fichiers évènements
        std::ifstream fichier(path, std::ios::in);
        std::string Lu;

        if(fichier) {

                //on teste les différentes lignes pour chacune des caractéristiques de l'evenement
                while (getline(fichier, Lu, '\n')) {

                        std::string delimiter = ":";
                        std::string token = Lu.substr(0, Lu.find(delimiter));

                        if(token == "Titre") {
                                this->title = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Description_Event") {
                                this->description = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }


                        if(token == "Choix1_Titre") {
                                this->title1 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Choix1_Alimentation") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->food1;
                        }
                        if(token == "Choix1_Vie") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->life1;
                        }
                        if(token == "Choix1_Epuisement") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fatigue1;
                        }
                        if(token == "Choix1_Peur") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fear1;
                        }
                        if(token == "Choix1_Time") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->time1;
                        }
                        if(token == "Choix1_Loot") {
                                this->loot1 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Choix1_Next") {
                                this->next1 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }


                        if(token == "Choix2_Titre") {
                                this->title2 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Choix2_Alimentation") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->food2;
                        }
                        if(token == "Choix2_Vie") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->life2;
                        }
                        if(token == "Choix2_Epuisement") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fatigue2;
                        }
                        if(token == "Choix2_Peur") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->fear2;
                        }
                        if(token == "Choix2_Time") {
                                std::string tmp = Lu.substr(token.size() + 1, Lu.find("\n"));
                                std::istringstream iss(tmp);
                                iss >> this->time2;
                        }
                        if(token == "Choix2_Loot") {
                                this->loot2 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                        if(token == "Choix2_Next") {
                                this->next2 = Lu.substr(token.size() + 1, Lu.find("\n"));
                        }
                }
                fichier.close();

                descriptionZone = Zonedetext(440, 200, 400, 400, *window);
                descriptionZone.setTexteaaf(title + " : \n\n" + description);
                descriptionZone.setFont("./Assets/GeosansLight.ttf");
                descriptionZone.setCharacterSize(28);
                descriptionZone.setTextColor(sf::Color::White);
                descriptionZone.setBgColor(sf::Color(255, 255, 255, 10));

                choix1Zone = Zonedetext(20, 200, 400, 120, *window);
                choix1Zone.setTexteaaf(title1);
                choix1Zone.setFont("./Assets/crackin.ttf");
                choix1Zone.setCharacterSize(26);
                choix1Zone.setTextColor(sf::Color::White);
                choix1Zone.setBgColor(sf::Color(245, 255, 245, 10));

                choix2Zone = Zonedetext(860, 200, 400, 120, *window);
                choix2Zone.setTexteaaf(title2);
                choix2Zone.setFont("./Assets/crackin.ttf");
                choix2Zone.setCharacterSize(26);
                choix2Zone.setTextColor(sf::Color::White);
                choix2Zone.setBgColor(sf::Color(245, 255, 245, 10));

        }
        else{
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        }



}

std::string Events::getTitle(){
        return title;
}
std::string Events::getDescription(){
        return description;
}

int Events::getFood1(){
        return food1;
}
int Events::getLife1(){
        return life1;
}
int Events::getFatigue1(){
        return fatigue1;
}
int Events::getFear1(){
        return fear1;
}
int Events::getTime1(){
        return time1;
}
std::string Events::getTitle1(){
        return title1;
}
std::string Events::getLoot1(){
        return loot1;
}
std::string Events::getNext1(){
        return next1;
}

int Events::getFood2(){
        return food2;
}
int Events::getLife2(){
        return life2;
}
int Events::getFatigue2(){
        return fatigue2;
}
int Events::getFear2(){
        return fear2;
}
int Events::getTime2(){
        return time2;
}
std::string Events::getTitle2(){
        return title2;
}
std::string Events::getLoot2(){
        return loot2;
}
std::string Events::getNext2(){
        return next2;
}

Zonedetext Events::getDescriptionZone() {
        return descriptionZone;
}

Zonedetext Events::getChoix1Zone() {
        return choix1Zone;
}

Zonedetext Events::getChoix2Zone() {
        return choix2Zone;
}

void Events::draw(sf::RenderTarget& target, sf::RenderStates states) const {

        sf::RectangleShape statRect; //on crée un rectangle pour afficher les différentes évolutions que va induire l'évènement

        //On affiche la description et le titre de l'évènement

        sf::String affichage = this->description;
        // for (int i = 32; i < affichage.getSize(); i+=32) {
        //         affichage.insert(i, "\n");
        // }
        // affichage = this->title + " : \n\n" + affichage;
        sf::Font font;
        font.loadFromFile(("./Assets/crackin.ttf"));
        // font.loadFromFile(("./Assets/GeosansLight.ttf"));
        sf::Text DescriptionTxt(affichage, font, 32);
        // DescriptionTxt.setPosition(440, 200);
        // DescriptionTxt.setFillColor(sf::Color::White);
        // target.draw(DescriptionTxt, states);


        // descriptionZone.wrapText();


        // //Enfin on affiche le titre et chacune des caractéristiques du choix
        // affichage = this->title1;
        // for (int i = 30; i < this->title1.size(); i+=30) {
        //         affichage.insert(i, "\n");
        // }
        // DescriptionTxt.setString(affichage);
        // DescriptionTxt.setFont(font);
        // DescriptionTxt.setCharacterSize(32);
        // DescriptionTxt.setPosition(50, 175);
        // // target.draw(DescriptionTxt, states);
        //
        // affichage = this->title2;
        // for (int i = 30; i < this->title2.size(); i+=30) {
        //         affichage.insert(i, "\n");
        // }
        // DescriptionTxt.setString(affichage);
        // DescriptionTxt.setFont(font);
        // DescriptionTxt.setCharacterSize(32);
        // DescriptionTxt.setPosition(850, 175);
        // target.draw(DescriptionTxt, states);

        //Pour chacun des choix, on considère l'evolution de chaque statistique
        //On gère le cas ou l'evenement nous tue
        if (abs(this->life1) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(150, 350));
                target.draw(Kill, states);
        }
        //Puis le cas classique ou l'evenement nous fait gagner ou perdre en statistiques
        else{

                statRect.setSize(sf::Vector2f(abs(this->life1) * 20, 30));
                statRect.setPosition(sf::Vector2f(150, 350));
                statRect.setFillColor(sf::Color(238, 16, 16));
                target.draw(statRect, states);
        }

        //on fait cela pour chaque statistique
        if (abs(this->food1) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(150, 400));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(abs(this->food1) * 20, 30));
                statRect.setPosition(sf::Vector2f(150, 400));
                statRect.setFillColor(sf::Color(255, 255, 50));
                target.draw(statRect, states);
        }

        if (abs(this->fatigue1) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(150, 450));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(abs(this->fatigue1) * 20, 30));
                statRect.setPosition(sf::Vector2f(150, 450));
                statRect.setFillColor(sf::Color(161, 6, 132));
                target.draw(statRect, states);
        }
        if (this->fear1 >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(150, 500));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(abs(this->fear1) * 20, 30));
                statRect.setPosition(sf::Vector2f(150, 500));
                statRect.setFillColor(sf::Color(255, 127, 0));
                target.draw(statRect, states);
        }

        //Ici on charge nos icones qu'on place devant l'évolution de statistiques
        sf::Sprite icon;
        sf::Texture textureIcon;
        if (!textureIcon.loadFromFile("./Assets/hearth.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(85, 340);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/meat.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(85, 390);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/sleep.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(85, 440);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/ghost.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(85, 490);
        target.draw(icon, states);



        //On réitère la même opération pour le choix 2
        if (abs(this->life2) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(1055, 350));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(-abs(this->life2) * 20, 30));
                statRect.setPosition(sf::Vector2f(1135, 350));
                statRect.setFillColor(sf::Color(238, 16, 16));
                target.draw(statRect, states);
        }

        if (abs(this->food2) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(1055, 400));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(-abs(this->food2) * 20, 30));
                statRect.setPosition(sf::Vector2f(1135, 400));
                statRect.setFillColor(sf::Color(255, 255, 50));
                target.draw(statRect, states);
        }

        if (abs(this->fatigue2) >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(1055, 450));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(-abs(this->fatigue2) * 20, 30));
                statRect.setPosition(sf::Vector2f(1135, 450));
                statRect.setFillColor(sf::Color(161, 6, 132));
                target.draw(statRect, states);
        }

        if (this->fear2 >= MAX_STAT) {

                sf::Text Kill;
                Kill.setString("KILL");
                Kill.setFillColor(sf::Color::White);
                Kill.setFont(font);
                Kill.setCharacterSize(40);
                Kill.setPosition(sf::Vector2f(1055, 500));
                target.draw(Kill, states);
        }
        else{

                statRect.setSize(sf::Vector2f(-abs(this->fear2) * 20, 30));
                statRect.setPosition(sf::Vector2f(1135, 500));
                statRect.setFillColor(sf::Color(255, 127, 0));
                target.draw(statRect, states);
        }


        if (!textureIcon.loadFromFile("./Assets/hearth.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1145, 340);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/meat.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1145, 390);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/sleep.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1145, 440);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/ghost.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1145, 490);
        target.draw(icon, states);




}
