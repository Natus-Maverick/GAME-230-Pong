#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "BatBlue.h"
#include "Ball.h"
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace sf;

int main()
{
	int windowWidth = 1024;
	int windowHeight = 768;
	// Make a window that is 1024 by 768 pixels
	// And has the title "Pong"
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

	int scoreA = 0;
	int scoreB = 0;
	bool end = false;
	bool blockup = false;
	bool col = true;

	// create a bat
	BatBlue bat(10.0f, windowHeight / 4 - 75.0f);

	// create A.I. bats
	BatBlue ai(windowWidth - 30.0f, windowHeight / 4 - 75.0f);

	BatBlue ai0(10.0f, windowHeight *3 / 4 - 75.0f);

	BatBlue ai1(windowWidth - 30.0f, windowHeight *3 / 4 - 75.0f);
	
	BatBlue block(windowWidth / 2, 2.0f);

	// create a ball
	Ball ball(windowWidth / 2, windowHeight / 2);

	Texture tt;
	tt.loadFromFile("bg.png");
	Sprite background(tt);

	Text hud;

	Text score1;
	Text score2;

	SoundBuffer point;
	SoundBuffer victory;
	SoundBuffer pad_b;
	SoundBuffer wall_b;
	point.loadFromFile("Point.wav");
	victory.loadFromFile("Victory.wav");
	pad_b.loadFromFile("paddle_bounce.wav");
	wall_b.loadFromFile("wall_bounce.wav");

	Sound sound;

	// We need to choose a font
	Font font;
	font.loadFromFile("The Led Display St.ttf");

	// Set the font to our message
	hud.setFont(font);
	score1.setFont(font);
	score2.setFont(font);

	// Make fonts big
	hud.setCharacterSize(75);
	score1.setCharacterSize(75);
	score2.setCharacterSize(75);

	// Choose color
	hud.setFillColor(sf::Color::White);
	score1.setFillColor(sf::Color::White);
	score2.setFillColor(sf::Color::White);

	//Set positions
	hud.setPosition(windowWidth / 2 - 365, windowHeight / 2 - 75);
	score1.setPosition(15,15);
	score2.setPosition(windowWidth - 75, 15);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && bat.getPosition().top > 0 )
		{
			// move up
			bat.moveUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && bat.getPosition().top + 100 <= windowHeight / 2)
		{
			// move down
			bat.moveDown();
		}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			// quit
			window.close();
		}

		//block move
		if (blockup == true && block.getPosition().top > 0)
		{
			block.blockUp();
		}

		if (blockup == false && block.getPosition().top + 100 < windowHeight)
		{
			block.blockDown();
		}

		if (block.getPosition().top <= 0)
		{
			blockup = false;
		}

		if (block.getPosition().top + 100 >= windowHeight)
		{
			blockup = true;
		}

		//A.I.
		if (ball.getYAxis() > ai.getPosition().top + 100 && ai.getPosition().top + 100 <= windowHeight / 2 - 1)
		{
			ai.moveDown();
		}
		if (ball.getYAxis() < ai.getPosition().top)
		{
			ai.moveUp();
		}

		//A.I. 0
		if (ball.getYAxis() > ai0.getPosition().top + 50)
		{
			ai0.moveDown();
		}
		if (ball.getYAxis() < ai0.getPosition().top - 50 && ai0.getPosition().top > windowHeight / 2 + 1)
		{
			ai0.moveUp();
		}

		//A.I. 1
		if (ball.getYAxis() > ai1.getPosition().top + 50)
		{
			ai1.moveDown();
		}
		if (ball.getYAxis() < ai1.getPosition().top - 50 && ai1.getPosition().top > windowHeight / 2 + 1)
		{
			ai1.moveUp();
		}

		if (ball.getPosition().left < 0)
		{
			ball.hitLeft();

			sound.setBuffer(point);
			sound.play();
			// ScoreB + 1
			scoreB++;
			

			if (scoreB >= 5) {
				ball.stop();
				sound.setBuffer(victory);
				sound.play();
				// Declare Winner
				std::stringstream winb;
				winb << "Player B wins!";
				hud.setString(winb.str());
				end = true;
			}
		}

		if (ball.getPosition().left + 30 > windowWidth)
		{
			ball.hitRight();

			sound.setBuffer(point);
			sound.play();
			// ScoreA + 1
			scoreA++;

			if (scoreA >= 5) {
				ball.stop();
				sound.setBuffer(victory);
				sound.play();
				// Declare Winner
				std::stringstream wina;
				wina << "Player A wins!";
				hud.setString(wina.str());
				end = true;
			}

		}

		// Handle ball hitting top or bottom
		if (ball.getPosition().top < 0 || ball.getPosition().top + 30 > windowHeight)
		{
			sound.setBuffer(wall_b);
			sound.play();
			ball.reboundSides();
		}

		//Ball hitting the block
		if (ball.getPosition().intersects(block.getPosition()) && col == false)
		{
			sound.setBuffer(pad_b);
			sound.play();
			ball.reboundblock();
			col = true;
		}

		// Has the ball hit the player's bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			col = false;
			sound.setBuffer(pad_b);
			sound.play();
			if (ball.getPosition().top - bat.getPosition().top < 20)
				ball.rebound4();
			if (ball.getPosition().top - bat.getPosition().top >= 20 && ball.getPosition().top - bat.getPosition().top < 40)
				ball.rebound3();
			if (ball.getPosition().top - bat.getPosition().top >= 40 && ball.getPosition().top - bat.getPosition().top < 60)
				ball.reboundBat1();
			if (ball.getPosition().top - bat.getPosition().top >= 60 && ball.getPosition().top - bat.getPosition().top < 80)
				ball.rebound2();
			if (ball.getPosition().top - bat.getPosition().top >= 60)
				ball.rebound1();	
		}
		// Has the ball hit the A.I.'s bat?
		if (ball.getPosition().intersects(ai.getPosition()))
		{
			col = false;
			sound.setBuffer(pad_b);
			sound.play();
			if (ball.getPosition().top - ai.getPosition().top < 20)
				ball.rebound8();
			if (ball.getPosition().top - ai.getPosition().top >= 20 && ball.getPosition().top - ai.getPosition().top < 40)
				ball.rebound7();
			if (ball.getPosition().top - ai.getPosition().top >= 40 && ball.getPosition().top - ai.getPosition().top < 60)
				ball.reboundBat2();
			if (ball.getPosition().top - ai.getPosition().top >= 60 && ball.getPosition().top - ai.getPosition().top < 80)
				ball.rebound6();
			if (ball.getPosition().top - ai.getPosition().top >= 80)
				ball.rebound5();
		}

		// Has the ball hit the A.I.'s bat?
		if (ball.getPosition().intersects(ai0.getPosition()))
		{
			col = false;
			sound.setBuffer(pad_b);
			sound.play();
			if (ball.getPosition().top - ai0.getPosition().top < 20)
				ball.rebound4();
			if (ball.getPosition().top - ai0.getPosition().top >= 20 && ball.getPosition().top - ai0.getPosition().top < 40)
				ball.rebound3();
			if (ball.getPosition().top - ai0.getPosition().top >= 40 && ball.getPosition().top - ai0.getPosition().top < 60)
				ball.reboundBat1();
			if (ball.getPosition().top - ai0.getPosition().top >= 60 && ball.getPosition().top - ai0.getPosition().top < 80)
				ball.rebound2();
			if (ball.getPosition().top - ai0.getPosition().top >= 60)
				ball.rebound1();
		}

		// Has the ball hit the A.I.'s bat?
		if (ball.getPosition().intersects(ai1.getPosition()))
		{
			col = false;
			sound.setBuffer(pad_b);
			sound.play();
			if (ball.getPosition().top - ai1.getPosition().top < 20)
				ball.rebound8();
			if (ball.getPosition().top - ai1.getPosition().top >= 20 && ball.getPosition().top - ai1.getPosition().top < 40)
				ball.rebound7();
			if (ball.getPosition().top - ai1.getPosition().top >= 40 && ball.getPosition().top - ai1.getPosition().top < 60)
				ball.reboundBat2();
			if (ball.getPosition().top - ai1.getPosition().top >= 60 && ball.getPosition().top - ai1.getPosition().top < 80)
				ball.rebound6();
			if (ball.getPosition().top - ai1.getPosition().top >= 80)
				ball.rebound5();
		}

		ball.update();
		bat.update();
		ai.update();
		ai0.update();
		ai1.update();
		block.update();

		std::stringstream sa;
		sa << scoreA;
		score1.setString(sa.str());

		std::stringstream sb;
		sb << scoreB;
		score2.setString(sb.str());

		window.clear();

		window.draw(background);

		window.draw(bat.getShape());

		window.draw(ai.getShape());

		window.draw(ai0.getShape());

		window.draw(ai1.getShape());

		window.draw(block.getShape());

		window.draw(ball.getShape());


		// Draw our scores and Winner Declare
		window.draw(hud);
		window.draw(score1);
		window.draw(score2);

		// Show everything we just drew
		window.display();

		//Restart
		if (end == true && event.key.code == sf::Keyboard::Space)
		{
			scoreA = 0;
			scoreB = 0;
			ball.hitLeft();
			hud.setString("");
			end = false;
		}
	}

	return 0;
}

