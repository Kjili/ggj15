/*
 * Copyright (c) 2015-2017 Annemarie Mattmann, Johannes Mattmann,
 * Matthias Gazzari, Moritz Hagemann, Sebastian Artz
 * 
 * Licensed under the MIT license. See the LICENSE file for details.
 */

#include "DoorItem.hpp"
#include "../global.hpp"
#include "../Level.hpp"

DoorItem::DoorItem(sf::Sprite* sprite, bool vertical_, bool closed):
	Item(sprite, 0, 0 ,0, 0),
	wasClosed(closed),
	vertical(vertical_)
{
	blocksPath = closed;
	collectable = false;
	openDoorTextureRect = sf::IntRect(3*32, 4*32, 32, 64);
	closedDoorTextureRect = sf::IntRect(1*32, 4*32, 32, 64);
	if (!vertical)
	{
		sprite->setRotation(-90);
		sprite->move(0, 32);
	}
}

void DoorItem::draw(sf::RenderTarget &renderTarget, sf::Shader *renderShader)
{
	if (mySprite != 0)
	{
		renderTarget.draw(*mySprite, renderShader);
	}
}

void DoorItem::update(sf::Time deltaTime) {
	//if (gb::sceneManager.getCurrentScene()->readyToLeave()) blocksPath = false; //TODO: temporäre Bedingung (deprecated) zum Testen, ersetzen!!

	if (mySprite != 0)
	{
		if (blocksPath)
		{
			mySprite->setTextureRect(closedDoorTextureRect);
			wasClosed = true;
		}
		else
		{
			mySprite->setTextureRect(openDoorTextureRect);
			if (wasClosed) gb::soundManager.playSound("sound/door.ogg");
			wasClosed = false;
		}
	}
}

void DoorItem::toggle()
{
	blocksPath = !blocksPath;
}
