#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <string>
#include <list>
#include "Bird.h"
#include "Obstacles.h"
#include "Collision.h"

std::string to_string(int number) //my compiler still has the to_string bug and I am too lazy to fix it, so I just copied this function from someone in stack overflow
{
    std::string number_string = "";
    number = abs(number);
    char ones_char;
    int ones = 0;
    while(1){
        ones = number % 10;
        switch(ones){
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
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}

int main()
{
    srand(time(0));
    sf::RenderWindow app(sf::VideoMode(1000,800), "Flappy Bird");
    app.setFramerateLimit(240); //important bc the game's speed depend on this
    app.setKeyRepeatEnabled(false);

    sf::SoundBuffer buffer2, buffer3;
    buffer2.loadFromFile("sounds/coin.wav"); buffer3.loadFromFile("sounds/game_over.wav");
    sf::Sound coin, game_over_sound;
    coin.setBuffer(buffer2); game_over_sound.setBuffer(buffer3);

    sf::Font font; //just loading font
    font.loadFromFile("fonts/arial.ttf");

    sf::Text score; score.setFont(font); score.setPosition(480,150); score.setOutlineThickness(3); score.setCharacterSize(50); //score text line
    sf::Text game_over; game_over.setFont(font); game_over.setPosition(130,200); game_over.setFillColor(sf::Color(79,75,77)); game_over.setCharacterSize(60); game_over.setString("Game Over! (R to restart)");//game_over text line
    sf::Text fps; fps.setFont(font); fps.setFillColor(sf::Color::Black); fps.setCharacterSize(24);//fps text line

    sf::Texture t; t.loadFromFile("images/background.png"); sf::Sprite background(t); //background line

    Bird bird; //create bird

    Obstacles first(bird); //there will be 3 pipes, (6 in total if you count 1 pipe as 2), they will just keep coming and going
    Obstacles second(bird);
    Obstacles third(bird);

    second.x=first.x+400; // the standard x was 600, so 400 pixels to the right relative to the first obstacle
    third.x=first.x+800; // same explanation

    int frame_counter; float fps_counter; sf::Clock delay; /*fps clock*/ sf::Clock delay2; /*bird speed clock*/

    Collision obj(bird, first, second, third);

    while(app.isOpen())
    {
        obj.isCollide();
        if(first.x<-150){first.x=1000;first.y=rand()%400+350;} if(first.x==5){if(bird.alive==1){bird.counter++;coin.play();}}
        else if(second.x<-150){second.x=1000;second.y=rand()%400+350;} if(second.x==5){if(bird.alive==1){bird.counter++;coin.play();}}
        else if(third.x<-150){third.x=1000;third.y=rand()%400+350;} if(third.x==5){if(bird.alive==1){bird.counter++;coin.play();}}

        sf::Event e;
        while(app.pollEvent(e))
        {
            if(e.type==sf::Event::Closed)app.close();

            if(e.type==sf::Event::MouseButtonPressed)
            {
                if(e.mouseButton.button==sf::Mouse::Left)
                {
                     bird.leftClick();
                }
            }

            if(e.type==sf::Event::KeyPressed)
            {
                if(e.key.code==sf::Keyboard::R) //Restart the game
                {
                    //for(auto i:{first,second,third})i.reset(); //is this reset function tooooo ugly or is it acceptable? How to make it better?
                    first.reset(); second.reset(); third.reset();
                    bird.reset(); //default
                }
            }
        }

        bird.checkHeight();

        app.clear();  //draw paragraph
        app.draw(background);

        first.draw(app); second.draw(app);third.draw(app); //for(auto:i{first,second,third}) didn't work with objects that aren't pointers. Why?

        bird.draw(app);

        score.setString(to_string(bird.counter)); app.draw(score); //score paragraph

        if(delay.getElapsedTime().asSeconds() > 0.001){fps_counter = frame_counter/delay.restart().asSeconds(); frame_counter = 0;} //fps paragraph
        fps.setString(to_string(fps_counter)); app.draw(fps);

        if(bird.alive)
        {
            if(delay2.getElapsedTime().asSeconds()>0.005) //  1/0.005 = 200 fps for the bird
            {
             bird.movement(); //updates bird position
             delay2.restart();
            }

        first.movement(); second.movement(); third.movement(); //for(auto i:{first,second,third}) i.movement(); didn't work. Why?
        }
        else {app.draw(game_over); if(bird.auxiliar_sound==1)game_over_sound.play(); bird.auxiliar_sound = 0;} //game over frame and sound

        app.display();

        frame_counter++; //fps purposes
    }
    return 0;
}
