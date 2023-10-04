#include <SFML\Graphics.hpp>
#include "cube.h"
#include "ScreenConstants.h"

bool Cube::operator==(const Cube& rhs) const
{
	return this->cubeID == rhs.cubeID;
};

Cube::Cube(float x, float y, float width, float height, int ID)
{
	this->cubeID = ID;
	this->direction = sf::Vector2f{0, 0};
	sf::Vector2f startPos = { x, y };
	sf::Vector2f size = { width, height };
	this->shape = sf::RectangleShape(size);
	this->shape.setPosition(startPos);
};

void Cube::ChangeDirection(sf::Vector2f targetPosition)
{
	sf::Vector2f directionToTarget = targetPosition - shape.getPosition();

	float distance = std::sqrt(directionToTarget.x * directionToTarget.x + directionToTarget.y * directionToTarget.y);

	directionToTarget /= distance;

	AddForce((sf::Vector2f)(directionToTarget * 0.01f));
}

void Cube::Move()
{
	// Убедимся, что скорость не превышает лимит
	float speedMagnitude = std::sqrt(speed.x * speed.x + speed.y * speed.y);
	if (speedMagnitude > SPEED_LIMIT)
	{
		speed *= SPEED_LIMIT / speedMagnitude;
	}

	if (GetX() + speed.x < SCREEN_SIZE_X - BORDERS and GetY() + speed.y < SCREEN_SIZE_Y - BORDERS and GetX() + speed.x > BORDERS and GetY() + speed.y > BORDERS)
		this->shape.move(speed);
	else
		this->shape.move(-speed * 3.0f);
}

float Cube::GetX() {
	return this->shape.getPosition().x;
};

float Cube::GetY() {
	return this->shape.getPosition().y;
}

void Cube::AddForce(sf::Vector2f newSpeed) {
	if (newSpeed.x < SPEED_LIMIT and newSpeed.y < SPEED_LIMIT)
		this->speed += newSpeed;
	else
		this->speed -= sf::Vector2f(speed.x / newSpeed.x, speed.y / newSpeed.y);
}

sf::RectangleShape Cube::GetShape()
{
	return this->shape;
}
;

sf::Vector2f Cube::GetVector() {
	return this->shape.getPosition();
};
