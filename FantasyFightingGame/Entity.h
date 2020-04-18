#ifndef ENTITY_H
#define ENTITY_H

//base class for enemy, boss, and hero
class Entity {
private:
	double damage, armor, hp, maxHp;
public:
	//setting inital values
	Entity(double d = 0, double a = 0, double health = 0, double maxHealth = 0) {
		damage = d;
		armor = a;
		hp = health;
		maxHp = maxHealth;
	}

	//setters and getters
	double getDamage() const { return damage; }
	double getArmor() const { return armor; }
	double getHp() const { return hp; }
	double getMaxHp() const { return maxHp; }
	void setDamage(double d) { damage = d; }
	void setArmor(double a) { armor = a; }
	void setHp(double health) { hp = health; }
	void setMaxHp(double maxHealth) { maxHp = maxHealth; }

	//making Entity an abstract class and setting up polymorphism
	virtual void displayStats() = 0;
};

#endif