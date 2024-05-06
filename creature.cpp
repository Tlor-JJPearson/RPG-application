#include"creature.h"
#include"main.h"
#include"roll.h"

using namespace std;

creature::creature(std::string name) {
	this->name = name;
	Class = "unknown";
	ClassID = 0;
	ID = roll(1000000000);
	Align = false;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	STR = floor((Strength - 10) / 2);
	DEX = floor((Dexterity - 10) / 2);
	CON = floor((Constitution - 10) / 2);
	INT = floor((Intelligence - 10) / 2);
	WIS = floor((Wisdom - 10) / 2);
	CHA = floor((Charisma - 10) / 2);
	iniRoll = 0;
	attackDie = 4;
	hitDie = 8;
	level = 1;
	maxHP = level * (hitDie + CON);
	HP = maxHP;
	AC = 10 + DEX;
	saveDC = 8 + level;
	Reflex = DEX + level;
	Fortitude = CON + level;
	Will = WIS + level;
	maxSlots = 0;
	slots = maxSlots;
}
creature::creature() {
	this->name = "unknown";
	Class = "unknown";
	ClassID = 0;
	ID = roll(1000000000);
	Align = false;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	STR = floor((Strength - 10) / 2);
	DEX = floor((Dexterity - 10) / 2);
	CON = floor((Constitution - 10) / 2);
	INT = floor((Intelligence - 10) / 2);
	WIS = floor((Wisdom - 10) / 2);
	CHA = floor((Charisma - 10) / 2);
	iniRoll = 0;
	attackDie = 4;
	hitDie = 8;
	level = 1;
	maxHP = level * (hitDie + CON);
	HP = maxHP;
	AC = 10 + DEX;
	saveDC = 8 + level;
	Reflex = DEX + level;
	Fortitude = CON + level;
	Will = WIS + level;
	maxSlots = 0;
	slots = maxSlots;
}

bool creature::isDead()
{
	if (HP <= 0) { return true; }
	else { return false; }
}

void creature::updateStats() {
	if (Strength > 20) Strength = 20;
	if (Dexterity > 20) Dexterity = 20;
	if (Constitution > 20) Constitution = 20;
	if (Intelligence > 20) Intelligence = 20;
	if (Wisdom > 20) Wisdom = 20;
	if (Charisma > 20) Charisma = 20;
	STR = floor((Strength - 10) / 2);
	DEX = floor((Dexterity - 10) / 2);
	CON = floor((Constitution - 10) / 2);
	INT = floor((Intelligence - 10) / 2);
	WIS = floor((Wisdom - 10) / 2);
	CHA = floor((Charisma - 10) / 2);
	maxHP = level * (hitDie + CON);
}

void creature::display() {
	cout << name << "  " << Class << " Lv" << level << endl;
	Sleep(100);
	cout << "STR: " << Strength << " (" << STR << ")" << endl;
	Sleep(100);
	cout << "DEX: " << Dexterity << " (" << DEX << ")" << endl;
	Sleep(100);
	cout << "CON: " << Constitution << " (" << CON << ")" << endl;
	Sleep(100);
	cout << "INT: " << Intelligence << " (" << INT << ")" << endl;
	Sleep(100);
	cout << "WIS: " << Wisdom << " (" << WIS << ")" << endl;
	Sleep(100);
	cout << "CHA: " << Charisma << " (" << CHA << ")" << endl;
	Sleep(300);
	cout << "AC: " << AC << endl;
	cout << "HP: " << HP << "/" << maxHP << endl;
	cout << "Save DC: " << saveDC << endl;
	Sleep(300);
	cout << "To saves:\nReflex: " << Reflex << "\nFortitude: " << Fortitude << "\nWill: " << Will << endl;
	cout << "Available spell slots: " << maxSlots << endl;
	cout << endl;
	Sleep(200);
}
void creature::rest() {
	HP = maxHP;
	slots = maxSlots;
}
void creature::levelUp()
{
	level++;
	cout << name << " got to level " << level << "!" << endl;
	Sleep(500);
	if (ClassID == 1) {
		Strength += 2;
		Constitution++;
		updateStats();
		if (Strength >= 15) { AC = 19; }
		else if (Strength >= 13) { AC = 18; }
		else {
			if (DEX > 0) { AC = 13 + DEX; }
			else { AC = 13; }
		}
		if (STR >= DEX) { saveDC = level + STR + 8; }
		else {saveDC = level + DEX + 8;}
		Reflex = DEX + level;
		Fortitude = CON + level;
		Will = WIS;
		cout << "Strength +2 and Constitution +1!" << endl;
		if (level == 3) { cout << "Now you can attack twice!" << endl; }
	}
	else if (ClassID == 2) {
		maxSlots++;
		Intelligence += 2;
		Dexterity++;
		updateStats();
		if (Dexterity >= 10) { AC = DEX + 10; }
		else {AC = 10;}
		AC = 10 + DEX;
		saveDC = INT + level + 8;
		Reflex = DEX + level;
		Fortitude = CON;
		Will = WIS + level;
		cout << "Intelligence +2 and Constitution +1!" << endl;
	}
	else if (ClassID == 3) {
		maxSlots++;
		Wisdom += 2;
		Dexterity++;
		updateStats();
		if (Dexterity >= 10) { AC = DEX + 13; }
		else { AC = 13; }
		saveDC = WIS + level + 8;
		Reflex = DEX;
		Fortitude = CON + level;
		Will = WIS + level;
		cout << "Wisdom +2 and Dexterity +1!" << endl;
	}
	else if (ClassID == 4) {
		Dexterity += 2;
		Wisdom++;
		updateStats();
		if (Dexterity >= 10) { AC = DEX + 12; }
		else { AC = 12; }
		saveDC = INT + level + 8;
		Reflex = DEX + level;
		Fortitude = CON;
		Will = WIS + level;
		cout << "Dexterity +2 and Wisdom +1!" << endl;
	}
	Sleep(500);
	rest();
	display();
	Sleep(2000);
}

void creature::fireball(std::vector<creature> &target){
	if (slots > 0) {
		slots--;
		cout << name << " casts a Fireball spell!" << endl;
		int damage = rollMany(level, 6);
		for (int i = 0; i < target.size(); i++) { target[i].HP -= target[i].reflexSave(saveDC, damage);}
	}
}

void creature::cureWounds(std::vector<creature>& friends) {
	if (slots > 0) {
		slots--;
		cout << name << " casts a Cure Wounds spell!" << endl;
		int heal = rollMany(level, 8);
		if (WIS > 0) { heal += WIS; }
		int k = 1;
		cout << "Whom should I heal?" << endl;
		for (int i = 0; i < friends.size(); i++) { 
			cout << k << ". " << friends[i].name << " (HP: " << friends[i].HP << "/" << friends[i].maxHP << endl;
			k++;
		}
		do {
			cin >> k;
			if (k > friends.size()) { cout << "I cannot heal the air!" << endl; }
		} while (k > friends.size());
		k--;
		friends[k].HP += heal;
		cout << "You healed " << friends[k].name << " for " << heal << " hit points!" << endl;
		if (friends[k].HP > friends[k].maxHP) { friends[k].HP = friends[k].maxHP; }
	}
}
///attacker.attack(target);
void creature::attack(creature& target) {
	int j = 0;
	int dmg = 0;
	int r = roll(20);
	cout << this->name << " is attacking!" << endl;
	Sleep(500);
	switch (r) {
	case 1:
		cout << "Natural 1! Total miss on " << target.name << "!" << endl;
		Sleep(500);
		break;
	case 20:
		cout << "Natural 20! Critical hit!" << endl;
		Sleep(500);
		if (ClassID == 4) { dmg += roll(this->attackDie) + this->attackDie + rollMany(this->level, 6) + rollMany(this->level-1, 6) + this->DEX;}
		else { dmg += roll(this->attackDie) + this->STR + this->attackDie; }
		cout << target.name << " takes " << dmg << " damage!" << endl;
		break;
	default:
		if (ClassID == 4) { r = r + this->DEX + this->level; }
		else { r = r + this->STR + this->level; }
		cout << r << " to hit?" << endl;
		Sleep(500);
		if (r >= target.AC) {
			cout << "That hits!" << endl;
			Sleep(500);
			if (ClassID == 4) { dmg += roll(this->attackDie) + rollMany(this->level, 6) + this->DEX;}
			else { dmg += roll(this->attackDie) + this->STR; }
			cout << target.name << " takes " << dmg << " damage!" << endl;
		}
		else { cout << "Thats a miss on " << target.name << "!" << endl; }
	}
	Sleep(750);
	if (dmg < 0) { dmg = 0; }
	target.HP -= dmg;
}

int creature::reflexSave(int save, int damage) {
	int r = roll(20) + this->Reflex;
	if (this->HP > 0) {
		if (r >= save) {
			damage = damage / 2;
			cout << this->name << " has passed the save and takes " << damage << " damage." << endl;
		}
		else { cout << this->name << " has failed the save and takes " << damage << " damage." << endl; }
		Sleep(750);
	}
	return damage;
}

void creature::doTurn(std::vector<creature>& target, std::vector<creature>& friends) {
	int c = 0;
	int d = 0;
	if (HP > 0) {
		if (ClassID == 2) {//if Mage
			while (true) {
				cout << "What should " << name << " (HP: " << HP << "/" << maxHP << ") do?\n1. Attack\n2. Fireball (Slots: " << slots << ")" << endl;
				while (true) {
					cin >> c;
					if (c < 0 || c > 2) { cout << "Illogical answer!" << endl; }
					else { break; }
				}
				if (c == 1) {
					cout << "Which enemy do you want to attack? " << endl;
					for (size_t i = 0; i < target.size(); i++) {
						if (target[i].HP > 0) { cout << i + 1 << ". " << target[i].name << " (Initiative: " << target[i].iniRoll << "  HP: " << target[i].HP << "/" << target[i].maxHP << ")" << endl; }
					}
					while (true) {
						cin >> d;
						if (d<1 || d>target.size()) { cout << "Please, this is a serious debate! " << endl; }
						else { break; }
					}
					d--;
					attack(target[d]);
					break;
				}
				if (c == 2) {
					if (slots <= 0) { cout << "I cannot cast more spells!" << endl; }
					else {
						fireball(target);
						break;
					}
				}
			}
		}
		if (this->ClassID == 3) {//if Cleric
			while (true) {
				cout << "What should " << this->name << " (HP: " << this->HP << "/" << this->maxHP << ") do?\n1. Attack\n2. Cure Wounds (Slots: " << this->slots << ")" << endl;
				while (true) {
					cin >> c;
					if (c < 0 || c > 2) { cout << "What blasphemy is this?" << endl; }
					else { break; }
				}
				if (c == 1) {
					cout << "Which enemy do you want to attack? " << endl;
					for (size_t i = 0; i < target.size(); i++) {
						if (target[i].HP > 0) { cout << i + 1 << ". " << target[i].name << " (Initiative: " << target[i].iniRoll << "  HP: " << target[i].HP << "/" << target[i].maxHP << ")" << endl; }
					}
					while (true) {
						cin >> d;
						if (d<1 || d>target.size()) { cout << " Gods see no such way! " << endl; }
						else { break; }
					}
					d--;
					attack(target[d]);
					break;
				}
				if (c == 2) {
					if (slots <= 0) { cout << "I cannot cast more spells!" << endl; }
					else {
						cureWounds(friends);
						break;
					}
				}
			}
		}
		if (this->ClassID == 1) {//if Fighter
			cout << "Which enemy should " << this->name << " (HP: " << this->HP << "/" << this->maxHP << ") want to attack? " << endl;
			for (size_t i = 0; i < target.size(); i++) {
				if (target[i].HP > 0) { cout << i + 1 << ". " << target[i].name << " (Initiative: " << target[i].iniRoll << "  HP: " << target[i].HP << "/" << target[i].maxHP << ")" << endl; }
			}
			while (true) {
				cin >> d;
				if (d<1 || d>target.size()) { cout << " This is impossible to do! " << endl; }
				else { d--; break; }
			}
			attack(target[d]);
			if (this->level == 3) {
				cout << "Extra attack!" << endl;
				attack(target[d]);
			}
		}
		if (this->ClassID == 0) { //if just a monster
			do { d = roll(target.size()) - 1; } while (target[d].HP <= 0);
			attack(target[d]);
		}
		if (this->ClassID == 4) { //if Rogue
			cout << "Which enemy should " << this->name << " (HP: " << this->HP << "/" << this->maxHP << ") stab? " << endl;
			for (size_t i = 0; i < target.size(); i++) {
				if (target[i].HP > 0) { cout << i + 1 << ". " << target[i].name << " (Initiative: " << target[i].iniRoll << "  HP: " << target[i].HP << "/" << target[i].maxHP << ")" << endl; }
			}
			while (true) {
				cin >> d;
				if (d<1 || d>target.size()) { cout << " Heh. Not a chance! " << endl; }
				else { d--; break; }
			}
			attack(target[d]);
		}
		if (target[d].HP <= 0) { cout << target[d].name << " is dead!" << endl; }
	}
	else { cout << this->name << " is still down!" << endl; }
	Sleep(750);
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

fighter::fighter(std::string name) {
	Class = "Fighter";
	ClassID = 1;
	ID = roll(1000000000);
	Align = true;
	this->name = name;
	level = 1;
	hitDie = 10;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	updateStats();
	attackDie = 8;
	HP = maxHP;
	if (Strength >= 15) { AC = 19; }
	else if (Strength >= 13) { AC = 18; }
	else {
		if (DEX > 0) { AC = 13 + DEX; }
		else { AC = 13; }
	}
	if (STR >= DEX) saveDC = level + STR + 8;
	else saveDC = level + DEX + 8;
	Reflex = DEX + level;
	Fortitude = CON + level;
	Will = WIS;
	maxSlots = 0;
	slots = maxSlots;
}
///////////////////////////////////////////////////////////////////
mage::mage(std::string name) {
	Class = "Mage";
	ClassID = 2;
	ID = roll(1000000000);
	Align = true;
	this->name = name;
	level = 1;
	hitDie = 6;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	updateStats();
	attackDie = 4;
	HP = maxHP;
	if (Dexterity >= 10) AC = DEX + 10;
	else AC = 10;
	saveDC = INT + level + 8;
	slots = 2;
	Reflex = DEX + level;
	Fortitude = CON;
	Will = WIS + level;
	maxSlots = level;
	slots = maxSlots;
}
///////////////////////////////////////////////////////////////////
cleric::cleric(std::string name) {
	Class = "Cleric";
	ClassID = 3;
	ID = roll(1000000000);
	Align = true;
	this->name = name;
	level = 1;
	hitDie = 8;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	updateStats();
	attackDie = 6;
	HP = maxHP;
	if (DEX >= 10) AC = DEX + 13;
	else AC = 13;
	saveDC = WIS + level + 8;
	Reflex = DEX;
	Fortitude = CON + level;
	Will = WIS + level;
	maxSlots = level;
	slots = maxSlots;
}
rogue::rogue(std::string name) {
	Class = "Rogue";
	ClassID = 4;
	ID = roll(1000000000);
	Align = true;
	this->name = name;
	level = 1;
	hitDie = 7;
	Strength = statRoll();
	Dexterity = statRoll();
	Constitution = statRoll();
	Intelligence = statRoll();
	Wisdom = statRoll();
	Charisma = statRoll();
	updateStats();
	attackDie = 6;
	HP = maxHP;
	if (Dexterity >= 10) AC = DEX + 12;
	else AC = 12;
	saveDC = INT + level + 8;
	Reflex = DEX + level;
	Fortitude = CON;
	Will = WIS + level;
	maxSlots = 0;
	slots = maxSlots;
}
/////////////////////////////////////////////
/////////////////////////////////////////////
goblin::goblin() {
	Class = "Goblin";
	name = "Goblin";
	ID = roll(1000000000);
	hitDie = 6;
	Align = false;
	Strength = 8;
	Dexterity = 14;
	Constitution = 10;
	Intelligence = 10;
	Wisdom = 8;
	Charisma = 8;
	updateStats();
	attackDie = 6;
	level = 1;
	HP = maxHP;
	AC = DEX + 12;
	saveDC = level + 8;
	Reflex = DEX;
	Fortitude = CON;
	Will = WIS;
	iniRoll = 0;
}
ogre::ogre() {
	Class = "Ogre";
	name = "Ogre";
	ID = roll(1000000000);
	level = 2;
	Align = false;
	hitDie = 10;
	Strength = 19;
	Dexterity = 8;
	Constitution = 16;
	Intelligence = 5;
	Wisdom = 7;
	Charisma = 7;
	updateStats();
	attackDie = 8;
	HP = maxHP;
	AC = DEX + 11;
	saveDC = level + 8;
	Reflex = DEX;
	Fortitude = CON;
	Will = WIS;
}
boss::boss() {
	Class = "Boss";
	name = "Boss";
	level = 3;
	ID = roll(1000000000);
	Align = false;
	hitDie = 10;
	Strength = 20;
	Dexterity = 20;
	Constitution = 20;
	Intelligence = 20;
	Wisdom = 20;
	Charisma = 20;
	updateStats();
	attackDie = 10;
	level = 3;
	HP = maxHP;
	AC = DEX + 13;
	saveDC = level + INT + 8;
	Reflex = DEX;
	Fortitude = level + CON;
	Will = level + WIS;
}
bandit::bandit() {
	Class = "Bandit";
	name = "Bandit";
	level = 2;
	ID = roll(1000000000);
	Align = false;
	hitDie = 6;
	Strength = 16;
	Dexterity = 12;
	Constitution = 12;
	Intelligence = 10;
	Wisdom = 10;
	Charisma = 10;
	updateStats();
	attackDie = 12;
	HP = maxHP;
	AC = DEX + 11;
	saveDC = level + DEX + 8;
	Reflex = DEX + 20;
	Fortitude = CON;
	Will = WIS;
}