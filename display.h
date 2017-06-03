#pragma once

#include <array>

class Display
{
public:
  Display();
  void Clear();
private:
  std::array<char, 2048> buffer; // 64x32 buffer
};
