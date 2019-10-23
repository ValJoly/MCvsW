#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "loot.hpp"
#include "perso.hpp"


#define _RED "\x1B[31m"
#define _YELLOW "\x1b[33m"
#define _BLUE "\x1B[34m"
#define _WHITE "\x1B[37m"
#define _PURPLE "\x1B[35m"
#define _GREEN "\x1B[32m"
#define _DEFAULT "\x1B[0m"


#define MAX_STAT 20

Perso::Perso(){
        std::random_device rd;
        life = MAX_STAT / 2;
        food = MAX_STAT / 2;
        fatigue = MAX_STAT / 2;
        fear = MAX_STAT / 2;
        time = 0;
        stuffSize = 4;
        play = true;
        stuff = {};

        //on ouvre un flux en lecture pour récuperer les prénoms du fichier ndm
        std::ifstream fichier("Divers/ndm.txt", std::ios::in);
        std::string Lu;

        if(fichier) {
                std::vector<std::string> names;

                while (getline(fichier, Lu, '\n')) {
                        names.push_back(Lu);
                }
                //ici on choisit un nom au hasard parmi tout ceux existant pour donner un nom au personnage
                name = names[rd()%names.size()];



                fichier.close();
        }
        else{
                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
        }

}
//méthode get et set classique
int Perso::getFood(){
        return food;
}
int Perso::getLife(){
        return life;
}
int Perso::getFatigue(){
        return fatigue;
}
int Perso::getFear(){
        return fear;
}
int Perso::getTime(){
        return time;
}
int Perso::getStuffSize(){
        return stuffSize;
}
std::string Perso::getName(){
        return name;
}
std::vector<Loot> Perso::getStuff(){
        return stuff;
}


void Perso::setFood(int p_food){
        this->food = p_food;
}
void Perso::setLife(int p_life){
        this->life = p_life;
}
void Perso::setFatigue(int p_fatigue){
        this->fatigue = p_fatigue;
}
void Perso::setFear(int p_fear){
        this->fear = p_fear;
}
void Perso::setTime(int p_time){
        this->time = p_time;
}

void Perso::setStuffSize(int p_stuffSize) {
        this->stuffSize = p_stuffSize;
}

//cette méthode sert lorque le personnage utilise un objet, pour le supprimer de l'inventaire
void Perso::eraseStuff(int cell)/*elle prend en paramètre la cellule contenant l'objet a efface */{

        this->stuff.erase(stuff.begin() + cell); //on enlève l'objet

        //puis on repositionne graphiquement ceux qui restent dans l'inventaire
        for (int i = 0; i < stuff.size(); i++) {
                stuff[i].setPosition(sf::Vector2f(200, i * 80 + 150));
        }

}

//cette méthode est utile quand le personnage obtient un objet
void Perso::setStuff(Loot thing)/*Elle prend en paramètre un objet*/{

        //on regarde s'il a de la place dans son inventaire
        if (stuff.size() >= stuffSize) /*Si ce n'est pas le cas*/ {

                std::random_device rd; //on génère un nombre aléatoire

                int cell = rd()%stuff.size();

                this->eraseStuff(cell); //pour effacer l'objet dans la case correspondante l'objet

                this->setStuff(thing); //et mettre le nouveau à sa place

        }
        else if (stuff.size() < stuffSize) /*Sinon on n'ajoute simplement l'objet dans l'inventaire*/ {
                stuff.push_back(thing);
        }

        //On repositionne graphiquement les objets dans l'inventaire
        for (int i = 0; i < stuff.size(); i++) {
                stuff[i].setPosition(sf::Vector2f(200, i * 80 + 150));
        }


}



void Perso::draw(sf::RenderTarget& target, sf::RenderStates states) const {

        //on crée les différentes variables qui vont nous permettre d'afficher nos icones et les jauges
        sf::Sprite icon;
        sf::Texture textureIcon;
        sf::RectangleShape statRect; //évolution des jauges au cours du temps
        sf::RectangleShape statFull; //montre où se trouve le maximum de chaque jauges

        //On affiche pour chaque caractéristiques une icone et la jauge
        if (!textureIcon.loadFromFile("./Assets/hearth.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(35, 0);

        statRect.setSize(sf::Vector2f(this->life * 20, 30));
        statRect.setPosition(sf::Vector2f(100, 10));
        statRect.setFillColor(sf::Color(238, 16, 16));

        statFull.setSize(sf::Vector2f(MAX_STAT*20, 30));
        statFull.setFillColor(sf::Color(255, 255, 255, 100));
        statFull.setPosition(sf::Vector2f(100, 10));

        target.draw(statFull, states);
        target.draw(statRect, states);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/meat.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1100, 0);

        statRect.setSize(sf::Vector2f(-this->food * 20, 30));
        statRect.setPosition(sf::Vector2f(1080, 10));
        statRect.setFillColor(sf::Color(255, 255, 50));

        statFull.setSize(sf::Vector2f(-MAX_STAT*20, 30));
        statFull.setFillColor(sf::Color(255, 255, 255, 100));
        statFull.setPosition(sf::Vector2f(1080, 10));

        target.draw(statFull, states);
        target.draw(statRect, states);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/sleep.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(35, 50);

        statRect.setSize(sf::Vector2f(this->fatigue * 20, 30));
        statRect.setPosition(sf::Vector2f(100, 60));
        statRect.setFillColor(sf::Color(161, 6, 132));

        statFull.setSize(sf::Vector2f(MAX_STAT*20, 30));
        statFull.setFillColor(sf::Color(255, 255, 255, 100));
        statFull.setPosition(sf::Vector2f(100, 60));

        target.draw(statFull, states);
        target.draw(statRect, states);
        target.draw(icon, states);


        if (!textureIcon.loadFromFile("./Assets/ghost.png")) {
                std::cout << "Erreur dans le chargement de l'image" << '\n';
        }
        icon.setTexture(textureIcon);
        icon.setPosition(1100, 50);

        statRect.setSize(sf::Vector2f(-this->fear * 20, 30));
        statRect.setPosition(sf::Vector2f(1080, 60));
        statRect.setFillColor(sf::Color(255, 127, 0));

        statFull.setSize(sf::Vector2f(-MAX_STAT*20, 30));
        statFull.setFillColor(sf::Color(255, 255, 255, 100));
        statFull.setPosition(sf::Vector2f(1080, 60));

        target.draw(statFull, states);
        target.draw(statRect, states);
        target.draw(icon, states);

        //On affiche le nom et le temps de jeu du personnage
        sf::Text timeTxt;
        sf::Font font;

        std::stringstream ss;
        ss << time;

        font.loadFromFile(("./Assets/crackin.ttf"));

        timeTxt.setString(name + "  " + ss.str().c_str() + "H");
        timeTxt.setFillColor(sf::Color(255, 255, 255));
        timeTxt.setFont(font);
        timeTxt.setCharacterSize(40);
        timeTxt.setPosition(500, 100);


        target.draw(timeTxt);
}



bool Perso::isPlay(){

        if (this->life > MAX_STAT) {
                this->life = MAX_STAT;
        }

        if (this->food <= 0 || this->food >= MAX_STAT) {
                play = false;
        }
        if (this->life <= 0) {
                play = false;
        }
        if (this->fatigue <= 0 || this->fatigue >= MAX_STAT) {
                play = false;
        }
        if (this->fear <= 0 || this->fear >= MAX_STAT) {
                play = false;
        }
        return play;
}
