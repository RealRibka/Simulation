#pragma once
#include <SFML\Graphics.hpp>

class Cube
{
public:
	bool operator==(const Cube& rhs) const;

	Cube(float x, float y, float widht, float height, int ID);

	float GetX();

	float GetY();

	sf::RectangleShape GetShape();

	sf::Vector2f GetVector();

	void ChangeDirection(sf::Vector2f vector);

	void Move();

	void AddForce(sf::Vector2f newSpeed);
// --------
private:
	const float SPEED_LIMIT = 1.0f;
	float widht;
	float height;

	int cubeID;
	
	sf::RectangleShape shape;
	sf::Vector2f direction; 
	sf::Vector2f speed;
};