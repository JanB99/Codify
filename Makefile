CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags --libs sdl2` -lSDL2_image -lSDL2_ttf
IN = src/main.c src/graphics.c
OUT = -o out

default:
	$(CC) $(IN) $(OUT) $(CFLAGS)
	./out 