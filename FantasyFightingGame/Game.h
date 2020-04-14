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
	Shop
	Create new character
	Victory message when 10 bosses beaten
Things left to do:
	Neccesary ASAP:
		Save
		Load player
	Neccesary when all else is done:
		Squash bugs
		Patch it all together to make a cohesive game :)
	Non-neccisities (to add if I have time and desire):
		Help menu
		Map
		Extra story with some bosses
		Show how much more gold need to buy shop item
		Make healing actualy useful
*/

class Game {
private:
	//composing game of an enemy, a boss, and a hero
	Enemy enemy;
	Boss boss;
	Hero hero;

	//other vars (for shop)
	double lvlMult, critCLvl, critMLvl, healLvl;
public:
	Game() {
		lvlMult = critCLvl = critMLvl = healLvl = 1;
		srand(time(NULL));
	}



	void playGame() {
		if (welcomeScreen()) {
			//load player
			refreshAll();
		}
		else {
			string n;
			cout << "Please enter a name for your player: ";
			cin >> n;
			hero.setName(n);
			storyline();
		}
		main();
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
			return true;
		}
		else if (input == 'N' || input == 'n') {
			return false;
		}
	}



	void storyline() {
		cout << "A long time ago there was a great chief named Sannhet. He ruled all the land, as far as the eye could see." << endl;
		cout << "However, unbeknownst to him, a challenger was waiting to overthrow him. His name was Bedrageri. Bedrageri" << endl;
		cout << "spread countless apocryphal about Sannhet deceiving his subjects. People began to doubt Sannhet's integrity " << endl;
		cout << "and therefore his power to protect them. Bedrageri promised truthfulness and security if people would join " << endl;
		cout << "him and depose Sannhet. Many believed him and joined his cause. Several months later Bedrageri and all his " << endl;
		cout << "followers surprise attacked Sannhet and he was quickly overwhelmed. Many centuries have passed now and Bedrageri " << endl;
		cout << "still rules with very few remaining loyal to Sannhet. It is your job young " << hero.getName() << " to train and defeat Bedrageri once and for all." << endl << endl;
		cout << "You must begin at once..." << endl;
	}



	bool isWinner() {
		if (boss.getLevel() == 11) {
			cout << "Congradualtions! You have defeated Bedrageri and restored the world to its former prowess!" << endl;
			//save in here before the game closes to allow for people to keep playing later if they desire
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
				cout << "You went to the shop" << endl;
				shop();
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
				cout << "Would you like to save? (Y/N)" << endl;
				cin >> input;
				while (input != "Y" && input != "y" && input != "N" && input != "n") {
					cout << "Please enter Y or N: ";
					cin >> input;
				}
				if (input == "Y" || input == "y") {
					cout << "You saved the game" << endl;
					//save here
					input = "e";
				}
				else if (input == "N" || input == "n") {
					cout << "You did not save the game" << endl;
					input = "e";
				}
			}
		} while (input != "e" && !isWinner());
	}



	void shop() {
		system("color 8E"); //light yellow on grey text (8E)
		cout << "Welcome to ye ol' butikken! Have a look at ma wares and let me know if ya wanta buy anything." << endl;
		char input = ' ';
		do {
			displayShopItems();
			cin >> input;
			while (input != '1' && input != '2' && input != '3' && input != '4' && input != 'L') {
				cout << "Please enter 1, 2, 3, 4, or L (case sensitive): ";
				cin >> input;
			}
			if (input == '1') {
				if (hero.getGold() >= (lvlMult * 150)) {
					cout << "Here ya go! Thanks for your purchase!" << endl << endl;
					hero.setGold(hero.getGold() - (lvlMult * 150));
					lvlMult++;
				}
				else {
					cout << "I gotta make a living here! Come back when you have to cover this" << endl << endl;
				}
			}
			else if (input == '2') {
				if (hero.getGold() >= (critCLvl * 30)) {
					if (critCLvl == 10) { //This stops crit chance at 50% 
						cout << "Sorry! I'm all out!" << endl << endl;
					}
					else {
						cout << "Here ya go! Thanks for your purchase!" << endl << endl;
						hero.setGold(hero.getGold() - (critCLvl * 30));
						critCLvl++;
						hero.setCritChance(0.05 * (critCLvl - 1));
					}
				}
				else {
					cout << "I gotta make a living here! Come back when you have to cover this" << endl << endl;
				}
			}
			else if (input == '3') {
				if (hero.getGold() >= (critMLvl * 25)) {
					cout << "Here ya go! Thanks for your purchase!" << endl << endl;
					hero.setGold(hero.getGold() - (critMLvl * 25));
					critMLvl++;
					hero.setCritMult((.3 * (critCLvl - 1)) + 2);
				}
				else {
					cout << "I gotta make a living here! Come back when you have to cover this" << endl << endl;
				}
			}
			else if (input == '4') {
				if (hero.getGold() >= (healLvl * 35)) {
					cout << "Here ya go! Thanks for your purchase!" << endl << endl;
					hero.setGold(hero.getGold() - (healLvl * 35));
					healLvl++;
					hero.setHeal((5 * (healLvl - 1)) + 5);
				}
				else {
					cout << "I gotta make a living here! Come back when you have to cover this" << endl << endl;
				}
			}
			else if (input == 'L') {
				cout << "Come back soon!" << endl << endl;
			}
		} while (input != 'L');
	}



	void displayShopItems() {
		cout << "1. This here will make you level up an extra level every time you would normally level up. (level " << lvlMult << ", total levels each level up: " << lvlMult << ") Cost: " << (lvlMult * 150) << endl; //****Add cost in here somehow****
		cout << "2. Now that there is a fancy one. It increases your critical chance by 5% (level " << critCLvl << ", cc = " << (hero.getCritChance() * 100) << "%) Cost: " << (critCLvl * 30) << endl;
		cout << "3. That is also very useful. It increases your critical multiplier by .3 (level " << critMLvl << ", cm = " << hero.getCritMult() << ") Cost: " << (critMLvl * 25) << endl;
		cout << "4. I thought you'd like that. It boosts your healing by 5. (level " << healLvl << ", healing = " << hero.getHeal() << ") Cost: " << (healLvl * 35) << endl;
		cout << "So, You've seen what I got. What do ya wanta buy? (You currently have " << hero.getGold() << " gold) (1, 2, 3, 4, or L (leave shop)): ";
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
				}
				if (boss.getHp() <= 0) {
					cout << "You defeated the boss!" << endl;
					cout << "The boss leveled up! He is now level " << (boss.getLevel() + 1) << "!" << endl << endl;
					hero.setGold(hero.getGold() + boss.getGold());
					boss.setLevel(boss.getLevel() + 1);
					boss.refresh();
				}
				else {
					double holdBossHealth;
					holdBossHealth = boss.getHp();
					boss.setHp(boss.getHp() + boss.getHpRegen());
					if (boss.getHp() > boss.getMaxHp()) {
						boss.setHp(boss.getMaxHp());
					}
					cout << "The boss healed himself for " << (boss.getHp() - holdBossHealth) << " hp!" << endl;
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

				double holdBossHealth;
				holdBossHealth = boss.getHp();
				boss.setHp(boss.getHp() + boss.getHpRegen());
				if (boss.getHp() > boss.getMaxHp()) {
					boss.setHp(boss.getMaxHp());
				}
				cout << "The boss healed himself for " << (boss.getHp() - holdBossHealth) << " hp!" << endl;
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



	//refresh all the stats (to be used after file input to simplify setting)
	void refreshAll(string n = "Phil", double lm = 1, double ccl = 1, double cml = 1, double healLevel = 1, double bl = 1, double hl = 1) {
		hero.setName(n);
		hero.setLevel(hl);
		hero.refresh();

		boss.setLevel(bl);
		boss.refresh();

		lvlMult = lm;
		critCLvl = ccl;
		critCLvl = cml;
		healLvl = healLevel;
		hero.setCritChance(0.05 * (critCLvl - 1));
		hero.setCritMult((.3 * (critCLvl - 1)) + 2);
		hero.setHeal((5 * (healLvl - 1)) + 5);
	}



	void displayAll() {
		enemy.displayStats();
		boss.displayStats();
		hero.displayStats();
	}
};
#endif