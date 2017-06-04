#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Display
{
public:
  Display();
  bool updatePixel(short x, short y);
  void draw();
  void clear();
private:
  std::array<bool, 2048> _buffer; // 64x32 buffer
  sf::RenderWindow _renderWindow;
};
