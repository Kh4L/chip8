#include "display.h"

#include <iostream>

Display::Display(unsigned int resolution)
  :_renderWindow(sf::VideoMode(64 * resolution, 32 * resolution), "Chip8"),
  _resolution(resolution)
{
  _renderWindow.setFramerateLimit(42);
  for (bool& px : _buffer)
    px = false;
}

int Display::drawSprite(int x, int y, std::vector<char>& sprite)
{
  int collision = 0;
  for (unsigned int yDelta = 0; yDelta < sprite.size(); ++yDelta) {
    char currentByte = sprite[yDelta];
    for (int xDelta = 0; xDelta < 8; ++xDelta) {
        if ((currentByte & 0x80) == 0x80) {
          bool& px = _buffer[(y + yDelta) * 64 + (x + xDelta)];
          collision = px ? 1 : 0;
          _buffer[(y + yDelta) * 64 + (x + xDelta)] = !px;
        }
        currentByte <<= 1;
    }
  }
  return collision;
}
void Display::draw()
{
  _renderWindow.clear(sf::Color::Black);

  /*
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
  */
  for (unsigned int i = 0; i < 2048; ++i) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(_resolution, _resolution));
    rectangle.setFillColor((_buffer[i] ? sf::Color::White : sf::Color::Black));
    rectangle.setPosition((i % 64)  * _resolution, (i / 64) * _resolution);
    _renderWindow.draw(rectangle);
  }

  //_renderWindow.draw(shape);
  _renderWindow.display();
}

void Display::clear()
{
  for (bool& px : _buffer)
    px = false;
}
