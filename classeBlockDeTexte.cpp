#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "classeBlockDeText.hpp"


//constructeur

Zonedetext::Zonedetext()
{
        font.loadFromFile("./Assets/GeosansLight.ttf");
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Cyan);
        text.setString("non initialiser");
        texteaaff=("non init");
        blockdetext=sf::RectangleShape();
        blockdorigine=blockdetext;
        setBgColor(sf::Color(0,0,0,0));
}


Zonedetext::Zonedetext(sf::RenderWindow& window)
{
        this->window=&window;
        font.loadFromFile("./Assets/GeosansLight.ttf");
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Cyan);
        text.setString("non initialiser");
        texteaaff=("non init");
        blockdetext=sf::RectangleShape();
        blockdorigine=blockdetext;
        taillefenetreorigine=sf::Vector2f(window.getSize().x,window.getSize().y);
        setBgColor(sf::Color(0,0,0,0));
}


Zonedetext::Zonedetext(float posx,float posy,float largeur,float hauteur,sf::RenderWindow& window)
{
        this->window=&window;
        // font.loadFromFile("GeosansLight.ttf");
        text.setFont(font);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Cyan);
        text.setString("non initialiser");
        texteaaff=("non init");
        blockdetext.setPosition(sf::Vector2f(posx,posy));
        blockdetext.setSize(sf::Vector2f(largeur,hauteur));
        blockdorigine=blockdetext;
        taillefenetreorigine=sf::Vector2f(window.getSize().x,window.getSize().y);
        setBgColor(sf::Color(0,0,0,0));
}


void Zonedetext::setTexteaaf(std::string line){
        this->texteaaff = line;
}

void Zonedetext::setFont(std::string path){
        this->font.loadFromFile(path);
        this->text.setFont(font);
}

void Zonedetext::setCharacterSize(int caracSize){
        this->text.setCharacterSize(caracSize);
}

void Zonedetext::wrapText() {
        std::string templigne = texteaaff; //valeur temporaire
        /*\n ger� automatiquement par sfml donc il suffit de le plac� au bon endroit*/

        text.setPosition(blockdetext.getPosition().x,blockdetext.getPosition().y);
        float taillemoyennedunchar=text.getCharacterSize()/(2.6);//nb arbitraire depend de la police de charactere //taille en px
        unsigned int charmaxv2 = (blockdetext.getGlobalBounds().width/taillemoyennedunchar); //calcule du nombre de char max part ligne grace a la taille d'un char(moyenne) //plus stable que v1
        unsigned int curseur=0; //curseur que l'on va faire avanc�
        unsigned int curseurdebutligne=0;

        //tour 0
        int nbchar=0; //prochain " "
        int positioncharsechapement = 0;  // prochain \n
        while(texteaaff.length()>curseur&&texteaaff.length()>0)
        {
                // tour n


                nbchar = texteaaff.find_first_of(" ",curseur); //recherche du prochain " " vers l'avant
                positioncharsechapement = texteaaff.find_first_of("\n",(curseur));//recherche du prochain "\n" vers l'avant

                //gestion de \n en amont du reste car il peut avoir un \n sans la fin du mot du coup reduit la taille du mot
                if(positioncharsechapement== -1) //si plus de \n
                {

                }
                else
                {
                        if(positioncharsechapement<nbchar && positioncharsechapement >curseur) //on regarde si \n est entre le curseur et nbchar
                        {
                                curseur=positioncharsechapement;
                                curseurdebutligne=curseur;
                        }

                }




                if (nbchar == -1) //si fin de ligne dans ce cas pas de " " a la fin donc -1
                {
                        if(charmaxv2<(texteaaff.length()-curseur))//si le mot est trop grand pour la ligne
                        {
                                texteaaff=texteaaff.substr(0,(charmaxv2-3));
                                texteaaff=texteaaff+"...";
                        }
                        else
                        {
                                if (charmaxv2>texteaaff.length()-curseurdebutligne) //fin du text
                                        curseur = texteaaff.length();
                                else
                                {
                                        texteaaff.insert((curseur),"\n"); //sinon pas de prise en compte du dernier mot
                                        curseur = texteaaff.length();
                                }
                        }
                }
                else //sinon c'est pas la fin
                {
                        if(charmaxv2<(nbchar-curseur))//si le mot est trop grand pour la ligne
                        {
                                texteaaff=texteaaff.substr(0,(charmaxv2-3));
                                texteaaff=texteaaff+"...";
                        }
                        else
                        {
                                if(charmaxv2 > nbchar-curseurdebutligne) //fin du mot //plus de place sur la ligne
                                {
                                        curseur=nbchar+1; // pour eviter que nbchar soit stuck sur le meme " "
                                }
                                else
                                {
                                        texteaaff.insert((curseur),"\n");
                                        curseurdebutligne=curseur;
                                }
                        }
                }
        }


        text.setString(texteaaff);//on set le string a la fin
        window->draw(blockdetext); //affichage
        window->draw(text);
        texteaaff=templigne; //on replace le string original a sa place sinon il y aura plein de \n partout
}

void Zonedetext::setBgColor(sf::Color color) {
        couleurbackground=color;
        blockdetext.setFillColor(color);
}

void Zonedetext::recalculedetaille(sf::Event event) {     //a mettre dans la boucle event car sinon plusieur retour resize
        // addition au lieu de ratio pas besois taille de depart // moins de vairable
        if (event.type == sf::Event::Resized)
        {
                ratiox=window->getSize().x/taillefenetreorigine.x;
                ratioy=window->getSize().y/taillefenetreorigine.y;
                blockdetext.setPosition(blockdorigine.getGlobalBounds().left*ratiox,blockdorigine.getGlobalBounds().top*ratioy); // ne marche pas il faut la position de depart poura voir quelque chose de coh�rent
                blockdetext.setScale(ratiox,ratioy);
        }
}

void Zonedetext::setTextColor(sf::Color color){
        // text.setStyle(sf::Text::Bold);
        text.setFillColor(color);
}
