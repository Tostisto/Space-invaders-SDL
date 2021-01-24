#include "gameover.h"

static void logic(void);
static void draw(void);

void game_over(void)
{
	sdl.transfer.logic = logic;
	sdl.transfer.draw = draw;
}

static void logic(void)
{
	if (sdl.key[SDL_SCANCODE_SPACE])
	{
		init_game();
	}

	if (sdl.key[SDL_SCANCODE_ESCAPE])
	{
		SDL_close();
	}
}

static void draw(void)
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf Error: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	TTF_Font *big_font = TTF_OpenFont("resources/font/dogica.ttf", 80);
	TTF_Font *font = TTF_OpenFont("resources/font/dogica.ttf", 30);
	if (font == NULL)
	{
		printf("TTF_OpenFont Error:  %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Rect gameover, play, exit;
	SDL_Texture *texture;

	draw_text(sdl.renderer, big_font, &texture, &gameover, 280, 200, "GAME OVER");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &gameover);

	draw_text(sdl.renderer, font, &texture, &play, 400, 400, "Play Again - SPACE");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &play);

	draw_text(sdl.renderer, font, &texture, &exit, 440, 500, "QUIT - ESCAPE");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &exit);

	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	TTF_Quit();
}
