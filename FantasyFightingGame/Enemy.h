#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <ctime>
#include <iostream>

using namespace std;

//enemy inheriting from entity
class Enemy : public Entity {
private: 
	double goldDropChance, maxGoldDrop;
public:
	//setting all of the enemy's values. 
	Enemy(double d = 2, double a = 0, double health = 10, double maxHealth = 10, double gdc = 3, double mgd = 20) : Entity(d, a, health, maxHealth) {
		setDamage(d);
		setArmor(a);
		setHp(health);
		setMaxHp(maxHealth);
		goldDropChance = gdc;//1 / (9-GDC) chance (if 9, 100% chance) (17% here)
		maxGoldDrop = mgd;
		srand(time(NULL));
	}

	//getters and setters specific to enemy
	double getGoldDropChance() const { return goldDropChance; }
	double getMaxGoldDrop() const { return maxGoldDrop; }
	void setGoldDropChance(double GDC) { goldDropChance = GDC; }
	void setMaxGoldDrop(double MGD) { maxGoldDrop = MGD; }


	//other functions
	double goldDropped() {
		//picking a random number between 0 and 9, if it is less than or equal to the chance drop full gold
		if ((rand() % 10) <= goldDropChance) {
			cout << "The enemy dropped " << maxGoldDrop << " gold!" << endl;

			return maxGoldDrop;
		}
		//if it is not less then drop 1/3 of the max gold
		else {
			cout << "The enemy dropped " << floor(maxGoldDrop / 3) << " gold!" << endl;
			return floor(maxGoldDrop / 3);
		}
	}

	//polymorphic display function
	virtual void displayStats() {
		cout << "Enemy stats: " << endl;
		cout << "\tDamage: " << getDamage() << ", Armor: " << getArmor() << ", Health: " << getHp() << "/" << getMaxHp() << ", Max possible gold: " << maxGoldDrop << endl;
	}
};

#endif