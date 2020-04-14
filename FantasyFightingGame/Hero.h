#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include <iostream>

using namespace std;

//hero inheriting from entity
class Hero : public Entity {
private:
	string name;
	int level;
	double critChance, critMult, healing, gold;
public:
	//Setting the Hero's stats. 
	Hero(double d = 5, double a = 0, double health = 15, double maxHealth = 15, string n = "Phil", int l = 1, double cc = 0, double cm = 2, double heal = 5, double g = 0) : Entity(d, a, health, maxHealth) {
		setDamage(d);
		setArmor(a);
		setHp(health);
		setMaxHp(maxHealth);
		name = n;
		level = l;
		critChance = cc;
		critMult = cm;
		healing = heal;
		gold = g;
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
	void levelUp() {
		level++;
		//30% increase to damage, 20% on armor and maxHp (with an extra +1 each level on armor to allow initial growth), Crit chance/mult and healing are upgraded in the shop
		setDamage(floor(getDamage() * 1.3));
		if (getArmor() < 5) {
			setArmor(getArmor() + 1);
		}
		else {
			setArmor(floor(getArmor() * 1.2));
		}
		setMaxHp(floor(getMaxHp() * 1.2));
		//setHp(getMaxHp());
	}

	//polymorphic display function
	virtual void displayStats() {
		cout << name << "'s stats:" << endl;
		cout << "Level: " << level << ", Damage: " << getDamage() << ", Armor: " << getArmor();
		cout << ", Health: " << getHp() << "/" << getMaxHp() << ", Healing: " << healing << ", Critical Chance: ";
		cout << critChance << ", Critical Multiplier: " << critMult << ", Gold: " << gold << endl;
	}
};
#endif