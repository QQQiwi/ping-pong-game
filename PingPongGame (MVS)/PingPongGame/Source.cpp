#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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
	void check(float window_height)
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Ping Pong");

	// get the size of the window
	sf::Vector2u size = window.getSize();
	unsigned int window_width = size.x;
	unsigned int window_height = size.y;

	Paddle first_player("Ivan", true, false, window_width, window_height);
	Paddle second_player("Kekus", false, false, window_width, window_height);

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
		
		first_player.check(window_height);
		window.draw(first_player.sprite);

		second_player.check(window_height);
		window.draw(second_player.sprite);

        // end the current frame
        window.display();

	}

	return 0;
}