#include "Room.h"

Room::Room()
{
	north = NO_EXIT;
	east = NO_EXIT;
	south = NO_EXIT;
	west = NO_EXIT;

	description = DEFAULT_TITLE;
	title = DEFAULT_TITLE;
	inventory = NOTHING;


}

int Room::getNorth()
{
	return north;
}

void Room::setNorth(int newNorth)
{
	north = newNorth;
}

int Room::getEast()
{
	return east;
}

void Room::setEast(int newEast)
{
	east = newEast;
}

int Room::getSouth()
{
	return south;
}

void Room::setSouth(int newSouth)
{
	south = newSouth;
}

int Room::getWest()
{
	return west;
}

void Room::setWest(int newWest)
{
	west = newWest;
}

string Room::getDesc()
{
	return description;
}

void Room::setDesc(string newDesc)
{
	description = newDesc;
}

string Room::getTitle()
{
	return title;
}

void Room::setTitle(string newTitle)
{
	title = newTitle;
}

string Room::getInventory()
{
	return inventory;
}

void Room::setInventory(string newInventory)
{
	inventory = newInventory;
}
