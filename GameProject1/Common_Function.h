
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>




const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int NUM_THREATS = 5;
const int THREAT_AMO_SPEED = 7;
const int THREAT_MOVE_SPEED = 3;

const int MAINOBJECT_AMO_SPEED = 15;
const int MAINOBJECT_MOVE_SPEED = 7;

const int POS_X_START_MAIN_OBJ = 100;
const int POS_Y_START_MAIN_OBJ = 200;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* g_tutorial = NULL;


static SDL_Event g_even;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Music* g_background_music;

static char g_name_background[] = { "gfx/background.png" };
static char g_name_mainObject[] = { "gfx/PlaneObject.png" };
static char	g_name_exp_main[] = { "gfx/Explosion1.png" };
static char g_name_exp_threat[] = { "gfx/Explosion2.png" };

static char	g_name_threatObject[] = { "gfx/Enemy1.png" };
static char g_name_amo_1[] = { "gfx/laser.png" };
static char g_name_amo_2[] = { "gfx/sphere.png" };
static char g_name_amo_3[] = { "gfx/sphere2.png" };

static char g_name_main_power[] = { "gfx/HeartIcon.png" };
static char g_name_start_background[] = { "gfx/start_bg.png" };
static char g_name_tutorial[] = { "gfx/Tutorial.png" };

static char g_name_font_points[] = { "font/prstart.ttf" };
//static char g_name_font_menu[] = { "font/" }

static char g_name_audio_gunSound1[] = { "sfx/gunSound1.wav" };
static char g_name_audio_gunSound2[] = { "sfx/gunSound2.wav" };
static char g_name_audio_explosionSound1[] = { "sfx/Explosion2.wav" };
static char g_name_audio_explosionSound2[] = { "sfx/Explosion1.wav" };
static char g_name_audio_backgroundMusic[] = { "sfx/backgroundMusic2.wav" };


namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	int ShowMenu(SDL_Surface* des, TTF_Font* font);

	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);


}


#endif
