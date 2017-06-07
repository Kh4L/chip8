#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Display
{
public:
  Display(unsigned int resolution = 2);
  int drawSprite(int x, int y, std::vector<char>& sprite);
  void draw();
  void clear();
private:
  sf::RenderWindow _renderWindow;
  unsigned int _resolution;
  std::array<bool, 2048> _buffer; // 64x32 buffer
};
