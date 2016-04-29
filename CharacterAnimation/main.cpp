#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

#define DEBUG 1
#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif // DEBUG

// Main Window
sf::RenderWindow window;

sf::Texture texture;
sf::Sprite sprite(texture);
sf::RectangleShape background(sf::Vector2f(WIDTH, HEIGHT));
enum Directions {Down, Left, Right, Up};
sf::Vector2i source(0, Left);   // Direction
sf::Time deltaTime;
float timer = 0.0f;
bool isMovingUp = false;        // gotta be a better way
bool isMovingDown = false;
bool isMovingRight = false;
bool isMovingLeft = false;
float x = 100.0f, y = 100.0f;   // use vector
float velX = 100.0f;        //use vector
float velY = 100.0f;


void setup(){
    // Initialize Main Window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "My First SFML Game",
                  sf::Style::Titlebar | sf::Style::Close);
    if (texture.loadFromFile("SpriteSheet.png"))
        sprite.setTexture(texture, true);
    background.setFillColor(sf::Color(255, 255, 255));
}

void update(){
    // Draw the sprite
    sprite.setPosition(x, y);
    sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 48, 32, 48));
    window.draw(sprite);
    timer += deltaTime.asSeconds();
    if (timer >= 0.1){
        if (isMovingUp || isMovingDown || isMovingLeft || isMovingRight)
            source.x++;
        timer = 0;
    }
    if (source.x * 32 >= texture.getSize().x)
        source.x = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            isMovingUp = true;
            //LOG("UP")
    }else{
        isMovingUp = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            isMovingDown = true;
            //LOG("Down")
    }else{
        isMovingDown = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            isMovingRight = true;
            //LOG("Right")
    }else{
        isMovingRight = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            isMovingLeft = true;
            //LOG("Left")
    }else{
        isMovingLeft = false;
    }
    if (isMovingDown){
        source.y = Down;
        y += velY * deltaTime.asSeconds();
        isMovingLeft = false;
        isMovingRight = false;
        isMovingUp = false;
    }else if (isMovingUp){
        source.y = Up;
        y -= velY * deltaTime.asSeconds();
        isMovingLeft = false;
        isMovingRight = false;
        isMovingDown = false;
    }else if (isMovingLeft){
        source.y = Left;
        x -= velX * deltaTime.asSeconds();
        isMovingUp = false;
        isMovingRight = false;
        isMovingDown = false;
    }else if (isMovingRight){
        source.y = Right;
        x += velX * deltaTime.asSeconds();
        isMovingLeft = false;
        isMovingUp = false;
        isMovingDown = false;
    }
    if (!(isMovingDown || isMovingLeft || isMovingRight || isMovingUp))
        source.x = 0;

    if (y <= 0){
        y = 0;

    }
    if (x <= 0)
        x = 0;
    if (y >= HEIGHT-48)
        y = HEIGHT-48;
    if (x >= WIDTH-32)
        x = WIDTH-32;
}

int main()
{
    setup();
    // create a clock which will help us keep time and passage of time
    sf::Clock clock;
	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                /*case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up){
                        source.y = Up;
                        LOG("Up")
                    }
                    else if (event.key.code == sf::Keyboard::Down){
                        source.y = Down;
                        LOG("Down")
                    }
                    else if (event.key.code == sf::Keyboard::Right){
                        source.y = Right;
                        LOG("Right");
                    }
                    else if (event.key.code == sf::Keyboard::Left){
                        source.y = Left;
                        LOG("Left")
                    }
                    break;*/
            }

        }

        // clock and delta time
        deltaTime = clock.restart();
        // Clear screen
        window.clear();
        window.draw(background);
        update();
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
