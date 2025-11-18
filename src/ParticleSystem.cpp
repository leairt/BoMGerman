#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>

#include "ParticleSystem.h"

#include "Game.h"

class Game;

ParticleSystem::ParticleSystem(int n)
{
    particles = vector<Particle>(n),
    lifetime = sf::seconds(3);
    emitter = sf::Vector2f(0.0f, 0.0f);

    sf::Texture texture;
    if(texture.loadFromFile("res\\Gradient.png"))
        gradient = texture.copyToImage();
}

void ParticleSystem::start(Bomb &bomb) {
    parent = &bomb;
    emitter = bomb.getPosition();
    for (int i = 0; i < particles.size(); ++i) {
        // give a random velocity and lifetime to the particle
        float angle = (rand() % 360) * 3.14f / 180.f;
        float speed = (rand() % 400) + 100.f;
        particles[i].velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
        particles[i].lifetime = sf::milliseconds((rand() % 450) + 50);
        particles[i].dead = false;
        particles[i].position = emitter;
    }
}

void ParticleSystem::update(sf::Time elapsed)
{
    int n = 0; // broj aktivnih èestica
    for (int i = 0; i < particles.size(); ++i) {
       // update the particle lifetime
       Particle& p = particles[i];
       p.lifetime -= elapsed;

       // if the particle is dead
       if(p.lifetime <= sf::Time::Zero) {
          p.dead = true;
          continue;
       }

       n++; // aktivna èestica

       // update the position of the corresponding vertex
       p.position += p.velocity * elapsed.asSeconds();

       float ratio1 = p.lifetime.asSeconds() / lifetime.asSeconds();

       float max_distance = 150.f;
       float ratio2 = sqrt((emitter.x - p.position.x)*(emitter.x - p.position.x)+(emitter.y - p.position.y)*(emitter.y - p.position.y)) / max_distance;

       double x = 512.f - 512.f * ratio2;
       double y = 2000.f * ratio1;
       if(x < 0)
            x = 0.f;
       if(x >= 512)
            x = 511.f;
       if(y < 0)
            y = 0.f;
       if(x >= 512)
            y = 511.f;
       p.color = gradient.getPixel(y, x);
       parent->onParticleMove(p);
    }
}


