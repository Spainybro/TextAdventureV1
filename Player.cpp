#include "Player.h"

Player::Player()
{
	playerPos = 0;
	inventory[0, 1, 2] = NOTHING;
}

Player::Player(int NewPos,string newInventory)
{
	playerPos = NewPos;
	inventory[0, 1, 2] = newInventory;
}

int Player::getPlayerPos()
{
	return playerPos;
}

void Player::setPlayerPos(int newPos)
{
	playerPos = newPos;
}

string Player::getInventory(int inventoryPos)
{
	return inventory[inventoryPos];
}

void Player::setInventory(string newInventory, int inventoryPos)
{
	inventory[inventoryPos] = newInventory;
}