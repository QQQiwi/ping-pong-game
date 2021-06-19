#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include <string>

class Paddle
{
public:
	std::string name;
	bool is_left;
	bool is_bot;
	int score = 0;
	float window_height;

	//Left coordinate of the rectangle
	float sprite_left = 10.f;
	//Right coordinate of the rectangle
	float sprite_right = 10.f;
	//Width of the rectangle
	float sprite_width = 8.f;
	//Height of the rectangle
	float sprite_height = 100.f;

	// create test sprite of Paddle
	sf::Sprite sprite;

	// constructor of object Paddle
	Paddle(std::string player_name, bool player_is_left, bool player_is_bot, float window_width, float player_window_height)
	{
		name = player_name;
		is_left = player_is_left;
		is_bot = player_is_bot;
		window_height = player_window_height;

		sf::Texture texture;
		sprite.setTexture(texture);
		// by this setter i can change color of my entities
		sprite.setColor(sf::Color(0, 255, 0)); // this is green

		if (is_left)
		{
			// position
			sprite.setPosition(sf::Vector2f(window_width*0.01f, window_height / 2.f));
		}
		else
		{
			// position
			sprite.setPosition(sf::Vector2f(window_width - window_width*0.02f, window_height / 2.f));
		}
	}

	// check of position and so on
	void check()
	{
		// by this getter i can take position of my entities
		sf::Vector2f position = this->sprite.getPosition();
		int sprite_x = position.x;
		int sprite_y = position.y;

		if (is_left)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if (!(sprite_y == window_height - this->sprite_height))
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, 0.1f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (!(sprite_y == 0))
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
				if (!(sprite_y == window_height - this->sprite_height))
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, 0.1f);
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (!(sprite_y == 0))
				{
					// left key is pressed: move our character
					this->sprite.move(0.f, -0.1f);
				}
			}
		}
		this->sprite.setTextureRect(sf::IntRect(this->sprite_left, this->sprite_right,
			this->sprite_width, this->sprite_height));
	}
};

class Ball
{
public:
	float speed = 0.1f;
	float window_width;
	float window_height;
	bool move_to_right;

	sf::Vector2f last_position;
	float ball_size = 10.f;

	// create test shape of Ball
	sf::CircleShape shape;

	// constructor of object Paddle
	Ball(bool move_to_right, float player_window_width, float player_window_height)
	{
		this->move_to_right = move_to_right;

		window_width = player_window_width;
		window_height = player_window_height;

		shape.setRadius(ball_size);
		shape.setFillColor(sf::Color(255, 0, 0));

		sf::Vector2f center(player_window_width / 2.f, player_window_height / 2.f);

		// position
		shape.setPosition(center);
		
		last_position = center;
		if (move_to_right)
		{
			last_position.x -= speed;
		}
		else
		{
			last_position.x += speed;
		}
	};

	void check(bool &move_to_right, Paddle cur_paddle)
	{
		// by this getter i can take position of my entities
		sf::Vector2f position = this->shape.getPosition();
		sf::Vector2f paddle_position = cur_paddle.sprite.getPosition();

		float cur_x = position.x;
		float cur_y = position.y;

		// if ball is touched by paddle - he change direction
		bool is_ball_over_paddle = (cur_y + 2*ball_size >= paddle_position.y && cur_y <= paddle_position.y + cur_paddle.sprite_height);

		if (move_to_right && cur_x + 2*ball_size >= paddle_position.x && is_ball_over_paddle)
		{
			last_position.x = cur_x + speed;
			move_to_right = !move_to_right;
		}
		if (!move_to_right && cur_x <= paddle_position.x + cur_paddle.sprite_width && is_ball_over_paddle)
		{
			last_position.x = cur_x - speed;
			move_to_right = !move_to_right;
		}

		this->shape.move(cur_x - last_position.x, cur_y - last_position.y);
		
		last_position.x = cur_x;
		last_position.y = cur_y;
			
	}
	// out
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");

	// get the size of the window
	sf::Vector2u size = window.getSize();
	unsigned int window_width = size.x;
	unsigned int window_height = size.y;

	bool move_to_right = true;

	Paddle first_player("Ivan", true, false, window_width, window_height);
	Paddle second_player("Kekus", false, false, window_width, window_height);
	Ball kekus(move_to_right, window_width, window_height);

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
		
		first_player.check();
		window.draw(first_player.sprite);

		second_player.check();
		window.draw(second_player.sprite);

		if (move_to_right)
		{
			kekus.check(move_to_right, second_player);
		}
		else
		{
			kekus.check(move_to_right, first_player);
		}
		window.draw(kekus.shape);

        // end the current frame
        window.display();

	}

	return 0;
}