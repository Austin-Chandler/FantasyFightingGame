#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Boss.h"
#include "Hero.h"
#include <iostream>

using namespace std;

class Game {
private:
	//composing game of an enemy, a boss, and a hero
	Enemy enemy;
	Boss boss;
	Hero hero;
public:
	Game() {

	}

	bool welcomeScreen() {
		char input = ' ';
		cout << "Hello! Welcome to: Sannhet's Legacy! Would you like to load a character? (Y/N)" << endl;
		cin >> input;
		while (input != 'Y' && input != 'y' && input != 'N' && input != 'n') {
			cout << "Please enter Y or N: ";
			cin >> input;
		}
		if (input == 'Y' || input == 'y') {
			cout << "Welcome" << endl;
			return true;
		}
		else if (input == 'N' || input == 'n') {
			cout << "Bye" << endl;
			return false;
		}
	}

	void resetEnemy() {
		//setting enemy starts to 80% of hero stats
		enemy.setDamage(floor(.8 * hero.getDamage()));
		enemy.setArmor(floor(.8 * hero.getArmor()));
		enemy.setMaxHp(floor(.8 * hero.getMaxHp()));
		enemy.setHp(enemy.getMaxHp());
		enemy.setMaxGoldDrop((hero.getLevel() * 2) + 20); //add 2 * the hero level to the original 20 gold (e.x. @level 4 the enemy will drop a max of (20 + (4*2)) = 28 gold)
		if (hero.getLevel() % 10 == 0) { //every 10 hero levels increase the gold drop chance chance from the enemy
			enemy.setGoldDropChance(enemy.getGoldDropChance() + 1);
		}
	}

	void testLevel() {
		for (int i = 0; i < 1; i++) {					//Add this bit later to the end of forest() but change 1 to variable that holds level up repition 
			hero.levelUp();
		}
		resetEnemy();
		hero.displayStats();
		enemy.displayStats();
	}

	void displayAll() {
		enemy.displayStats();
		boss.displayStats();
		hero.displayStats();
	}
};
#endif