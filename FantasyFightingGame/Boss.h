#ifndef BOSS_H
#define BOSS_H

#include "Entity.h"
#include <iostream>
#include <cmath>

using namespace std;

//boss inheriting from entity
class Boss : public Entity {
private:
	int level;
	double gold, hpRegen;
public:
	//setting all of the boss' values.
	Boss(double d = 7, double a = 5, double health = 25, double maxHealth = 25, int l = 1, double g = 100, double hpr = 5) : Entity(d, a, health, maxHealth) {
		setDamage(d);
		setArmor(a);
		setHp(health);
		setMaxHp(maxHealth);
		level = l;
		gold = g;
		hpRegen = hpr;
	} 

	//getters and setters specific to Boss
	int getLevel() const { return level; }
	double getGold() const { return gold; }
	double getHpRegen() const { return hpRegen; }
	void setLevel(int l) { level = l; }
	void setGold(double g) { gold = g; }
	void setHpRegen(double hpr) { hpRegen = hpr; }

	//other functions
	//level changes and loading in a level
	void refresh() {
		setDamage(floor(pow(2, (level - 1)) * 7));
		setArmor(floor(pow(2, (level - 1)) * 5));
		setMaxHp(floor(pow(2, (level - 1)) * 25));
		gold = floor(pow(1.5, (level - 1)) * 100);
		hpRegen = floor(pow(2, (level - 1)) * 5);
	}

	//polymorphic display function
	virtual void displayStats() {
		cout << "Boss stats: " << endl;
		cout << "\tLevel: " << level << ", Damage: " << getDamage() << ", Armor: " << getArmor();
		cout << ", Health: " << getHp() << "/" << getMaxHp() << ", Health regeneration: " << hpRegen << ", Gold: " << gold << endl;
	}
};
#endif