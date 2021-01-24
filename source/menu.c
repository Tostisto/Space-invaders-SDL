#include "menu.h"

static void logic(void);
static void draw(void);

int enemy_Speed;
int enemy_SpawnSpeed;
int player_lives;
int enemy_lives;

void menu_init(void)
{
	sdl.transfer.logic = logic;
	sdl.transfer.draw = draw;
}

static void logic(void)
{
	if (sdl.key[SDL_SCANCODE_SPACE])
	{
		enemy_Speed = 3;
		enemy_SpawnSpeed = 100;
		player_lives = 3;
		enemy_lives = 2;
		init_game();
	}

	if (sdl.key[SDL_SCANCODE_H])
	{
		enemy_Speed = 4;
		enemy_SpawnSpeed = 90;
		player_lives = 1;
		enemy_lives = 3;
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

	TTF_Font *tittle = TTF_OpenFont("resources/font/MachineGunk-nyqg.ttf", 120);
	TTF_Font *font = TTF_OpenFont("resources/font/dogica.ttf", 30);
	if (font == NULL || tittle == NULL)
	{
		printf("TTF_OpenFont Error:  %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Rect titt, text1, text2, text3;
	SDL_Texture *texture;

	draw_text(sdl.renderer, tittle, &texture, &titt, 300, 150, "Space Invaders");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &titt);

	draw_text(sdl.renderer, font, &texture, &text1, 330, 400, "Normal mode - SPACE");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &text1);

	draw_text(sdl.renderer, font, &texture, &text2, 460, 490, "Hard mode - H");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &text2);

	draw_text(sdl.renderer, font, &texture, &text3, 475, 580, "Quit - ESC");
	SDL_RenderCopy(sdl.renderer, texture, NULL, &text3);

	TTF_CloseFont(tittle);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	TTF_Quit();
}
