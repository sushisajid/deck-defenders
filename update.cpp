#include <iostream>
#include <string>
#include <chrono>
#include <thread> //3rd and 4th libraries are for cooldown
#include <ctime>
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
    Tower(int h = 100) : health(h)
    {
    }
    void setTexture(int num)
    {
        // Load the texture from the file
        if (num == 1)
        { // if num is 1 tou enemy ka texture load ho
            if (!TowerTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/tower.png"))
            {
                std::cout << "Tower sprite not loaded." << std::endl;
            }
            else
            {
                std::cout << " Tower sprite loaded." << std::endl;
                // Set the texture of the sprite
                sprite.setTexture(TowerTexture);
                float scaleFactor = 0.2f; // You can adjust this value as needed

                // Apply the scaling factors to the sprite
                sprite.setScale(scaleFactor, scaleFactor);

                // Set the origin of the sprite to its center
                sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

                // Set the position of the sprite
                sprite.setPosition(sf::Vector2f(300, 300));
            }
        }
        else if (num == 0)
        {
            // Load the texture from the file
            if (!TowerTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/playerTower.jpeg"))
            {
                std::cout << "Tower sprite not loaded." << std::endl;
            }
            else
            {
                std::cout << " Tower sprite loaded." << std::endl;
                // Set the texture of the sprite
                sprite.setTexture(TowerTexture);
                float scaleFactor = 0.2f; // You can adjust this value as needed

                // Apply the scaling factors to the sprite
                sprite.setScale(scaleFactor, scaleFactor);

                // Set the origin of the sprite to its center
                sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

                // Set the position of the sprite
                sprite.setPosition(sf::Vector2f(300, 300));
            }
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
        cout << health << " ";
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
    sf::Sprite getSprite()
    {
        return sprite;
    }
};

// for player
class Card // Attack function will be called when two cards intersect with each other(sfml)
{
protected:
    int health, defence, attack;

    int cooldownSeconds;
    bool isDestroyed; // Flag to indicate if the card is destroyed
    sf::Sprite sprite;
    bool moveFlag = true;

public:
    Card(int h, int d, int a, int cds = 5) : health(h), defence(d), attack(a), cooldownSeconds(cds)
    {
        sprite.setScale(sf::Vector2f(0.1, 0.1));
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

    int getAttack() { return attack; }

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
    sf::Sprite getSprite()
    {
        return sprite;
    }
    virtual void move()
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y - 0.02));
    }

    void setMoveflag(bool flag)
    {

        moveFlag = flag;
    }
    bool getMoveFlag()
    {
        return moveFlag;
    }
};
class HighAttack : public Card
{
public:
    sf::Texture highAttackTexture;
    // sf::Sprite sprite; // Declare sprite variable
    HighAttack(int h = 100, int d = 5, int a = 10, int cds = 5) : Card(h, d, a, cds)
    {

        if (!highAttackTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/highattack.jpeg"))
        {
            cout << "High Attack sprite not loaded." << endl;
        }
        cout << " High Attack sprite loaded." << endl;
        sprite.setTexture(highAttackTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 450));
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y - 0.02));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
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

        if (!highDefenceTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/highdefence.jpeg"))
        {
            cout << "High Defence sprite not loaded." << endl;
        }
        cout << "High Defence sprite loaded." << endl;
        sprite.setTexture(highDefenceTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 450));
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y - 0.007));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
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

        if (!MidTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/mid.jpeg"))
        {
            cout << "Mid sprite not loaded." << endl;
        }
        cout << "Mid sprite loaded." << endl;
        sprite.setTexture(MidTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 450));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y - 0.02));
    }
};
class Legendary : public Card
{
public:
    sf::Texture LegendaryTexture;
    // sf::Sprite sprite; // Declare sprite variable
    Legendary(int h = 100, int d = 20, int a = 20, int cds = 10) : Card(h, d, a, cds)
    {

        if (!LegendaryTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/legendary.jpeg"))
        {
            cout << "Legendary sprite not loaded." << endl;
        }
        cout << "Legendary sprite loaded." << endl;
        sprite.setTexture(LegendaryTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 450));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    void drawSprite(sf::RenderWindow &window)
    {
        Card::drawSprite(window); // Call base class drawSprite
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y - 0.02));
    }
};

// for enemy
class EnemyCard // Attack function will be called when two cards intersect with each other(sfml)
{
protected:
    int health, defence, attack;

    int cooldownSeconds;
    bool isDestroyed; // Flag to indicate if the card is destroyed
    sf::Sprite sprite;
    bool moveFlag = true;

public:
    EnemyCard(int h, int d, int a, int cds = 5) : health(h), defence(d), attack(a), cooldownSeconds(cds)
    {
        sprite.setScale(sf::Vector2f(-0.1, 0.1));
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
    void setMoveflag(bool flag)
    {
        moveFlag = flag;
    }

    int getAttack() { return attack; }

    void draw(sf::RenderWindow &window)
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
    sf::Sprite getSprite()
    {
        return sprite;
    }
    virtual void move()
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y + 0.02));
    }

    bool getMoveFlag()
    {
        return moveFlag;
    }
};
class EnemyHighAttack : public EnemyCard
{
public:
    sf::Texture highAttackTexture;
    // sf::Sprite sprite; // Declare sprite variable
    EnemyHighAttack(int h = 100, int d = 5, int a = 10, int cds = 5) : EnemyCard(h, d, a, cds)
    {

        if (!highAttackTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/highattack.jpeg"))
        {
            cout << "Enemy High Attack sprite not loaded." << endl;
        }
        cout << " High Attack sprite loaded." << endl;
        sprite.setTexture(highAttackTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 150));
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y + 0.02));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    // void drawSprite(sf::RenderWindow &window)
    // {
    //     EnemyCard::drawSprite(window); // Call base class drawSprite
    // }
};
class EnemyHighDefence : public EnemyCard
{
public:
    sf::Texture highDefenceTexture;
    // sf::Sprite sprite; // Declare sprite variable
    EnemyHighDefence(int h = 100, int d = 10, int a = 5, int cds = 5) : EnemyCard(h, d, a, cds)
    {

        if (!highDefenceTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/highdefence.jpeg"))
        {
            cout << "Enemy High Defence sprite not loaded." << endl;
        }
        cout << "High Defence sprite loaded." << endl;
        sprite.setTexture(highDefenceTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 150));
    }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y + 0.007));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    // void drawSprite(sf::RenderWindow &window)
    // {
    //     EnemyCard::drawSprite(window); // Call base class drawSprite
    // }
};
class EnemyMid : public EnemyCard
{
public:
    sf::Texture MidTexture;
    // sf::Sprite sprite; // Declare sprite variable
    EnemyMid(int h = 100, int d = 5, int a = 5, int cds = 5) : EnemyCard(h, d, a, cds)
    {

        if (!MidTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/mid.jpeg"))
        {
            cout << "Enemy Mid sprite not loaded." << endl;
        }
        cout << "Mid sprite loaded." << endl;
        sprite.setTexture(MidTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 150));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    // void drawSprite(sf::RenderWindow &window)
    // {
    //     EnemyCard::drawSprite(window); // Call base class drawSprite
    // }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y + 0.02));
    }
};
class EnemyLegendary : public EnemyCard
{
public:
    sf::Texture LegendaryTexture;
    // sf::Sprite sprite; // Declare sprite variable
    EnemyLegendary(int h = 100, int d = 20, int a = 20, int cds = 10) : EnemyCard(h, d, a, cds)
    {

        if (!LegendaryTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/legendary.jpeg"))
        {
            cout << "Enemy Legendary sprite not loaded." << endl;
        }
        cout << "Legendary sprite loaded." << endl;
        sprite.setTexture(LegendaryTexture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(sf::Vector2f(300, 150));
    }
    void AttackEnemy() {}
    void TakeDamage(int damage)
    {
        int damageTaken = damage - defence;
        if (damageTaken < 0)
            damageTaken = 0; // so it doesnt add up to health.

        health -= damageTaken;
        if (health <= 0)
        {
            health = 0;
        }
    }
    // void drawSprite(sf::RenderWindow &window)
    // {
    //     EnemyCard::drawSprite(window); // Call base class drawSprite
    // }
    void move() override
    {
        float x, y;
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;
        sprite.setPosition(sf::Vector2f(x, y + 0.02));
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

    // PLAYER: allocated memory for each class (Max of 10 cards of each type) for player
    HighAttack **ha = new HighAttack *[MaxCardsOfEachType];
    HighDefence **hd = new HighDefence *[MaxCardsOfEachType];
    Mid **mid = new Mid *[MaxCardsOfEachType];
    Legendary **lg = new Legendary *[MaxCardsOfEachType];
    int haCount = 0;
    int hdCount = 0;
    int midCount = 0;
    int lgCount = 0;

    // ENEMY: allocated memory for each class (Max of 10 cards of each type) for enemy also
    srand(time(nullptr));
    EnemyHighAttack **Eha = new EnemyHighAttack *[MaxCardsOfEachType];
    EnemyHighDefence **Ehd = new EnemyHighDefence *[MaxCardsOfEachType];
    EnemyMid **Emid = new EnemyMid *[MaxCardsOfEachType];
    EnemyLegendary **Elg = new EnemyLegendary *[MaxCardsOfEachType];
    int eHaCount = 0;
    int eHdCount = 0;
    int eMidCount = 0;
    int eLgCount = 0;
    int random = 0;
    int enemySpawnFlag = 0;

    // created two towers objects
    Tower PlayerTower;
    Tower EnemyTower;
    PlayerTower.setTexture(0);
    EnemyTower.setTexture(1);

    int count = 0;

    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    //(half of window width)
    float xMiddle = windowWidth / 2;

    //  (close to the top of the window)
    float yTop = 50;

    // (close to the bottom of the window)
    float yBottom = windowHeight - 50;

    // Set the position of the top middle tower
    EnemyTower.setPosition(xMiddle, yTop);

    // Set the position of the bottom middle tower
    PlayerTower.setPosition(xMiddle, yBottom);

    // background setup
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/background.jpeg"))
    {
        cout << "Background not loaded" << endl;
    }
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    int flag = 1; // cooldown wala; to make sure that there isnt a cooldown timer before the first card
    int haCheck = 0;
    int hdCheck = 0;
    int midCheck = 0;
    int lgCheck = 0;

    int EhaCheck = 0;
    int EhdCheck = 0;
    int EmidCheck = 0;
    int ElgCheck = 0;
    sf::Texture loadingScreenTexture;
    sf::Sprite loadingScreen;
    if (!loadingScreenTexture.loadFromFile("C:/Users/Muntaha/OneDrive/Desktop/Semester 2/OOP/project/start.jpeg"))
    {
        cout << "Loading screen not loaded" << endl;
    }
    else
    {
        loadingScreen.setTexture(loadingScreenTexture);
    }
    window.draw(loadingScreen);
    cout << "Loading screen drawn" << endl;
    window.display();
    // sleep(3);
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
                                ha[haCount] = new HighAttack(100, 5, 15, 5);
                                haCount++;
                                enemySpawnFlag += 1;
                            }
                        }
                        else
                        {
                            ha[haCount] = new HighAttack(100, 5, 15, 5);
                            haCount++;
                            flag = 0;
                            enemySpawnFlag += 1;
                        }
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
                                hd[hdCount] = new HighDefence(100, 7, 10, 5);
                                hdCount++;
                                enemySpawnFlag += 1;
                            }
                        }
                        else
                        {
                            hd[hdCount] = new HighDefence(100, 7, 10, 5);
                            hdCount++;
                            flag = 0;
                            enemySpawnFlag += 1;
                        }
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
                                mid[midCount] = new Mid(100, 6, 8, 5);
                                midCount++;
                                enemySpawnFlag += 1;
                            }
                        }
                        else
                        {
                            mid[midCount] = new Mid(100, 6, 8, 5);
                            midCount++;
                            flag = 0;
                            enemySpawnFlag += 1;
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
                                lg[lgCount] = new Legendary(100, 10, 17, 5);
                                lgCount++;
                                enemySpawnFlag += 1;
                            }
                        }
                        else
                        {
                            lg[lgCount] = new Legendary(100, 10, 17, 5);
                            lgCount++;
                            flag = 0;
                            enemySpawnFlag += 1;
                        }
                    }
                }
                // enemy spawn

                cout << "EnemySpawnFlag: " << enemySpawnFlag << endl;
                // for enemy
                if (enemySpawnFlag % 2 == 0)
                {
                    // random = 4;
                    random = (rand() % 4) + 1; // random generation between 1 and 4

                    if (random == 1)
                    {
                        if (eHaCount < MaxCardsOfEachType)
                        {
                            Eha[eHaCount] = new EnemyHighAttack(100, 5, 15, 5);
                            eHaCount++;
                        }
                    }
                    else if (random == 2)
                    {
                        if (eHdCount < MaxCardsOfEachType)
                        {
                            Ehd[eHdCount] = new EnemyHighDefence(100, 7, 10, 5);
                            eHdCount++;
                        }
                    }
                    else if (random == 3)
                    {
                        if (eMidCount < MaxCardsOfEachType)
                        {
                            Emid[eMidCount] = new EnemyMid(100, 6, 8, 5);
                            eMidCount++;
                        }
                    }
                    else if (random == 4)
                    {
                        if (eLgCount < MaxCardsOfEachType)
                        {
                            Elg[eLgCount] = new EnemyLegendary(100, 10, 17, 5);
                            eLgCount++;
                        }
                    }
                }
            }
        }
        // card interactions

        // for highAttack
        for (int i = 0; i < haCount; i++)
        {
            for (int j = 0; j < eHaCount; j++)
            {
                if (ha[i]->getSprite().getGlobalBounds().intersects(Eha[j]->getSprite().getGlobalBounds()))
                {
                    ha[i]->setMoveflag(false);
                    Eha[j]->setMoveflag(false);
                    Eha[j]->TakeDamage(ha[i]->getAttack());
                    ha[i]->TakeDamage(Eha[j]->getAttack());
                    cout << "Player card health: " << ha[i]->getHealth() << endl;
                    cout << "Enemy Card Health: " << Eha[i]->getHealth() << endl;
                    haCheck = 1;
                    EhaCheck = 1;
                }
                haCheck = 0;
                EhaCheck = 0;
                if (EhaCheck == 0)
                {
                    Eha[j]->setMoveflag(true);
                }
                if (haCheck == 0)
                {
                    ha[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eHdCount; j++)
            {
                if (ha[i]->getSprite().getGlobalBounds().intersects(Ehd[j]->getSprite().getGlobalBounds()))
                {
                    ha[i]->setMoveflag(false);
                    Ehd[j]->setMoveflag(false);
                    Ehd[j]->TakeDamage(ha[i]->getAttack());
                    ha[i]->TakeDamage(Ehd[j]->getAttack());
                    cout << "Player card health: " << ha[i]->getHealth() << endl;
                    cout << "Enemy Card Health: " << Ehd[i]->getHealth() << endl;
                    haCheck = 1;
                    EhdCheck = 1;
                }
                haCheck = 0;
                EhdCheck = 0;
                if (EhdCheck == 0)
                {
                    Ehd[j]->setMoveflag(true);
                }

                if (haCheck == 0)
                {
                    ha[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eMidCount; j++)
            {
                if (ha[i]->getSprite().getGlobalBounds().intersects(Emid[j]->getSprite().getGlobalBounds()))
                {
                    ha[i]->setMoveflag(false);
                    Emid[j]->setMoveflag(false);
                    Emid[j]->TakeDamage(ha[i]->getAttack());
                    ha[i]->TakeDamage(Emid[j]->getAttack());
                    cout << "Player card health: " << ha[i]->getHealth() << endl;
                    haCheck = 1;
                    EmidCheck = 1;
                }
                haCheck = 0;
                EmidCheck = 0;
                if (EmidCheck == 0)
                {
                    Emid[j]->setMoveflag(true);
                }
                if (haCheck == 0)
                {
                    ha[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eLgCount; j++)
            {
                if (ha[i]->getSprite().getGlobalBounds().intersects(Elg[j]->getSprite().getGlobalBounds()))
                {
                    ha[i]->setMoveflag(false);
                    Elg[j]->setMoveflag(false);
                    Elg[j]->TakeDamage(ha[i]->getAttack());
                    ha[i]->TakeDamage(Elg[j]->getAttack());
                    cout << "Player card health: " << ha[i]->getHealth() << endl;
                    haCheck = 1;
                    ElgCheck = 1;
                }

                ElgCheck = 0;
                haCheck = 0;
                if (ElgCheck == 0)
                {
                    Elg[j]->setMoveflag(true);
                }
                if (haCheck == 0)
                {
                    ha[i]->setMoveflag(true);
                }
            }
        }

        // for highDefence
        for (int i = 0; i < hdCount; i++)
        {
            for (int j = 0; j < eHaCount; j++)
            {
                if (hd[i]->getSprite().getGlobalBounds().intersects(Eha[j]->getSprite().getGlobalBounds()))
                {
                    hd[i]->setMoveflag(false);
                    Eha[j]->setMoveflag(false);
                    hd[i]->TakeDamage(Eha[j]->getAttack());
                    Eha[j]->TakeDamage(hd[i]->getAttack());
                    cout << "Player card health: " << hd[i]->getHealth() << endl;
                    hdCheck = 1;
                    EhaCheck = 1;
                }
                hdCheck = 0;
                EhaCheck = 0;
                if (hdCheck == 0)
                {
                    hd[i]->setMoveflag(true);
                }
                if (EhaCheck == 0)
                {
                    Eha[j]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eHdCount; j++)
            {
                if (hd[i]->getSprite().getGlobalBounds().intersects(Ehd[j]->getSprite().getGlobalBounds()))
                {
                    hd[i]->setMoveflag(false);
                    Ehd[j]->setMoveflag(false);
                    hd[i]->TakeDamage(Ehd[j]->getAttack());
                    Ehd[j]->TakeDamage(hd[i]->getAttack());
                    cout << "Player card health: " << hd[i]->getHealth() << endl;
                    // cout << " Card damage is 0"; // this is working
                    hdCheck = 1;
                    EhdCheck = 1;
                }
                hdCheck = 0;
                EhdCheck = 0;
                if (EhdCheck == 0)
                {
                    Ehd[j]->setMoveflag(true);
                }
                if (hdCheck == 0)
                {
                    hd[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eMidCount; j++)
            {
                if (hd[i]->getSprite().getGlobalBounds().intersects(Emid[j]->getSprite().getGlobalBounds()))
                {
                    hd[i]->setMoveflag(false);
                    Emid[j]->setMoveflag(false);
                    hd[i]->TakeDamage(Emid[j]->getAttack());
                    Emid[j]->TakeDamage(hd[i]->getAttack());
                    cout << "Player card health: " << hd[i]->getHealth() << endl;
                    hdCheck = 1;
                    EmidCheck = 1;
                }
                hdCheck = 0;
                EmidCheck = 0;
                if (EmidCheck == 0)
                {
                    Emid[j]->setMoveflag(true);
                }
                if (hdCheck == 0)
                {
                    hd[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eLgCount; j++)
            {
                if (hd[i]->getSprite().getGlobalBounds().intersects(Elg[j]->getSprite().getGlobalBounds()))
                {
                    hd[i]->setMoveflag(false);
                    Elg[j]->setMoveflag(false);
                    hd[i]->TakeDamage(Elg[j]->getAttack());
                    Elg[j]->TakeDamage(hd[i]->getAttack());
                    cout << "Player card health: " << hd[i]->getHealth() << endl;
                    hdCheck = 1;
                    ElgCheck = 1;
                }
                hdCheck = 0;
                ElgCheck = 0;

                if (hdCheck == 0)
                {
                    hd[i]->setMoveflag(true);
                }

                if (ElgCheck == 0)
                {
                    Elg[j]->setMoveflag(true);
                }
            }
        }

        // for mid
        for (int i = 0; i < midCount; i++)
        {
            for (int j = 0; j < eHaCount; j++)
            {
                if (mid[i]->getSprite().getGlobalBounds().intersects(Eha[j]->getSprite().getGlobalBounds()))
                {
                    mid[i]->setMoveflag(false);
                    Eha[j]->setMoveflag(false);
                    mid[i]->TakeDamage(Eha[j]->getAttack());
                    Eha[j]->TakeDamage(mid[i]->getAttack());
                    cout << "Player card health: " << mid[i]->getHealth() << endl;
                    midCheck = 1;
                    EhaCheck = 1;
                }
                midCheck = 0;
                EhaCheck = 0;
                if (EhaCheck == 0)
                {
                    Eha[j]->setMoveflag(true);
                }
                if (midCheck == 0)
                {
                    mid[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eHdCount; j++)
            {
                if (mid[i]->getSprite().getGlobalBounds().intersects(Ehd[j]->getSprite().getGlobalBounds()))
                {
                    mid[i]->setMoveflag(false);
                    Ehd[j]->setMoveflag(false);
                    mid[i]->TakeDamage(Ehd[j]->getAttack());
                    Ehd[j]->TakeDamage(mid[i]->getAttack());
                    cout << "Player card health: " << mid[i]->getHealth() << endl;
                    cout << " Card damage is 0"; // this is working
                    midCheck = 1;
                    EhdCheck = 1;
                }
                midCheck = 0;
                EhdCheck = 0;
                if (EhdCheck == 0)
                {
                    Ehd[j]->setMoveflag(true);
                }
                if (midCheck == 0)
                {
                    mid[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eMidCount; j++)
            {
                if (mid[i]->getSprite().getGlobalBounds().intersects(Emid[j]->getSprite().getGlobalBounds()))
                {
                    mid[i]->setMoveflag(false);
                    Emid[j]->setMoveflag(false);
                    mid[i]->TakeDamage(Emid[j]->getAttack());
                    Emid[j]->TakeDamage(mid[i]->getAttack());
                    cout << "Player card health: " << mid[i]->getHealth() << endl;

                    midCheck = 1;
                    EmidCheck = 1;
                }
                midCheck = 0;
                EmidCheck = 0;
                if (EmidCheck == 0)
                {
                    Emid[j]->setMoveflag(true);
                }
                if (midCheck == 0)
                {
                    mid[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eLgCount; j++)
            {
                if (mid[i]->getSprite().getGlobalBounds().intersects(Elg[j]->getSprite().getGlobalBounds()))
                {
                    mid[i]->setMoveflag(false);
                    Elg[j]->setMoveflag(false);
                    mid[i]->TakeDamage(Elg[j]->getAttack());
                    Elg[j]->TakeDamage(mid[i]->getAttack());
                    cout << "Player card health: " << mid[i]->getHealth() << endl;
                    midCheck = 1;
                    ElgCheck = 1;
                }
                midCheck = 0;
                ElgCheck = 0;
                if (ElgCheck == 0)
                {
                    Elg[j]->setMoveflag(true);
                }
                if (midCheck == 0)
                {
                    mid[i]->setMoveflag(true);
                }
            }
        }

        // for legendary
        for (int i = 0; i < lgCount; i++)
        {
            for (int j = 0; j < eHaCount; j++)
            {
                if (lg[i]->getSprite().getGlobalBounds().intersects(Eha[j]->getSprite().getGlobalBounds()))
                {
                    lg[i]->setMoveflag(false);
                    Eha[j]->setMoveflag(false);
                    lg[i]->TakeDamage(Eha[i]->getAttack());
                    Eha[j]->TakeDamage(lg[i]->getAttack());
                    cout << "Player card health: " << lg[i]->getHealth() << endl;
                    lgCheck = 1;
                    EhaCheck = 1;
                }
                lgCheck = 0;
                EhaCheck = 0;
                if (EhaCheck == 0)
                {
                    Eha[j]->setMoveflag(true);
                }
                if (lgCheck == 0)
                {
                    lg[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eHdCount; j++)
            {
                if (lg[i]->getSprite().getGlobalBounds().intersects(Ehd[j]->getSprite().getGlobalBounds()))
                {
                    lg[i]->setMoveflag(false);
                    Ehd[j]->setMoveflag(false);
                    lg[i]->TakeDamage(Ehd[j]->getAttack());
                    Ehd[j]->TakeDamage(lg[i]->getAttack());
                    cout << "Player card health: " << lg[i]->getHealth() << endl;
                    cout << " Card damage is 0"; // this is working
                    lgCheck = 1;
                    EhdCheck = 1;
                }
                lgCheck = 0;
                EhdCheck = 0;
                if (EhdCheck == 0)
                {
                    Ehd[j]->setMoveflag(true);
                }
                if (lgCheck == 0)
                {
                    lg[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eMidCount; j++)
            {
                if (lg[i]->getSprite().getGlobalBounds().intersects(Emid[j]->getSprite().getGlobalBounds()))
                {
                    lg[i]->setMoveflag(false);
                    Emid[j]->setMoveflag(false);
                    lg[i]->TakeDamage(Emid[j]->getAttack());
                    Emid[j]->TakeDamage(lg[i]->getAttack());
                    cout << "Player card health: " << lg[i]->getHealth() << endl;
                    lgCheck = 1;
                    EmidCheck = 1;
                }
                lgCheck = 0;
                EmidCheck = 0;
                if (EmidCheck == 0)
                {
                    Emid[j]->setMoveflag(true);
                }
                if (lgCheck == 0)
                {
                    lg[i]->setMoveflag(true);
                }
            }
            for (int j = 0; j < eLgCount; j++)
            {
                if (lg[i]->getSprite().getGlobalBounds().intersects(Elg[j]->getSprite().getGlobalBounds()))
                {
                    lg[i]->setMoveflag(false);
                    Elg[j]->setMoveflag(false);
                    lg[i]->TakeDamage(Elg[i]->getAttack());
                    Elg[j]->TakeDamage(lg[i]->getAttack());
                    cout << "Player card health: " << lg[i]->getHealth() << endl;
                    lgCheck = 1;
                    ElgCheck = 1;
                }
                lgCheck = 0;
                ElgCheck = 0;
                if (ElgCheck == 0)
                {
                    Elg[j]->setMoveflag(true);
                }
                if (haCheck == 0)
                {
                    ha[i]->setMoveflag(true);
                }
            }
        }

        // to delete all objects

        // for player
        // deleting cards that are dead
        for (int i = 0; i < haCount; i++)
        {
            if (ha[i] != nullptr && ha[i]->getHealth() == 0)
            {
                for (int j = i; j < haCount - 1; j++)
                {
                    ha[j] = ha[j + 1];
                }
                ha[haCount - 1] = nullptr;
                cout << "Player Card Dead" << endl;
                haCount--;
            }
        }
        for (int i = 0; i < hdCount; i++)
        {
            if (hd[i] != nullptr && hd[i]->getHealth() == 0)
            {
                for (int j = i; j < hdCount - 1; j++)
                {
                    hd[j] = hd[j + 1];
                }
                hd[hdCount - 1] = nullptr;
                cout << "Card Dead" << endl;
                hdCount--;
            }
        }
        for (int i = 0; i < midCount; i++)
        {
            if (mid[i] != nullptr && mid[i]->getHealth() == 0)
            {
                for (int j = i; j < midCount - 1; j++)
                {
                    mid[j] = mid[j + 1];
                }
                mid[midCount - 1] = nullptr;
                cout << "Card Dead" << endl;
                midCount--;
            }
        }
        for (int i = 0; i < lgCount; i++)
        {
            if (lg[i] != nullptr && lg[i]->getHealth() == 0)
            {
                for (int j = i; j < lgCount - 1; j++)
                {
                    lg[j] = lg[j + 1];
                }
                lg[lgCount - 1] = nullptr;
                cout << "Card Dead" << endl;
                lgCount--;
            }
        }
        // for enemy
        for (int i = 0; i < eHaCount; i++)
        {
            if (Eha[i] != nullptr && Eha[i]->getHealth() == 0)
            {
                for (int j = i; j < eHaCount - 1; j++)
                {
                    Eha[j] = Eha[j + 1];
                }
                Eha[eHaCount - 1] = nullptr;
                eHaCount--;
            }
        }
        for (int i = 0; i < eHdCount; i++)
        {
            if (Ehd[i] != nullptr && Ehd[i]->getHealth() == 0)
            {
                for (int j = i; j < eHdCount - 1; j++)
                {
                    Ehd[j] = Ehd[j + 1];
                }
                Ehd[eHdCount - 1] = nullptr;
                cout << "Enemy Card dead.";
                eHdCount--;
            }
        }
        for (int i = 0; i < eMidCount; i++)
        {
            if (Emid[i] != nullptr && Emid[i]->getHealth() == 0)
            {
                for (int j = i; j < eMidCount - 1; j++)
                {
                    Emid[j] = Emid[j + 1];
                }
                Emid[eMidCount - 1] = nullptr;
                cout << "Card deleted";
                eMidCount--;
            }
        }
        for (int i = 0; i < eLgCount; i++)
        {
            if (Elg[i] != nullptr && Elg[i]->getHealth() == 0)
            {
                for (int j = i; j < eLgCount - 1; j++)
                {
                    Elg[j] = Elg[j + 1];
                }
                Elg[eLgCount - 1] = nullptr;
                eLgCount--;
            }
        }

        // checking intersection with enemy tower for all objects and decreasing tower health
        bool EnemytowerAlive = true;
        bool PlayerTowerAlive = true;
        for (int i = 0; i < haCount; i++)
        {
            if (ha[i]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds()))
            {
                ha[i]->setMoveflag(false);
                EnemyTower.setHealth(10);

                if (EnemyTower.getHealth() == 0)
                {
                    EnemytowerAlive = false;
                }
            }
        }
        for (int i = 0; i < hdCount; i++)
        {
            if (hd[i]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds()))
            {
                hd[i]->setMoveflag(false);
                EnemyTower.setHealth(10);

                if (EnemyTower.getHealth() == 0)
                {
                    EnemytowerAlive = false;
                }
            }
        }
        for (int i = 0; i < midCount; i++)
        {
            if (mid[i]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds()))
            {
                mid[i]->setMoveflag(false);
                EnemyTower.setHealth(10);

                if (EnemyTower.getHealth() == 0)
                {
                    EnemytowerAlive = false;
                }
            }
        }
        for (int i = 0; i < lgCount; i++)
        {
            if (lg[i]->getSprite().getGlobalBounds().intersects(EnemyTower.getSprite().getGlobalBounds()))
            {
                lg[i]->setMoveflag(false);
                EnemyTower.setHealth(10);

                if (EnemyTower.getHealth() == 0)
                {
                    EnemytowerAlive = false;
                }
            }
        }

        // checking enemy troops intersection with tower
        for (int i = 0; i < eHaCount; i++)
        {
            if (Eha[i]->getSprite().getGlobalBounds().intersects(PlayerTower.getSprite().getGlobalBounds()))
            {
                Eha[i]->setMoveflag(false);
                PlayerTower.setHealth(10);

                if (PlayerTower.getHealth() == 0)
                {
                    PlayerTowerAlive = false;
                }
            }
        }
        for (int i = 0; i < eHdCount; i++)
        {
            if (Ehd[i]->getSprite().getGlobalBounds().intersects(PlayerTower.getSprite().getGlobalBounds()))
            {
                Ehd[i]->setMoveflag(false);
                PlayerTower.setHealth(10);

                if (PlayerTower.getHealth() == 0)
                {
                    PlayerTowerAlive = false;
                }
            }
        }
        for (int i = 0; i < eHaCount; i++)
        {
            if (Eha[i]->getSprite().getGlobalBounds().intersects(PlayerTower.getSprite().getGlobalBounds()))
            {
                Eha[i]->setMoveflag(false);
                PlayerTower.setHealth(10);

                if (PlayerTower.getHealth() == 0)
                {
                    PlayerTowerAlive = false;
                }
            }
        }
        for (int i = 0; i < eMidCount; i++)
        {
            if (Emid[i]->getSprite().getGlobalBounds().intersects(PlayerTower.getSprite().getGlobalBounds()))
            {
                Emid[i]->setMoveflag(false);
                PlayerTower.setHealth(10);

                if (PlayerTower.getHealth() == 0)
                {
                    PlayerTowerAlive = false;
                }
            }
        }
        for (int i = 0; i < eLgCount; i++)
        {
            if (Elg[i]->getSprite().getGlobalBounds().intersects(PlayerTower.getSprite().getGlobalBounds()))
            {
                Elg[i]->setMoveflag(false);
                PlayerTower.setHealth(10);

                if (PlayerTower.getHealth() == 0)
                {
                    PlayerTowerAlive = false;
                }
            }
        }

        window.clear();
        window.draw(background);

        // draw all objects

        // for player
        for (int i = 0; i < haCount; ++i)
        {
            if (ha[i] != nullptr)
            {
                ha[i]->draw(window);
                if (ha[i]->getMoveFlag())
                {
                    ha[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < hdCount; ++i)
        {
            if (hd[i] != nullptr)
            {
                hd[i]->draw(window);
                if (hd[i]->getMoveFlag())
                {
                    hd[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < midCount; ++i)
        {
            if (mid[i] != nullptr)
            {
                mid[i]->draw(window);
                if (mid[i]->getMoveFlag())
                {
                    mid[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < lgCount; ++i)
        {
            if (lg[i] != nullptr)
            {
                lg[i]->draw(window);
                if (lg[i]->getMoveFlag())
                {
                    lg[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        // for enemy
        for (int i = 0; i < eHaCount; ++i)
        {
            if (Eha[i] != nullptr)
            {
                // cout<<"Andar arha hai"<<endl;
                Eha[i]->draw(window);
                if (Eha[i]->getMoveFlag())
                {
                    Eha[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < eHdCount; ++i)
        {
            if (Ehd[i] != nullptr)
            {
                Ehd[i]->draw(window);
                if (Ehd[i]->getMoveFlag())
                {
                    Ehd[i]->move();
                }
            }
            else
            {

                cout << "Andar arha hai" << endl;
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < eMidCount; ++i)
        {
            if (Emid[i] != nullptr)
            {
                // cout<<"Andar arha hai"<<endl;
                Emid[i]->draw(window);
                if (Emid[i]->getMoveFlag())
                {
                    Emid[i]->move();
                }
            }
            else
            {
                cout << "Card sprite not being drawn." << endl;
            }
        }
        for (int i = 0; i < eLgCount; ++i)
        {
            if (Elg[i] != nullptr)
            {
                // cout<<"Andar arha hai"<<endl;
                Elg[i]->draw(window);
                if (Elg[i]->getMoveFlag())
                {
                    Elg[i]->move();
                }
            }
            else
            {
            }
        }

        // for towers
        if (PlayerTowerAlive)
        {
            PlayerTower.draw(window);
        }
        else
        {
            cout << "YOU LOST :(  ";
        }
        if (EnemytowerAlive)
        {
            EnemyTower.draw(window);
        }
        else
        {
            cout << "Enemy Tower Destroyed. YOU WIN  ";
            break;
            /*each of the three lines commented below ae used to "hault" the program but mere pas sahi nhi chal rhe so try each
            of these lines individually on ur pc and lmk which one works*/

            // this_thread::sleep_for(seconds(5));
            //  system("pause");
            //  cin.get()
        }

        window.display();
    }

    return 0;
}