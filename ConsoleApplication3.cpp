// ConsoleApplication3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "main.h"

using namespace std;

void rollInitiative(vector<creature>& players, vector<creature>& enemies, vector<creature>& initiative) {
	for (size_t i = 0; i < players.size(); i++) { 
		players[i].iniRoll = roll(20) + players[i].DEX;
		initiative.push_back(players[i]); 
	}
	for (size_t i = 0; i < enemies.size(); i++) { 
		enemies[i].iniRoll = roll(20) + enemies[i].DEX;
		initiative.push_back(enemies[i]); 
	}
	for (int j = 0; j < 10; j++) {
		creature temp;
		for (size_t i = 0; i < initiative.size() - 1; i++) {
			if (initiative[i].iniRoll < initiative[i + 1].iniRoll) {
				temp = initiative[i + 1];
				initiative[i + 1] = initiative[i];
				initiative[i] = temp;
			}
		}
	}
	cout << "\n___________INITIATIVE ORDER___________\n" << endl;
	Sleep(1000);
	for (size_t i = 0; i < initiative.size(); i++) {
		cout << i + 1 << ". " << initiative[i].name << ": " << initiative[i].iniRoll << endl;
		Sleep(500);
	}
}

bool battle(vector<creature>& players, vector<creature>& enemies, vector<creature>& initiative) {
	rollInitiative(players, enemies, initiative);
	int playerDeaths = 0;
	int enemyDeaths = 0;
	bool flag;
	while ((enemyDeaths < enemies.size()) && (playerDeaths < players.size())) {
		playerDeaths = 0;
		enemyDeaths = 0;
		for (int j = 0; j < initiative.size(); j++) { //next people in initiative
			flag = false;
			playerDeaths = 0;
			enemyDeaths = 0;
			if (initiative[j].Align == true) { 
				for (int i = 0;i<players.size();i++){//if player
					if (players[i].HP > players[i].maxHP) { players[i].HP = players[i].maxHP; }
					if (initiative[j].ID == players[i].ID) { 
						players[i].doTurn(enemies, players); 
						flag = true;
						break;
					}
				}
				if (flag == false) { 
					cout << "ID not found. Initiative attacks." << endl;
					initiative[j].doTurn(enemies, players);
				}
			}
			else {// if enemy
				for (int i = 0; i < enemies.size(); i++) {
					if (enemies[i].HP > enemies[i].maxHP) { enemies[i].HP = enemies[i].maxHP; }
					if (initiative[j].ID == enemies[i].ID) {
						enemies[i].doTurn(players, enemies);
						flag = true;
						break;
					}
				}
				if (flag == false) {
					cout << "ID not found. Initiative attacks." << endl;
					initiative[j].doTurn(players, enemies);
				}
			}
			for (int k = 0; k < players.size(); k++) { playerDeaths += players[k].isDead(); }
			for (int k = 0; k < enemies.size(); k++) { enemyDeaths += enemies[k].isDead(); }
			if ((playerDeaths == players.size()) || (enemyDeaths == enemies.size())) { break; }

			for (int j = 0; j < enemies.size(); j++) { if (enemies[j].HP < 0) { enemies[j].HP = 0; } }
			for (int k = 0; k < players.size(); k++) { if (players[k].HP < 0) { players[k].HP = 0; } }
		}
	}
	if (playerDeaths == players.size()) { 
		cout << "You lose! GAME OVER." << endl;
		return false;
	}
	else { cout << "YOU ARE A WINNER!" << endl;
		enemies.clear();
		initiative.clear();
		return true;
	}
}
void wait() {
	std::string input;
	Sleep(1500);
	cout << "Give any input to continue:" << endl;
	cin >> input;
}
void allRest(vector<creature> &players) {
	for (int i = 0; i < players.size(); i++) { players[i].rest(); }
	cout << "You feel rested!" << endl;
	wait();
}
void allLevelUp(vector<creature>& players) {
	for (int i = 0; i < players.size(); i++) { players[i].levelUp(); }
	wait();
}
int main(){
	srand(time(0));
	int n;
	cout << "====================================" << '\n' << "         CHARACTER CREATOR          " << '\n' << "====================================" << endl;
	cout << "How many characters (1-5)?";
	cin >> n;
	if (n < 1 || n>5) cout << "You must be joking!" << endl;
	else {
		vector<creature> initiative;
		vector<creature> players;
		vector<creature> enemies;
		std::string NAME;
		int c;
		for (int i = 0; i < n; i++) {
			do {
				cout << "Name your character: " << endl;
				cin >> NAME;
				cout << "Pick class:\n1. Fighter\n2. Mage\n3. Cleric\n4. Rogue\n5. Randomize" << endl;
				cin >> c;
				if (c == 5) c = roll(4);
				switch (c) {
				case 1: {
					fighter f1(NAME);
					players.push_back(f1);
				}
					  break;
				case 2: {
					mage m1(NAME);
					players.push_back(m1);
				}
					  break;
				case 3: {
					cleric c1(NAME);
					players.push_back(c1);
				}
					  break;
				case 4: {
					rogue r1(NAME);
					players.push_back(r1);
				}
					  break;
				default:
					cout << "Incorrect number." << endl;
					break;
				}
			} while (c < 1 || c>4);
			players[i].display();
		}
		int choice;
		cout << "====================================" << '\n' << "         ENTER THE DUNGEON          " << '\n' << "====================================" << endl;

		cout << "FLOOR 1: Goblins' den." << endl;
		goblin gob[10];
		for (int i = 0; i < n; i++) { enemies.push_back(gob[i]); }
		bool result = battle(players, enemies, initiative);
		if (result == false) { return 0; }
		allLevelUp(players);

		cout << "FLOOR 2: Ogres' cavern." << endl;
		ogre ogr[5];
		n = (n / 2);
		for (int i = 0; i < n; i++) { enemies.push_back(ogr[i]); }
		enemies.push_back(gob[4]);
		result = battle(players, enemies, initiative);
		if (result == false) { return 0; }
		allRest(players);
		
		n = players.size() * 2;
		cout << "Choose your path : \n1.Goblin party.\n2.Ogres' brood." << endl;
		do {
			 cin >> choice;
			 if ((choice != 1) && (choice != 2)) { cout << "Choose a proper way!" << endl; }
		} while ((choice!=1) && (choice != 2));
		if (choice == 1) {
			cout << "FlOOR 3A: Goblin party" << endl;
			for (int i = 0; i < n; i++) { enemies.push_back(gob[i]); }
		}
		if (choice == 2) {
			n = n / 2;
			cout << "FLOOR 3B: Ogres' brood" << endl;
			for (int i = 0; i < n ; i++) { enemies.push_back(ogr[i]); }
		}
		result = battle(players, enemies, initiative);
		if (result == false) { return 0; }
		allLevelUp(players);
		
		if (players.size() > 1) {
			cout << "FLOOR 4: The Boss's Mafia." << endl;
			Sleep(2000);
			cout << "\nBOSS: What? You are already here!? Stop them, boys!\nWhoever kills one of them gets a lifetime of toilet paper!" << endl;
			bandit banda[10];
			n = players.size() * 2;
			for (int i = 0; i < n; i++) { enemies.push_back(banda[i]); }
				result = result = battle(players, enemies, initiative);
				if (result == false) { return 0; }
			
		}
		n = players.size();
		if (players.size() == 1) {cout << "BOSS: 'Hahaha! Fool! You think you can take me down alone!?\n Go back where you came from and get some friends for a change!'\n" << endl;}
		else { cout << "BOSS: 'What? Several people at my lair? I will not let you disturb my organization!'\n" << endl; }
		Sleep(2000);
		cout << "FINAL FLOOR: The lair of Boss" << endl;
		boss bos;
		enemies.push_back(bos);
		if (n > 2) { for (int i = 0; i < n - 2; i++) { enemies.push_back(ogr[i]); } }
		result = battle(players, enemies, initiative);
		if (result == false) { 
			if (players.size() == 1) { cout << "BAD ENDING: You cannot beat the boss alone you lonely edgelord!" << endl;}
			Sleep(2000);
			return 0; 
		}
		cout << "BOSS: 'No!!!! How could this happen!?" << endl;
		Sleep(1000);
		if (players.size() == 1) { 
			cout << "BOSS: Haha! Just kidding! You've actually fallen to my trap!\n Boys! Seize the intruder! Time to interrogate the bait!";
			Sleep(3500);
			cout << "BAD ENDING: You cannot beat the boss alone, even if you actually win, you edgy loner from the shadows!";
			Sleep(2000);
			return 0;
		}
		cout <<"CONGRATULATIONS! YOU BEAT THE DUNGEON!" << endl;
	}
	Sleep(2000);
	return 0;
}
