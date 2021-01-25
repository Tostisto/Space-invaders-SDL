#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAX_KEYS 350

typedef struct Entity Entity;
typedef struct Texture Texture;

struct Texture
{
	SDL_Texture *texture;
	Texture *other;
};

typedef struct
{
	void (*logic)(void);
	void (*draw)(void);
} Transfer;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Transfer transfer;
	Texture textureHead, *textureTail;
	int key[MAX_KEYS];
} SDL_Context;

struct Entity
{
	int x;
	int y;
	int move_x;
	int move_y;
	int width;
	int height;
	int lives;
	int side;
	int reload;
	SDL_Texture *texture;
	Entity *other;
};

typedef struct
{
	Entity enemyHead, *enemyTail;
	Entity bulletHead, *bulletTail;
	int score;
} Game;
