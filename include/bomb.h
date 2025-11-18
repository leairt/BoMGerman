#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "ParticleSystem.h"

struct Particle;
class ParticleSystem;
class Game;

class Bomb : public sf::Sprite
{
    public:
        Bomb();
        Bomb(Game &game);
        void init();
        void update(sf::Time elapsed);
        void explode();
        void draw(sf::RenderWindow& window);
        void onParticleMove(Particle &p);
        bool contains(sf::Vector2f p);
    private:
        Game *parent;
        sf::Texture costume;
        int state = 0; // 0 - postavljena, 1 - ekspozija, 2 - nema je vise

        sf::Time lifetime;
        ParticleSystem particles = ParticleSystem(200);

        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};

#endif // BOMB_H
