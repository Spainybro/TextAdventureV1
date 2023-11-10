#pragma once
#include <string>
#include <iostream>

#define NOTHING "NOTHING"

using namespace std;

class Player
{
public:
	Player();
	Player(int  NewPos , string newInventory);


	int getPlayerPos();
	void setPlayerPos(int newPos);

	string getInventory(int inventoryPos);
	void setInventory(string newInventory,int inventoryPos);
	
	
private:
	
	int playerPos;
	string inventory[3];

};