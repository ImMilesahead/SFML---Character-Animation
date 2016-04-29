#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDTH 800
#define HEIGHT 600


// This is a macro used for debugging code in an easier way
#define DEBUG 0
#if DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif // DEBUG

// Main Window
sf::RenderWindow window;
sf::Texture spriteSheet;    // spritesheet for the character
sf::Sprite character(spriteSheet);     //actual sprite to be drawn to the screen
sf::RectangleShape background(sf::Vector2f(WIDTH, HEIGHT));     // background to be drawn first
enum Directions {Down, Left, Right, Up};    // directions to tell the character what way to face
sf::Vector2i source(0, Left);   // Direction the character is facing and where along the
                                //walking animation they are
sf::Time deltaTime;     // time inbetween frames
float timer = 0.0f;     // timer to be used for timing things
bool isMovingUp = false;        // gotta be a better way
bool isMovingDown = false;      // see if those keys are pressed down
bool isMovingRight = false;     // and if the player is moving in that direction
bool isMovingLeft = false;      // used for determining which sprite to show
// Use Vectors here
float x = 100.0f;   // characters x coorident
float y = 100.0f;   // character's Y coorident
float velX = 100.0f;    // character's velocity in the X direction in pixels per second
float velY = 100.0f;    // character's velocity in the Y direction in pixels per second

int cWidth = 32;        // character's width
int cHeight = 48;       // character's height

void setup(){
    // Initialize Main Window
    window.create(sf::VideoMode(WIDTH, HEIGHT), "My First SFML Game",
                  sf::Style::Titlebar | sf::Style::Close);
    if (spriteSheet.loadFromFile("SpriteSheet.png"))
        character.setTexture(spriteSheet, true);
    background.setFillColor(sf::Color(255, 255, 255));
}

void update(){
    // increase the timer
    timer += deltaTime.asSeconds();

    // limit the walking animation so it does not go to fast or slow
    if (timer >= 0.1){
        if (isMovingUp || isMovingDown || isMovingLeft || isMovingRight)
            source.x++;
        timer = 0;
    }
    // restart the walking animation
    if (source.x * cWidth >= spriteSheet.getSize().x)
        source.x = 0;


    // see what keys are being pressed and toggle the corisponding flags
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

    // Using this to make sure the direction the character is moving
    // is always the direction the sprite is facing
    // and to make it only go one direction at a time - no diagonal
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

    // reset the walking animation if we are not moving
    if (!(isMovingDown || isMovingLeft || isMovingRight || isMovingUp))
        source.x = 0;

    // Boundries
    if (y <= 0)
        y = 0;
    if (x <= 0)
        x = 0;
    if (y >= HEIGHT-cHeight)
        y = HEIGHT-cHeight;
    if (x >= WIDTH-cWidth)
        x = WIDTH-cWidth;

    // Draw the sprite
    character.setPosition(x, y);
    character.setTextureRect(sf::IntRect(source.x * cWidth, source.y * cHeight, cWidth, cHeight));
    window.draw(character);
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
