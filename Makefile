CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=gnu11 -Iinclude

SRC = src/main.c \
      src/menu.c \
      src/system.c \
	  src/health.c \
	  src/network.c \
	  src/security.c \
	  src/report.c \
	  src/utils.c \

OBJ = $(SRC:.c=.o)

TARGET = sysguard

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)