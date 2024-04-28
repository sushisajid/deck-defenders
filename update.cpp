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

class Tower
{
private:
    int health;

public:
    sf::Texture TowerTexture;
    sf::Sprite sprite; // Declare sprite variable

    // Constructor
    Tower(int h = 40) : health(h)
    {
        // Load the texture from the file
        if (!TowerTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/tower.jpg"))
        {
            std::cout << "Tower sprite not loaded." << std::endl;
        }
        else
        {
            std::cout << " Tower sprite loaded." << std::endl;
            // Set the texture of the sprite
            sprite.setTexture(TowerTexture);
            float scaleFactor = 0.5f; // You can adjust this value as needed

            // Apply the scaling factors to the sprite
            sprite.setScale(scaleFactor, scaleFactor);

            // Set the origin of the sprite to its center
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

            // Set the position of the sprite
            sprite.setPosition(sf::Vector2f(300, 300));
        }
    }

    // Set position
    void setPosition(float x, float y)
    {
        sprite.setPosition(sf::Vector2f(x, y));
    }
    void setHealth(int damage)
    {
        health -= damage;
        if (health <= 0)
            health = 0;
    }

    int getHealth() const
    {
        return health;
    }

    // Draw function
    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }
};
class Card // Attack function will be called when two cards intersect with each other(sfml)
{
protected:
    int health, defence, attack;
    time_point<steady_clock> lastUsedTime;
    int cooldownSeconds;
    bool isDestroyed; // Flag to indicate if the card is destroyed
    sf::Sprite sprite;

public:
    Card(int h, int d, int a, int cds = 5) : health(h), defence(d), attack(a), cooldownSeconds(cds) {}

    virtual void AttackEnemy() = 0;
    virtual void TakeDamage(int damage) = 0;

    void setHealth(int health)
    {
        this->health = health;
    }
    int getHealth()
    {
        return health;
    }

    void use()
    {
        if (isDestroyed)
            return;

        auto currentTime = chrono::steady_clock::now();
        auto timeSinceLastUse = currentTime - lastUsedTime;
        auto remainingTime = chrono::seconds(cooldownSeconds) - timeSinceLastUse;

        if (remainingTime.count() <= 0)
        {
            lastUsedTime = currentTime;
            cout << "Using card." << endl;
        }
        else
        {
            cout << "Card is still on cooldown. Remaining time: " << remainingTime.count() << " seconds." << endl;
        }
    }
    void drawSprite(sf::RenderWindow &window)
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
     sf::Texture highAttackTexture;
    // sf::Sprite sprite; // Declare sprite variable
    HighAttack(int h = 100, int d = 5, int a = 10, int cds = 5) : Card(h, d, a, cds)
    {

        
        if (!highAttackTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/barbarians.jpeg"))
        {
            cout << "High Attack sprite not loaded." << endl;
        }
        cout << " High Attack sprite loaded." << endl;
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
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};
class HighDefence : public Card
{
public:
    sf::Texture highDefenceTexture;
    //sf::Sprite sprite; // Declare sprite variable
    HighDefence(int h = 100, int d = 10, int a = 5, int cds = 5) : Card(h, d, a, cds)
    {
        
        if (!highDefenceTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/Giant.jpg"))
        {                                      
            cout << "High Defence sprite not loaded." << endl;
        }
        cout<<"High Defence sprite loaded."<<endl;
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
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};

class Mid : public Card
{
public:
     sf::Texture MidTexture;
    // sf::Sprite sprite; // Declare sprite variable
    Mid(int h = 100, int d = 5, int a = 5, int cds = 5) : Card(h, d, a, cds)
    {

        if (!MidTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/barbarians.jpeg"))
        {
            cout << "Mid sprite not loaded." << endl;
        }
        cout<<"Mid sprite loaded."<<endl;
        sprite.setTexture(MidTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(600, 600));
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
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};
class Legendary : public Card
{
public:
    sf::Texture LegendaryTexture;
    // sf::Sprite sprite; // Declare sprite variable
    Legendary(int h = 100, int d = 20, int a = 20, int cds = 10) : Card(h, d, a, cds)
    {
        
        if (!LegendaryTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/barbarians.jpeg"))
        {
            cout << "Legendary sprite not loaded." << endl;
        }
        cout<<"Legendary sprite loaded."<<endl;
        sprite.setTexture(LegendaryTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(600, 0));
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
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(600, 600), ("Deck Defenders"));

    HighAttack *ha = nullptr;
    HighDefence *hd = nullptr;
    Mid *mid = nullptr;
    Legendary *lg = nullptr;
    Tower PlayerTower;
    Tower EnemyTower;

    int count = 0;

    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    //(half of window width)
    float xMiddle = windowWidth / 2;

    //  (close to the top of the window)
    float yTop = 0;

    // (close to the bottom of the window)
    float yBottom = windowHeight;

    // Set the position of the top middle tower
    EnemyTower.setPosition(xMiddle, yTop);

    // Set the position of the bottom middle tower
    PlayerTower.setPosition(xMiddle, yBottom);

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
                        ha = new HighAttack(5, 5, 10, 5);
                        ha->use();
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (hd == nullptr)
                    {
                        hd = new HighDefence(5, 5, 10, 5);
                        hd->use();
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
                if (event.key.code == sf::Keyboard::E) // sprite not loading!
                {
                    if (mid == nullptr)
                    {
                        mid = new Mid(5, 5, 10, 5);
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    if (lg == nullptr)
                    {
                        lg = new Legendary(5, 5, 10, 5);
                    }
                    // creating an object in this condition is not good, as it gets destroyed after we leave the if block
                }
                // checking if the object goes wheh health is zero
                if (event.key.code == sf::Keyboard::A && ha)
                {
                    ha->setHealth(ha->getHealth() - 1);
                }
                if (event.key.code == sf::Keyboard::S && hd)
                {
                    hd->setHealth(hd->getHealth() - 1);
                }
                if (event.key.code == sf::Keyboard::D && lg)
                {
                    lg->setHealth(lg->getHealth() - 1);
                }
                if (event.key.code == sf::Keyboard::F && mid)
                {
                    mid->setHealth(mid->getHealth() - 1);
                }
                // to delete all objects

                if (ha != nullptr)
                {
                    if (ha->getHealth() == 0)
                    {
                        delete ha;
                        ha = nullptr;
                    }
                }
                if (hd != nullptr)
                {
                    if (hd->getHealth() == 0)
                    {
                        delete hd;
                        hd = nullptr;
                    }
                }
                if (mid != nullptr)
                {
                    if (mid->getHealth() == 0)
                    {
                        delete mid;
                        mid = nullptr;
                    }
                }
                if (lg != nullptr)
                {
                    if (lg->getHealth() == 0)
                    {
                        delete lg;
                        lg = nullptr;
                    }
                }

                if (EnemyTower.getHealth() == 0)
                {
                    cout << "Player won !" << endl;
                    // delete the sprite!
                }
                if (PlayerTower.getHealth() == 0)
                {
                    cout << "Enemy won !" << endl;
                    // delete the sprite!
                }
            }
        }

        window.clear(sf::Color::Yellow);
        EnemyTower.draw(window);
        PlayerTower.draw(window);
        if (ha != nullptr)
            ha->drawSprite(window);
        if (hd != nullptr)
            hd->drawSprite(window);
        if (mid != nullptr)
            mid->drawSprite(window);
        if (lg != nullptr)
            lg->drawSprite(window);
        // if (ha != nullptr && hd != nullptr && mid != nullptr && lg != nullptr)
        // {
        //     count++;
        //     cout << "all \n";
        //     ha->drawSprite(window);
        //     hd->drawSprite(window);
        //     mid->drawSprite(window);
        //     lg->drawSprite(window);
        // }
        // else if (ha != nullptr)
        // {
        //     count++;
        //     cout << "ha \n";
        //     ha->drawSprite(window);
        // }
        // else if (hd != nullptr)
        // {
        //     count++;
        //     cout << "hd \n";
        //     hd->drawSprite(window);
        // }
        // else if (mid != nullptr)
        // {
        //     count++;
        //     cout << "mid \n";
        //     mid->drawSprite(window);
        // }
        // else if (lg != nullptr)
        // {
        //     count++;
        //     cout << "lg \n";
        //     lg->drawSprite(window);
        // }
        window.display();
    }
}