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
    // get sprite
    sf::Sprite getSprite()
    {
        return sprite;
    }

    // Set position
    void setPosition(float x, float y)
    {
        sprite.setPosition(sf::Vector2f(x, y));
    }
    void setHealth(int damage)
    {
        health -= damage;
        cout << health << " ";
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
    // time_point<steady_clock> lastUsedTime;
    int cooldownSeconds;
    bool isDestroyed; // Flag to indicate if the card is destroyed
    sf::Sprite sprite;

public:
    Card(int h, int d, int a, int cds = 5) : health(h), defence(d), attack(a), cooldownSeconds(cds)
    {
    }

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

    void draw(sf::RenderWindow &window)
    {
        if (!isDestroyed)
        {
            window.draw(sprite);
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
    void setInitPos()
    {
        sprite.setPosition(sf::Vector2f(2, 2));
    }
    void move()
    {
        float xpos, ypos;
        xpos = sprite.getPosition().x;
        ypos = sprite.getPosition().y;

        sprite.setPosition(sf::Vector2f(xpos, ypos - 0.2)); // 0.02
    }
    sf::Sprite getSprite()
    {
        return sprite;
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
        sprite.setScale(sf::Vector2f(0.3, 0.3));
        sprite.setPosition(sf::Vector2f(300, 400));
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
    // sf::Sprite sprite; // Declare sprite variable
    HighDefence(int h = 100, int d = 10, int a = 5, int cds = 5) : Card(h, d, a, cds)
    {

        if (!highDefenceTexture.loadFromFile("C:/Users/Administrator/Desktop/game practice/images/Giant.jpg"))
        {
            cout << "High Defence sprite not loaded." << endl;
        }
        cout << "High Defence sprite loaded." << endl;
        sprite.setTexture(highDefenceTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setScale(sf::Vector2f(0.3, 0.3));
        sprite.setPosition(sf::Vector2f(300, 400));
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
        cout << "Mid sprite loaded." << endl;
        sprite.setTexture(MidTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setScale(sf::Vector2f(0.3, 0.3));
        sprite.setPosition(sf::Vector2f(300, 400));
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
        cout << "Legendary sprite loaded." << endl;
        sprite.setTexture(LegendaryTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setScale(sf::Vector2f(0.3, 0.3));
        sprite.setPosition(sf::Vector2f(300, 400));
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

bool coolDown(int coolDownSeconds)
{
    auto currentTime = std::chrono::steady_clock::now();
    static auto startTime = currentTime;
    auto timeSinceLast = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (timeSinceLast < std::chrono::seconds(coolDownSeconds))
    {
        std::cout << "Card is still on cooldown. Remaining time: " << (coolDownSeconds - timeSinceLast.count()) << " seconds." << std::endl;
        return false;
    }
    else
    {
        startTime = currentTime;
        return true;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), ("Deck Defenders"));

    // the max num of each class cards can be 10
    int MaxCardsOfEachType = 10;

    // allocated memory for each class (Max of 10 cards of each type)
    HighAttack **ha = new HighAttack *[MaxCardsOfEachType];
    HighDefence **hd = new HighDefence *[MaxCardsOfEachType];
    Mid **mid = new Mid *[MaxCardsOfEachType];
    Legendary **lg = new Legendary *[MaxCardsOfEachType];

    int haCount = 0;
    int hdCount = 0;
    int midCount = 0;
    int lgCount = 0;

    bool HighAttackMove = true;
    bool HighDefenceMove = true;
    // bool MidMove=true;
    // bool LegendaryMove=true;

    // created two towers objects
    Tower PlayerTower;
    Tower EnemyTower;

    int count = 0;

    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    //(half of window width)
    float xMiddle = windowWidth / 2;

    //  (close to the top of the window)
    float yTop = 70;

    // (close to the bottom of the window)
    float yBottom = windowHeight - 70;

    // Set the position of the top middle tower
    EnemyTower.setPosition(xMiddle, yTop);

    // Set the position of the bottom middle tower
    PlayerTower.setPosition(xMiddle, yBottom);

    int flag = 1;
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
                    if (haCount < MaxCardsOfEachType)
                    {
                        if (flag == 0)
                        {
                            if (coolDown(5) == true)
                            {
                                ha[haCount] = new HighAttack(5, 5, 10, 5);
                                haCount++;
                            }
                        }
                        else
                        {
                            ha[haCount] = new HighAttack(5, 5, 10, 5);
                            haCount++;
                            flag = 0;
                        }
                        // if(ha[haCount]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds())){//check interseciton
                        //     HighAttackMove=false;//flag to indicate stop moving
                        //     EnemyTower.setHealth(10);//10 damage done by highattack for every attack
                        // }
                    }
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    if (hdCount < MaxCardsOfEachType)
                    {
                        if (flag == 0)
                        {
                            if (coolDown(5) == true)
                            {
                                hd[hdCount] = new HighDefence(5, 5, 10, 5);
                                hdCount++;
                            }
                        }
                        else
                        {
                            hd[hdCount] = new HighDefence(5, 5, 10, 5);
                            hdCount++;
                            flag = 0;
                        }
                        //  if(hd[hdCount]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds())){//check interseciton
                        //     HighDefenceMove=false;//flag to indicate to stop moving
                        //     EnemyTower.setHealth(5);//5 damage done by highdefence for every attack
                        // }
                    }
                }
                if (event.key.code == sf::Keyboard::E)
                {
                    if (midCount < MaxCardsOfEachType)
                    {
                        if (flag == 0)
                        {
                            if (coolDown(5) == true)
                            {
                                mid[midCount] = new Mid(5, 5, 10, 5);
                                midCount++;
                            }
                        }
                        else
                        {
                            mid[midCount] = new Mid(5, 5, 10, 5);
                            midCount++;
                            flag = 0;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    if (lgCount < MaxCardsOfEachType)
                    {
                        if (flag == 0)
                        {
                            if (coolDown(10) == true)
                            {
                                lg[lgCount] = new Legendary(5, 5, 10, 5);
                                lgCount++;
                            }
                        }
                        else
                        {
                            lg[lgCount] = new Legendary(5, 5, 10, 5);
                            lgCount++;
                            flag = 0;
                        }
                    }
                }
            }

            // to check for intersection
            for (int i = 0; i <= haCount; i++)
            {
                if (EnemyTower.getSprite().getGlobalBounds().intersects(ha[i]->getSprite().getGlobalBounds()))
                {                            
                    HighAttackMove = false;   // flag to indicate stop moving
                    EnemyTower.setHealth(10); // 10 damage done by highattack for every attack
                }
            }
            // to delete all objects

            for (int i = 0; i < haCount; i++)
            {
                if (ha[i] != nullptr)
                {
                    if (ha[i]->getHealth() == 0)
                    {
                        delete ha[i];
                        ha[i] = nullptr;
                    }
                }
            }
            for (int i = 0; i < hdCount; i++)
            {
                if (hd[i] != nullptr)
                {
                    if (hd[i]->getHealth() == 0)
                    {
                        delete hd[i];
                        hd[i] = nullptr;
                    }
                }
            }
            for (int i = 0; i < midCount; i++)
            {
                if (mid[i] != nullptr)
                {
                    if (mid[i]->getHealth() == 0)
                    {
                        delete mid[i];
                        mid[i] = nullptr;
                    }
                }
            }
            for (int i = 0; i < lgCount; i++)
            {
                if (lg[i] != nullptr)
                {
                    if (lg[i]->getHealth() == 0)
                    {
                        delete lg[i];
                        lg[i] = nullptr;
                    }
                }
            }

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            // {
            //     flag = 1;
            // }
        }

        window.clear();

        bool drawTower = true;
        if (EnemyTower.getHealth() == 0 || PlayerTower.getHealth() == 0)
        {
            drawTower = false;
        }
        // draw all objects
        for (int i = 0; i < haCount; ++i)
        {
            if (ha[i])
            {
                ha[i]->draw(window);
                if (HighAttackMove == true)
                {
                    ha[i]->move();
                }
            }
        }
        for (int i = 0; i < hdCount; ++i)
        {
            if (hd[i])
            {

                hd[i]->draw(window);
                if (HighDefenceMove == true)
                {
                    hd[i]->move();
                }
            }
        }
        for (int i = 0; i < midCount; ++i)
        {
            if (mid[i])
            {
                mid[i]->draw(window);
                mid[i]->move();
            }
        }
        for (int i = 0; i < lgCount; ++i)
        {
            if (lg[i])
            {
                lg[i]->draw(window);
                lg[i]->move();
            }
        }
        if (drawTower == true)
        {
            PlayerTower.draw(window);
            EnemyTower.draw(window);
        }
        else
        {
            cout << endl
                 << "Tower Destroyed. Game Over." << endl;
            // system("pause");
        }

        window.display();
    }

    return 0;
}