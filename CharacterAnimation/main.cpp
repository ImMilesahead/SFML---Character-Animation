#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 600

class Character{
private:
    float timer = 0.0f;
    float animSpeed = 0.05f;
    int top, left, right, bottom;
    enum Directions {Up, Left, Down, Right};
    sf::RenderWindow *window;
    sf::Time *deltaTime;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2i size;
    sf::Texture spriteSheet;
    sf::Sprite character;
    sf::Vector2i source;
public:
    Character(sf::RenderWindow *window, sf::Time *deltaTime){
        if (spriteSheet.loadFromFile("spritesheet.png"))
        character.setTexture(spriteSheet, true);
        this -> window = window;
        this -> deltaTime = deltaTime;
        source = sf::Vector2i(0, Left);
        position = sf::Vector2f(75.0f, 75.0f);
        size = sf::Vector2i(64, 64);
        character.setTexture(spriteSheet);
        velocity = sf::Vector2f(100.0f, 100.0f);
    }
    void animate(){
        if (source.x * size.x >= spriteSheet.getSize().x)
            source.x = 0;       // restart the walking animation
        bool moving = true;     // see what keys are being pressed and move accordingly
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            source.y = Up;
            position.y -= velocity.y * (*deltaTime).asSeconds();
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            source.y = Down;
            position.y += velocity.y * (*deltaTime).asSeconds();
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            source.y = Right;
            position.x += velocity.x * (*deltaTime).asSeconds();
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            source.y = Left;
            position.x -= velocity.x * (*deltaTime).asSeconds();
        }else{
            moving = false;
        }
        timer += (*deltaTime).asSeconds();  // increase the timer
        if (timer >= animSpeed){    // limit the walking animation so it does not go to fast or slow
            if (moving)
                source.x++;
            timer = 0;
        }
        if (!moving)        // reset the walking animation if we are not moving
            source.x = 0;
        if (position.y <= 0)        // Check Boundries
            position.y = 0;
        else if (position.y >= HEIGHT-size.y)
            position.y = HEIGHT-size.y;
        if (position.x <= 0)
            position.x = 0;
        else if (position.x >= WIDTH-size.x)
            position.x = WIDTH-size.x;
        character.setPosition(position.x, position.y);      // Set the sprite's position
        character.setTextureRect(sf::IntRect(source.x * size.x, source.y * size.y, size.x, size.y));        // Select which sprite from the sprite sheet we will be using
        (*window).draw(character);      // Draw the sprite
    }
    void update(){
        this -> animate();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My First SFML Game", sf::Style::Titlebar | sf::Style::None);     // Create and initialize the main window
    sf::Time deltaTime;     // Create a time object to hold a value of time between frames
    sf::Clock clock;       // Create a clock for us to keep track of the time between frames
    Character character(&window, &deltaTime);       // Initialize the character
    while (window.isOpen())     // Start the game loop
    {
        deltaTime = clock.restart();    // Get the time between frames
        window.clear(sf::Color::Cyan);  // Clear the screen and set the background color
        character.update(); // Update the character
        window.display();   // Update the window
    }
    return EXIT_SUCCESS;
}
