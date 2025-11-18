#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Hero.h"
#include "Bomb.h"

using namespace std;

class Particle;

class Game
{
    public:
        Game();
        void start();
        void addBomb(sf::Vector2f position);
        bool collision(Hero &player);
        void onParticleMove(Particle &p);

    private:
        vector<sf::Sprite> walls;
        vector<Bomb> bombs;
        Hero player1;
        Hero player2;
        Bomb bombTemplate;

        sf::RectangleShape rectangle;
        sf::Texture textureCrate1;
        sf::Texture textureCrate2;
        sf::Music music;

        void init();
};

#endif // GAME_H
