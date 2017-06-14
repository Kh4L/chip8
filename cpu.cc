#include "cpu.h"

#define XREG _V[(_opcode & 0x0F00) >> 8]
#define YREG _V[(_opcode & 0x00F0) >> 4]

Cpu::Cpu(Ram& ram, Display& display, Keys& keys)
: _ram(ram), _display(display), _keys(keys)
{
}

void Cpu::cycle()
{
  //std::cout << std::setfill('0') << std::setw(4)
  //          << std::hex << _opcode << "\t";
  switch (_opcode & 0xF000) {
    case 0x000:
      switch (_opcode) {
        case 0x00E0: // Clear the display. CLS
          _display.clear();
          break;
        case 0x00EE: // Return from a subroutine. RET
          _pc = _stack[_sp];
          _sp--;
          break;
        default: // Jump to a machine code routine at nnn. SYS
          _pc = _opcode & 0xFFF;
      }
    break;
    case 0x1000: // Jump to location nnn. JMP
      _pc = _opcode & 0xFFF;
      break;
    case 0x2000: // Call subroutine at nnn. CALL
      _sp++;
      _stack[_sp] = _pc;
      _pc = _opcode & 0xFFF;
      break;
    case 0x3000: // Skip next instruction if Vx = kk. SE
      if (XREG == (0xFF & _opcode))
        _pc += 2;
      break;
    case 0x4000: // Skip next instruction if Vx != kk. SNE
      if (XREG != (0xFF & _opcode))
        _pc += 2;
      break;
    case 0x5000: // Skip next instruction if Vx = Vy. SE
      if (XREG == YREG)
        _pc += 2;
      break;
    case 0x6000: // Set Vx = kk. LD
      XREG = 0xFF & _opcode;
      break;
    case 0x7000: // Set Vx = Vx + kk. ADD
      XREG += 0xFF & _opcode;
      break;
    case 0x8000:
      switch (_opcode & 0x000F) {
        case 0x0001: // Set Vx = Vx OR Vy. OR
          XREG = XREG | YREG;
          break;
        case 0x0002: // Set Vx = Vx AND Vy. AND
          XREG = XREG & YREG;
          break;
        case 0x0003: // Set Vx = Vx XOR Vy. XOR
          XREG = XREG ^ YREG;
          break;
        case 0x0004: // Set Vx = Vx + Vy, set VF = carry. ADD
            if (XREG + YREG > 255)
              _V[0xF] = 1;
            XREG += YREG;
          break;
        case 0x0005: // Set Vx = Vx - Vy, set VF = NOT borrow SUB.
            _V[0xF] = (XREG < YREG) ? 1 : 0;
            XREG -= YREG;
          break;
        case 0x0006: // Set Vx = Vx SHR 1. SHR
          _V[0xF] = XREG % 2;
          XREG >>= 1;
          break;
        case 0x0007: // Set Vx = Vy - Vx, set VF = NOT borrow. SUBN
          _V[0xF] = (YREG < XREG) ? 1 : 0;
          XREG = YREG - XREG;
          break;
        case 0x000E: // Set Vx = Vx SHL 1. SHL
          _V[0xF] = (XREG & 0x80) ? 1 : 0;
          XREG <<= 1;
          break;
        default:
          std::cout << "Bad op";
          break;
        }
    case 0x9000: // Skip next instruction if Vx != Vy. SE
      if (XREG != YREG)
        _pc += 2;
      break;
    case 0xA000: // Set I = nnn. LD I
      _I = _opcode & 0xFFF;
      break;
    case 0xB000: // Jump to location nnn + V0. JP
      _pc = (_opcode & 0xFFF) + _V[0];
      break;
    case 0xC000: // Set Vx = random byte AND kk. RND
      XREG = (rand() % 256) & (_opcode & 0xFF);
      break;
    case 0xD000:
    {
    // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision. DRW
      std::vector<char> sprite;
      std::cout << "SIZE OF DRW " << (_opcode & 0xF) << std::endl;
      // http://fr.cppreference.com/w/cpp/language/operator_precedence
      for (int i = 0; i < (_opcode & 0xF); ++i)
        sprite.push_back(_ram[_I + i]);
      _V[0xF] = _display.drawSprite(XREG, YREG, sprite);
    }
    break;
    case 0xE000:
      switch (_opcode & 0x00FF) {
        case 0x009E: // Skip next instruction if key with the value of Vx is pressed. SKP Vx
          if (_keys[XREG])
            _pc += 2;
          break;
        case 0x00A1: // Skip next instruction if key with the value of Vx is not pressed. SKNP Vx
          if (!_keys[XREG])
            _pc += 2;
          break;
        default:
          std::cout << "Bad op";
          break;
      }
      break;
    case 0xF000:
      switch (_opcode & 0x00FF) {
        case 0x0007: // Set Vx = delay timer value. LD Vx, DT
          XREG = _dt;
          break;
        case 0x000A: // Wait for a key press, store the value of the key in Vx. LD Vx, K
          XREG = _keys.waitForKey();
          break;
        case 0x0015: // Set delay timer = Vx. LD
          _dt = XREG;
          break;
        case 0x0018: // Set sound timer = Vx. LD
          _st = XREG;
          break;
        case 0x001E: // Set I = I + Vx. LD I, V
          _I += XREG;
          break;
        case 0x0029: // Set I = location of sprite for digit Vx. LD F, Vx
          _I = XREG  * 5; // x5 because Fonts starts at 0 and are 5 bytes long,
          break;
        case 0x0033: // Store BCD representation of Vx in memory locations I, I+1, and I+2. LD B, Vx
          _ram[_I] = (XREG / 100) % 10;
          _ram[_I + 1] = (XREG / 10) % 10;
          _ram[_I + 2] = XREG % 10;
          break;
        case 0x0055: // Store registers V0 through Vx in memory starting at location I. LD [I], Vx
        {
          char x = (_opcode & 0xF00) >> 8;
          for (char i = 0; i <= x; i++) {
            _ram[_I + i] = _V[i];
          }
          //memcpy(_ram + _I, opcode, x * sizof(char));
        }
          break;
        case 0x0065: // Read registers V0 through Vx from memory starting at location I.  LD Vx, [I]
        {
          char x = (_opcode & 0xF00) >> 8;
          for (char i = 0; i < x; i++) {
            _V[i] = _ram[_I + i];
          }
        }
         break;
        default:
          std::cout << "Bad op";
          break;
      }
      break;
    default:
      std::cout << "Bad op";
      break;
  }
//  std::cout << std::endl;
}

void Cpu::run()
{
  _pc = 0x200;
  _sp = 0;
  _dt = 0;
  _st = 0;
/*
for (int i = 0x200; i < 2048; ++i) {
  short n = _ram[i];
  std::cout << std::hex << n << std::endl;
}
  return;
  */
  for (;;) {
    // Interesing : _opcode = _ram[_pc] << 8; give wrong results
    _opcode = _ram[_pc];
    _opcode <<= 8;
    _opcode += _ram[_pc + 1];
    _pc += 2;

    this->cycle();
    _display.draw();
    _keys.getKeys();
    if (_dt > 0)
      --_dt;
    if (_st > 0)
      --_st;
  }
}
