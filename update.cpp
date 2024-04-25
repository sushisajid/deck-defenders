/* make a base class for card.
ussmein health, defense, aur attack stats hon gay
 make pure virtual functions of attack enemy, update health.
 phir make child classes of all card types*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread> //3rd and 4th libraries are for cooldown
#include <SFML/Graphics.hpp>

using namespace std;
using namespace chrono;

class Card // Attack function will be called when two cards intersect with each other(sfml)
{
protected:
    int health, defence, attack;
    chrono::time_point<chrono::steady_clock> lastUsedTime;
    int cooldownSeconds;
    bool isDestroyed; // Flag to indicate if the card is destroyed
    sf::Sprite sprite;

public:
    Card(int h, int d, int a, int cds = 5) : health(h), defence(d), attack(a), cooldownSeconds(cds) {}

    virtual void AttackEnemy() = 0;
    virtual void TakeDamage(int damage) = 0;

    void use()
    {
        if (steady_clock::now() >= lastUsedTime + chrono::seconds(cooldownSeconds)) // from the chrono library
        {
            lastUsedTime = chrono::steady_clock::now();
            cout << "Using card." << endl;
        }
        else
        {
            cout << "Card is still on cooldown." << endl;
        }
    }
    virtual void drawSprite(sf::RenderWindow &window)
    {
        if (!isDestroyed)
        {
            window.draw(sprite);
        }
    }
    void destroy()
    {
        isDestroyed = true;
    }
    bool destroyed()
    {
        return isDestroyed;
    }
    void move()
    {
        sprite.setPosition(sf::Vector2f(2, 2));
    }
};

class HighAttack : public Card
{
public:
    HighAttack(int h = 100, int d = 5, int a = 10, int cds = 5) : Card(h, d, a, cds)
    {

        sf::Texture highAttackTexture;
        if (!highAttackTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/barbarians.jpeg"))
        {
            cout << "High Attack sprite not loaded." << endl;
        }
        cout << "Sprite loaded." << endl;
        sprite.setTexture(highAttackTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 300));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window) override
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};
class HighDefence : public Card
{
public:
    HighDefence(int h = 100, int d = 10, int a = 5, int cds = 5) : Card(h, d, a, cds)
    {
        sf::Texture highDefenceTexture;
        if (!highDefenceTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/Giant.jpg"))
        {
            cout << "High Defence sprite not loaded." << endl;
        }
        sprite.setTexture(highDefenceTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(0, 0));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window) override
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};

class Mid : public Card
{
public:
    Mid(int h = 100, int d = 5, int a = 5, int cds = 5) : Card(h, d, a, cds)
    {

        sf::Texture MidTexture;
        if (!MidTexture.loadFromFile("images/barbarians.jpeg"))
        {
            cout << "High Attack sprite not loaded." << endl;
        }
        sprite.setTexture(MidTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window) override
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};
class Legendary : public Card
{
public:
    Legendary(int h = 100, int d = 20, int a = 20, int cds = 10) : Card(h, d, a, cds)
    {
        sf::Texture LegendaryTexture;
        if (!LegendaryTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/barbarians.jpeg"))
        {
            cout << "High Attack sprite not loaded." << endl;
        }

        sprite.setTexture(LegendaryTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        health -= damage;
        if (health < 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window) override
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};

int main()
{
    //     int cds;
    //     Legendary lg(100, 20, 20, cds);
    //     lg.use();
    //     //this_thread::sleep_for(chrono::seconds(3)); // system paused for 3 secs
    //     lg.use();

    sf::RenderWindow window(sf::VideoMode(600, 600), ("Deck Defenders"));

    HighAttack *ha = nullptr;
    HighDefence *hd = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                    if (ha == nullptr)
                    {
                        ha = new HighAttack(100, 5, 10, 5);
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (ha == nullptr)
                    {
                        hd = new HighDefence(100, 5, 10, 5);
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
            }
        }
        window.clear();
        if (ha != nullptr)
        {
            ha->drawSprite(window);
        }
        else if (hd != nullptr)
        {
            hd->drawSprite(window);
        }
        window.display();
    }
}