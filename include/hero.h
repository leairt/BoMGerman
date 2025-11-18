#ifndef HERO_H
#define HERO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Game;

class Hero : public sf::Sprite
{
    public:
        // enum za komande
        sf::Keyboard::Key Right;
        sf::Keyboard::Key Left;
        sf::Keyboard::Key Up;
        sf::Keyboard::Key Down;
        sf::Keyboard::Key DropBomb;

        Hero();
        void init(int player);
        void onKeyPressed(Game &game);
        void onKeyReleased(Game &game, sf::Keyboard::Key key);
        void die();
    private:
        bool dead;
        sf::Texture costumeFront;
        sf::Texture costumeBack;
        sf::Texture costumeRight;
        sf::Texture costumeLeft;
        sf::Texture costumeDead;

        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};

#endif // HERO_H
