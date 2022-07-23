#include "../headers/graphics.h"

char* loadFile(const char* path){
    FILE* text = fopen(path, "r");
    if (text == NULL){
        fprintf(stderr, "Unable to open file\n");
        exit(1);
    }

    fseek(text, 0L, SEEK_END);
    long int size = ftell(text);
    fseek(text, 0L, SEEK_SET);

    char* textbuf = (char*)malloc(sizeof(char) * size);
    fread(textbuf, size, 1, text);

    fclose(text);
    return textbuf;
}

void handleEvents(State* state){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch (e.type){
            case SDL_QUIT:
                state->running = 0;
                break;
            default: break;
        }
    }
}

static const Color palette[] = {
    (Color){255, 255, 255}, // +
    (Color){255, 255, 255}, // - 
    (Color){255, 255, 255}, // * 
    (Color){255, 255, 255}, // / 
    (Color){255, 255, 255}, // % 
    (Color){255, 255, 255}, // --
    (Color){255, 255, 255}, // ++
    (Color){255, 255, 255}, // <<
    (Color){255, 255, 255}, // >>

    (Color){255, 255, 255}, // (  
    (Color){255, 255, 255}, // )  
    (Color){255, 255, 255}, // {  
    (Color){255, 255, 255}, // }  
    (Color){255, 255, 255}, // [  
    (Color){255, 255, 255}, // ]  
    (Color){255, 255, 255}, // ;  
    (Color){255, 255, 255}, // ,  
    (Color){255, 255, 255}, // .  
    (Color){255, 255, 255}, // ?  
    (Color){255, 255, 255}, // :  

    (Color){255, 255, 255}, // =  
    (Color){255, 255, 255}, // == 
    (Color){255, 255, 255}, // !  
    (Color){255, 255, 255}, // != 
    (Color){255, 255, 255}, // <  
    (Color){255, 255, 255}, // <= 
    (Color){255, 255, 255}, // >  
    (Color){255, 255, 255}, // >= 
    (Color){255, 255, 255}, // && 
    (Color){255, 255, 255}, // || 
    (Color){255, 255, 255}, // &  
    (Color){255, 255, 255}, // |  
    (Color){255, 255, 255}, // ^  
    (Color){255, 255, 255}, // ~  

    (Color){255, 255, 255}, // += 
    (Color){255, 255, 255}, // -= 
    (Color){255, 255, 255}, // *= 
    (Color){255, 255, 255}, // /= 
    (Color){255, 255, 255}, // %= 

    (Color){200, 182, 226}, // const       
    (Color){200, 182, 226}, // int         
    (Color){200, 182, 226}, // double      
    (Color){200, 182, 226}, // float       
    (Color){200, 182, 226}, // char        
    (Color){200, 182, 226}, // unsigned    
    (Color){200, 182, 226}, // long        
    (Color){200, 182, 226}, // enum        
    (Color){200, 182, 226}, // struct      
    (Color){200, 182, 226}, // union       
    (Color){200, 182, 226}, // typedef     

    (Color){181, 20, 111}, // IDENTIFIER  
    (Color){254, 177, 57}, // STRING      
    (Color){240, 220, 255}, // NUMBER      
    (Color){255, 255, 255}, // TRUE        
    (Color){255, 255, 255}, // FALSE       
    (Color){255, 255, 255}, // NULL   
     
    (Color){20, 178, 244}, // return      
    (Color){20, 178, 244}, // do          
    (Color){20, 178, 244}, // while       
    (Color){20, 178, 244}, // for         
    (Color){20, 178, 244}, // if          
    (Color){20, 178, 244}, // else        
    (Color){170, 20, 244}, // preproc

    (Color){255, 255, 255}, // WHITE_SPACE 
    (Color){255, 255, 255}, // TAB_SPACE   
    (Color){255, 255, 255}, // CARR_SPACE  
    (Color){255, 255, 255}, // NEW_LINE    
};

void render_char(State* state, Font* f, char ch, int x, int y, float scale, Color color){
    SDL_Texture* tex = SDL_CreateTextureFromSurface(state->rend, f->glyphs[ch - MIN_CHARS]);
    SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
    SDL_RenderCopy(state->rend, tex, NULL, &(SDL_Rect){x, y, (int)(f->charWidth * scale), (int)(f->charHeight * scale)});
    SDL_DestroyTexture(tex);
}

void render_text(State* state, Font* f, TokenList* list, int x, int y, float scale){
    SDL_SetRenderDrawColor(state->rend, 51, 51, 51, 51);
    SDL_RenderClear(state->rend);

    int yoff = 0;
    int xoff = 0;
    

    for (size_t j = 0; j < list->index; j++){
        
        Color c = palette[list->tokens[j].type];
        size_t n = strlen(list->tokens[j].lexeme);
        for (size_t i = 0; i < n; i++){
            if (list->tokens[j].type == NEW_LINE){
                yoff += (int)(f->charHeight * scale);
                xoff = 0;
                continue;
            }
            if (x + xoff * (int)(f->charWidth * scale) > WIDTH - x){
                yoff += (int)(f->charHeight * scale);
                xoff = 0;
            }
            render_char(state, f, list->tokens[j].lexeme[i], x + xoff * (int)(f->charWidth * scale), y + yoff, scale, c);
            xoff++;
        }
    } 

    SDL_RenderPresent(state->rend);
}

Font* init_font(const char* path){
    if (TTF_Init() != 0){
        fprintf(stderr, "Unable to initialize TTF: %s\n", SDL_GetError());
        exit(1);
    }

    Font* f = malloc(sizeof(Font));

    f->font = TTF_OpenFont(path, 128);
    if (f->font == NULL){
        fprintf(stderr, "Unable to initialize font: %s\n", TTF_GetError());
        TTF_Quit();
        exit(1);
    }

    Uint16 ch;
    for (ch = MIN_CHARS; ch < MAX_CHARS; ch++){
        f->glyphs[ch-MIN_CHARS] = TTF_RenderGlyph_Blended(f->font, ch, (SDL_Color){255, 255, 255, 255});
    }
    TTF_GlyphMetrics(f->font, MIN_CHARS, NULL, NULL, NULL, NULL, &f->charWidth);
    f->charHeight = TTF_FontHeight(f->font);

    return f;
}

State* init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    State* s = (State*)malloc(sizeof(State));
    s->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (s->window == NULL){
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    s->rend = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
    if (s->rend == NULL){
        fprintf(stderr, "Unable to initialize renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_Quit();
        exit(1);
    }

    s->running = 1;

    return s;
}

void clean(State* state, Font* f){
    for (size_t i = 0; i < MAX_CHARS-MIN_CHARS; i++)
        SDL_FreeSurface(f->glyphs[i]);
    SDL_DestroyRenderer(state->rend);
    SDL_DestroyWindow(state->window);
    TTF_Quit();
    SDL_Quit();
}