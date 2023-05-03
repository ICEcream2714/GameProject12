
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "ExplosionObject2.h"
#include "PlayerPower.h"
#include "TextObject.h"
#include "BossObject.h"
#include "ItemObject.h"



TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;

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

	g_font_text = TTF_OpenFont(g_name_font_score, 20);
	g_font_menu = TTF_OpenFont(g_name_font_score, 35);
	if (g_font_text == NULL || g_font_menu == NULL)
	{
		return false;
	}

	

	return true;
}


int main(int arc, char*argv[])
{
	srand(time(NULL));

	double bkgn_x = 0;

	bool is_quit = false;
	if (Init() == false)
		return 0;


	SDL_WM_SetCaption("Space War", "gfx/Icon1.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("gfx/Icon1.bmp"), NULL);

	//--------- Apply background ---------


	g_bkground = SDLCommonFunc::LoadImage(g_name_background);
	if (g_bkground == NULL)
	{
		return 0;
	}

	Mix_PlayMusic(g_background_music, -1);


	unsigned int highest_score_value = 0;
	int pre_time_val = 0;

	// Make random y
	int main_rand_y = rand() % 600 + 60;


SetRestart:

	int max_boss_hit = MAX_BOSS_HIT_COUNT;

	int boss_time = 0;

	// ------ Player Power ------

	PlayerPower player_power;
	player_power.Init();


	// ------ Init Texts... ------

	TextObject score_game;
	score_game.SetColor(TextObject::WHITE_TEXT);

	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject high_score;
	high_score.SetColor(TextObject::WHITE_TEXT);



	//------- Init MainObject ---------

	MainObject plane_object;
	bool ret = plane_object.LoadImg(g_name_mainObject);
	plane_object.set_clip();
	plane_object.SetRect(POS_X_START_MAIN_OBJ, main_rand_y) ;
	if (!ret)
	{
		return 0;
	}


	// ------- Init BossObject -------

	BossObject boss_object;
	ret = boss_object.LoadImg(g_name_boss_object);
	if (!ret)
	{
		return 0;
	}
	boss_object.set_clip();
	boss_object.set_x_val(BOSS_MOVE_SPEED);

	AmoObject* p_amo_boss = new AmoObject();
	boss_object.InitAmo(p_amo_boss);


	// -------- Init Health Item --------

	ItemObject health_item;
	ret = health_item.LoadImg(g_name_health_item);
	if (!ret)
		return 0;
	health_item.set_x_val(SPEED_HEALTH_ITEM);


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



	//-------- Init ThreatObject ---------

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

	

	// Variables for GameLoop
	

	double frame_mainObject = 0;
	double frame_threatObject = 0;
	double frame_bossObject = 0;

	unsigned int die_number = 0;
	unsigned int score_value = 0;

	int boss_hit_cnt = 0;

	Uint32 time_val = SDL_GetTicks() / 1000 - pre_time_val;

	double y_amo = 0;
	bool boss_die = true;
	bool exit = false;
	bool show_health_item = false;

	bool is_invicible = false;
	Uint32 time_invicible = 0;


	// Init Main Menu

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_menu);
	if (ret_menu == 1)
	{
		is_quit = true;
	}
	if (ret_menu == 0)
	{
		pre_time_val += time_val;
	}


	//-------- Game Loop ----------

	while (!is_quit) 
	{
		while (SDL_PollEvent(&g_even)) 
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			plane_object.HandleInputAction(g_even, g_sound_bullet, exit);
		}
		
		if (exit){
			pre_time_val += time_val;
			goto SetRestart;
		}

		if (time_val < time_invicible){
			is_invicible = true;
		}
		else
			is_invicible = false;

		if (boss_die == true){
			boss_hit_cnt == 0;
		}
		else
		{

		}
		

		main_rand_y = rand() % 600 + 60;

		time_val = SDL_GetTicks() / 1000 - pre_time_val;

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


		// ------- Run BossObject -------

		if (time_val % TIME_UNTIL_BOSS == 0 && (time_val - boss_time) > TIME_UNTIL_BOSS &&
			boss_die == true && boss_hit_cnt < max_boss_hit)
		{
			max_boss_hit += ADD_MAX_BOSS_HIT_COUNT;
			boss_die = false;
		}

		// ------- Show Health Item -------

		if (show_health_item == true)
		{
			health_item.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			health_item.Show(g_screen);

			// Check collision btw MainObject & HealthItem

			bool health_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), health_item.GetRect());

			if (health_col)
			{
				die_number--;

				player_power.Increase();
				player_power.Render(g_screen);

				//-------- Update screen --------
				if (SDL_Flip(g_screen) == -1)
				{
					SDLCommonFunc::CleanUp();
					SDL_Quit();
					return 0;
				}

				show_health_item = false;

				health_item.Reset(SCREEN_WIDTH);
			}
			else if (health_item.GetRect().x == -WIDTH_HEALTH_ITEM)
			{
				show_health_item = false;
				health_item.Reset(SCREEN_WIDTH);
			}
				
		}

		if (time_val > TIME_UNTIL_BOSS)
		{
			if (boss_hit_cnt < max_boss_hit && boss_die == false)
			{

				boss_object.set_frame(frame_bossObject / 7);
				boss_object.HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				boss_object.ShowBossObject(g_screen);

				y_amo += 0.2;
				if (y_amo >= 1)
				{
					y_amo = 0;
				}
				boss_object.MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, y_amo);


				++frame_bossObject;

				if (frame_bossObject / 7 >= 10)
					frame_bossObject = 0;


				// Check collision btw BossObject's Missile & MainObject
				// Check collision btw MainObject & BossObject

				bool is_col_boss = SDLCommonFunc::CheckCollision(plane_object.GetRect(), boss_object.GetRect());

				bool is_col_missile = false;

				std::vector<AmoObject*> missile_arr = boss_object.GetAmoList();
				for (int m = 0; m < missile_arr.size(); m++)
				{
					AmoObject* p_missile = missile_arr.at(m);
					if (p_missile)
					{
						is_col_missile = SDLCommonFunc::CheckCollision(p_missile->GetRect(), plane_object.GetRect());
						if (is_col_missile == true)
						{
							boss_object.ResetAmo(p_missile);
							break;
						}
					}
				}

				if ((is_col_missile || is_col_boss) && is_invicible == false)
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
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}

					}

					die_number++;
					if (die_number <= 2)
					{
						SDL_Delay(1000);
						time_invicible = time_val + MAINOBJECT_TIME_INVICIBLE;
						plane_object.SetRect(POS_X_START_MAIN_OBJ, main_rand_y);
						player_power.Decrease();
						player_power.Render(g_screen);

						//-------- Update screen --------
						if (SDL_Flip(g_screen) == -1)
						{
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}

					}
					else
					{
						SDL_Delay(1500);
						pre_time_val += time_val;
						goto SetRestart;

					}


				}

				// Check collision btw MainObject's bullet & BossObject

				bool hit_col = false;

				std::vector<AmoObject*> amo_list_1 = plane_object.GetAmoList();
				for (int im = 0; im < amo_list_1.size(); im++)
				{
					AmoObject* p_amo = amo_list_1.at(im);
					if (p_amo != NULL)
					{
						hit_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), boss_object.GetRect());
						if (hit_col)
						{

							boss_hit_cnt++;

							int ex = 0;
							while (ex < 8)
							{
								int x_pos = p_amo->GetRect().x - EXP_WIDTH_2 * 0.5;
								int y_pos = p_amo->GetRect().y - EXP_HEIGHT_2 * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.ShowEx(g_screen);

								++ex;

								//SDL_Delay(50);

								//-------- Update screen --------
								if (SDL_Flip(g_screen) == -1)
									return 0;
							}

							if (boss_hit_cnt == max_boss_hit)
							{
								score_value += max_boss_hit - ADD_MAX_BOSS_HIT_COUNT;
								boss_time = time_val;

								show_health_item = true;

								for (int m = 0; m < missile_arr.size(); m++)
								{
									AmoObject* p_missile = missile_arr.at(m);
									if (p_missile)
									{
										boss_object.ResetAmo(p_missile);
									}
								}

							}

							plane_object.RemoveAmo(im);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}

					}
				}



			}

			else
			{
				boss_die = true;
				boss_hit_cnt = 0;
				
				boss_object.set_frame(frame_bossObject / 7);
				boss_object.HandleMoveBackward(SCREEN_WIDTH, SCREEN_HEIGHT);
				boss_object.ShowBossObject(g_screen);

				++frame_bossObject;

				if (frame_bossObject / 7 >= 10)
					frame_bossObject = 0;

			}
			
		}

		// ------- Run Threat -------

		for (int tt = 0; tt < NUM_THREATS; tt++)
		{
			
			ThreatsObject* p_threat = (p_threats + tt);
			if (p_threat)
			{
				p_threat->set_frame(frame_threatObject / 15);
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->ShowThreatObject(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				++frame_threatObject;

				if (frame_threatObject / 15 >= 10)
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
				if ((is_col || is_col1) && is_invicible == false)
				{

					Mix_PlayChannel(-1, g_sound_exp[1], 0);
					for (int ex = 0; ex < 7; ex++)
					{
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);

						if (is_col)
						{
							int x_pos1 = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXP_WIDTH_2 * 0.5;
							int y_pos1 = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXP_HEIGHT_2 * 0.5;

							exp_threat.set_frame(ex);
							exp_threat.SetRect(x_pos1, y_pos1);
							exp_threat.ShowEx(g_screen);
						}

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

					p_threat->Reset(SCREEN_WIDTH);

					die_number++;
					if (die_number <= 2)
					{
						SDL_Delay(1000);
						time_invicible = time_val + MAINOBJECT_TIME_INVICIBLE;
						plane_object.SetRect(POS_X_START_MAIN_OBJ, main_rand_y);
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
						delete[] p_threats;
						SDL_Delay(1500);
						pre_time_val += time_val;
						goto SetRestart;
						
						//// MessageBox
						//if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
						//{
						//	delete[] p_threats;
						//	SDLCommonFunc::CleanUp();
						//	SDL_Quit();
						//	return 1;

						//}
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

							score_value++;


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

		/*

		// Show time for game
		std::string str_time = "TIME ";
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(SCREEN_WIDTH - 270, 40);
		time_game.CreateGameText(g_font_text, g_screen);

		*/
		

		// Show score value to screen

		std::string val_str_score = std::to_string(score_value);
		std::string strscore("SCORE: ");
		strscore += val_str_score;

		score_game.SetText(strscore);
		score_game.CreateGameText(g_font_text, g_screen);


		// Show high score to screen

		if (highest_score_value < score_value)
		{
			highest_score_value = score_value;
		}

		std::string val_str_hScrore = std::to_string(highest_score_value);
		std::string strHighScore("HIGHSCORE: ");
		strHighScore += val_str_hScrore;

		high_score.SetText(strHighScore);
		high_score.SetRect(SCREEN_WIDTH - 270, 10);
		high_score.CreateGameText(g_font_text, g_screen);
		

		//-------- Update screen --------
		if ( SDL_Flip(g_screen) == -1)
			return 0;

	}


	delete[] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
	
}