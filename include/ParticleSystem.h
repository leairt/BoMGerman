#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

using namespace std;

struct Particle
{
    sf::Vector2f velocity;
    sf::Time lifetime;
    sf::Vector2f position;
    sf::Color color;
    bool dead = false;
};

class Bomb;

// https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(int n);

    void start(Bomb &bomb);
    void update(sf::Time elapsed);
private:
    vector<Particle> particles;
    sf::Time lifetime;
    sf::Vector2f emitter;
    sf::Image gradient;
    Bomb *parent;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        for (size_t i = 0; i < particles.size(); ++i) {
            Particle p = particles[i];

            // skip if the particle is dead
            if (p.dead)
                continue;

            sf::CircleShape circle;
            float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
            circle.setRadius(100 * ratio);
            circle.setFillColor(p.color);
            circle.setPosition(p.position);
            target.draw(circle);
        }
    }
};

#endif // PARTICLESYSTEM_H
