#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "creature.h"
#include <sstream>
#include <fstream>
class Game {
private:
    struct Point {
        double x, y;
    };
    std::vector<Creature> enemy, team, creatures, creatures_enemy;
    std::vector<sf::Sprite> endpos;
    std::vector<Point> lobbypos = { {640,400},{380,660},{750,700} };

    struct Table {
        sf::Sprite table;
        sf::Texture TableTexture;
        sf::Texture button_texture;
        sf::Sprite button, button1, button2, button3;
        sf::Texture button_texture1, button_texture2, button_texture3;       
    };
    Table table;


public:
    bool is_pause;
    sf::Sprite lobbybackground, background, copy, button_skip;
    sf::Texture texture, texturebackground, texture4;
    int transition_lvl = 3;
    int ispicked[4] = { 0,0,0,0 };//выбран ли игрок; хранится значение в каком кубике хранится
    int isbusy[4] = { 0,0,0,0 };//занят ли "кубик" значение индекса выбранного игрока
    struct Menu {
        sf::Text start, about, settings, exit, name;
        sf::Font font;
        int menuNum;
        sf::Texture menuBackground, menuAboutUs, menuSettings;
        sf::Sprite menuBg, About, Settings;
    };
    Menu menu_sprites;
    std::vector<Point> lvlteam = { {100,950},{200,950},{300,950},{100,400},{100,500} };
    std::vector<Point> lvlenemy = { {600,950},{700,950},{800,950},{600,400},{600,500} };
    Game();
    std::vector<Creature>& getEnemies() { return enemy; }
    std::vector<Creature>& getCreatures() { return creatures; }
    std::vector<Creature>& getCreatures_enemy() { return creatures_enemy; }
    std::vector<Creature>& getTeames() { return team; }
    std::vector<Point>& getlobbypos() { return lobbypos; }
    std::vector<sf::Sprite>& getendpos() { return endpos; }

    bool isTeamalive();
    void menu(sf::RenderWindow& window) {
        menu_sprites.start.setFillColor(sf::Color::White);
        menu_sprites.about.setFillColor(sf::Color::White);
        menu_sprites.settings.setFillColor(sf::Color::White);
        menu_sprites.exit.setFillColor(sf::Color::White);

        if (menu_sprites.menuNum == 0) {

            if (sf::IntRect(100, 100, 100, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.start.setFillColor(sf::Color::Blue); }
            if (sf::IntRect(100, 200, 200, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.about.setFillColor(sf::Color::Blue); }
            if (sf::IntRect(100, 300, 125, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.settings.setFillColor(sf::Color::Blue); }
            if (sf::IntRect(100, 400, 75, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.exit.setFillColor(sf::Color::Blue); }

            if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::IntRect(100, 100, 100, 30).contains(sf::Mouse::getPosition(window))))
                || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::IntRect(100, 200, 200, 30).contains(sf::Mouse::getPosition(window))))
                || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::IntRect(100, 300, 125, 30).contains(sf::Mouse::getPosition(window))))
                || (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::IntRect(100, 400, 75, 30).contains(sf::Mouse::getPosition(window)))))

            {
                if (sf::IntRect(100, 100, 100, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.menuNum = 1; }
                if (sf::IntRect(100, 200, 200, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.menuNum = 2; }
                if (sf::IntRect(100, 300, 125, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.menuNum = 3; }
                if (sf::IntRect(100, 400, 75, 30).contains(sf::Mouse::getPosition(window))) { menu_sprites.menuNum = 4; }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (menu_sprites.menuNum == 1) transition_lvl = 0;//если нажали первую кнопку, то выходим из меню 
                if (menu_sprites.menuNum == 2)
                {
                   window.draw(menu_sprites.About); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); menu_sprites.menuNum = 0;
                }
                if (menu_sprites.menuNum == 3)
                {
                    menu_sprites.Settings.setScale(1.3, 1.2); window.draw(menu_sprites.Settings); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))menu_sprites.menuNum = 0;
                }
                if (menu_sprites.menuNum == 4) { window.close(); }
            }
            window.draw(menu_sprites.menuBg);
            window.draw(menu_sprites.start);
            window.draw(menu_sprites.about);
            window.draw(menu_sprites.settings);
            window.draw(menu_sprites.exit);
            window.draw(menu_sprites.name);
        }

    }
    void setbackground(sf::RenderWindow& window, sf::Sprite& background) {
        background.setOrigin(background.getGlobalBounds().width / 2, background.getGlobalBounds().height / 2);
        background.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        background.setScale(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height);

        window.draw(background);


    }
    void lobby(sf::RenderWindow& window,  sf::Event event) {
        setlocale(LC_ALL, "Russian");
        window.draw(button_skip);
        for (int i = 0; i < getendpos().size(); i++) {
            window.draw(getendpos()[i]);
        };

        for (int i = 0; i < getCreatures().size(); i++) {
            window.draw(getCreatures()[i].getSprite());
        }
        setbutton(window,event);
        if (is_pause)return;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            sf::Vector2i pos = sf::Mouse::getPosition(window);
            for (int i = 0; i < getCreatures().size(); i++) {

                if (getCreatures()[i].getSprite().getGlobalBounds().contains(pos.x, pos.y))
                {


                    int dX = pos.x;
                    int  dY = pos.y;
                    if (ispicked[i] == 0) {
                        for (int g = 0; g < getendpos().size(); g++) {
                            if (isbusy[g] == 0) {
                               getCreatures()[i].setPosition(getendpos()[g].getPosition().x, getendpos()[g].getPosition().y);

                                ispicked[i] = g + 1;
                                isbusy[g] = i + 1;
                                break;
                            }

                        }

                    }
                    else {
                        getCreatures()[i].setPosition(getlobbypos()[i].x, getlobbypos()[i].y);
                        isbusy[ispicked[i] - 1] = 0;
                        ispicked[i] = 0;

                    }
                }

            }
            if (button_skip.getGlobalBounds().contains(pos.x, pos.y)) {
                
                    getTeames().clear();
                    getEnemies().clear();
                    for (int i = 0; i < getendpos().size(); i++) {
                        if (isbusy[i] != 0) {
                            getTeames().push_back(getCreatures()[isbusy[i] - 1]); 
                        }
                        ispicked[i] = 0; 
                        isbusy[i] = 0;
                        

                    }
                    if (getTeames().size() == 0)return;
                    for (int i = 0; i < getCreatures().size(); i++) {
                        getCreatures()[i].setPosition(getlobbypos()[i].x, getlobbypos()[i].y);
                    }

                    transition_lvl = 1;

                    return;
                
              
            }
        }
    }
    void lvl_update( ) {
        
        getEnemies().clear();
        for (int i = 0; i < getTeames().size(); i++) {
            getTeames()[i].setPosition(lvlteam[i].x, lvlteam[i].y);
            getTeames()[i].setHP(getTeames()[i].getconstHP());
            getTeames()[i].life = true;
            getTeames()[i].lifebar.setPosition(getTeames()[i].getX() - getTeames()[i].getWidth() / 2, getTeames()[i].getY() - getTeames()[i].getHeight() / 2 - 40);
            getTeames()[i].lifebar.setScale(1, 1);
        }

        srand(time(0));
        int g;
        //auto it = std::find_if(line.begin(), line.end(), isdigit);
        //std::cout << std::atoi(line.c_str() + (it - line.begin()));
        for (int i = 0; i < 3; i++) {
            std::stringstream string;

            Creature creature("");
            g = rand() % 3;
            string << "Images/enemy" << g << ".png";
            creature = getCreatures_enemy()[g];

            creature.setPosition(lvlenemy[i].x, lvlenemy[i].y);
            creature.lifebartexture.loadFromFile("Images/lifebar_enemy.png");
            creature.texture.loadFromFile(string.str());


            getEnemies().push_back(creature);
            getEnemies()[i].getSprite().setTexture(getEnemies()[i].texture);
            getEnemies()[i].getSprite().setScale(1.7, 1.7);
            getEnemies()[i].lifebar.setPosition(getEnemies()[i].getX() - getEnemies()[i].getWidth() / 2, getEnemies()[i].getY() - getEnemies()[i].getHeight() / 2 - 20);
            getEnemies()[i].lifebar.setTexture(getEnemies()[i].lifebartexture);

        }

        for (int i = 0; i < getEnemies().size(); i++) {

            getEnemies()[i].getSprite().setTexture(getEnemies()[i].texture);
            getEnemies()[i].lifebar.setTexture(getEnemies()[i].lifebartexture);
        }

    }
    bool isEnenmyalive() {
        for (int i = 0; i < getEnemies().size(); i++) {
            if (getEnemies()[i].life == true)return true;
        }
        return false;
    }

    void setbutton(sf::RenderWindow& window,  sf::Event event) {

        
        window.draw(table.button);
        

        if (is_pause) {
            window.draw(table.table);
            window.draw(table.button1);
            window.draw(table.button2);
            window.draw(table.button3);

        }


        
        //setbackground(window,exil);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (table.button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) || sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
                is_pause = true;
                table.table.setTexture(table.TableTexture);

                window.draw(table.table);
            }
            if ( table.button1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) ) {
                is_pause = false;
            }
            else if (table.button2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) ) {
                copy.setPosition(window.getSize().x + copy.getGlobalBounds().width / 2, copy.getGlobalBounds().height / 2);
                is_pause = false; transition_lvl = 0; 
            }
            else if (table.button3.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) ) {
                window.close();
            }
        }
    }
};
