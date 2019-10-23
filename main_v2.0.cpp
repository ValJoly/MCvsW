#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <random>
#include <cmath>

#include <chrono>
#include <thread>


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


#include "classeBlockDeText.hpp"

#include "fonction.hpp"

#include "bouton.hpp"
#include "event.hpp"
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


int main (void){

        sf::RenderWindow window(sf::VideoMode(1280, 720), "MCvsW", sf::Style::Close); // On créé l'objet qui correspond a la fenetre


        sf::Vector2f size(250, 150);
        sf::Vector2f position(640 - size.x / 2, 460 - size.y / 2);
        sf::String name("Play");


        //On crée un bouton pour commencer une partie
        Bouton btPlay(position, size, sf::Color(255, 255, 255), name);

        size.x = 92;
        size.y = 92;
        position.x = 20;
        position.y = 20;
        name = "";
        sf::String pathTexture("./Assets/options.png");
        Bouton settingsBt(position, size, pathTexture, name); //On crée le bouton pour acceder au "paramètre"

        pathTexture = "./Assets/retour.png";
        position.x = 1178;
        position.y = 618;
        Bouton inventoryBack(position, size, pathTexture, name); //Bouton pour sortir de notre inventaire dans la parie

        size.x = 80;
        size.y = 80;
        position.x = 550;
        position.y = 20;
        name = "";
        pathTexture = "./Assets/backpack.png";
        Bouton inventory(position, size, pathTexture, name); //Bouton pour acceder a notre inventaire

        position.x = window.getSize().x - size.x - 20;
        position.y = 20;
        pathTexture = "./Assets/croix.png";
        Bouton retourBt(position, size, pathTexture, name); //Bouton pour Terminer une partie et revenir au menu

        size = sf::Vector2f(200, 100);
        position = sf::Vector2f(640 - size.x / 2, 300 - size.y / 2);
        name = "Tuto";
        Bouton tutoBt(position, size, sf::Color(255, 255, 255), name); //Bouton pour accéder au tutoriel

        size = sf::Vector2f(200, 100);
        position = sf::Vector2f(640 - size.x / 2, 550 - size.y / 2);
        name = "Achievement";
        Bouton AchievBt(position, size, sf::Color(255, 255, 255), name); //Bouton pour accéder au achievement ; il ne fonctionne pour l'instant car nous n'avons pas encore développé cette fonctionnalitée

        size = sf::Vector2f(150, 75);
        position = sf::Vector2f(size.x, 600 - size.y / 2);
        name = "Choix 1";
        Bouton choix1Bt(position, size, sf::Color(255, 255, 255), name); //Bouton pour choisir le choix1 de l'évènement

        size = sf::Vector2f(150, 75);
        position = sf::Vector2f(window.getSize().x - size.x * 2, 600 - size.y / 2);
        name = "Choix 2";
        Bouton choix2Bt(position, size, sf::Color(255, 255, 255), name); //Bouton pour choisir le choix2 de l'évènement

        //Permet de gérer l'affichage du score et du HighScore
        sf::Text DescriptionTxt;
        sf::Text HighScoreTxt;
        sf::Text Score;
        sf::Text rewardTxt;
        sf::Font font;

//On créé des rectangles, des sprite et des textures pour l'affichage des statistiques d'un objet lorsqu'on le recupère

        sf::RectangleShape stat_hearth;
        sf::RectangleShape stat_meat;
        sf::RectangleShape stat_sleep;
        sf::RectangleShape stat_ghost;
        sf::RectangleShape stat_addBag;

        sf::Sprite spr;
        sf::Sprite icon_hearth;
        sf::Sprite icon_meat;
        sf::Sprite icon_sleep;
        sf::Sprite icon_ghost;
        sf::Sprite icon_addBag;

        sf::Texture texture;
        sf::Texture textureBtSet;
        sf::Texture textureIcon_hearth;
        sf::Texture textureIcon_meat;
        sf::Texture textureIcon_sleep;
        sf::Texture textureIcon_ghost;
        sf::Texture textureIcon_addBag;

//On crée notre fond d'écran pour l'intégralité du jeu
        sf::RectangleShape BckGndReward;
        BckGndReward.setFillColor(sf::Color(80, 26, 0));
        BckGndReward.setSize(sf::Vector2f(800, 300));
        BckGndReward.setPosition(1280/2 - 400, 720/2 - 150);

//On instancie un objet de la classe Event, qui va correpondre à l'évènement courant
        Events currentEvent(window);
        std::string path ="./Events/Scenario/eventScenario.txt"; //On commence chaque partie par le Scénario du jeu

//On créé une instance de la classe Perso, représentant notre personnage au cours de la partie
        Perso mrToutLeMonde;

//On commence sur le menu principal, on fera evoluer ces variables booléennes pour accéder aux différentes fenêtres
        bool menu = true; //Est-ce que l'on est dans le menu (true) ou non (false)
        bool play = false; //Est-ce que l'on joue (true) ou non (false)
        bool achievement = false; //Est-ce que l'on regarde les Achievements (true) ou non (false)
        bool settings = false;  //Est-ce que l'on est dans les paramètre oui (true), non (false)
        bool tuto = false; //Est-ce que l'on est dans le tutoriel (true) ou non (false)
        bool bag = false; //Est-ce que l'on est dans l'inventaire (true) ou non (false)
        bool reward = false; //Est-ce que l'on obtient un objet (true) ou non (false)

        bool seeBt = true; //Est-ce que l'on vois les bouton des parametres
        bool tutoSee = false; //Est ce que l'on vois le Tuto
        bool death = false; //Est-ce que l'on est mort, oui (true), non (false)



        //On charge la police pour tout les texte
        font.loadFromFile(("./Assets/crackin.ttf"));


        Zonedetext tutoZone( 0, 0, 1280, 720, window);
        tutoZone.setTexteaaf("Lorsque vous arrivez devant les évènements : \nCliquez sur \"Choix 1\" pour réaliser le premier choix \nCliquez sur  \"Choix 2\" pour réaliser le deuxième choix \nCliquez sur le petit sac, en haut, au milieu, de la fenêtre pour accéder à votre inventaire \n\nQuand vous êtes dans l'inventaire, \nCliquez sur l'objet que vous désirez utiliser. \n\nSi votre inventaire est au complet mais que vous récupérer un nouvel objet, \ncelui ci détruira au hasard l'un de vos objets actuels pour le remplacer \nN'hésitez donc surtout pas à les utiliser régulièrement. \n\nEn choisissant l'une des possibilitées, '\n'vous influez directement sur vos statistiques de manière '\n'positive ou negative. \nLorque l'une de vos statistiques indiquent \"KILL\" cela signifie que l'évènement vous tue instantanément. \n\nEn cliquant sur la croix en haut à droit, vous quittez votre partie et revenez sur le menu principal. Mais attention, cela ne sauvegarde pas votre partie en cours ! \n\nBonne chance à vous, aventurier !");
        tutoZone.setFont("./Assets/crackin.ttf");
        tutoZone.setCharacterSize(25);
        tutoZone.setTextColor(sf::Color::White);
        tutoZone.setBgColor(sf::Color(0, 0, 0, 75));

        bool clkReleased = false;


        window.setFramerateLimit(0); //On defini le framerate de la fenetre au maximumm que chaque ordinateur peut suporter
        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) /*On lit tout les evenements qui sont arrivés depuis le dernier tour de boucle*/ {
                        if (event.type == sf::Event::Closed) //Si un evenement est "fermer la fenetre" alors on termine tout et on ferme la fenetre
                                window.close();

                        if (event.type == sf::Event::MouseButtonReleased) {
                                if (event.mouseButton.button == sf::Mouse::Left) /*On regarde si les evenements qui on eut lieu sont des cliques de boutons ou non*/ {
                                        //Si toutes ces conditions sont remplient en renvoie true
                                        clkReleased = true;
                                }
                        }
                }
                /*debut du code graphique*/

                //Si on est sur le menu
                if (menu == true) {
                        if (!texture.loadFromFile("./Assets/BckGnd.jpg")) {
                                std::cerr << "Erreur de chargement du background" << ' ';
                        }
                        spr.setTexture(texture);
                        if (btPlay.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si on clique sur le bouton Play alors on change de bloc pour commencer une partie
                                menu = false;
                                play = true;
                        }
                        if (settingsBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si le bouton des paramètres est cliqué on change de bloc pour aller dans les paramètres
                                menu = false;
                                settings = true;
                        }
                }

                //Si on est en train de jouer
                if (play == true) {
                        currentEvent.fill(path); //On remplit l'évenement courant avec le chemin d'accèes mis en place au debut
                        //On charge et on applique notre background
                        if (!texture.loadFromFile("./Assets/BckGnd.jpg")) {
                                std::cerr << "Erreur de chargement du background" << ' ';
                        }
                        spr.setTexture(texture);
                        if (retourBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si on appuie sur le bouton retour, on revient sur le menu est on annule la partie en cours
                                play = false;
                                menu = true;

                                mrToutLeMonde = Perso();
                                path = "./Events/Scenario/eventScenario.txt";
                        }
                        if (choix1Bt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Ici on applique aux statistiques du joueur celles du choix que le joueur vient de faire
                                mrToutLeMonde.setLife(mrToutLeMonde.getLife() + currentEvent.getLife1());
                                mrToutLeMonde.setFear(mrToutLeMonde.getFear() + currentEvent.getFear1());
                                mrToutLeMonde.setFood(mrToutLeMonde.getFood() + currentEvent.getFood1());
                                mrToutLeMonde.setFatigue(mrToutLeMonde.getFatigue() + currentEvent.getFatigue1());
                                mrToutLeMonde.setTime(mrToutLeMonde.getTime() + currentEvent.getTime1());

                                if (currentEvent.getLoot1()!= "NULL") {
                                        //Si le choix que nous avons fait contient un évènement alors on le rajoute a l'inventaire de notre personnage
                                        Loot loot("./Loots/" + currentEvent.getLoot1(), sf::Vector2f(200, mrToutLeMonde.getStuff().size() * 80 + 150));
                                        mrToutLeMonde.setStuff(loot);

                                        reward = true; //On précise qu'on devra afficher a l'écran notre nouvel objet

                                        if(reward) {
                                                //on met en forme le texte necessaire
                                                rewardTxt.setString("Vous avez obtenu: " + loot.getName());
                                                rewardTxt.setFillColor(sf::Color::White);
                                                rewardTxt.setFont(font);
                                                rewardTxt.setCharacterSize(40);
                                                rewardTxt.setPosition(1280/2 - 400, 720/2 - 150);

                                                //On charge toutes les textures des icones pour afficher l'objet obtenu, notre récompense
                                                if (!textureIcon_hearth.loadFromFile("./Assets/hearth.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_hearth.setTexture(textureIcon_hearth);
                                                icon_hearth.setPosition(250, 330);

                                                stat_hearth.setSize(sf::Vector2f(abs(loot.getLife()) * 20, 30));
                                                stat_hearth.setPosition(sf::Vector2f(310, 340));
                                                stat_hearth.setFillColor(sf::Color(238, 16, 16));

                                                if (!textureIcon_meat.loadFromFile("./Assets/meat.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_meat.setTexture(textureIcon_meat);
                                                icon_meat.setPosition(250, 430);

                                                stat_meat.setSize(sf::Vector2f(abs(loot.getFood()) * 20, 30));
                                                stat_meat.setPosition(sf::Vector2f(310, 440));
                                                stat_meat.setFillColor(sf::Color(255, 255, 50));


                                                if (!textureIcon_sleep.loadFromFile("./Assets/sleep.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_sleep.setTexture(textureIcon_sleep);
                                                icon_sleep.setPosition(550, 330);

                                                stat_sleep.setSize(sf::Vector2f(abs(loot.getFatigue()) * 20, 30));
                                                stat_sleep.setPosition(sf::Vector2f(610, 340));
                                                stat_sleep.setFillColor(sf::Color(161, 6, 132));


                                                if (!textureIcon_ghost.loadFromFile("./Assets/ghost.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_ghost.setTexture(textureIcon_ghost);
                                                icon_ghost.setPosition(550, 430);

                                                stat_ghost.setSize(sf::Vector2f(abs(loot.getFear()) * 20, 30));
                                                stat_ghost.setPosition(sf::Vector2f(610, 440));
                                                stat_ghost.setFillColor(sf::Color(255, 127, 0));

                                                if(!textureIcon_addBag.loadFromFile("./Assets/addBag.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_addBag.setTexture(textureIcon_addBag);
                                                icon_addBag.setPosition(800, 380);

                                                stat_addBag.setSize(sf::Vector2f(abs(loot.getAddStuff()) * 20, 30));
                                                stat_addBag.setPosition(sf::Vector2f(860, 390));
                                                stat_addBag.setFillColor(sf::Color::Black);

                                        }


                                }


                                if (currentEvent.getNext1() != "NULL") /*On regarde s'il y a un évènement suivant à celui en cours*/ {
                                        path = "./Events/" + currentEvent.getNext1(); //Si c'est le cas, on lit le fichier correspodant pour remplir l'évènement courant avec les nouvelles caracteristiques.
                                }
                                else{
                                        path = randomEvent(elements()); //Sinon on charge un évènement aléatoire parmit tous ceux existants
                                }
                        }
                        //Même description que précédement avec le 2eme choix
                        else if (choix2Bt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                mrToutLeMonde.setLife(mrToutLeMonde.getLife() + currentEvent.getLife2());
                                mrToutLeMonde.setFear(mrToutLeMonde.getFear() + currentEvent.getFear2());
                                mrToutLeMonde.setFood(mrToutLeMonde.getFood() + currentEvent.getFood2());
                                mrToutLeMonde.setFatigue(mrToutLeMonde.getFatigue() + currentEvent.getFatigue2());
                                mrToutLeMonde.setTime(mrToutLeMonde.getTime() + currentEvent.getTime2());

                                if (currentEvent.getLoot2()!= "NULL") {
                                        Loot loot("./Loots/" + currentEvent.getLoot2(), sf::Vector2f(200, mrToutLeMonde.getStuff().size() * 80 + 150));

                                        mrToutLeMonde.setStuff(loot);

                                        reward = true;

                                        if(reward) {

                                                rewardTxt.setString("Vous avez obtenu: " + loot.getName());
                                                rewardTxt.setFillColor(sf::Color::White);
                                                rewardTxt.setFont(font);
                                                rewardTxt.setCharacterSize(40);
                                                rewardTxt.setPosition(1280/2 - 400, 720/2 - 150);


                                                if (!textureIcon_hearth.loadFromFile("./Assets/hearth.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_hearth.setTexture(textureIcon_hearth);
                                                icon_hearth.setPosition(250, 330);

                                                stat_hearth.setSize(sf::Vector2f(abs(loot.getLife()) * 20, 30));
                                                stat_hearth.setPosition(sf::Vector2f(310, 340));
                                                stat_hearth.setFillColor(sf::Color(238, 16, 16));

                                                if (!textureIcon_meat.loadFromFile("./Assets/meat.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_meat.setTexture(textureIcon_meat);
                                                icon_meat.setPosition(250, 430);

                                                stat_meat.setSize(sf::Vector2f(abs(loot.getFood()) * 20, 30));
                                                stat_meat.setPosition(sf::Vector2f(310, 440));
                                                stat_meat.setFillColor(sf::Color(255, 255, 50));


                                                if (!textureIcon_sleep.loadFromFile("./Assets/sleep.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_sleep.setTexture(textureIcon_sleep);
                                                icon_sleep.setPosition(550, 330);

                                                stat_sleep.setSize(sf::Vector2f(abs(loot.getFatigue()) * 20, 30));
                                                stat_sleep.setPosition(sf::Vector2f(610, 340));
                                                stat_sleep.setFillColor(sf::Color(161, 6, 132));


                                                if (!textureIcon_ghost.loadFromFile("./Assets/ghost.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_ghost.setTexture(textureIcon_ghost);
                                                icon_ghost.setPosition(550, 430);

                                                stat_ghost.setSize(sf::Vector2f(abs(loot.getFear()) * 20, 30));
                                                stat_ghost.setPosition(sf::Vector2f(610, 440));
                                                stat_ghost.setFillColor(sf::Color(255, 127, 0));

                                                if(!textureIcon_addBag.loadFromFile("./Assets/addBag.png")) {
                                                        std::cout << "Erreur dans le chargement de l'image" << ' ';
                                                }
                                                icon_addBag.setTexture(textureIcon_addBag);
                                                icon_addBag.setPosition(800, 380);

                                                stat_addBag.setSize(sf::Vector2f(abs(loot.getAddStuff()) * 20, 30));
                                                stat_addBag.setPosition(sf::Vector2f(860, 390));
                                                stat_addBag.setFillColor(sf::Color::Black);

                                        }

                                }


                                if (currentEvent.getNext2() != "NULL") {
                                        path = "./Events/" + currentEvent.getNext2();
                                }
                                else{
                                        path = randomEvent(elements());
                                }
                        }
                        else if (inventory.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si le joueur essaie d'accéder a son inventaire (s'il clique sur le bouton inventaire) on change de bloc pour aller dans l'inventiare
                                play = false;
                                bag = true;
                        }
                        if (!mrToutLeMonde.isPlay()) {
                                //Si le personnage est mort on arrete le jeu et on vas dans le bloque death
                                play = false;
                                death = true;
                        }

                }

                //Si le personnage est mort on va en afficher les causes
                if (death) {

                        if(mrToutLeMonde.getFood() <= 0) {

                                DescriptionTxt.setString(L"Cela fait des jours que vous n'avez pas trouvez suffisamment à manger... Vous commencer à entendre votre ventre vous parler... La discussion est si intéressante que vous ne faites plus attention à votre environnement... Vous succombez...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);

                        }

                        else if(mrToutLeMonde.getFood() >= MAX_STAT) {

                                DescriptionTxt.setString(L"En passant votre temps à vous empiffrer,  vous prenez énormement de poids et ne pouvez plus vous déplacer... Vous finissez par rendre l'âme en essayant de vous lever...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);

                        }

                        else if (mrToutLeMonde.getLife() <= 0) {

                                DescriptionTxt.setString(L"Vous sentez votre dernier souffle s'extirper de votre corps...   Vous agonisez doucement à terre en pensant à la vie et à son sens ......42 ?...... Vous finissez par succomber de vos blessures...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);

                        }

                        else if(mrToutLeMonde.getFatigue() <=0) {

                                DescriptionTxt.setString(L"Vous êtes infatigué, beaucoup trop excité... À force d'être hyper actif, votre coeur ne vous suit plus... Vous mourrez d'arrêt cardiaque...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);



                        }

                        else if(mrToutLeMonde.getFatigue() >= MAX_STAT) {

                                DescriptionTxt.setString(L"À force de lutter contre le sommeil,   votre corps finit par vous lacher ...  Vous tombez littéralement de fatigue sans jamais vous réveiller...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);


                        }

                        else if(mrToutLeMonde.getFear() <= 0) {


                                DescriptionTxt.setString(L"Vous êtes trop detendu dans votre environnement...Tout se passe beaucoup trop bien...   Vous n'êtes plus du tout attentif, trop confiant, vous sautez dans un ravin en criant \"Je voooooole\"...   R.I.P.");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);


                        }
                        else if(mrToutLeMonde.getFear() >= MAX_STAT) {

                                DescriptionTxt.setString(L"Un soir, au coin du feu, vous apercevez une grande ombre derrière vous.   Vous partez en courant, sans regarder en arrière.   Dans la précipitation, vous tombez dans une crevasse et... vous succombez...   C'était pourtant juste votre ombre...");
                                DescriptionTxt.setFillColor(sf::Color::White);
                                DescriptionTxt.setFont(font);
                                DescriptionTxt.setCharacterSize(40);
                                DescriptionTxt.setPosition(0,0);

                        }

                        if (retourBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si le bouton retour est pressé on recommence. Donc on recrée un personnage avec ses caractéristiques par defaut
                                mrToutLeMonde = Perso();
                                //Puis on remet l'évènement en cours à celui de départ, donc le scénario
                                path = "./Events/Scenario/eventScenario.txt";
                                //Puis une fois cela fait on change de bloc pour retourner sur le menu
                                death = false;
                                menu = true;
                        }

                        //On convertit le temps du joueur en une chaine de caractère
                        std::stringstream ss_score;
                        ss_score << mrToutLeMonde.getTime();

                        //On fait de meme pour le meilleur score
                        std::stringstream ss_highScore;
                        ss_highScore << testScore(mrToutLeMonde.getTime());

                        //Puis on met en place le texte à afficher
                        std::string tmp_score = "Vous avez survecu :  ";
                        std::string tmp_H = "H";
                        std::string tmp_highS = "Votre meilleur score est :  ";

                        sf::String scrTmp = tmp_score + ss_score.str().c_str() + tmp_H;
                        sf::String HscorTmp = tmp_highS + ss_highScore.str().c_str() + tmp_H;

                        Score.setString(scrTmp);
                        Score.setFillColor(sf::Color::White);
                        Score.setFont(font);
                        Score.setCharacterSize(40);
                        Score.setPosition(550,500);

                        HighScoreTxt.setString(HscorTmp);
                        HighScoreTxt.setFillColor(sf::Color::White);
                        HighScoreTxt.setFont(font);
                        HighScoreTxt.setCharacterSize(40);
                        HighScoreTxt.setPosition(500,600);



                }




                //Si on est dans l'inventaire
                if (bag) {
                        //On charge la texture du background
                        if (!texture.loadFromFile("./Loots/Assets/bckGndInventory.jpg")) {
                                std::cout << "Erreur lors du chargement de l'image" << ' ';
                        }
                        spr.setTexture(texture);

                        if (inventoryBack.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                //Si le bouton de retour est pressé alors on quitte l'inventaire et on revient sur le jeu
                                play = true;
                                bag = false;
                        }

                        for (int i = 0; i < mrToutLeMonde.getStuff().size(); i++) /*On parcourt le tableau correspondant a l'inventaire du joueur*/ {
                                if (mrToutLeMonde.getStuff()[i].getLootBt().isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                        //Si l'un des objets est utilisé alors on met a jour les statistiques du joueur
                                        mrToutLeMonde.setLife(mrToutLeMonde.getLife() + mrToutLeMonde.getStuff()[i].getLife());
                                        mrToutLeMonde.setFear(mrToutLeMonde.getFear() + mrToutLeMonde.getStuff()[i].getFear());
                                        mrToutLeMonde.setFood(mrToutLeMonde.getFood() + mrToutLeMonde.getStuff()[i].getFood());
                                        mrToutLeMonde.setFatigue(mrToutLeMonde.getFatigue() + mrToutLeMonde.getStuff()[i].getFatigue());
                                        mrToutLeMonde.setStuffSize(mrToutLeMonde.getStuffSize() + mrToutLeMonde.getStuff()[i].getAddStuff());

                                        //Puis on enlève l'objet utilisé de l'inventaire
                                        mrToutLeMonde.eraseStuff(i);
                                }
                        }
                }







                //settings
                if (settings == true) {
                        if (tuto) {
                                if (retourBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {

                                        seeBt = true;
                                        tuto = false;
                                }
                        }
                        if (achievement) {
                                //pas encore développé
                        }
                        else{
                                //

                                if (retourBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                        settings = false;
                                        menu = true;
                                        seeBt = true;
                                }
                                if (tutoBt.isPressed(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, clkReleased, window) == true) {
                                        seeBt = false;
                                        tuto = true;
                                }

                        }
                }

                clkReleased = false;

                /*fin du code*/

                //Affichage de chaque élément mis en place au dessus
                window.clear();           //On efface tout ce qu'il y avait précédement dans la fenêtre
                window.draw(spr);         //window.draw(...) permet de mettre en place l'affichage de ce qu'il y a en parametre

                if (menu) {
                        window.draw(btPlay);
                        window.draw(settingsBt);
                }
                if (settings) {
                        if (seeBt) {
                                window.draw(tutoBt);
                                window.draw(AchievBt);
                        }
                        if (!seeBt) {
                                // window.draw(tutoTxt);
                                tutoZone.wrapText();
                        }
                        window.draw(retourBt);
                }
                if (play) {
                        window.draw(retourBt);
                        window.draw(choix1Bt);
                        window.draw(choix2Bt);

                        window.draw(currentEvent);

                        currentEvent.getDescriptionZone().wrapText();
                        currentEvent.getChoix1Zone().wrapText();
                        currentEvent.getChoix2Zone().wrapText();

                        window.draw(mrToutLeMonde);
                        window.draw(inventory);


                }

                if (reward) {
                        window.draw(BckGndReward);
                        window.draw(rewardTxt);

                        window.draw(stat_hearth);
                        window.draw(stat_meat);
                        window.draw(stat_sleep);
                        window.draw(stat_ghost);
                        window.draw(stat_addBag);

                        window.draw(icon_hearth);
                        window.draw(icon_meat);
                        window.draw(icon_sleep);
                        window.draw(icon_ghost);
                        window.draw(icon_addBag);



                        window.display();
                        std::this_thread::sleep_for(std::chrono::seconds(3));
                        reward = false;
                        // window.clear();
                }

                if (bag) {

                        //On boucle sur chaque élément du tableau pour tous les afficher
                        for (int i = 0; i < mrToutLeMonde.getStuff().size(); i++) {
                                window.draw(mrToutLeMonde.getStuff()[i]);
                        }
                        window.draw(mrToutLeMonde);
                        window.draw(inventoryBack);
                }

                if (death) {
                        window.draw(DescriptionTxt);
                        window.draw(retourBt);
                        window.draw(HighScoreTxt);
                        window.draw(Score);
                }
                window.display();   //Permet d'afficher ce qui est mis en place par tous les window.draw(...)
        }


        return 0;
}
