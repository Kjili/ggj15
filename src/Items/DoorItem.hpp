/*
 * DoorItem.h
 *
 *  Created on: 28.02.2015
 *      Author: johannes
 */

#ifndef DOORITEM_H_
#define DOORITEM_H_

#include "../Item.hpp"

class Level;

class DoorItem: public Item {
private:
	bool wasClosed;
	bool vertical;
	sf::IntRect openDoorTexture;
	sf::IntRect closedDoorTexture;
public:
	DoorItem(sf::Sprite* sprite, bool vertical_, bool closed = true);
	virtual ~DoorItem();

	virtual bool applyEffect(Level& level);
	void draw(sf::RenderTarget &renderTarget, sf::Shader *renderShader);
	virtual void update(sf::Time deltaTime);
	void toggle();
};

#endif /* DOORITEM_H_ */
