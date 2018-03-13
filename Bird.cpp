#include "Bird.h"

Bird::Bird(sf::RenderWindow &a) : app(a)
{
	t.loadFromFile("images/bird.png");
	buffer.loadFromFile("sounds/flap.wav"); flap.setBuffer(buffer);
	s.setTexture(t);
	s.setOrigin(30, 22);
	s.setPosition(x, y);
}

void Bird::leftClick()
{
	if (alive == 1)flap.play();
	dy = -4;
}

void Bird::movement()
{
	dy += 0.1; if (dy<0) angle = -30; else angle = 0; //if bird going up, rotate it -30 degrees
	y += dy; //moves down the bird - value got testing
}

void Bird::checkHeight()
{
	if (y>700) alive = 0;
}

void Bird::reset()
{
	y = 400; dy = 0;
	counter = 0; alive = 1; auxiliar_sound = 1;
}

void Bird::draw()
{
	s.setPosition(x, y);
	s.setRotation(angle);
	app.draw(s);
}
