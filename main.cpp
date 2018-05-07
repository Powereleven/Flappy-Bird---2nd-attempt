#include <ctime>
#include <string>
#include "Bird.h"
#include "Obstacles.h"
#include "Collision.h"

#if defined(_STRING_)
using std::to_string;
#else
std::string to_string(int number) // fix compilation on GCC
{
	std::string number_string = "";
	number = abs(number);
	char ones_char;
	int ones = 0;
	while (1)
	{
		ones = number % 10;
		switch (ones)
		{
		case 0: ones_char = '0'; break;
		case 1: ones_char = '1'; break;
		case 2: ones_char = '2'; break;
		case 3: ones_char = '3'; break;
		case 4: ones_char = '4'; break;
		case 5: ones_char = '5'; break;
		case 6: ones_char = '6'; break;
		case 7: ones_char = '7'; break;
		case 8: ones_char = '8'; break;
		case 9: ones_char = '9'; break;
		}
		number -= ones;
		number_string = ones_char + number_string;
		if (number == 0)
		{
			break;
		}
		number = number / 10;
	}
	return number_string;
}
#endif

int main()
{
	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(1000, 800), "Flappy Bird");
	app.setFramerateLimit(360); //important bc the game's speed depend on this
	app.setKeyRepeatEnabled(false);

	sf::SoundBuffer buffer2, buffer3;
	buffer2.loadFromFile("sounds/coin.wav"); buffer3.loadFromFile("sounds/game_over.wav");
	sf::Sound coin, game_over_sound;
	coin.setBuffer(buffer2); game_over_sound.setBuffer(buffer3);

	sf::Font font; //just loading font
	font.loadFromFile("fonts/arial.ttf");

	sf::Text score; score.setFont(font); score.setPosition(480, 150); score.setOutlineThickness(3); score.setCharacterSize(50); //score text line
	sf::Text game_over; game_over.setFont(font); game_over.setPosition(130, 200); game_over.setFillColor(sf::Color(79, 75, 77)); game_over.setCharacterSize(60); game_over.setString("Game Over! (R to restart)");//game_over text line
	sf::Text fps; fps.setFont(font); fps.setFillColor(sf::Color::Black); fps.setCharacterSize(24);//fps text line

	sf::Texture t; t.loadFromFile("images/background.png"); sf::Sprite background(t); //background line

	Bird bird(app); //create bird

	Obstacles first;//there will be 3 pipes, (6 in total if you count 1 pipe as 2), they will just keep coming and going
	Obstacles second;
	Obstacles third;

	second.x = first.x + 400; // the standard x was 600, so 400 pixels to the right relative to the first obstacle
	third.x = first.x + 800; // same explanation

	int frame_counter = 0; float fps_counter; sf::Clock delay; /*fps clock*/ sf::Clock delay2; /*bird speed clock*/

	Collision objects(bird, first, second, third, coin);

	while (app.isOpen())
	{

		objects.isCollide();
		objects.update();

		sf::Event e;
		while (app.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)app.close();

			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					bird.leftClick();
				}
			}

			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::R) //Restart the game
				{
					for (auto i : { &first,&second,&third }) i->reset();
					bird.reset(); //default
				}
			}
		}

		bird.checkHeight();

		app.clear();  //draw paragraph
		app.draw(background);

		for (auto i : { &first,&second,&third }) i->draw(app);

		bird.draw();

		score.setString(to_string(bird.counter)); app.draw(score); //score paragraph

		if (delay.getElapsedTime().asSeconds() > 0.001) { fps_counter = frame_counter / delay.restart().asSeconds(); frame_counter = 0; } //fps paragraph
		fps.setString(to_string(fps_counter)); app.draw(fps);

		if (bird.alive)
		{
			if (delay2.getElapsedTime().asSeconds() > 0.005) //  1/0.005 = 200 fps for the bird
			{
				bird.movement(); //updates bird position
				delay2.restart();
			}

			for (auto i : { &first,&second,&third }) i->movement();
		}
		else { app.draw(game_over); if (bird.auxiliar_sound == 1)game_over_sound.play(); bird.auxiliar_sound = 0; } //game over frame and sound

		app.display();

		frame_counter++; //fps purposes
	}
	return 0;
}
