#include "common.h"

extern void init_game(void);
extern void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int x, int y, char *text);
extern void SDL_close(void);

extern SDL_Context sdl;