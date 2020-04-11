#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include <iostream>

using namespace std;

//hero inheriting from entity
class Hero : Entity {
private:
	string name;
	int level;
	double critChance, critMult, healing, gold;
public:
	//Setting the Hero's stats. 
	Hero() {
		setDamage(4);
		setArmor(0);
		setHp(15);
		setMaxHp(15);
		name = "Phil";
		level = 1;
		critChance = 0.0;
		critMult = 2;
		healing = 5;
		gold = 0;
	}

	//setters and getters... so many setters and getters...
	double getCritChance() const { return critChance; }
	double getCritMult() const { return critMult; }
	double getHeal() const { return healing; }
	int getLevel() const { return level; }
	double getGold() const { return gold; }
	string getName() const { return name; }
	void setCritChance(double cc) { critChance = cc; }
	void setCritMult(double cm) { critMult = cm; }
	void setHeal(double h) { healing = h; }
	void setLevel(int l) { level = l; }
	void setGold(double g) { gold = g; }
	void setName(string n) { name = n; }

	//other functions 
	void levelUp() { level++; }

	//polymorphic display function
	virtual void displayStats() {
		cout << name << "'s stats:" << endl;
		cout << "Level: " << level << ", Damage: " << getDamage() << ", Armor: " << getArmor();
		cout << ", Health: " << getHp() << "/" << getMaxHp() << ", Healing: " << healing << ", Critical Chance: ";
		cout << critChance << ", Critical Multiplier: " << critMult << ", Gold: " << gold << endl;
	}
};
#endif