#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace sf;

class Ball
{
private:
	Vector2f position;

	CircleShape ballShape;

	float xVelocity;
	float yVelocity;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();

	CircleShape getShape();

	float getYAxis();
	
	void stop();

	void reboundSides();

	void reboundblock();

	void reboundBat1();

	void reboundBat2();

	void rebound1();

	void rebound2();

	void rebound3();

	void rebound4();

	void rebound5();

	void rebound6();

	void rebound7();

	void rebound8();

	void hitLeft();

	void hitRight();

	void update();

};
