#pragma once
#include <memory>
#include <iomanip>
#include "ram.h"
#include "display.h"
#include "keys.h"

class Cpu
{
public:
  Cpu(Ram& ram, Display& display, Keys& keys);
  void run();

private:
  short _opcode;
  short _V[16];
  short _I;
  short _pc;
  short _stack[16];
  char _sp;

  char _dt;
  char _st;

  Ram& _ram;
  Display& _display;
  Keys& _keys;

  void cycle();
};
