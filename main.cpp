#include <SFML/Graphics.hpp>
#include <iostream>
#include "creature.h"
#include "game.h"
#include <ctime>
#include <sstream>

using namespace sf;

void lvl_transition(sf::RenderWindow& window, Game& game, int time, int& bounces, int& lvl_transition, int& lvl);
int choose(std::vector<Creature>);

int main() {
    srand(time(0));
    View view;
    RenderWindow window(sf::VideoMode(1920, 1080), "Game", Style::Fullscreen);//
    view.reset(FloatRect(0, 0, 2560, 1080));
    Game game;
    Clock clock;
    double Frames = 0;
    int level = 0, bounces = 0;
    window.setFramerateLimit(30);
    game.setbackground(window, game.menu_sprites.menuBg);

    game.setbackground(window, game.copy);
    game.copy.setPosition(window.getSize().x + game.copy.getGlobalBounds().width / 2, game.copy.getGlobalBounds().height / 2);
    game.setbackground(window, game.background);
    game.setbackground(window, game.lobbybackground);

    for (int i = 0; i < game.getCreatures().size(); i++) {
        game.getCreatures()[i].getSprite().setTexture(game.getCreatures()[i].texture);
        game.getCreatures()[i].lifebar.setTexture(game.getCreatures()[i].lifebartexture);
        game.getCreatures()[i].getSprite().setScale(1.7, 1.7);
    }

    while (window.isOpen()) {


        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800; //скорость игры
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        Frames += time / 300;
        if (Frames >= 3) Frames = 0;
        window.clear();

        sf::Vector2u windowsize = window.getSize();

        if (game.transition_lvl == 3) {
            game.menu(window);

            window.display();
            continue;
        }
        else if (game.transition_lvl == 0) {
            level = 0;
            window.draw(game.lobbybackground);

            game.lobby(window, event);

            window.display();
            continue;
        }

        else if (game.transition_lvl == 1) {


            window.draw(game.background);

            window.draw(game.copy);
            if (level == 0)window.draw(game.lobbybackground);
            lvl_transition(window, game, time, bounces, game.transition_lvl, level);
            window.display();
            continue;
        }
        window.draw(game.background);
        game.setbutton(window, event);
        for (int i = 0; i < game.getTeames().size(); i++) {
            window.draw(game.getTeames()[i].getSprite());
            window.draw(game.getTeames()[i].lifebar);

        }
        for (int i = 0; i < game.getEnemies().size(); i++) {
            if (game.getEnemies()[i].life) {
                window.draw(game.getEnemies()[i].getSprite());
                window.draw(game.getEnemies()[i].lifebar);
            }
        }
        if (game.is_pause) { window.display(); continue; }

        //team attacking
        if (game.isEnenmyalive()) {
            if (game.isTeamalive()) {
                for (int i = 0; i < game.getTeames().size(); i++) {
                    if (game.getTeames()[i].life) {
                        game.getTeames()[i].attack(game.getEnemies()[choose(game.getEnemies())], time, Frames);

                    }

                }

                for (int i = 0; i < game.getEnemies().size(); i++) {
                    if (game.getEnemies()[i].life) {
                        game.getEnemies()[i].attack(game.getTeames()[choose(game.getTeames())], time, Frames);
                    }
                }
            }
            else {
                game.setbackground(window, game.lobbybackground);
                game.copy.setPosition(window.getSize().x + game.copy.getGlobalBounds().width / 2, game.copy.getGlobalBounds().height / 2);
                game.transition_lvl = 0; level = 0;

            }
        }
        else {
            game.transition_lvl = 1; level++;

        }
        window.display();

    }
    return 0;
}




void lvl_transition(sf::RenderWindow& window, Game& game, int time, int& bounces, int& lvl_transition, int& lvl) {
    bool isbounce = false;
    if (game.copy.getPosition().x > window.getSize().x / 2) {
        game.lobbybackground.move(-time * 0.55, 0);
        game.background.move(-time * 0.55, 0);
        game.copy.move(-time * 0.55, 0);
    }
    for (int i = 0; i < game.getTeames().size(); i++) {
        window.draw(game.getTeames()[i].getSprite());
        if (game.getTeames()[i].getY() - 30 < game.getTeames()[i].getSprite().getPosition().y && game.getTeames()[i].getY() > game.getTeames()[i].getSprite().getPosition().y) {
            if (bounces % 2 == 0) {
                game.getTeames()[i].getSprite().setPosition(game.getTeames()[i].getSprite().getPosition().x, game.getTeames()[i].getSprite().getPosition().y + 0.1 * time);
            }
            else {
                game.getTeames()[i].getSprite().setPosition(game.getTeames()[i].getSprite().getPosition().x, game.getTeames()[i].getSprite().getPosition().y - 0.1 * time);
            }
        }
        else {
            game.getTeames()[i].getSprite().setPosition(game.getTeames()[i].getSprite().getPosition().x, game.getTeames()[i].getSprite().getPosition().y + (bounces % 2 == 0 ? -0.1 * time : 0.1 * time));
            isbounce = true;


        }
        if (game.getTeames()[i].getX() > game.lvlteam[i].x) { game.getTeames()[i].getSprite().setPosition(game.getTeames()[i].getSprite().getPosition().x - 2 * time * game.getTeames()[i].getSpeed(), game.getTeames()[i].getSprite().getPosition().y); }

    }
    if (bounces == 15) {

        bounces = 0;
        lvl_transition = -2;//чтобы больше ни лобби ни чего другого не было
        game.background.setPosition(game.background.getGlobalBounds().width / 2, game.background.getGlobalBounds().height / 2);

        game.lobbybackground.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        game.lvl_update();
    }
    if (isbounce) {
        isbounce = false;
        bounces++;
    }

}

int choose(std::vector<Creature> vector) {
    for (int i = 0; i < vector.size(); i++) {
        int g = rand() % vector.size();
        if (vector[g].life)return g;
    }
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].life)return i;
    }

}
