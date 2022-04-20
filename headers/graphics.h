#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define FPS 30
#define WIDTH 800
#define HEIGHT 800

#define MAX_CHARS 128
#define MIN_CHARS 0

typedef struct {
    SDL_Window* window;
    SDL_Renderer* rend;
    unsigned int running;
} State;

typedef struct {
    TTF_Font* font;
    SDL_Surface* glyphs[MAX_CHARS - MIN_CHARS];
    int charWidth;
    int charHeight;
} Font;

State* init(const char* title, int width, int height);
void clean(State* state, Font* f);
void handleEvents(State* state);
void render_text(State* state, Font* f, const char* text, int x, int y, float scale);

char* loadFile(const char* path);
Font* init_font(const char* path);

#endif // GRAPHICS_H_