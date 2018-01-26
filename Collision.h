#ifndef COLLISION_H
#define COLLISION_H
#include "Bird.h"
#include "Obstacles.h"

class Collision
{
    public:
        Collision(Bird &bird, Obstacles &first, Obstacles &second, Obstacles &third) : first(first), second(second), third(third), bird(bird) {}
        Obstacles &first; Obstacles &second; Obstacles &third; Bird &bird;
        int current_obstacle_x; //to get the current obstacle coordinates for collision purposes / PS: current obstacle means the closest one. As soon as the score goes 1 up, the current obstacle is updated
        int current_obstacle_y;
        void isCollide()
        {
            //collision paragraph
        if(bird.counter%3==0){current_obstacle_x = first.x; current_obstacle_y = first.y;} //defining what Obstacles' object to use as the closest one (current one)
        if(bird.counter%3==1){current_obstacle_x = second.x; current_obstacle_y = second.y;}
        if(bird.counter%3==2){current_obstacle_x = third.x; current_obstacle_y = third.y;}
        if(bird.x+30>current_obstacle_x && (bird.y-22<800-current_obstacle_y || bird.y+22>1000-current_obstacle_y)) bird.alive = 0; //pipe's + bird collision line
        }
};

#endif // COLLISION_H
