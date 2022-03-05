#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Creature {
private:
	std::string name;
	int   damage, armor,dir1;
	double hp, consthp;
	double speed, x, y, attackspeed,attackreload,width, height;
	sf::Sprite sprite;
public:
	sf::Sprite lifebar;

	sf::Texture texture;
	sf::Texture lifebartexture;
	double dx, dy;
	bool life;

	Creature(std::string file, std::string fname="Lox", int fhp = 500, double fspeed = 0.1, int fdamage = 75,
		int farmor = 50, double fx = 0, double fy = 0, int fdir1 = 0,double fattackspeed=2,double fheight = 100, double fwidth = 48) :
		name(fname), hp(fhp), damage(fdamage), armor(farmor),speed(fspeed),x(fx),y(fy) ,dir1(fdir1),attackspeed(fattackspeed),width(fwidth),height(fheight),consthp(fhp){
		attackreload = attackspeed;
		texture.loadFromFile(file);
		lifebartexture.loadFromFile("Images/lifebar.png");
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		//lifebar
		lifebar.setTexture(lifebartexture);
		lifebar.setPosition(x,y+height/2-40);
		life = true;
	}

	//getters
	std::string getName();
	double getHP();
	int getDamage();
	int getArmor();
	double getDistance(Creature);
	std::vector<double> getDist(Creature);
	int getDir1();
	double getSpeed();
	double getX();
	double getY();
	double getAttackspeed();
	double getAttackreload();
	double getHeight();
	double getWidth(); 
	double getAttackdist();
	double getconstHP();
	sf::Sprite& getSprite();
	sf::Sprite& getBar();
	//setters
	void setAttackspeed(double);
	void setName(std::string);
	void setHP(int);
	void setDamage(int);
	void setArmor(int);
	void setSpeed(double);
	void setDir1(int);
	void setX(double);
	void setY(double);
	void setAttackreload(double);
	void setPosition(double, double);
	void showStatus();//статус игрока
	void update(double time, double Frames);
	void attack(Creature& creature, double time, double Frames) {
		bool enemy = getDist(creature)[0] < 0 ? true : false;
		
		if (getAttackreload() > 0) {
			setAttackreload(getAttackreload() - 1/time*1.5);
			if (!enemy) {
				if (getX() < getSprite().getPosition().x) { 
					getSprite().setPosition(sprite.getPosition().x - getSpeed() * time / 4, sprite.getPosition().y); 
					lifebar.setPosition(sprite.getPosition().x - getWidth() / 2, sprite.getPosition().y - getHeight() / 2 - 40);
				}
				
			}
			else {
				if (getX() > getSprite().getPosition().x) { getSprite().setPosition(sprite.getPosition().x + getSpeed() * time / 4, sprite.getPosition().y);
				lifebar.setPosition(sprite.getPosition().x - getWidth() / 2, sprite.getPosition().y - getHeight() / 2 - 40);
				}
			}
		}
		else {
			bool ismove=false;
			if (!enemy) {
				if (getX()+20  > getSprite().getPosition().x) {
					ismove = true;
					getSprite().setPosition(sprite.getPosition().x + getSpeed() * time / 4, sprite.getPosition().y);
					lifebar.setPosition(sprite.getPosition().x - getWidth() / 2, sprite.getPosition().y - getHeight() / 2 - 40);
				}

			}
			else {
				if (getX() -20 < getSprite().getPosition().x) {
					ismove = true;
					getSprite().setPosition(sprite.getPosition().x - getSpeed() * time / 4, sprite.getPosition().y);
					lifebar.setPosition(sprite.getPosition().x - getWidth() / 2, sprite.getPosition().y - getHeight() / 2 - 40);
				}
			}

			
			if(!ismove) {
				creature.setHP(creature.getHP() - damage);
				creature.lifebar.setScale(creature.getHP() / creature.getconstHP(), 1);
				setAttackreload(getAttackspeed());
				if (creature.getHP() <= 0) { creature.life = false; 
				creature.lifebar.setScale(0,0);
				}
			}
		}
	}
};



class Item {
private:
	double prop;
	char to;
public:
	void add_prop(Creature &creature );
	void del_prop(Creature& creature);
};


