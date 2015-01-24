#include "SceneManager.hpp"
#include "Tile.hpp"
#include "globals.hpp"
#include <iostream>
#include "Player.hpp"
#include <string>
#include <sstream>

SceneManager::SceneManager(){
	std::vector<sf::Vector2i> *tmpVector = new std::vector<sf::Vector2i>();
	tmpVector->push_back(sf::Vector2i(0,0));
	tmpVector->push_back(sf::Vector2i(1,0));
	tmpVector->push_back(sf::Vector2i(2,0));
	tmpVector->push_back(sf::Vector2i(3,0));
	colorToTilePositionMap[0x11941bff] = tmpVector; // grass
	tmpVector = new std::vector<sf::Vector2i>();
	tmpVector->push_back(sf::Vector2i(0,3));
	tmpVector->push_back(sf::Vector2i(1,3));
	tmpVector->push_back(sf::Vector2i(2,3));
	tmpVector->push_back(sf::Vector2i(3,3));
	colorToTilePositionMap[0x969896ff] = tmpVector; // stone
	tmpVector = new std::vector<sf::Vector2i>();
	tmpVector->push_back(sf::Vector2i(0,1));
	tmpVector->push_back(sf::Vector2i(1,1));
	tmpVector->push_back(sf::Vector2i(2,1));
	tmpVector->push_back(sf::Vector2i(3,1));
	colorToTilePositionMap[0x9b6d27ff] = tmpVector; // dirt
	tmpVector = new std::vector<sf::Vector2i>();
	tmpVector->push_back(sf::Vector2i(0,2));
	tmpVector->push_back(sf::Vector2i(1,2));
	tmpVector->push_back(sf::Vector2i(2,2));
	tmpVector->push_back(sf::Vector2i(3,2));
	colorToTilePositionMap[0x5f5f5fff] = tmpVector; // wet stone
	tmpVector = new std::vector<sf::Vector2i>();
	tmpVector->push_back(sf::Vector2i(2,9));
	colorToTilePositionMap[0x000100ff] = tmpVector; // wall
	
	loadScene(std::string(PATH) + "levels/level000");
}

sf::Vector2i SceneManager::getTilePosition(sf::Uint32 color)
{
	std::map<sf::Uint32, std::vector<sf::Vector2i>*>::const_iterator conIt = colorToTilePositionMap.find(color);
	if (conIt != colorToTilePositionMap.end())
	{
		std::vector<sf::Vector2i> *tmpVec = colorToTilePositionMap[color];

		int numTiles = tmpVec->size();
		float rnd = 1.f * rand() / RAND_MAX;

		for (int i=0;i<numTiles;i++)
		{
			if (rnd < 1.f*i/numTiles)
			{
				return (*tmpVec)[i];
			}
		}

		return (*tmpVec)[numTiles-1];
	}
	return sf::Vector2i(0, 13);
}

//sf::Vector2i SceneManager::getRandomGrassPosition()
//{
//	float rnd = rand() / RAND_MAX;
//	int grassCount = 4;
//	if (rnd < 1./grassCount)
//	{
//		return sf::Vector2i(0,0);
//	}
//	if (rnd < 2./grassCount)
//	{
//		return sf::Vector2i(1,0);
//	}
//	if (rnd < 3./grassCount)
//	{
//		return sf::Vector2i(2,0);
//	}
//
//	return sf::Vector2i(3,0);
//}

void SceneManager::showScene(std::string sceneName) {
	// load scene if not existent and set currentScene
}

void SceneManager::update(sf::Time deltaT) {
	processEditMode();	// only for edit mode
	scene.update(deltaT);
}

void SceneManager::loadScene(std::string fileName)
{
	// load textures for level
	std::cout << std::string(PATH) << std::endl;
	tileTexture.loadFromFile(std::string(PATH) + "img/TileMap.png");
	playerTexture.loadFromFile(std::string(PATH) + "img/player.png");
	itemTexture.loadFromFile(std::string(PATH) + "img/items.png");
	coinTexture.loadFromFile(std::string(PATH) + "img/timeBar.png");
	// load and set timebar
	timeBarTexture.loadFromFile(std::string(PATH) + "img/timeBar.png");

	timeBarTexture.setRepeated(true);
	sf::Sprite *guiSprite = new sf::Sprite();
	guiSprite->setTexture(timeBarTexture);
	sf::Sprite *coinSprite = new sf::Sprite();
	coinSprite->setTexture(coinTexture);
	GUI* gui = new GUI(guiSprite,coinSprite);
	gui->setTimeout(20);
	scene.setGUI(gui);
	// load image bitmapt file
	sf::Image levelImg;
	levelImg.loadFromFile(fileName+".png");
	
	// create sprites for each tile
	for (int x=0;x<Scene::sizeX * Scene::largeTileSizeX;x++)
	{
		for (int y=0;y<Scene::sizeY * Scene::largeTileSizeY;y++)
		{
			// set tile sprite texture
			sf::Sprite* sprite = new sf::Sprite();
			sprite->setTexture(tileTexture);
			// get level code (from bitmap)
			sf::Color tmpColor = levelImg.getPixel(x, y);
			sf::Uint32 colorKey = 0;

			colorKey |= tmpColor.r << 3*8;
			colorKey |= tmpColor.g << 2*8;
			colorKey |= tmpColor.b << 1*8;
			colorKey |= tmpColor.a << 0*8;
			// resolve the correct tile based on the color code (and set correct texture rect)
			sf::Vector2i tmpPos;

			tmpPos = getTilePosition(colorKey);

//			tmpPos = sf::Vector2i(0, 3);
			sprite->setTextureRect(sf::IntRect(tmpPos.x*Tile::pixelSizeX, tmpPos.y*Tile::pixelSizeY, Tile::pixelSizeX, Tile::pixelSizeY));
			// set position of the sprite inside the map
			sprite->setPosition(Tile::tileScaleFactor*x*Tile::pixelSizeX, Tile::tileScaleFactor*y*Tile::pixelSizeY);
			// create the tile and add it to the scene
			Tile* tmpTile = new Tile();
			sprite->setScale(Tile::tileScaleFactor, Tile::tileScaleFactor);
			tmpTile->mySprite = sprite;
			scene.setTile(tmpTile, x, y);
		}
	}
	scene.player = new Player();
	sf::Sprite *playerSprite = new sf::Sprite();
	sf::Sprite *doggieSprite = new sf::Sprite();
	playerSprite->setTexture(playerTexture);
	doggieSprite->setTexture(playerTexture);
	scene.player->mySprite = playerSprite;

	scene.player->doggieSprite = doggieSprite;

	// read text file
	std::string textFileName = fileName + ".txt";
	std::ifstream infile(textFileName);
	std::string line;
	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    std::string part;
	    iss >> part;

	    if (part == "start")
	    {
	    	std::cout<<"start found"<<std::endl;
	    }

	    std::cout<<line<<std::endl;

	    // process pair (a,b)
	}

}

void SceneManager::processEditMode()
{
	for (int key=4;key<13;key++)
	{
		if (input[key] == true)
		{
			sf::Vector2i globalPosition = sf::Mouse::getPosition(window);

			sf::Vector2f localPosition;
			localPosition.x = 1.f*globalPosition.x/(Tile::pixelSizeX*Tile::tileScaleFactor);
			localPosition.y = 1.f*globalPosition.y/(Tile::pixelSizeY*Tile::tileScaleFactor);
//			std::cout<<localPosition.x<<", "<<localPosition.y<<std::endl;


			sf::Vector2i tmpPos;
			tmpPos.x = round(localPosition.x);
			tmpPos.y = round(localPosition.y);

			GameObject* tmpTile = scene.getTile(tmpPos.x, tmpPos.y);
			Tile* newTile = new Tile();

			newTile->mySprite = tmpTile->mySprite;

			sf::Vector2i posInTexture = sf::Vector2i(0, 0); // grass
			newTile->mySprite->setTextureRect(sf::IntRect(posInTexture.x*Tile::pixelSizeX, posInTexture.y*Tile::pixelSizeY, Tile::pixelSizeX, Tile::pixelSizeY));
			scene.setTile(newTile,tmpPos.x, tmpPos.y);
		}
	}
}

Scene SceneManager::getCurrentScene()
{
	return scene;
}
