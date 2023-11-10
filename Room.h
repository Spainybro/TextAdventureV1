#pragma once
#include <iostream>
#include <string>
using namespace std;

#define DEFAULT_TITLE "NOTHING"
#define NO_EXIT -1
#define NOTHING "NOTHING"

class Room
{
private:
	int north, east, south, west;
	string description,title,inventory;

public:
	Room();

	int getNorth();
	void setNorth(int newNorth);

	int getEast();
	void setEast(int newEast);

	int getSouth();
	void setSouth(int newSouth);

	int getWest();
	void setWest(int newWest);

	string getDesc();
	void setDesc(string newDesc);

	string getTitle();
	void setTitle(string newTitle);

	string getInventory();
	void setInventory(string newInventory);
};