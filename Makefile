CC = clang++
BIN = chip8
OBJS = disassembler.o keys.o display.o ram.o cpu.o main.o
RM = rm -rvf
CXXFLAGS += -std=c++14
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

all: $(BIN)


$(BIN): $(OBJS)
	$(CC) $(CXXFLAGS) $(SFMLFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BIN)

exec: $(BIN)
	./$(BIN)
