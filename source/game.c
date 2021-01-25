#include "game.h"

static void logic(void);
static void draw(void);

static void player_init(void);
static void player_control(void);

static void enemy(void);
static void enemy_spawn(void);
static void draw_enemy(void);

static void bullet(void);
static void shot_bullet(void);
static int bullet_hit(Entity *bullet);
static void draw_bullet(void);

static void game_area_border(void);
static int player_health(Entity *enemy);
static void draw_stats(void);

static Entity *player;
static SDL_Texture *player_texture;
static SDL_Texture *enemy_texture;
static SDL_Texture *bullet_texture;

static Mix_Chunk *shot;
static Mix_Chunk *explosion;

static int spawn_enemy_timer;

void init_game(void)
{
	sdl.transfer.logic = logic;
	sdl.transfer.draw = draw;

	player_texture = loadTexture("resources/img/player.png");
	enemy_texture = loadTexture("resources/img/enemy.png");
	bullet_texture = loadTexture("resources/img/bullet.png");

	shot = Mix_LoadWAV("resources/Audio/fire.wav");
	explosion = Mix_LoadWAV("resources/Audio/explosion.wav");

	memset(sdl.key, 0, sizeof(int) * MAX_KEYS);
	memset(&game, 0, sizeof(Game));

	game.enemyTail = &game.enemyHead;
	game.bulletTail = &game.bulletHead;

	player_init();
}

void play_shot()
{
	Mix_PlayChannel(-1, shot, 0);
}

void play_explosions()
{
	Mix_PlayChannel(-1, explosion, 0);
}

static void player_init()
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	game.enemyTail->other = player;
	game.enemyTail = player;

	player->texture = player_texture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->width, &player->height);

	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 1.2;

	player->lives = player_lives;
	player->side = 1;
}

static void player_control(void)
{
	if (player != NULL)
	{
		player->move_x = player->move_y = 0;

		if (sdl.key[SDL_SCANCODE_UP] || sdl.key[SDL_SCANCODE_W])
		{
			player->move_y = -10;
		}

		if (sdl.key[SDL_SCANCODE_DOWN] || sdl.key[SDL_SCANCODE_S])
		{
			player->move_y = 10;
		}

		if (sdl.key[SDL_SCANCODE_LEFT] || sdl.key[SDL_SCANCODE_A])
		{
			player->move_x = -10;
		}

		if (sdl.key[SDL_SCANCODE_RIGHT] || sdl.key[SDL_SCANCODE_D])
		{
			player->move_x = 10;
		}

		if (sdl.key[SDL_SCANCODE_SPACE] && player->reload <= 0)
		{
			shot_bullet();
			play_shot();
		}

		if (player->reload > 0)
		{
			player->reload--;
		}

		if (sdl.key[SDL_SCANCODE_ESCAPE])
		{
			SDL_close();
		}
	}
}

static void enemy(void)
{
	Entity *enemy, *prev;

	prev = &game.enemyHead;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		enemy->x += enemy->move_x;
		enemy->y += enemy->move_y;

		if (enemy != player && (enemy->y > SCREEN_HEIGHT || enemy->lives == 0 || player_health(enemy)))
		{
			if (enemy == game.enemyTail)
			{
				game.enemyTail = prev;
			}
			prev->other = enemy->other;
			free(enemy);
			enemy = prev;
		}

		prev = enemy;
	}
}

static void enemy_spawn(void)
{
	Entity *enemy;

	spawn_enemy_timer--;

	if (spawn_enemy_timer <= 0)
	{
		enemy = malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		game.enemyTail->other = enemy;
		game.enemyTail = enemy;

		enemy->x = rand() % SCREEN_WIDTH;

		enemy->y = 0;
		enemy->texture = enemy_texture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->width, &enemy->height);

		enemy->move_y = enemy_Speed;

		enemy->side = 0;
		enemy->lives = enemy_lives;
		spawn_enemy_timer = enemy_SpawnSpeed;
	}
}

static void logic(void)
{
	player_control();

	enemy();

	enemy_spawn();

	bullet();

	game_area_border();
}

static void shot_bullet(void)
{
	Entity *bullet;

	bullet = malloc(sizeof(Entity));
	memset(bullet, 0, sizeof(Entity));
	game.bulletTail->other = bullet;
	game.bulletTail = bullet;
	bullet->x = player->x;
	bullet->y = player->y;
	bullet->move_y = -15;
	bullet->lives = 1;
	bullet->texture = bullet_texture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);

	bullet->x += (player->width / 2) - (bullet->width / 2);

	bullet->side = 1;

	player->reload = 10;
}

static void bullet(void)
{
	Entity *bullet, *prev;

	prev = &game.bulletHead;

	for (bullet = game.bulletHead.other; bullet != NULL; bullet = bullet->other)
	{
		bullet->y += bullet->move_y;

		if (bullet_hit(bullet) || bullet->y < -bullet->y)
		{
			if (bullet == game.bulletTail)
			{
				game.bulletTail = prev;
			}
			prev->other = bullet->other;
			free(bullet);
			bullet = prev;
		}
		prev = bullet;
	}
}

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MIN(y1 + h1, y2 + h2) > MAX(y1, y2)) && (MIN(x1 + w1, x2 + w2) > MAX(x1, x2));
}

static int player_health(Entity *enemy)
{
	if (collision(player->x, player->y, player->width, player->height, enemy->x, enemy->y, enemy->width, enemy->height))
	{

		play_explosions();

		player->lives--;

		return 1;
	}

	if (enemy->y == SCREEN_HEIGHT)
	{
		player->lives--;
	}

	if (player->lives < 1)
	{
		game_over();
	}

	return 0;
}

static int bullet_hit(Entity *bullet)
{
	Entity *enemy;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		if (collision(bullet->x, bullet->y, bullet->width, bullet->height, enemy->x, enemy->y, enemy->width, enemy->height) && enemy->side != bullet->side)
		{
			bullet->lives = 0;
			enemy->lives--;

			if (enemy->lives == 0)
			{
				play_explosions();
				game.score = game.score + 10;
			}
			return 1;
		}
	}
	return 0;
}

static void game_area_border(void)
{
	if (player != NULL)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}

		if (player->y < 0)
		{
			player->y = 0;
		}

		if (player->x > SCREEN_WIDTH - player->width)
		{
			player->x = SCREEN_WIDTH - player->width;
		}

		if (player->y > SCREEN_HEIGHT - player->height)
		{
			player->y = SCREEN_HEIGHT - player->height;
		}
	}
}

static void draw_enemy(void)
{
	Entity *enemy;

	for (enemy = game.enemyHead.other; enemy != NULL; enemy = enemy->other)
	{
		draw_texture(enemy->texture, enemy->x, enemy->y);
	}
}

static void draw_bullet(void)
{
	Entity *bullet;

	for (bullet = game.bulletHead.other; bullet != NULL; bullet = bullet->other)
	{
		draw_texture(bullet->texture, bullet->x, bullet->y);
	}
}

static void draw_stats(void)
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf Error: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	TTF_Font *font = TTF_OpenFont("resources/font/dogica.ttf", 25);
	if (font == NULL)
	{
		printf("TTF_OpenFont Error:  %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Rect score, lives;
	SDL_Texture *texture;

	char text_score[50];
	char text_lives[50];

	sprintf(text_score, "Score: %03d", game.score);
	sprintf(text_lives, "Lives: %03d", player->lives);

	draw_text(sdl.renderer, font, &texture, &score, 10, 10, text_score);
	SDL_RenderCopy(sdl.renderer, texture, NULL, &score);

	draw_text(sdl.renderer, font, &texture, &lives, 10, 50, text_lives);
	SDL_RenderCopy(sdl.renderer, texture, NULL, &lives);

	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	TTF_Quit();
}

static void draw(void)
{
	draw_enemy();

	draw_bullet();

	draw_stats();
}

void SDL_close(void)
{
	Mix_FreeChunk(shot);

	Mix_FreeChunk(explosion);
    
	Mix_CloseAudio();

	SDL_DestroyRenderer(sdl.renderer);

	SDL_DestroyWindow(sdl.window);

	SDL_Quit();

	exit(0);
}
