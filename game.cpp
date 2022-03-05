#include "creature.h"
#include <cmath>
#include "game.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

 Game::Game() {
    
	 for (int i = 0; i < 3; i++) {
         std::stringstream file;
         file << "Images/hero" << i << ".png";
		 Creature creature(file.str(),"chel");
        
		 creatures.push_back(creature);
		 creatures[i].setPosition(lobbypos[i].x, lobbypos[i].y);

         std::stringstream file1;
         file << "Images/enemy" << i << ".png";
         Creature creature1(file1.str(), "chel");
         creatures_enemy.push_back(creature1);
	 }
     //table
     table.TableTexture.loadFromFile("Images/table.png");
     table.button_texture.loadFromFile("Images/menubutton.png");
     table.button_texture1.loadFromFile("Images/continue.png");
     table.button_texture2.loadFromFile("Images/settings.png");
     table.button_texture3.loadFromFile("Images/exit.png");
     table.table.setTexture(table.TableTexture);
     table.button.setTexture(table.button_texture);
     table.button1.setTexture(table.button_texture1);
     table.button2.setTexture(table.button_texture2);
     table.button3.setTexture(table.button_texture3);
     table.button.setPosition(0, 0);
     table.button1.setPosition(850, 400);
     table.button2.setPosition(850, 460);
     table.button3.setPosition(850, 520);
     table.table.setPosition(500, 200);

     texturebackground.loadFromFile("Images/background.png");
     background.setTexture(texturebackground);
     texture.loadFromFile("Images/lobby.png");
     lobbybackground.setTexture(texture);
     copy.setTexture(texturebackground);
     //menu
     menu_sprites.font.loadFromFile("CyrilicOld.ttf");
     menu_sprites.start.setFont(menu_sprites.font);
     menu_sprites.about.setFont(menu_sprites.font);
     menu_sprites.settings.setFont(menu_sprites.font);
     menu_sprites.exit.setFont(menu_sprites.font);
     menu_sprites.name.setFont(menu_sprites.font);
     menu_sprites.start.setString("Play");
     menu_sprites.about.setString("About the program ");
     menu_sprites.settings.setString("Settings");
     menu_sprites.exit.setString("Exit");
     menu_sprites.name.setString("Jabronis adventure");
     menu_sprites.name.setFillColor(sf::Color::Red);
     menu_sprites.name.setCharacterSize(48);

     menu_sprites.menuAboutUs.loadFromFile("Images/menu/background.png");
     menu_sprites.menuBackground.loadFromFile("Images/menu/menu.png");
     menu_sprites.menuSettings.loadFromFile("Images/menu/settings.jpg");
     menu_sprites.menuBg.setTexture(menu_sprites.menuBackground); menu_sprites.About.setTexture(menu_sprites.menuAboutUs), menu_sprites.Settings.setTexture(menu_sprites.menuSettings);

     menu_sprites.menuBg.setPosition(0, 0);
     menu_sprites.start.setPosition(100, 100);
     menu_sprites.about.setPosition(100, 200);
     menu_sprites.settings.setPosition(100, 300);
     menu_sprites.exit.setPosition(100, 400);
     menu_sprites.name.setPosition(750,50);

     texture4.loadFromFile("Images/button.png");
     button_skip.setTexture(texture4);
     button_skip.setPosition(1800,0);
     


	for (int i = 0; i < 4; i++) {
        sf::Texture texture;
        texture.loadFromFile("");
		sf::Sprite kubik;
		endpos.push_back(kubik);
	}



  
	endpos[0].setPosition(100, 925);
	endpos[1].setPosition(200, 925);
	endpos[2].setPosition(300, 925);
	endpos[3].setPosition(400, 925);

 }

 bool Game::isTeamalive() {
	 for (int i = 0; i < getTeames().size(); i++) {
		 if (getTeames()[i].life == true)return true;
	 }
	 return false;
 }
