#include "keys.h"

Keys::Keys()
{
  _map = {
    {_keyboard.Num1, 0x1}, {_keyboard.Num2, 0x2}, {_keyboard.Num3, 0x3}, {_keyboard.Num4, 0xC},
    {_keyboard.Q, 0x4}, {_keyboard.W, 0x5}, {_keyboard.E, 0x6}, {_keyboard.R, 0xD},
    {_keyboard.A, 0x7}, {_keyboard.S, 0x8}, {_keyboard.D, 0x9}, {_keyboard.F, 0xE},
    {_keyboard.Z, 0xA}, {_keyboard.X, 0x0}, {_keyboard.C, 0xB}, {_keyboard.V, 0xF}
  };

  for (auto i = 0; i < 16; ++i) {
    operator[](i) = false;
  }
}

void Keys::getKeys()
{
  for (auto i = 0; i < 16; ++i) {
    operator[](_map[i].value) = _keyboard.isKeyPressed(_map[i].key);
  }
}

short Keys::waitForKey()
{
  for (;;) {
    getKeys();
    for (auto i = 0; i < 16; ++i) {
      if (operator[](i))
      {
        std::cout << "Pressed " << i << "\n";
        return i;
      }
    }
  }
  return 0;
}
