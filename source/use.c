#include "use.h"

void draw_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, int x, int y, char *text)
{
	int text_width;
	int text_height;
	SDL_Surface *surface;
	SDL_Color textColor = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, text, textColor);
	*texture = SDL_CreateTextureFromSurface(sdl.renderer, surface);

	SDL_FreeSurface(surface);

	text_width = surface->w;
	text_height = surface->h;

	rect->x = x;
	rect->y = y;
	rect->w = text_width;
	rect->h = text_height;
}

SDL_Texture *loadTexture(char *file)
{
	SDL_Texture *texture;

	texture = IMG_LoadTexture(sdl.renderer, file);

	return texture;
}

void draw_texture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect draw_texture;

	draw_texture.x = x;
	draw_texture.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &draw_texture.w, &draw_texture.h);

	SDL_RenderCopy(sdl.renderer, texture, NULL, &draw_texture);
}


void key_is_UP(SDL_KeyboardEvent *inc)
{
	if (inc->repeat == 0)
	{
		sdl.key[inc->keysym.scancode] = 0;
	}
}

void key_is_DOWN(SDL_KeyboardEvent *inc)
{
	if (inc->repeat == 0)
	{
		sdl.key[inc->keysym.scancode] = 1;
	}
}

void input(void)
{
	SDL_Event inc;

	while (SDL_PollEvent(&inc))
	{
		switch (inc.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			key_is_DOWN(&inc.key);
			break;

		case SDL_KEYUP:
			key_is_UP(&inc.key);
			break;

		default:
			break;
		}
	}
}
