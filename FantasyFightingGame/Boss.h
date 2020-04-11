#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"
#include <iostream>

using namespace std;

//boss inheriting from entity
class Boss : Entity {
private:
	int level;
	double gold, hpRegen;
public:
	//setting all of the boss' values.
	Boss() {
		setDamage(7);
		setArmor(5);
		setHp(25);
		setMaxHp(25);
		level = 1;
		gold = 100;
		hpRegen = 5;
	} 
	
	//getters and setters
	int getLevel() const { return level; }
	double getGold() const { return gold; }
	double getHpRegen() const { return hpRegen; }
	void setLevel(int l) { level = l; }
	void setGold(double g) { gold = g; }
	void setHpRegen(double hpr) { hpRegen = hpr; }

	//other functions
	void levelUp() { level++; }

	//polymorphic display function
	virtual void displayStats() {
		cout << "Boss stats: " << endl;
		cout << "Level: " << level << ", Damage: " << getDamage() << ", Armor: " << getArmor();
		cout << ", Health: " << getHp() << "/" << getMaxHp() << ", Health regeneration: " << hpRegen << ", Gold: " << gold << endl;
	}
};
#endif