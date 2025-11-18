#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Hero.h"
#include "Game.h"

Hero::Hero()
{
}

void Hero::init(int player) {
    if(player == 1) {
        costumeFront.loadFromFile("res\\lealealea.png", sf::IntRect(0, 0, 245, 296));
        costumeLeft.loadFromFile("res\\lealealea.png", sf::IntRect(245, 0, 220, 296));
        costumeBack.loadFromFile("res\\lealealea.png", sf::IntRect(460, 0, 230, 296));
        costumeRight.loadFromFile("res\\lealealea.png", sf::IntRect(690, 0, 240, 296));
        //costumeDead.loadFromFile("res\\hero1.png", sf::IntRect(0, 0, 215, 296));
    }
    if(player == 2) {
        costumeFront.loadFromFile("res\\sergejsergej.png", sf::IntRect(0, 0, 215, 296));
        costumeLeft.loadFromFile("res\\sergejsergej.png", sf::IntRect(220, 0, 230, 296));
        costumeBack.loadFromFile("res\\sergejsergej.png", sf::IntRect(444, 0, 215, 296));
        costumeRight.loadFromFile("res\\sergejsergej.png", sf::IntRect(675, 0, 220, 296));
        //costumeDead.loadFromFile("res\\hero1.png", sf::IntRect(0, 0, 215, 296));
    }

    // smanjimo velicine slika
    setScale(0.32f, 0.32f);

    setTexture(costumeFront);

    dead = false;
}

void Hero::die() {
    // TODO: set costume dead
    dead = true;
    setTexture(costumeDead);

    /*
    if(soundBuffer.loadFromFile("res/death.mp3")) {
       sound.setBuffer(soundBuffer);
       sound.play();
    }
    */
}

void Hero::onKeyPressed(Game &game) {
    if(dead)
        return;

    if(sf::Keyboard::isKeyPressed(Left)) {
        move(-5.0f, 0.0f);
        setTexture(costumeLeft);
        if(game.collision(*this))
            move(+5.0f, 0.0f);
    }
    if(sf::Keyboard::isKeyPressed(Right)) {
        move(+5.0f, 0.0f);
        setTexture(costumeRight);
        if(game.collision(*this))
            move(-5.0f, 0.0f);
    }
    if(sf::Keyboard::isKeyPressed(Up)) {
        move(0.0f, -5.0f);
        setTexture(costumeBack);
        if(game.collision(*this))
            move(0.0f, +5.0f);
    }
    if(sf::Keyboard::isKeyPressed(Down)) {
        move(0.0f, +5.0f);
        setTexture(costumeFront);
        if(game.collision(*this))
            move(0.0f, -5.0f);
    }
    // if(sf::Keyboard::isKeyPressed(DropBomb)) {
    //    game.addBomb(getPosition());
    // }
}

void Hero::onKeyReleased(Game &game, sf::Keyboard::Key key) {
    if(key == DropBomb)
        game.addBomb(getPosition());
}


