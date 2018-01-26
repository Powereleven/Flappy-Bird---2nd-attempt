#include "Obstacles.h"

unsigned Obstacles::new_x = 600; //why can't you define the static variable in c++ when you declare it?

Obstacles::Obstacles(Bird &obj) : bird(obj)
{
    t1.loadFromFile("images/Obstacle_up.png");
    t2.loadFromFile("images/Obstacle_down.png");
    s_up.setTexture(t1); s_up.setOrigin(0,y); s_up.setPosition(x,0);
    s_down.setTexture(t2); s_down.setPosition(x,1000-y); // 1000 - y because it's 800 - y + 200, which is the height of the screen minus the height of the upper obstacle + 200 as height space the bird can fly through
}

void Obstacles::movement()
{
    x-=1;
}

void Obstacles::reset()
{
    x=new_x; y = rand()%400+350; new_x+=400; if(x==1400)new_x=600; //weird reset function. Is it acceptable? I made it this way because it has to loop through the 3 objects and reset their positions. Anyone with a better idea?
}

void Obstacles::draw(sf::RenderWindow& app)
{
    s_up.setOrigin(0,y); s_up.setPosition(x,0); s_down.setPosition(x,1000-y);
    app.draw(s_up);
    app.draw(s_down);
}
