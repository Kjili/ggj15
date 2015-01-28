#include "globals.hpp"
#include "PortalItem.hpp"
#include <cmath>
#include <iostream>

PortalItem::PortalItem(sf::Sprite* sprite):Item(sprite,0,0,16,32) {
	neverAgain=false;
	collectable = false;
	animClock = sf::Clock();
	animClock.restart();
}
PortalItem::~PortalItem(){
}

bool PortalItem::applyEffect()
{
	if (global::sceneManager.getCurrentScene().readyToLeave() && !neverAgain) 
	{
		global::soundManager.playSound("sound/won.ogg");
		neverAgain = true;
	}
	global::sceneManager.getCurrentScene().leave();
	return true;
};

void PortalItem::update (sf::Time deltaTime) {
	if (mySprite != 0)
	{
		int index = (1+std::sin(animClock.getElapsedTime().asSeconds() * 3.14)*2);
		mySprite->setTextureRect(sf::IntRect(16*index,0,16,32));
		global::window.draw(*mySprite);
	}
};
