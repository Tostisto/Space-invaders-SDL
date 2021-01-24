#include "common.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

extern void draw_texture(SDL_Texture *texture, int x, int y);
extern void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int x, int y, char *text);
extern void game_over(void);
extern void SDL_close(void);

extern SDL_Texture *loadTexture(char *file);

extern int enemy_SpawnSpeed;
extern int enemy_Speed;
extern int player_lives;
extern int enemy_lives;

extern SDL_Context sdl;
extern Game game;
