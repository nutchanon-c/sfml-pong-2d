#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

sf::RectangleShape player1(sf::Vector2f(10.f,40.f));
sf::RectangleShape player2(sf::Vector2f(10.f,40.f));
sf::RectangleShape ball(sf::Vector2f(7.f,7.f));

float dx = 0.1f, dy = -0.f, dt = 0.1f;
int score1 = 0, score2 = 0;
float paddleCenter, d;


void reset();

int main()
{


    stringstream s1s, s2s;
    s1s << score1;
    s2s << score2;

    sf::Font font;
    if(!font.loadFromFile("Monda-Regular.ttf"))
    {
        cout << "eRROR";
    }
    sf::Text p1score;
    p1score.setFont(font);
    p1score.setColor(sf::Color::White);
    p1score.setString(s1s.str());
    p1score.setCharacterSize(20);
    p1score.setPosition(35, 10);


    sf::Text p2score;
    p2score.setFont(font);
    p2score.setColor(sf::Color::White);
    p2score.setString(s2s.str());
    p2score.setCharacterSize(20);
    p2score.setPosition(500-35, 10);


    sf::RenderWindow window(sf::VideoMode(500, 500), "Pong Test", sf::Style::Close | sf::Style::Titlebar);

    player1.setFillColor(sf::Color::Green);
    player2.setFillColor(sf::Color::Green);
    ball.setFillColor(sf::Color::Red);
    ball.setOrigin(3.5f, 3.5f);
    player1.setOrigin(5.f, 20.f);
    player2.setOrigin(5.f, 20.f);
    ball.setPosition(250,250);
    int cnt = 2;
    //dy = ball.getPosition().y + dy * dt;
    sf::Vector2f player1Vector;
    float player1X, player1Y;
    sf::Color colors[] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue};
    player1.setPosition(50,250);
    player2.setPosition(450,250);
    bool collides = ball.getGlobalBounds().intersects(player2.getGlobalBounds()) || ball.getGlobalBounds().intersects(player1.getGlobalBounds());
    //player1.setOrigin(0,0);
    //player1.setPosition(150.f, 250-100.f);

    while (window.isOpen())
    {

        collides = ball.getGlobalBounds().intersects(player2.getGlobalBounds()) || ball.getGlobalBounds().intersects(player1.getGlobalBounds());
        //cout<<collides << "\n";

        ball.move(dx,dy);
        /*
        if(ball.getPosition().x > player2.getPosition().x || ball.getPosition().x < player1.getPosition().x)
        {
            dx = -dx;
            dy = -dy;
        }
        */
        if(collides)
        {
            collides = false;
            if(dx > 0)
            {
                ball.move(-0.5f, 0);
                /*
                paddleCenter = player2.getPosition().y + (40/2);
                d = paddleCenter - player2.getPosition().y;
                dy = (d * -0.1)/100;
                dy *= -1;
                */
                dy = ((ball.getPosition().y - player2.getPosition().y) / 40) / 50;

            }
            else
            {
                ball.move(0.5f, 0);
                /*
                paddleCenter = player1.getPosition().y + (40/2);
                d = paddleCenter - player1.getPosition().y;
                dy = (d * -0.1)/100;
                dy *= -1;
                */
                dy = ((ball.getPosition().y - player1.getPosition().y) / 40) / 50;
            }

            dx = -dx;

        }
        if(ball.getPosition().x > 500)
        {
            score1++;
            cout<<"P1 SCORED\n";
            s1s.str("");
            s1s.clear();
            s1s << score1;
            p1score.setString(s1s.str());
            //cout << s1s.str() << "\n";
            dy = 0;
            dx = -0.1f;
            ball.setPosition(250, 250);
        }
        if(ball.getPosition().x < 0)
        {
            score2++;
            cout << "P2 SCORED\n";
            s2s.str("");
            s2s.clear();
            s2s << score2;
            p2score.setString(s2s.str());
            dy = 0;
            dx = 0.1f;
            ball.setPosition(250, 250);
        }
        if(ball.getPosition().y < 0 || ball.getPosition().y > 500) dy *= -1;



        sf::Event event;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player1.move(0.f, 0.11f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player1.move(0.f, -0.11f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player2.move(0.f, 0.11f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player2.move(0.f, -0.11f);
        }

        player1Vector = player1.getPosition();
        player1X = player1Vector.x;
        player1Y = player1Vector.y;

        while (window.pollEvent(event))
        {
/*
            if((500 - player1Y < 200) || (500 - player1Y > 500) || (500 - player1X < 200) || (500 - player1X > 500))
            {
                player1.setFillColor(colors[cnt]);
                cnt = (cnt + 1) % 3;
                reset();
            }*/
            //cout << player1X << " " << player1Y << "\n";
            //cout << 500 - player1X << "\n";
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    //cout << "closed\n";
                    break;
                case sf::Event::Resized:
                    //cout << "resized " << event.size.width << "x" << event.size.height << "\n";
                    break;
                case sf::Event::TextEntered:
                    if(event.text.unicode < 128)
                    {
                        //printf("%c", event.text.unicode);
                        //cout << event.text.unicode;
                    }
            }



        }

        window.clear();
        window.draw(player1);
        window.draw(player2);
        window.draw(ball);
        window.draw(p1score);
        window.draw(p2score);
        window.display();
    }

    return 0;
}
void reset()
{
    player1.setPosition(150,150);
}
