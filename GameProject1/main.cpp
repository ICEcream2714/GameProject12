
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "ExplosionObject2.h"
#include "PlayerPower.h"
#include "TextObject.h"



TTF_Font* g_font_text = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
		return false;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;

	//Read file audio
	g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_gunSound1);
	g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_gunSound2);
	g_sound_exp[0] = Mix_LoadWAV(g_name_audio_explosionSound1);
	g_sound_exp[1] = Mix_LoadWAV(g_name_audio_explosionSound2);

	g_background_music = Mix_LoadMUS(g_name_audio_backgroundMusic);

	if (g_sound_exp[0] == NULL || g_sound_exp[1] == NULL
		|| g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL)
	{
		return false;
	}

	
	if (TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont(g_name_font_points, 20);
	if (g_font_text == NULL)
	{
		return false;
	}



	return true;
}


int main(int arc, char*argv[])
{
	double bkgn_x = 0;


	bool is_quit = false;
	if (Init() == false)
		return 0;

	//--------- Apply background ---------


	g_bkground = SDLCommonFunc::LoadImage(g_name_background);
	if (g_bkground == NULL)
	{
		return 0;
	}

	
	Mix_PlayMusic(g_background_music, -1);


	// ------ Player Power ------

	PlayerPower player_power;
	player_power.Init();


	// ------ Make Text... ------

	TextObject point_game;
	point_game.SetColor(TextObject::WHITE_TEXT);

	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);



	//------- Make MainObject ---------

	MainObject plane_object;
	bool ret = plane_object.LoadImg(g_name_mainObject);
	plane_object.set_clip();
	plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
	if (!ret)
	{
		return 0;
	}


	//--------- Init ExplosionObject ----------

	ExplosionObject exp_main;
	ret = exp_main.LoadImg(g_name_exp_main);
	exp_main.set_clip();
	if (!ret)
	{
		return 0;
	}

	ExplosionObject_2 exp_threat;
	ret = exp_threat.LoadImg(g_name_exp_threat);
	exp_threat.set_clip();
	if (!ret)
	{
		return 0;
	}



	//-------- Make ThreatObject ---------

	ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];

	for (int t = 0; t < NUM_THREATS; t++)
	{
		ThreatsObject* p_threat = (p_threats + t); 
		if (p_threat)
		{
			ret = p_threat->LoadImg(g_name_threatObject);
			if (!ret)
			{
				return 0;
			}

			int rand_y = rand() % 400;
			if (rand_y > SCREEN_HEIGHT)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}
			p_threat->set_clip();
			p_threat->SetRect(SCREEN_WIDTH + t*400, rand_y);
			p_threat->set_x_val(THREAT_MOVE_SPEED);


			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
		
	}

	


	//-------- Game Loop ----------

	double frame_mainObject = 0;
	double frame_threatObject = 0;

	unsigned int die_number = 0;
	unsigned int point_value = 0;

	while (!is_quit) 
	{
		while (SDL_PollEvent(&g_even)) 
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even, g_sound_bullet);
		}

		


		// Apply background
		bkgn_x -= 0.5;
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if (bkgn_x <= -SCREEN_WIDTH)
		{
			bkgn_x = 0;
		}

		// Show player power
		player_power.Render(g_screen);




		// MainObject Animation
		plane_object.set_frame(frame_mainObject / 7);
		plane_object.ShowMainObject(g_screen);

		plane_object.HandleMove();
		plane_object.MakeAmo(g_screen);

		++frame_mainObject;

		if (frame_mainObject / 7 >= 10)
			frame_mainObject = 0;

		

		//----- Run Threat -----

		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatsObject* p_threat = (p_threats + tt);
			if (p_threat)
			{
				p_threat->set_frame(frame_threatObject / 10);
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->ShowThreatObject(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				++frame_threatObject;

				if (frame_threatObject / 10.0 > 10)
					frame_threatObject = 0;



				// Check collision btw ThreatObject's Bullet & MainObject

				bool is_col1 = false;
				std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
				for (int am = 0; am < amo_arr.size(); am++)
				{
					AmoObject* p_amo = amo_arr.at(am);
					if (p_amo)
					{
						is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(), plane_object.GetRect());
						if (is_col1 == true)
						{
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}
 

				// Check Collision between MainObject & ThreatObject
				bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				
				//----- MainObject's Explosion gfx & sfx-----
				if (is_col || is_col1)
				{

					Mix_PlayChannel(-1, g_sound_exp[1], 0);
					for (int ex = 0; ex < 7; ex++)
					{
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);

						SDL_Delay(50);

						//-------- Update screen --------
						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
							

					}

					die_number++;
					if (die_number <= 2)
					{
						SDL_Delay(1000);
						plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);
						player_power.Decrease();
						player_power.Render(g_screen);

						if (SDL_Flip(g_screen) == -1)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
					else
					{
						// MessageBox
						if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
						{
							delete[] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;

						}
					}

					
				}
				
				// Check collision between MainObject's bullet & ThreatObject
				bool ret_col = false;

				std::vector<AmoObject*> amo_list = plane_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL)
					{
						ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if (ret_col)
						{

							point_value++;


							int ex = 0;
							while (ex < 8 )
							{
								int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXP_WIDTH_2 * 0.5;
								int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXP_HEIGHT_2 * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.ShowEx(g_screen);

								++ex;

								//SDL_Delay(50);

								//-------- Update screen --------
								if (SDL_Flip(g_screen) == -1)
									return 0;
							}

							p_threat->Reset(SCREEN_WIDTH + tt * 400);
							plane_object.RemoveAmo(im);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}

					}
				}
				
			}
			
		}

		// Show time for game
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(SCREEN_WIDTH - 200, 10);
		time_game.CreateGameText(g_font_text, g_screen);


		// Show point value to screen
		std::string val_str_point = std::to_string(point_value);
		std::string strPoint("Points: ");
		strPoint += val_str_point;

		point_game.SetText(strPoint);
		point_game.CreateGameText(g_font_text, g_screen);
		

		//-------- Update screen --------
		if ( SDL_Flip(g_screen) == -1)
			return 0;

	}

	delete[] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
}