#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Game.h"
#include "hero.h"

Game::Game()
{
    // init random
    srand (time(NULL));
}

void Game::start() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(1565, 785), "BoMGerman", sf::Style::Default);
    window.setFramerateLimit(60);

    // create a clock to track the elapsed time
    sf::Clock clock;

    init();

    // music.setVolume(15.0f);
    // music.play();

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if(event.type == sf::Event::KeyReleased) {
                player1.onKeyReleased(*this, event.key.code);
                player2.onKeyReleased(*this, event.key.code);
            }
        }

        player1.onKeyPressed(*this);
        player2.onKeyPressed(*this);

        sf::Time elapsed = clock.restart();
        for(int i = 0; i < bombs.size(); i++)
            bombs[i].update(elapsed);

        // clear screen
        window.clear();

        // draw white background
        window.draw(rectangle);

        // draw walls
        for(int i = 0; i < walls.size(); i++)
            window.draw(walls[i]);

        // draw bombs
        for(int i = 0; i < bombs.size(); i++)
            bombs[i].draw(window);

        window.draw(player1);
        window.draw(player2);

        window.display();
    }
}

void Game::addBomb(sf::Vector2f position) {
    Bomb bomb(*this);
    bomb.setScale(bombTemplate.getScale());
    bomb.setTexture(*bombTemplate.getTexture());
    bomb.setPosition(position);
    bombs.push_back(bomb);
}

void Game::init() {
    // background
    rectangle;
    rectangle.setFillColor(sf::Color::White);
    rectangle.setSize(sf::Vector2f(1565.f, 785.f));

    // walls
    textureCrate1.loadFromFile("res\\crate01.jpg");
    textureCrate2.loadFromFile("res\\crate02.jpg");

    for(int i = 0; i < 40; i++) {
        sf::Sprite spriteW(rand()%100 < 40 ? textureCrate1 : textureCrate2);
        spriteW.setPosition((rand()%20)*112, (rand()%10)*112);
        spriteW.setScale(0.18f, 0.18f);
        walls.push_back(spriteW);
    }

    player1.init(1);
    do {
        player1.setPosition((rand()%20)*112, (rand()%10)*112);
    } while(collision(player1));
    player1.Down = sf::Keyboard::S;
    player1.Up = sf::Keyboard::W;
    player1.Left = sf::Keyboard::A;
    player1.Right = sf::Keyboard::D;
    player1.DropBomb = sf::Keyboard::LControl;

    player2.init(2);
    do {
        player2.setPosition((rand()%20)*112, (rand()%10)*112);
    } while(collision(player2));
    player2.Down = sf::Keyboard::Down;
    player2.Up = sf::Keyboard::Up;
    player2.Left = sf::Keyboard::Left;
    player2.Right = sf::Keyboard::Right;
    player2.DropBomb = sf::Keyboard::RControl;

    bombTemplate.init();

    music.openFromFile("res\\POL-catch-me-short.wav");
    music.setLoop(true);
}

bool Game::collision(Hero &player) {
    // proverimo da igrac ne udari u zid ili u drogog igraca

    for(int i = 0; i < walls.size(); i++)
       if(player.getGlobalBounds().intersects(walls[i].getGlobalBounds()))
            return true;
    if(player1.getGlobalBounds().intersects(player2.getGlobalBounds()))
        return true;

    // proverimo da igrac nije napustio teren
    float offsetX = 80.f;
    float offsetY = 110.f;
    sf::Rect<float> screenRect(0.f + offsetX, 0.f + offsetY, 1600.f - 2*offsetX, 800.f - 2*offsetY);
    if(!player.getGlobalBounds().intersects(screenRect))
        return true;
    return false;
}

void Game::onParticleMove(Particle &p) {
    if(p.dead)
        return;

    // hit walls
    for(int i = 0; i < walls.size(); i++)
       if(walls[i].getGlobalBounds().contains(p.position.x, p.position.y)) {
           p.dead = true;
       }

    // hit heroes
    if(player1.getGlobalBounds().contains(p.position.x, p.position.y))
       player1.die();
    if(player2.getGlobalBounds().contains(p.position.x, p.position.y))
       player2.die();

    // eksplozija može da aktivira i otale bombe na putu
    for(int i = 0; i < bombs.size(); i++)
       if(bombs[i].contains(p.position)) {
            bombs[i].explode();
            p.dead = true;
       }
}
