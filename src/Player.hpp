#pragma once

#include <queue>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& doggieSize);
	bool intersects(const sf::Vector2u& tilePosition, const sf::Vector2f& tileSize);
	void move(sf::Time deltaTime, const sf::Vector2f& moveDir, const sf::Vector2f& sceneSize);
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget &renderTarget, sf::Shader *renderShader);
	// TODO move to private
	sf::RectangleShape _shape;
private:
	float _animationStep;
	int _direction;
	sf::RectangleShape _doggieShape;
	std::queue<sf::Vector2f> _positionQueue;
	std::queue<int> _directionQueue;
	
};

const static int PlayerAnimState[] = {0, 1, 1, 0, 2, 2};
const static int DoggieAnimState[] = {0, 2, 1, 3, 1, 4};
