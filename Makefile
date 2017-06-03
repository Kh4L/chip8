CC = g++
BIN = chip8
OBJS = disassembler.o keys.o display.o ram.o cpu.o main.o
RM = rm -rvf
CXXFLAGS += -std=c++14

all: $(BIN)


$(BIN): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $+

clean:
	$(RM) $(OBJS) $(BIN)

exec: $(BIN)
	./$(BIN)
