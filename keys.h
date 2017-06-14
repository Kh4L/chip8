#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

struct KeyMap
{
  sf::Keyboard::Key key;
  short value;
};

class Keys : public std::array<bool, 16>
{
public:
  Keys();
  short waitForKey();
  void getKeys();

private:
  sf::Keyboard _keyboard;
  std::vector<KeyMap> _map;
};
