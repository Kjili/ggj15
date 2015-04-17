/*
 * Level.hpp
 *
 *  Created on: 24.01.2015
 *      Author: sartz
 */

#pragma once

#include <SFML/System.hpp>
#include <vector>
#include "GameObject.hpp"
#include "GUI.hpp"
#include "Item.hpp"
#include "TextBox.hpp"
#include "Highscore.hpp"
#include "Scene.hpp"

struct TileFlightData
{
	GameObject *tile;
	sf::Vector2f currentPos;
	sf::Vector2f targetPos;
	sf::Vector2f momentum;
	sf::Vector2f startPos;
	float scale;
};

class Level: Scene {
public:
	Level();
	
	GameObject* getTile(int x, int y);
	void setTile(GameObject* obj, int x, int y);
	void setGUI(GUI* obj);
	void switchLargeTile(int x1, int y1, int x2, int y2);
	
	Scene* processEvent(sf::Event event, sf::RenderWindow& window) override final;
	void update(sf::Time deltaT, sf::RenderWindow& window) override final;
	void draw(sf::RenderTarget& target) override final;
	
	void leave();
	// hack hier, ne doch nicht xD
	GameObject * player;
	GUI* gui;
	TextBox* textBox;
	const std::vector<GameObject*> & getGameBoard() const;
/*private:
	std::vector<GameObject*> gameBoard;*/
	sf::Vector2i startPos;
	sf::Vector2i portalPos;
	std::vector<Item*> items;
//private:
	std::vector<GameObject*> gameBoard;
	std::vector<TileFlightData> tileAnimationPos;
	float tileAnimationTime;
	void updateTileAnimation(sf::Time deltaT);
	bool readyToLeave() const;
	void finishLevel();
	void loadScene(std::string name);
private:
	std::map<sf::Uint32, std::vector<sf::Vector2i>*> colorToTilePositionMap;
	std::map<sf::Uint32, bool> walkableTileState;
	sf::Vector2i getTilePosition(sf::Uint32 color, int x, int y, sf::Image levelImg);
	sf::Uint32 createColorKey(sf::Color color);
	std::vector<sf::Vector2i>* checkNeighbours(sf::Uint32 color, int x, int y, sf::Image levelImg);
	
	bool leaved;
	Highscore *highscore;
	bool fooexit;
};
