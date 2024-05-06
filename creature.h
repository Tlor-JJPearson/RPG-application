#pragma once
#include "main.h"
#include<string>
#include<vector>


class creature {
public:
	int maxHP;
	int level;

	std::string Class;
	std::string name;
	int ClassID;
	int ID;
	bool Align; //false = enemy (evil), true = friend (good)

	int Strength;
	int Dexterity;
	int Constitution;
	int Intelligence;
	int Wisdom;
	int Charisma;

	int STR;
	int DEX;
	int CON;
	int INT;
	int WIS;
	int CHA;

	int Reflex;
	int Fortitude;
	int Will;

	int attackDie;
	int hitDie;
	int HP;
	int AC;
	int saveDC;
	int maxSlots;
	int slots;

	int iniRoll;

	creature(std::string name);
	creature();

	bool isDead();

	void attack(creature& target); /// attacker.attack(target); 
	int reflexSave(int save, int damage); /// targeted.HP -= targeted.reflexSave(attacker, damage);

	void fireball(std::vector<creature>& target);
	void cureWounds(std::vector<creature>& friends);
	void doTurn(std::vector<creature>& target, std::vector<creature>& friends);

	void updateStats();
	void display();
	void rest();

	void levelUp();
	friend int roll(int die);
	friend int statRoll();
	friend int rollMany(int num, int die);

};



class fighter : public creature {
public:
	fighter(std::string name);
};

class mage : public creature {
public:
	mage(std::string name);
};

class cleric : public creature {
public:
	cleric(std::string name);
};
class rogue : public creature {
public:
	rogue(std::string name);
};

class goblin : public creature {
public:
	goblin();
};

class ogre : public creature {
public:
	ogre();
};

class boss : public creature {
public:
	boss();
};
class bandit : public creature {
public:
	bandit();
};