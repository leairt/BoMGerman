#include "bomb.h"
#include "game.h"

Bomb::Bomb()
{
    lifetime = sf::seconds(2);
    state = 0;
}

Bomb::Bomb(Game &game)
{
    lifetime = sf::seconds(2);
    state = 0;
    parent = &game;
}

void Bomb::init() {
    costume.loadFromFile("res\\bomb.png");

    // smanjimo velicinu slike
    setScale(0.18f, 0.18f);

    setTexture(costume);
}

void Bomb::update(sf::Time elapsed) {
    if(state == 0) {
       lifetime -= elapsed;

       if(lifetime <= sf::Time::Zero)
          explode();
    }
    if(state == 1) {
        particles.update(elapsed);
    }
}

void Bomb::explode() {
    if(state != 0)
        return;

    particles.start(*this);
    state = 1;

    if(soundBuffer.loadFromFile("res/Explosion1.wav")) {
       sound.setBuffer(soundBuffer);
       sound.play();
    }
}

void Bomb::onParticleMove(Particle &p) {
    parent->onParticleMove(p);
}

bool Bomb::contains(sf::Vector2f p) {
    if(state == 0)
        return getGlobalBounds().contains(p.x, p.y);
    return false;
}

void Bomb::draw(sf::RenderWindow& window) {
    if(state == 0)
        window.draw(*this);
    if(state == 1)
        window.draw(particles);
}

