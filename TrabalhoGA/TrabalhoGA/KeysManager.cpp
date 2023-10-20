#include "KeysManager.h"

void KeysManager::AddKey()
{
	keysQuantity++;
}

bool KeysManager::CheckColision(Sprite& key, Sprite& character)
{

	bool collisionX = character.GetPosition().x + character.GetDimension().x > key.GetPosition().x &&
		key.GetPosition().x + (key.GetDimension().x - 1) >= character.GetPosition().x;
	

	bool collisionY = character.GetPosition().y + character.GetDimension().y > key.GetPosition().y &&
		key.GetPosition().y + (key.GetDimension().y - 1) >= character.GetPosition().y;
	

	return collisionX && collisionY;
}

bool KeysManager::CanOpenGate()
{
	return keysQuantity == 3;
}
