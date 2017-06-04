#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
//#include <SFML/Keyboard.hpp>


class Keys : public std::array<bool, 16>
{
public:
  Keys();
  short wait();

private:
  void getKeys();
};
