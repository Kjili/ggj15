#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
class Level;

class GUI
{
public:
	GUI(Level* level);
	void setTimeout(int seconds);
	void applyTimeBufff(float progress);
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget &renderTarget);
	void resetCoins();
	void resetKeys();
	void addCoins(int amount);
	void addKeys(int amount);
	void setTimebuffFactor(float factor);
	float timeLeft();
	int coins;
	float timeoutSeconds;
private:
	sf::Clock timeoutClock;
	sf::Sprite* timeSprite;
	sf::Sprite* coinSprite;
	sf::Sprite* keySprite;
	float timeBuff;
	float pauseOffset;
	bool lastEnable;
	bool loosed;
	bool smallTime;
	float buffFactor;
	int keys;
	Level* level;
	sf::Font font;
	sf::Text levelNumber;
};
