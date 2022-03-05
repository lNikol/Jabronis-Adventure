#include "creature.h"
#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
std::string Creature::getName() { return name; }
double Creature::getHP() { return hp; }
double Creature::getconstHP() { return consthp; }
int Creature::getDamage() { return damage; }
int Creature::getArmor() { return armor; }
double Creature::getSpeed() { return speed; }
int Creature::getDir1() { return dir1; }
double Creature::getX() { return x; }
double Creature::getY() { return y; }
double Creature::getAttackspeed() { return attackspeed; }
double Creature::getHeight() { return height; };
double Creature::getWidth() { return width; };
double Creature::getAttackreload() { return attackreload; };
sf::Sprite& Creature::getSprite() {
	return sprite;
}
void Creature::setName(std::string fname) { name = fname; }
void Creature::setHP(int fhp) { hp = fhp; }
void Creature::setAttackspeed(double fa) { attackspeed = fa; }
void Creature::setDamage(int fdamage) {	damage = fdamage; }
void Creature::setArmor(int farmor) { armor = farmor; }
void  Creature::setDir1(int fdir) { dir1=fdir; }
void Creature::setSpeed(double fspeed) { speed = fspeed; };
void  Creature::setX(double fx) { x = fx; }
void  Creature::setY(double fy) { y = fy; }
void Creature::setAttackreload(double fattackreload) { attackreload = fattackreload; }
void Creature::setPosition(double fx, double fy) { setX(fx); setY(fy); sprite.setPosition(fx, fy); }
void Creature::showStatus() {
	std::cout << " Name:" << name << std::endl;
	std::cout << " HP:" << hp << std::endl;
	std::cout << " Armor:" << armor << std::endl;
	std::cout << " Damage:" << damage << std::endl<<std::endl;

}
double Creature::getDistance(Creature creature) {

	return sqrt(pow(creature.sprite.getPosition().x - sprite.getPosition().x, 2) + pow(creature.sprite.getPosition().y - sprite.getPosition().y, 2));
}
std::vector<double> Creature::getDist(Creature creature) {
	return { creature.sprite.getPosition().x - sprite.getPosition().x,creature.sprite.getPosition().y - sprite.getPosition().y };
}
void Item::add_prop(Creature & creature ) {
	switch (to) {
	//damage
	case('d'): creature.setDamage(creature.getDamage() + prop); break;
	//reload % от настоящей скорости атаки
	case('r'):
		prop *= creature.getAttackspeed() / 100; creature.setAttackspeed(creature.getAttackspeed() +prop); break;
	case('h'): creature.setHP(creature.getHP() + prop); break;

 }
}
void Item::del_prop(Creature& creature) {
	switch (to) {
		//damage
	case('d'): creature.setDamage(creature.getDamage() - prop); break;
		//reload % от настоящей скорости атаки
	case('r'):
		 creature.setAttackspeed(creature.getAttackspeed() - prop); break;
	case('h'): creature.setHP(creature.getHP() - prop); break;

	}
}
