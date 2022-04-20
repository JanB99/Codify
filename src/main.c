#include "../headers/graphics.h"

int main(int argc, char **argv){
    
    const char* text = loadFile("./resources/test.c");
    // size_t n = strlen(text);
    // for (size_t i = 0; i < n; i++){
    //     printf("char: %c --- %d\n", text[i], text[i]);
    // }

    State* state = init("Codify", WIDTH, HEIGHT);
    Font* f = init_font("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf");

    const int frameDelay = 1000/FPS;
    uint32_t frameStart;
    int frameTime;

    while (state->running){
        frameStart = SDL_GetTicks();

        handleEvents(state);
        render_text(state, f, text, 50, 50, 0.2);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    clean(state, f);
    return 0;
}

