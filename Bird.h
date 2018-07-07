#ifndef BIRD_H
#define BIRD_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird
{
public:
	sf::RenderWindow &app;
	sf::SoundBuffer buffer; sf::Sound flap; 
	sf::Texture t; sf::Sprite s; 
	float dy = 0; // for gravity
	bool alive = 1;
	int angle = 0;
	int counter = 0; // for score
	float x = 150, y = 400;
	bool auxiliar_sound = 1;

	Bird(sf::RenderWindow &);
	void checkHeight();
	void leftClick();
	void movement();
	void reset();
	void draw();
};

#endif // BIRD_H
