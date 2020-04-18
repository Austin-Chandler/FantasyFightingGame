#ifndef GAMEINFO_H
#define GAMEINFO_H

//this class holds game info for saves

class GameInfo {
private:
	string heroName;
	double lvlMult, critCLvl, critMLvl, healLvl, bossLvl, heroLvl, heroGold;
public:
	//setting some inital values (should never be used, will always take input)
	GameInfo(string n = " ", double lm = 1, double ccl = 1, double cml = 1, double healLevel = 1, double bl = 1, double hl = 1, double g = 0) {
		heroName = n;
		lvlMult = lm;
		critCLvl = ccl; 
		critMLvl = cml;
		healLvl = healLevel;
		bossLvl = bl;
		heroLvl = hl;
		heroGold = g;
	}

	//getters
	string getName() { return heroName;	}
	double getLM() { return lvlMult; }
	double getCCL() { return critCLvl; }
	double getCML() { return critMLvl; }
	double getHealLevel() { return healLvl; }
	double getBL() { return bossLvl; }
	double getHL() { return heroLvl; }
	double getG() { return heroGold; }

	//setters
	void setName(string n) { heroName = n; }
	void setLM(double lm) { lvlMult = lm; }
	void setCCL(double ccl) { critCLvl = ccl; }
	void setCML(double cml) { critMLvl = cml; }
	void setHealLevel(double healLevel) { healLvl = healLevel; }
	void setBL(double bl) { bossLvl = bl; }
	void setHL(double hl) { heroLvl = hl; }
	void setG(double g) { heroGold = g; }

};

#endif