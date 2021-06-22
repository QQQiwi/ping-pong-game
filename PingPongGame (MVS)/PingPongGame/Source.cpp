#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <string>

sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");

// get the size of the window
sf::Vector2u size = window.getSize();
unsigned int windowWidth = size.x;
unsigned int windowHeight = size.y;

sf::Vector2f center(windowWidth / 2.f, windowHeight / 2.f);

class Paddle
{
public:
	std::string name;
	bool isLeft;
	bool isBot;
	int score = 0;
	// it contains paddle current coordinates
	float curX;
	float curY;

	sf::Vector2f centerCoordinates;

	//Left coordinate of the rectangle
	float spriteLeft = 10.f;
	//Right coordinate of the rectangle
	float spriteRight = 10.f;
	//Width of the rectangle
	float spriteWidth = 8.f;
	//Height of the rectangle
	float spriteHeight = 100.f;

	// create test sprite of Paddle
	sf::Sprite sprite;

	// constructor of object Paddle
	Paddle(std::string playerName, bool playerIsLeft, bool playerIsBot)
	{
		name = playerName;
		isLeft = playerIsLeft;
		isBot = playerIsBot;

		sf::Texture texture;
		sprite.setTexture(texture);
		// by this setter i can change color of my entities
		sprite.setColor(sf::Color(0, 255, 0)); // this is green

		if (isLeft)
		{
			// position
			sprite.setPosition(sf::Vector2f(windowWidth*0.01f, windowHeight / 2.f));
		}
		else
		{
			// position
			sprite.setPosition(sf::Vector2f(windowWidth - windowWidth * 0.02f, windowHeight / 2.f));
		}
	}

	// check of position and so on
	void check()
	{
		// by this getter i can take position of my entities
		sf::Vector2f position = this->sprite.getPosition();
		curX = position.x;
		curY = position.y;

		// calculation center coordinates of paddle
		centerCoordinates.x = curX;
		centerCoordinates.y = curY + spriteHeight /2.f;

		if (isLeft)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (curY <= windowHeight - this->spriteHeight)
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, 0.1f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (curY >= 0)
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, -0.1f);
				}
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (curY <= windowHeight - this->spriteHeight)
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, 0.1f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (curY >= 0)
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, -0.1f);
				}
			}
		}
		this->sprite.setTextureRect(sf::IntRect(this->spriteLeft, this->spriteRight,
			this->spriteWidth, this->spriteHeight));
	}
};

class Ball
{
public:
	float speed = 0.07f;
	//bool moveToRight;

	// it contains ball current coordinates
	float curX;
	float curY;

	sf::Vector2f lastPosition;
	float ballRadius = 10.f;

	// create test shape of Ball
	sf::CircleShape shape;
	
	void cast(bool &moveToRight)
	{
		// position
		shape.setPosition(center);

		lastPosition = center;
		if (moveToRight)
		{
			lastPosition.x -= speed;
		}
		else
		{
			lastPosition.x += speed;
		}
	}

	// constructor of object Ball
	Ball(bool &moveToRight)
	{
		//this->moveToRight = moveToRight;

		shape.setRadius(ballRadius);
		shape.setFillColor(sf::Color(255, 0, 0));

		cast(moveToRight);
	};

	void paddleTouch(bool &moveToRight, Paddle &curPaddle)
	{
		float paddleCurX = curPaddle.curX;
		float paddleCurY = curPaddle.curY;

		bool isBallOverPaddle = (curY + 2 * ballRadius >= paddleCurY && curY <= paddleCurY + curPaddle.spriteHeight);

		if (!moveToRight && curX <= paddleCurX + curPaddle.spriteWidth && isBallOverPaddle)
		{
			sf::Vector2f pointCenter = curPaddle.centerCoordinates - sf::Vector2f(ballRadius, ballRadius);

			if (pointCenter.y > curY)
			{
				lastPosition.y = curY + speed;
			}
			if (pointCenter.y < curY)
			{
				lastPosition.y = curY - speed;
			}

			lastPosition.x = curX - speed;
			moveToRight = !moveToRight;
		}
		else if (moveToRight && curX + 2 * ballRadius >= paddleCurX && isBallOverPaddle)
		{
			sf::Vector2f pointCenter = curPaddle.centerCoordinates - sf::Vector2f(ballRadius, ballRadius);

			if (pointCenter.y > curY)
			{
				lastPosition.y = curY + speed;
			}
			if (pointCenter.y < curY)
			{
				lastPosition.y = curY - speed;
			}
			lastPosition.x = curX + speed;
			moveToRight = !moveToRight;
		}
	}

	void wallTouch()
	{
		if (curY + 2*ballRadius >= windowHeight)
		{
			lastPosition.y = curY + speed;
		}
		if (curY <= 0)
		{
			lastPosition.y = curY - speed;
		}
	}

	void check(bool &moveToRight, Paddle &curPaddle)
	{
		sf::Vector2f position = this->shape.getPosition();
		curX = position.x;
		curY = position.y;

		// if ball is touched by paddle - he change direction
		paddleTouch(moveToRight, curPaddle);
		// if ball touch wall - he also change direction
		wallTouch();

		this->shape.move(curX - lastPosition.x, curY - lastPosition.y);

		lastPosition.x = curX;
		lastPosition.y = curY;
	}
};

void isOut(Ball &ball, int &firstPlayerScore, int &secondPlayerScore, bool &moveToRight)
{
	if (ball.curX >= windowWidth)
	{
		firstPlayerScore++;
		//ball.moveToRight = !ball.moveToRight;
		ball.cast(moveToRight);
		std::cout << "first Player Score: " << firstPlayerScore << ' ';
	}
	else if (ball.curX <= 0)
	{
		secondPlayerScore++;
		//ball.moveToRight = !ball.moveToRight;
		ball.cast(moveToRight);
		std::cout << "second Player Score: " << secondPlayerScore << ' ';
	}
}

int main()
{
	// it set first direction of ball's move
	bool moveToRight = true;

	Paddle firstPlayer("Ivan", true, false);
	Paddle secondPlayer("Kekus", false, false);
	Ball ball(moveToRight);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// check position of player's paddles
		firstPlayer.check();
		window.draw(firstPlayer.sprite);

		secondPlayer.check();
		window.draw(secondPlayer.sprite);

		// if the ball is moving to left - then i should check 
		// if first player's paddle was touch a ball
		if (moveToRight)
		{
			ball.check(moveToRight, secondPlayer);
		}
		else
		{
			ball.check(moveToRight, firstPlayer);
		}
		//ball.shape.setPosition(secondPlayer.centerCoordinates - sf::Vector2f(ball.ballRadius, ball.ballRadius));
		window.draw(ball.shape);
		isOut(ball, firstPlayer.score, secondPlayer.score, moveToRight);

		// end the current frame
		window.display();
	}
	return 0;
}