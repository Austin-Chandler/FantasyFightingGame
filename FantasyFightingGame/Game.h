#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Boss.h"
#include "Hero.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

/*
Things Done:
	Welcome
	Storyline 
	Main loop input (action selector) 
	Forest
	Boss
	Stats
	isWinner()
	Gold functionality
	Level functionality
Things left to do:
	Neccesary ASAP:
		Shop
		Save
		Load player
		Victory message when 10 bosses beaten
		Create New Character 
	Neccesary When all else is done:
		Squash bugs
		Patch it all together to make a cohesive game :)
	Non-neccisities:
		Help (if time)
		Map
		Extra story with some bosses
*/

class Game {
private:
	//composing game of an enemy, a boss, and a hero
	Enemy enemy;
	Boss boss;
	Hero hero;

	//other vars
	double lvlMult = 1;
public:
	Game() {
		srand(time(NULL));
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
			system("color 80"); //black on grey text (80)
			cout << endl << "What would you like to do: go to shop (s), go to forest (f), fight a boss (b), save (save), check stats (stats), or end (e)?" << endl;
			hero.setHp(hero.getMaxHp());
			boss.setHp(boss.getMaxHp());
			cin >> input;

			//wrong input
			while (input != "s" && input != "f" && input != "b" && input != "save" && input != "stats" && input != "e") {
				cout << "Please enter s, f, b, save, stats, or e (case sensitive): ";
				cin >> input;
			}

			//shop
			if (input == "s") {
				cout << "You went to the shop" << endl; //set color here to 8E (light yellow on grey)
			}

			//forest
			else if (input == "f") {
				cout << "You headed into the forest to slay some baddies" << endl;
				forest();
			}

			//boss
			else if (input == "b") {
				cout << "Once you begin this battle you will not be able to run away until there is a victor. Are you sure you want to continue? (Y/N)" << endl;
				cin >> input;
				while (input != "Y" && input != "y" && input != "N" && input != "n") {
					cout << "Please enter Y or N: ";
					cin >> input;
				}
				if (input == "Y" || input == "y") {
					cout << "You went deep into the dangerous cave to find a big baddie" << endl;
					bossFight();
				}
				else if (input == "N" || input == "n") {
					cout << "You did not enter the cave" << endl;
				}
			}

			//save
			else if (input == "save") {
				cout << "Saved" << endl;
			}

			//stats
			else if (input == "stats") {
				displayAll();
			}

			//exit
			else if (input == "e") {
				cout << "Exit" << endl;
			}
		} while (input != "e" && !isWinner());
	}



	void forest() {
		char input = ' ';
		do {
			system("color 02"); //green on black text (02)
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
				if ((rand() % 100) <= (hero.getCritChance() * 100)) {													//to find crit chance get a random number 0 - 99 if it is less than cc * 100 its a crit hit. 
					enemy.setHp(enemy.getHp() - ((hero.getDamage() * hero.getCritMult()) - enemy.getArmor()));			//(8 <= 10) 8 is from rand()%100 10 is an example .1 crit chance * 100
					cout << "You attacked the baddie for a critical " << ((hero.getDamage() * hero.getCritMult()) - enemy.getArmor()) << " damage!" << endl;
				}
				else {
					enemy.setHp(enemy.getHp() - (hero.getDamage() - enemy.getArmor()));
					cout << "You attacked the baddie for " << (hero.getDamage() - enemy.getArmor()) << " damage!" << endl;
				}
				if (enemy.getHp() <= 0) {
					cout << "You defeated the baddie!" << endl << endl;
					hero.setLevel(hero.getLevel() + lvlMult);
					hero.refresh();
					cout << "You leveled up! You are now level " << hero.getLevel() << "!" << endl;
					hero.setGold(hero.getGold() + enemy.goldDropped());
					resetEnemy();
				}
				else {
					hero.setHp(hero.getHp() - (enemy.getDamage() - hero.getArmor()));
					cout << "The baddie attacked you for " << (enemy.getDamage() - hero.getArmor()) << " damage!" << endl;
					if (hero.getHp() <= 0) {
						double holdGold = hero.getGold();
						hero.setGold(hero.getGold() - enemy.getMaxGoldDrop());
						if (hero.getGold() < 0) {
							hero.setGold(0);
						}
						cout << "You were defeated by enemy" << endl << "You dropped " << (holdGold - hero.getGold()) << " gold..." << endl;
						input = 'r';
					}
				}
			}
			else if (input == 'h') {										//heal
				double holdHealth;//This is used to display how many health points were healed
				holdHealth = hero.getHp();
				hero.setHp(hero.getHp() + hero.getHeal());
				if (hero.getHp() > hero.getMaxHp()) {
					hero.setHp(hero.getMaxHp());
				}
				cout << "You healed yourself for " << (hero.getHp() - holdHealth) << " health points!" << endl;
				hero.setHp(hero.getHp() - (enemy.getDamage() - hero.getArmor()));
				cout << "The baddie attacked you for " << (enemy.getDamage() - hero.getArmor()) << " damage!" << endl;
				if (hero.getHp() <= 0) {
					double holdGold = hero.getGold();
					hero.setGold(hero.getGold() - enemy.getMaxGoldDrop());
					if (hero.getGold() < 0) {
						hero.setGold(0);
					}
					cout << "You were defeated by enemy" << endl << "You dropped " << (holdGold - hero.getGold()) << " gold..." << endl;
					input = 'r';
				}
			}
		} while (input != 'r');
	}



	void bossFight() {
		char input = ' ';
		do {
			system("color 04"); //Red on black text (04)
			boss.displayStats();
			hero.displayStats();
			cout << "What would you like to do: Attack (a) or Heal yourself (h)?" << endl;
			cin >> input;
			while (input != 'a' && input != 'h') {
				cout << "Please enter a, or h (case sensitive): ";
				cin >> input;
			}
			if (input == 'a') {										//attack
				if ((rand() % 100) <= (hero.getCritChance() * 100)) {													//to find crit chance get a random number 0 - 99 if it is less than cc * 100 its a crit hit. 
					boss.setHp(boss.getHp() - ((hero.getDamage() * hero.getCritMult()) - boss.getArmor()));			//(8 <= 10) 8 is from rand()%100 10 is an example .1 crit chance * 100
					cout << "You attacked the boss for a critical " << ((hero.getDamage() * hero.getCritMult()) - boss.getArmor()) << " damage!" << endl;
				}
				else {
					boss.setHp(boss.getHp() - (hero.getDamage() - boss.getArmor()) + boss.getHpRegen());
					cout << "You attacked the boss for " << (hero.getDamage() - boss.getArmor()) << " damage!" << endl;
					cout << "The boss healed himself for " << boss.getHpRegen() << " hp!" << endl;
				}
				if (boss.getHp() <= 0) {
					cout << "You defeated the boss!" << endl;
					cout << "The boss leveled up! He is now level " << (boss.getLevel() + 1) << "!" << endl << endl;
					hero.setLevel(hero.getLevel() + lvlMult);
					hero.refresh();
					cout << "You leveled up! You are now level " << hero.getLevel() << "!" << endl;
					hero.setGold(hero.getGold() + boss.getGold());
					boss.setLevel(boss.getLevel() + 1);
					boss.refresh();
				}
				else {
					boss.setHp(boss.getHp() + boss.getHpRegen());
					cout << "The boss healed himself for " << boss.getHpRegen() << " hp!" << endl;
					hero.setHp(hero.getHp() - (boss.getDamage() - hero.getArmor()));
					cout << "The boss attacked you for " << (boss.getDamage() - hero.getArmor()) << " damage!" << endl;
					if (hero.getHp() <= 0) {
						double holdGold = hero.getGold();
						hero.setGold(hero.getGold() - floor(boss.getGold() / 2));
						if (hero.getGold() < 0) {
							hero.setGold(0);
						}
						cout << "You were defeated by the boss" << endl << "You dropped " << (holdGold - hero.getGold()) << " gold..." << endl;
					}
				}
			}
			else if (input == 'h') {										//heal
				double holdHealth;//This is used to display how many health points were healed
				holdHealth = hero.getHp();
				hero.setHp(hero.getHp() + hero.getHeal());
				if (hero.getHp() > hero.getMaxHp()) {
					hero.setHp(hero.getMaxHp());
				}
				cout << "You healed yourself for " << (hero.getHp() - holdHealth) << " health points!" << endl;
				hero.setHp(hero.getHp() - (boss.getDamage() - hero.getArmor()));
				cout << "The boss attacked you for " << (boss.getDamage() - hero.getArmor()) << " damage!" << endl;
				if (hero.getHp() <= 0) {
					double holdGold = hero.getGold();
					hero.setGold(hero.getGold() - floor(boss.getGold() / 2));
					if (hero.getGold() < 0) {
						hero.setGold(0);
					}
					cout << "You were defeated by the boss" << endl << "You dropped " << (holdGold - hero.getGold()) << " gold..." << endl;
				}
			}
		} while (hero.getHp() > 0 && boss.getHp() > 0);
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



	void displayAll() {
		enemy.displayStats();
		boss.displayStats();
		hero.displayStats();
	}
};
#endif