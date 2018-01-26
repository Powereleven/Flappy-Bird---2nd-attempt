#ifndef BIRD_H
#define BIRD_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird
{
    public:
        sf::SoundBuffer buffer; sf::Sound flap; //all to do with sound in the same line
        sf::Texture t; sf::Sprite s; //all to do with image in the same line
        float dy = 0; // for gravity
        bool alive = 1;
        int angle = 0;
        int counter = 0; // for score
        float x = 150, y = 400;
        bool auxiliar_sound = 1;

        Bird();
        void checkHeight();
        void leftClick();
        void movement();
        void reset();
        void draw(sf::RenderWindow &app);
};

#endif // BIRD_H
