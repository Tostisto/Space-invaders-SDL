#include "main.h"

int main(void)
{
	memset(&sdl, 0, sizeof(SDL_Context));
	sdl.textureTail = &sdl.textureHead;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	sdl.window = SDL_CreateWindow("Space Invaders", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);

    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_Music* music;
    music = Mix_LoadMUS("resources/Audio/audio_hero_911_SIPML_J-0501.mp3");
	Mix_PlayMusic(music, -1);
	
	menu_init();

	memset(&game, 0, sizeof(Game));

	while (1)
	{
		input();

		SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
		SDL_RenderClear(sdl.renderer);

		sdl.transfer.draw();

		sdl.transfer.logic();

		SDL_RenderPresent(sdl.renderer);

		SDL_Delay(16);
	}

	Mix_FreeMusic(music);
	Mix_Quit();

	return 0;
}
