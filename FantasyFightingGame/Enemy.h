#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <ctime>
#include <iostream>

using namespace std;

//enemy inheriting from entity
class Enemy : Entity {
private: 
	double goldDropChance, maxGoldDrop;
public:
	//setting all of the enemy's values. 
	Enemy() {
		setDamage(2);
		setArmor(0);
		setHp(10);
		setMaxHp(10);
		goldDropChance = 5;//1 / (9-GDC) chance (if 9, 100% chance) (25% here)
		maxGoldDrop = 50;
		srand(time(NULL));
	}

	//getters and setters
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
		cout << "Damage: " << getDamage() << ", Armor: " << getArmor() << ", Health: " << getHp() << "/" << getMaxHp() << ", Max possible gold: " << maxGoldDrop << endl;
	}
};

#endif