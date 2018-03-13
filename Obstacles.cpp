#include "Obstacles.h"

unsigned Obstacles::new_x = 600; //why can't you define the static variable in c++ when you declare it?

Obstacles::Obstacles()
{
	t1.loadFromFile("images/Obstacle_up.png");
	t2.loadFromFile("images/Obstacle_down.png");
	s_up.setTexture(t1); s_up.setOrigin(0, y); s_up.setPosition(x, 0);
	s_down.setTexture(t2); s_down.setPosition(x, 1000 - y);

}

void Obstacles::movement()
{
	x -= 1;
}

void Obstacles::reset()
{
	x = new_x; y = rand() % 400 + 350; new_x += 400; if (x == 1400)new_x = 600;
}

void Obstacles::draw(sf::RenderWindow& app)
{
	s_up.setOrigin(0, y); s_up.setPosition(x, 0); s_down.setPosition(x, 1000 - y);
	app.draw(s_up);
	app.draw(s_down);
}
