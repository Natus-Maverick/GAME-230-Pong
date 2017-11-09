#include "BatBlue.h"


BatBlue::BatBlue(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	batShape.setSize(sf::Vector2f(20, 100));
	batShape.setPosition(position);
}

FloatRect BatBlue::getPosition()
{
	return batShape.getGlobalBounds();
}

RectangleShape BatBlue::getShape()
{
	return batShape;
}

void BatBlue::moveUp()
{
	position.y -= batSpeed;
}

void BatBlue::moveDown()
{
	position.y += batSpeed;
}

void BatBlue::blockUp()
{
	position.y -= blockSpeed;
}

void BatBlue::blockDown()
{
	position.y += blockSpeed;
}

void BatBlue::update()
{
	batShape.setPosition(position);
}