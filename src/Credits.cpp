/*
 * Copyright (c) 2015-2017 Annemarie Mattmann, Johannes Mattmann,
 * Matthias Gazzari, Moritz Hagemann, Sebastian Artz
 * 
 * Licensed under the MIT license. See the LICENSE file for details.
 */

#include "Credits.hpp"
#include "Menu.hpp"
#include "global.hpp"

Credits::Credits():
	Scene({800, 600})
{
	background.setTexture(&gb::ressourceManager.getTexture("./img/credits.png", true));
	speech.setFont(gb::ressourceManager.getFont(std::string(PATH) + "fonts/LiberationSerif-Regular.ttf"));
	speech.setFillColor(sf::Color(0x00, 0x00, 0x00));
	speech.setCharacterSize(16);
	speech.setPosition(sf::Vector2f(16, 16));
	speech.setString(
		std::string("Ingame usage:") + 
		"\nARROW keys - move the character" +
		"\nSPACE key - proceed with dialogue" +
		"\nS key- skip dialogue" +
		"\nESC key- return to menu" +
		"\n\n\nDeveloped by:\nAnnemarie Mattmann,\nJohannes Mattmann,\nMatthias Gazzari,\nMoritz Hagemann and\nSebastian Artz."
	);
	gb::soundManager.playMusic("sound/backgroundFast.ogg");
}

Scene* Credits::processEvent(sf::Event event, sf::RenderWindow& window)
{
	// preprocessing key input (to enhance code readability)
	sf::Keyboard::Key keyPressed = sf::Keyboard::Unknown;
	if (event.type == sf::Event::KeyPressed)
	{
		keyPressed = event.key.code;
	}
	// process events
	if (keyPressed == sf::Keyboard::Escape)
	{
		gb::soundManager.stopMusic();
		return new Menu(Menu::Command::CREDITS);
	}
	return this;
}
Scene* Credits::update(sf::Time deltaT, sf::RenderWindow& window)
{
	return this;
}

void Credits::draw(sf::RenderTarget& target, bool focus)
{
	target.draw(background);
	target.draw(speech);
}
