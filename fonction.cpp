#include "fonction.hpp"

//cette fonction renvoie un string qui correspond a un evement aleatoire parmi les val_max premiers evenements
std::string randomEvent(int val_max){

        std::string event, result;
        int rand_num;

        std::random_device rd;

        rand_num = rd()%val_max + 1;

        std::stringstream convert;
        convert << rand_num;
        result = convert.str();

        return event = "./Events/event" + result + ".txt";
}

//on test le score actuel du pesonnage et le score contenu dans le fichier hightscore.txt. Si le nouveaux est superieur alors on l'actualise dans le fichier
int testScore(int score){

        int val_highScore;
        std::ifstream highScore("./Divers/HighScore.txt", std::ios::in);


        highScore >> val_highScore;
        highScore.close();

        if(score > val_highScore) {
                std::ofstream highScore("./Divers/HighScore.txt", std::ios::trunc);

                highScore << score;
                highScore.close();

                return score; //Le score de la partie actuelle est superieur a celui du High Score
        }

        if(val_highScore > score)
                return val_highScore;  //Le High Score n'a pas ete battu, rien ne change
        return val_highScore;
}

//renvoie le nombre maximum d'evenement utilisable parmi tous ceux existants
int elements(){

        std::ifstream file;
        int nbElement = 0;
        file.open("./Events/event1.txt", std::ios::in);

        do {
                file.close();
                nbElement++;
                std::stringstream convert;
                convert << nbElement;

                std::string path = "";
                path = "./Events/event" + convert.str() + ".txt";
                file.open(path, std::ios::in);


        } while(file);

        nbElement -= 1;

        return nbElement;
}



void Dynamicresize(sf::Event event, sf::RenderWindow& renderWindow) //pour resize la fenetre
{


        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        renderWindow.setView(sf::View(visibleArea));

//reste  a mettre dans la class
}
