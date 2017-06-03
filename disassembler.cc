#include "disassembler.h"

const size_t SIZEOF_SHORT = 2;

void decodePrintOpcode(short opcode, short xreg, short yreg)
{
  std::cout << std::setfill('0') << std::setw(4)
            << std::hex << opcode << "\t";
  switch (opcode & 0xF000) {
    case 0x000:
      switch (opcode) {
        case 0x00E0: // Clear the display.
          std::cout << "CLS";
          break;
        case 0x00EE: // Return from a subroutine.
          std::cout << "RET";
          break;
        default: // Jump to a machine code routine at nnn.
          std::cout << "SYS " << std::hex << (opcode & 0xFFF);
      }
    break;
    case 0x1000: // Jump to location nnn.
      std::cout << "JMP " << std::hex << (opcode & 0xFFF);
      break;
    case 0x2000: // Call subroutine at nnn.
      std::cout << "CALL " << std::hex << (opcode & 0xFFF);
      break;
    case 0x3000: // Skip next instruction if Vx = kk.
      std::cout << "SE V" << std::hex << xreg << ", "
        << std::hex << (opcode & 0xFF);
      break;
    case 0x4000: // Skip next instruction if Vx != kk.
      std::cout << "SNE V" << std::hex << xreg << ", "
        << std::hex << (opcode & 0xFF);
      break;
    case 0x5000: // Skip next instruction if Vx = Vy.
      std::cout << "SE V" << std::hex << xreg << ", V"
        << std::hex << yreg;
      break;
    case 0x6000: // Set Vx = kk.
      std::cout << "LD V" << std::hex << xreg << ", "
        << std::hex << (opcode & 0xFF);
      break;
    case 0x7000: // Set Vx = Vx + kk.
      std::cout << "ADD V" << std::hex << xreg << ", "
        << std::hex << (opcode & 0xFF);
      break;
    case 0x8000:
      switch (opcode & 0x000F) {
        case 0x0001: // Set Vx = Vx OR Vy.
          std::cout << "OR V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x0002: // Set Vx = Vx AND Vy.
          std::cout << "AND V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x0003: // Set Vx = Vx XOR Vy.
          std::cout << "XOR V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x0004: // Set Vx = Vx + Vy, set VF = carry.
          std::cout << "ADD V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x0005: // Set Vx = Vx - Vy, set VF = NOT borrow.
          std::cout << "SUB V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x0006: // Set Vx = Vx SHR 1.
          std::cout << "SHR V" << std::hex << xreg;
          break;
        case 0x0007: // Set Vx = Vy - Vx, set VF = NOT borrow.
          std::cout << "SUBN V" << std::hex << xreg << ", V"
            << std::hex << yreg;
          break;
        case 0x000E:
          std::cout << "SHL V" << std::hex << xreg;
          break;
        default:
          std::cout << "Bad op";
          break;
        }
    case 0x9000: // Skip next instruction if Vx != Vy.
      std::cout << "SNE V" << std::hex << xreg << ", V"
        << std::hex << yreg;
      break;
    case 0xA000: // Set I = nnn.
      std::cout << "LD I, "
        << std::hex << (opcode & 0xFFF);
      break;
    case 0xB000: // Jump to location nnn + V0.
      std::cout << "JP V0, "
        << std::hex << (opcode & 0xFFF);
        break;
    case 0xC000: // Set Vx = random byte AND kk.
      std::cout << "RND V" << std::hex << xreg << ", "
        << std::hex << (opcode & 0xFF);
      break;
    case 0xD000: // Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
      std::cout << "DRW V" << std::hex << xreg << ", V" << std::hex << yreg
        << ", " << std::hex << (opcode & 0xF);
    break;
    case 0xE000:
      switch (opcode & 0x000F) {
        case 0x009E: // Skip next instruction if key with the value of Vx is pressed.
          std::cout << "SKP V" << std::hex << xreg;
          break;
        case 0x00A1: // Skip next instruction if key with the value of Vx is not pressed.
          std::cout << "SKNP V" << std::hex << xreg;
          break;
        default:
          std::cout << "Bad op";
          break;
      }
      break;
    case 0xF000:
      switch (opcode & 0x00FF) {
        case 0x0007: // Set Vx = delay timer value.
          std::cout << "LD V" << std::hex << xreg << ", DT";
          break;
        case 0x000A: // Wait for a key press, store the value of the key in Vx.
          std::cout << "LD V" << std::hex << xreg << ", K";
          break;
        case 0x0015: // Set delay timer = Vx.
          std::cout << "LD DT, V" << std::hex << xreg;
          break;
        case 0x0018: // Set sound timer = Vx.
          std::cout << "LD ST, V" << std::hex << xreg;
          break;
        case 0x001E: // Set I = I + Vx.
          std::cout << "LD I, V" << std::hex << xreg;
          break;
        case 0x0029: // Set I = location of sprite for digit Vx.
          std::cout << "LD F, V" << std::hex << xreg;
          break;
        case 0x0033: // Store BCD representation of Vx in memory locations I, I+1, and I+2.
          std::cout << "LD B, V" << std::hex << xreg;
          break;
        case 0x0055: // Store registers V0 through Vx in memory starting at location I.
          std::cout << "LD [I], V" << std::hex << xreg;
          break;
        case 0x0065: // Read registers V0 through Vx from memory starting at location I.
          std::cout << "LD V" << std::hex << xreg << ", [I]";
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
  std::cout << std::endl;
}

void disassemble(char* filename)
{
  short opcode;
  short ip = 0x200;
  std::ifstream binaryfstream(filename, std::ios::binary);

  while (!binaryfstream.eof())
    {
        opcode = binaryfstream.get() << 8;
        opcode += binaryfstream.get();

        short xreg = (opcode & 0x0F00) >> 8;
        short yreg = (opcode & 0x00F0) >> 4;

        std::cout << "0x" << std::setfill('0') << std::setw(4)
                  << std::hex << ip << ":\t";
        decodePrintOpcode(opcode, xreg, yreg);
        ip += 2;
    }
}
