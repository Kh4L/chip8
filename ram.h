#pragma once
#include <array>
#include <fstream>
#include <iostream>
#include <memory>

class Ram : public std::array<unsigned char, 4096>
{
public:
  Ram();
  bool loadProgram(char *filename);
};
