#ifndef OBSTACLES_H
#define OBSTACLES_H
#include <SFML/Graphics.hpp>

class Obstacles
{
public:
	sf::Texture t1, t2; sf::Sprite s_up, s_down; // all to do with image in the same line
	int x = 600; int y = rand() % 400 + 350; // the y value is the one that works for the dimensions of the obstacles, which are 150x800 in total so to cut the image the way I want this is the y I need
	static unsigned new_x; //auxiliar variable for weird reset function

	Obstacles();
	void movement();
	void reset();
	void draw(sf::RenderWindow& app);
};

#endif // OBSTACLES_H
