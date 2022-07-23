CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 `pkg-config --cflags --libs sdl2` -lSDL2_image -lSDL2_ttf
IN = src/main.c src/graphics.c src/lexer.c
OUT = -o out

default:
	$(CC) $(IN) $(OUT) $(CFLAGS)
	./out 