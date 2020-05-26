/*

    Primer ejemplo en el que cargamos SFML mostrando para ello un sprite
    reducido su tamanyo y pudiendo moverlo mediante las teclas WASD.

*/


#include <SFML/Graphics.hpp>

using namespace std;

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    //shape.setFillColor(sf::Color::Green);

    sf::Texture texture;
    texture.loadFromFile("/home/folklore/Game/img/baby.jpg");

    sf::Sprite baby;
    baby.setTexture(texture);
    baby.setPosition(100,100);
    baby.setTextureRect(sf::IntRect(10, 10, 32, 32));

    sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                baby.move(pos.x + 4, 0);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                baby.move(0, 4);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                baby.move(0, -4);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                baby.move(-4, 0);
        }

        window.clear();
        window.draw(baby);
        window.display();
    }

    return 0;
}