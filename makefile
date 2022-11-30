CC = gcc
EXECUTABLES = $(patsubst %.c, %, $(wildcard *.c))

.PHONY: clean

all: $(EXECUTABLES)
	@echo Compile tutorials for embedding python

%: %.c
	@$(CC) $< -o $@  `pkg-config --cflags` -lpython3.10

clean:
	@$(RM) $(EXECUTABLES)
