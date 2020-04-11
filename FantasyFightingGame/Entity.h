#ifndef ENTITY_H
#define ENTITY_H

//base class for enemy, boss, and hero
class Entity {
private:
	double damage, armor, hp, maxHp;
public:
	Entity() {
		damage = 0;
		armor = 0;
		hp = 0;
		maxHp = 0;
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