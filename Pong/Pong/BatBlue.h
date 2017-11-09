#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class BatBlue
{

private:
	Vector2f position;
	RectangleShape batShape;

	float batSpeed = .1f;
	float blockSpeed = .04f;

public:
	BatBlue(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	void moveUp();

	void moveDown();

	void blockUp();

	void blockDown();

	void update();
};

