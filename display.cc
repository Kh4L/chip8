#include "display.h"

Display::Display()
:_renderWindow(sf::VideoMode(64 * 5, 32 * 5), "Chip8")
{
  //_renderWindow = sf::RenderWindow(sf::VideoMode(64 * 5, 32 * 5), "Chip8");
  _renderWindow.setFramerateLimit(60);
  for (bool& px : _buffer)
    px = false;
}

bool Display::updatePixel(short x, short y)
{

}
void Display::draw()
{
  _renderWindow.clear(sf::Color(0, 0, 0, 255));
  sf::CircleShape shape(100.f);
     shape.setFillColor(sf::Color::Green);
  _renderWindow.draw(shape);
  _renderWindow.display();
}

void Display::clear()
{
  for (bool& px : _buffer)
    px = false;
}
