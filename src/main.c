#include "../headers/graphics.h"
#include "../headers/lexer.h"
#include <time.h> 

int main(int argc, char **argv){
    
    if (argc != 2) {
        fprintf(stderr, "Supply exactly 1 argument for the raw source code path.\n");
        exit(1);
    }
    char* text = loadFile(argv[1]);

    State* state = init("Codify", WIDTH, HEIGHT);
    Font* f = init_font("resources/LiberationMono-Bold.ttf");
    
    TokenList* tokenList = tokenize(text);
    printf("RAW TEXT:\n");
    for (size_t i = 0; i < tokenList->index; i++){
        printf("%s", tokenList->tokens[i].lexeme);
    }

    render_text(state, f, tokenList, 50, 50, 0.25);

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

