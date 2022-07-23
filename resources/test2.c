#include "../headers/graphics.h"
#include "../headers/lexer.h"
#include <time.h> 

int main(int argc, char **argv){
    (void) argc; (void) argv;
    char* text = loadFile("./resources/test.c");

    State* state = init("Codify", WIDTH, HEIGHT);
    Font* f = init_font("/usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf");

    TokenList* tokenList = tokenize(text);
    printf("RESULT:\n");
    for (size_t i = 0; i < tokenList->index; i++){
        printf("%s", tokenList->tokens[i].lexeme);
    }

    render_text(state, f, tokenList, 50, 50, 0.2);

    const int frameDelay = 1000/FPS;
    uint32_t frameStart;
    int frameTime;
    srand(time(NULL));

    while (state->running){
        frameStart = SDL_GetTicks();

        handleEvents(state);
        
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    clean(state, f);
    return 0;
}

