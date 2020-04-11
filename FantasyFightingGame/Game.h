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

	void storyline() {
		cout << "A long time ago there was a great chief named Sannhet. He ruled all the land, as far as the eye could see." << endl;
		cout << "However, unbeknownst to him, a challenger was waiting to overthrow him. His name was Bedrageri. Bedrageri" << endl;
		cout << "spread countless apocryphal about Sannhet deceiving his subjects. People began to doubt Sannhet's integrity " << endl;
		cout << "and therefore his power to protect them. Bedrageri promised truthfulness and security if people would join " << endl;
		cout << "him and depose Sannhet. Many believed himand joined his cause. Several months later Bedrageriand all his " << endl;
		cout << "followers surprise attacked Sannhetand he was quickly overwhelmed. Many centuries have passed nowand Bedrageri " << hero.getName() << endl;
		cout << "still rules with very few remaining loyal to Sannhet. It is your job young to train and defeat Bedrageri once and for all." << endl << endl;
		cout << "You must begin at once..." << endl;
	}

	bool isWinner() {
		if (boss.getLevel() == 11) {
			return true;
		}
		else {
			return false;
		}
	}

	void main() {
		string input = "";
		do {
			cout << "What would you like to do: go to shop (s), go to forest (f), fight a boss (b), save (save), check stats (stats), or end (e)?" << endl;
			cin >> input;
			while (input != "s" && input != "f" && input != "b" && input != "save" && input != "stats" && input != "e") {
				cout << "Please enter s, f, b, save, stats, or e (case sensitive): ";
				cin >> input;
			}
			if (input == "s") {
				cout << "You went to the shop" << endl;
			}
			else if (input == "f") {
				cout << "You headed into the forest to slay some baddies" << endl;
				forest();
			}
			else if (input == "b") {
				cout << "You went deep into the dangerous cave to find a big baddie" << endl;
			}
			else if (input == "save") {
				cout << "Saved" << endl;
			}
			else if (input == "stats") {
				displayAll();
			}
			else if (input == "e") {
				cout << "Exit" << endl;
			}
		} while (input != "e" && !isWinner());
	}

	void forest() {
		char input = ' ';
		do {
			enemy.displayStats();
			hero.displayStats();
			cout << "What would you like to do: Run [leave the forest] (r), Attack (a), or Heal yourself (h)?" << endl;
			cin >> input;
			while (input != 'r' && input != 'a' && input != 'h') {
				cout << "Please enter r, a, or h (case sensitive): ";
				cin >> input;
			}
			if (input == 'r') {												//run 
				cout << "You left the forest." << endl;
			}
			else if (input == 'a') {										//attack
				enemy.setHp(enemy.getHp() - (hero.getDamage() - enemy.getArmor()));
				cout << "You attacked the baddie for " << (hero.getDamage() - enemy.getArmor()) << " damage!" << endl;
				if (enemy.getHp() <= 0) {
					cout << "You defeated the baddie!" << endl << endl;
					for (int i = 0; i < 1; i++) {							//****change 1 (i < 1) to variable that holds level up repition****
						hero.levelUp();
						cout << "You leveled up!" << endl;
					}
					resetEnemy();
				}
				else {
					hero.setHp(hero.getHp() - (enemy.getDamage() - hero.getArmor()));
					cout << "The baddie attacked you for " << (enemy.getDamage() - hero.getArmor()) << " damage!" << endl;
					if (hero.getHp() <= 0) {
						cout << "You were defeated by enemy" << endl;
						input = 'r';
					}
				}
			}
			else if (input == 'h') {										//heal
				double holdHealth;
				holdHealth = hero.getHp();
				hero.setHp(hero.getHp() + hero.getHeal());
				if (hero.getHp() > hero.getMaxHp()) {
					hero.setHp(hero.getMaxHp());
				}
				cout << "You healed yourself for " << (hero.getHp() - holdHealth) << " health points!" << endl;
				hero.setHp(hero.getHp() - (enemy.getDamage() - hero.getArmor()));
				cout << "The baddie attacked you for " << (enemy.getDamage() - hero.getArmor()) << " damage!" << endl;
				if (hero.getHp() <= 0) {
					cout << "You were defeated by enemy" << endl << endl;
					input = 'r';
				}
			}
		} while (input != 'r');

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
		for (int i = 0; i < 1; i++) {					//Add this bit later to the end of forest() but change 1 (i < 1) to variable that holds level up repition 
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