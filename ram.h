#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <memory>

class Ram : public std::array<char, 4096>
{
public:
  Ram();
  bool loadProgram(char *filename);
};
