#include "Ball.h"
#include <stdlib.h>
#include <time.h>

float Raid;
float V = 0.1f;
float pi = 3.1416;

Ball::Ball(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	ballShape.setRadius(15);
	ballShape.setPosition(position);
	ballShape.setFillColor(Color::Red);

	srand(time(0));
	Raid = (rand()%40 + 80)* 0.01 * pi;
	xVelocity = V * cos(Raid);
	yVelocity = V * sin(Raid);

}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
	return ballShape;
}

float Ball::getYAxis()
{
	return position.y;
}

void Ball::reboundSides()
{
	yVelocity = -yVelocity;
}

void Ball::reboundBat1()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(1.93*pi);
	yVelocity = Velocity * sin(1.93*pi);
}

void Ball::reboundBat2()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(0.93*pi);
	yVelocity = Velocity * sin(0.93*pi);
}

void Ball::rebound1()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(0.25*pi);
	yVelocity = Velocity * sin(0.25*pi);
}
void Ball::rebound2()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(0.167*pi);
	yVelocity = Velocity * sin(0.167*pi);
}
void Ball::rebound3()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(1.83*pi);
	yVelocity = Velocity * sin(1.83*pi);
}
void Ball::rebound4()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(1.75*pi);
	yVelocity = Velocity * sin(1.75*pi);
}
void Ball::rebound5()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(0.75*pi);
	yVelocity = Velocity * sin(0.75*pi);
}
void Ball::rebound6()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(0.83*pi);
	yVelocity = Velocity * sin(0.83*pi);
}
void Ball::rebound7()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(1.17*pi);
	yVelocity = Velocity * sin(1.17*pi);
}
void Ball::rebound8()
{
	float Velocity = sqrt((xVelocity * xVelocity) + (yVelocity * yVelocity)) * 1.1;
	xVelocity = Velocity * cos(1.25*pi);
	yVelocity = Velocity * sin(1.25*pi);
}

void Ball::reboundblock()
{
	xVelocity = -xVelocity;
}

void Ball::hitLeft()
{
	position.y = 384;
	position.x = 512;
	srand(time(0));
	Raid = (rand() % 40 + 80)* 0.01 * pi;
	xVelocity = V * cos(Raid);
	yVelocity = V * sin(Raid);
}

void Ball::hitRight()
{
	position.y = 384;
	position.x = 512;
	srand(time(0));
	Raid = (rand() % 40 - 20)* 0.01 * pi;
	xVelocity = V * cos(Raid);
	yVelocity = V * sin(Raid);
}

void Ball::stop()
{
	position.y = 384;
	position.x = 512;
	xVelocity = 0;
	yVelocity = 0;
}

void Ball::update()
{
	// Update the ball position variables
	position.y += yVelocity;
	position.x += xVelocity;

	// Move the ball
	ballShape.setPosition(position);
}