#include <iostream>
#include <fstream>
#include <memory>
#include "disassembler.h"
#include "ram.h"
#include "cpu.h"

bool isDissambling(int argc, char **argv)
{
	for (size_t i = 0; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 'd') {
			return true;
		}
	}
	return false;
}
void badArgs()
{
	std::cout << "Usage: chip8 [OPTION] [FILE] " << std::endl;
	std::cout << "\t Options:" << std::endl;
	std::cout << "\t\t -d\t disassemble FILe and print it on stdout" << std::endl;
}
int main(int argc, char **argv)
{
	if (argc < 2) {
		badArgs();
		return 1;
	}

	if (isDissambling(argc, argv))
		disassemble(argv[2]);
	else {
		Ram ram;
		Display display(0x10);
		Keys keys;
		Cpu cpu(ram, display, keys);
		ram.loadProgram(argv[1]);
		cpu.run();
	}

	return 0;
}
