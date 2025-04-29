#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "fonts.h"
#include "bitmap.h"
#include "GUI_functions.h"
#include "core_functions.h"
#include "G_Scenes.h"
#include "sound.h"
#define screenWidth 1800
#define screenHeight 900
#define maxScores 100

//-------------------------------------------------------------------------------MAIN---------------------------------------------------------------------------------------
int main(void) {
	//Stworzenie ekranu i zdarzenia
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;
	//Uruchamianie biblioteki allegro5
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Blad uruchomienia biblioteki allegro.", NULL, NULL);
		return -1;
	}

	//Tworzenie ekranu
	display = al_create_display(screenWidth, screenHeight);
	if (!display) {
		al_show_native_message_box(NULL, NULL, NULL, "Blad ladowania ekranu.", NULL, NULL);
		return -1;
	}

	//Instalowanie urz¹dzeñ I/O i rozszerzeñ z biblioteki
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_ttf_addon();
	al_init_font_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(3);

	//Ustawienie kolejki zdarzeñ i Ÿróde³ zdarzeñ
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//Tworzenie czcionki, bitmap, stanu blokow pytan, dziwkow, pliku z wynikami

	Font font;
	Bitmap bitmap;
	AnswerBlock answerblock;
	Sound sound;

	FILE* scoreboardFile;
	int scoreCount = 0;
	struct Score scores[5];
	struct Question questions[40];

	//Tworzenie i ustawienie kursora
	ALLEGRO_BITMAP* cursorIMG = NULL;
	ALLEGRO_MOUSE_CURSOR* cursor = NULL;
	cursorIMG = al_load_bitmap("textures/cursor/cursor.png");
	cursor = al_create_mouse_cursor(cursorIMG, 0, 0);
	al_show_mouse_cursor(display);

	//Zmienne "wlaczajace" funkcje
	bool done = true; //W³¹czenie - Glowna petla gry
	bool LBfriend = false; //W³¹czenie - Kolo ratunkowe telefon do przyjaciela
	bool LBaudience = false; //W³¹czenie - Kolo Ratunkowe publicznosc
	bool LB50x50 = false; //W³¹czenie - Kolo ratunkowe 50 na 50
	bool sDimming = false; //W³¹czenie - Przyciemnianie ekranu
	bool isCheckBox = false; //W³¹czenie - CheckBox
	bool isQC = false; //W³¹czenie - InfoBox
	bool isName = false; //W³¹czenie - Pobieranie imienia
	bool isBad = false; //W³¹czenie - Zla odpowiedz
	bool isMenu = false; //W³¹czenie - Mini menu
	bool isLoad = false; //W³aczenie - £adowanie pytañ

	//Pozosta³e zmienne
	short scene = MENU; //Ustawienie sceny poczatkowej na Menu
	unsigned short background_state = 0; //Poczatkowe tlo
	unsigned short host_state = 0; //Poczatkowy stan prowadzacego
	char* nick = NULL; //Zaimplementowanie pustego nicku
	char* result = NULL; //Zmienna przechowujaca wylosowana bleda odpowiedz do kola ratunkowego pol na pol
	char* selectedToCheckAnswer = NULL; //Zmienna ktora przechowuje ktora odpowiedz zostala wybrana i wysyla ja do segmentu sprawdzania odpowiedzi
	int colorStateID = 0; //Zmienna odpowiadajaca za przekazywanie statusu bloku z odpowiedziami
	char selectedID = NULL; //Zmienna ktora ma przekazywac ID odpowiedzi ktora zosta³a wybrana
	short point = 0; //Zmienna przchowujaca punkty kontrolujaca postep w pytaniach (czyli inaczej na którym pytaniu ju¿ jesteœmy)
	unsigned int money[13] = { 0,500,1000,2000,5000,10000,20000,40000,75000,125000,250000,500000,1000000 }; // Tablica zawierajaca liczbe pieniedzy ktore aktualnie wygrywamy

	

	//Za³adowanie czacionek bitmap, danych blokoów, dziekow, eventow:
	al_set_mouse_cursor(display, cursor);
	LoadFonts(&font);
	LoadBitmaps(&bitmap);
	CreatingDimensionBlocks(&sLifebelt, &Player);
	LoadSounds(&sound);


	//Tworzenie muzyki grajacejw tle
	ALLEGRO_SAMPLE_INSTANCE* enter; //Muzyka na wejscie do gry
	ALLEGRO_SAMPLE_INSTANCE* main; //Muzyka na glowna gra
	ALLEGRO_SAMPLE_INSTANCE* re; //Muzyka na ekran przegranej
	enter = al_create_sample_instance(sound.Enter); 
	main = al_create_sample_instance(sound.Main); 
	re = al_create_sample_instance(sound.Result); 
	al_set_sample_instance_playmode(enter, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(main, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(re, ALLEGRO_PLAYMODE_LOOP);
	//Ustawienie muzyki aby grala w tle caly czas
	al_attach_sample_instance_to_mixer(enter, al_get_default_mixer());
	al_play_sample_instance(enter);
	//Ustawienie ikony
	al_set_display_icon(display, bitmap.icon);
	


	//Wyœwietlanie ekranu:
	while (done)
	{
		al_clear_to_color(al_map_rgb(17, 43, 29));
		al_wait_for_event(event_queue, &ev);
		//Tworzenie scen:
		switch (scene) {
			//Menu:
		case MENU: {
			//Wlaczenie muzyki na wejscie, rysowanie menu
			al_play_sample(sound.Enter, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP_ONCE, NULL);
			DrawScene_Menu(&font, &bitmap);

			//Interakcja z przyciskami menu:
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				//Przejscie do g³ownej gry:
				if (ev.mouse.x > 600 && ev.mouse.x < 1200 && ev.mouse.y > 480 && ev.mouse.y < 580) {
					//Ustawienie dzieku klikniecia i zatrzymanie muzyki grajacej na wejscie
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					al_stop_sample_instance(enter);
					//Zerowanie wszytskich wartosci gry:
					//Statusow graficznych kol ratunkowych
					sLifebelt.stateAudienceLB = 0;
					sLifebelt.stateFriendLB = 2;
					sLifebelt.stateHalfLB = 4;
					//Statusow blokow z pytaniami
					selectedID = 'R';
					//Statusu prowadzacego
					host_state = 0;
					//Liczby punktow
					point = 0;
					//Wlaczenie funkcji pobierajacej imie
					isName = true;
					//Wylaczenie kola ratunkowego 50x50
					LB50x50 = false;
					//Wlaczenie mozliwosci aktywacji kola ratunkowego
					Player.LifebelHalfAndHalfClicked = false;
					Player.LifebelPhoneCallToFriendClicked = false;
					Player.LifebeltAudienceVoteClicked = false;
					//Wlaczenie mozliwosci zaladowania pierszej puli pytan
					isLoad = true;
					//Wlaczenie przyciemniania ekranu
					sDimming = true;
					ScreenDimming(&sDimming);
					//Wlaczenie muzyki dla gry glownej
					al_attach_sample_instance_to_mixer(main, al_get_default_mixer());
					scene = MAINGAME;
				}
				//Przejscie do tablicy wyników:
				else if (ev.mouse.x > 600 && ev.mouse.x < 1200 && ev.mouse.y > 620 && ev.mouse.y < 720) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					scene = SCOREBOARD;
				}
				//Wyjscie z gry z zaputaniem czy chcemy napewno  wyjœæ
				//Ekran jest przyciemniany funkcj¹ rysujaca prostokat z ustawionym kanalem alfa
				else if (ev.mouse.x > 600 && ev.mouse.x < 1200 && ev.mouse.y > 760 && ev.mouse.y < 860) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					//Rysowanie efektu przyciemnienia ekranu
					al_draw_bitmap(bitmap.lines, 0, 0, 0);
					al_draw_filled_rectangle(0, 0, 1800, 900, al_map_rgba(1, 1, 1, 150));
					if (CheckBox(&font, &bitmap, &sound, display, &isCheckBox, "Napewno chcesz wyjsc z gry?")) {
						al_stop_sample_instance(enter);
						//Ukrycie myszki
						al_hide_mouse_cursor(display);
						//Wlaczenie przyciemniania ekranu
						sDimming = true;
						ScreenDimming(&sDimming);
						done = false;
					}
				}
			}

			break;
		}
			//Tablica wyników:
		case SCOREBOARD: {
			//Zaladowanie pliku z wynikami
			scoreboardFile = fopen("scoreboard.txt", "r");
			for (int i = 0; i < 5; i++) {
				read_score(&scores[i], scoreboardFile);
			}
			fclose(scoreboardFile);

			//Rysowanie tabelki, na chwilê obecn¹ bez uzupe³nienia jej wynikami
			for (int i = 0; i < 5; i++) {

				al_draw_bitmap(bitmap.blockScoreboard, 400, 235 + (i * 105), 0);
				al_draw_textf(font.f_Main, font.c_Main, 387 + 30, 245 + (i * 105) + 20, ALLEGRO_ALIGN_LEFT, "%d", i + 1);
				al_draw_textf(font.f_Main, font.c_Main, 387 + 110, 245 + (i * 105) + 20, ALLEGRO_ALIGN_LEFT, "%s", scores[i].nick);
				al_draw_textf(font.f_Main, font.c_Main, 387 + 820, 245 + (i * 105) + 20, ALLEGRO_ALIGN_CENTER, "%s zloty", scores[i].points);

			}
			//Interakcja z przyciskiem powrót
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (ev.mouse.x > 600 && ev.mouse.x < 1200 && ev.mouse.y > 760 && ev.mouse.y < 860) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					scene = MENU;
				}
			}
			DrawScene_Scoreboard(&font, &bitmap);

			break;
		}
			//G³ówna gra:
		case MAINGAME: {
			//Ladowanie puli pytan w zaleznosci od trudnosci
			if (point < 2 && isLoad ) {
				//Otwarcie pliku z pytaniami
				FILE* file_easy = fopen("questions-easy.txt", "r");
				//Za³adowanie pytañ
				for (int i = 0; i < 40; i++) {
					read_question(&questions[i], file_easy);
				}
				isLoad = false;
				setQuestionQueue(&questions);
				dequeue();
				fclose(file_easy);
			}
			else if (point == 2 && isLoad) {
				//Otwarcie pliku z pytaniami
				FILE* file_normal = fopen("questions-normal.txt", "r");
				//Za³adowanie pytañ
				for (int i = 0; i < 40; i++) {
					read_question(&questions[i], file_normal);
				}
				isLoad = false;
				setQuestionQueue(&questions);
				dequeue();
				fclose(file_normal);
			}
			else if (point == 7 && isLoad){
				//Otwarcie pliku z pytaniami
				FILE* file_hard = fopen("questions-hard.txt", "r");
				//Za³adowanie pytañ
				for (int i = 0; i < 40; i++) {
					read_question(&questions[i], file_hard);
				}
				isLoad = false;
				setQuestionQueue(&questions);
				dequeue();
				fclose(file_hard);
			} 

			//Pobieranie imienia
			if (isName) {
				nick = GetName(&font, &bitmap, &sound, display, &isName);
				if (strlen(nick) <= 0) {
					nick = "<NONAME>";
				}
				sDimming = true;
				ScreenDimming(&sDimming);
				al_play_sample_instance(main);
			}

			//Interakcja z ekranem gry
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				//Wybranie odpowiedzi A
				if (ev.mouse.x > 100 && ev.mouse.x < 800 && ev.mouse.y > 730 && ev.mouse.y < 790) {
					selectedID = 'A';
					selectedToCheckAnswer = "A";
					colorStateID = 1;
					isCheckBox = true;
					host_state = 1;

				}
				//Wybranie odpowedzi B
				if (ev.mouse.x > 1000 && ev.mouse.x < 1700 && ev.mouse.y > 730 && ev.mouse.y < 790) {
					selectedID = 'B';
					selectedToCheckAnswer = "B";
					colorStateID = 1;
					isCheckBox = true;
					host_state = 1;
				}
				//Wybranie odpowiedzi C
				else if (ev.mouse.x > 100 && ev.mouse.x < 800 && ev.mouse.y > 810 && ev.mouse.y < 870) {
					selectedID = 'C';
					selectedToCheckAnswer = "C";
					colorStateID = 1;
					isCheckBox = true;
					host_state = 1;
				}
				//Wybranie odpowiedzi D
				else if (ev.mouse.x > 1000 && ev.mouse.x < 1700 && ev.mouse.y > 810 && ev.mouse.y < 870) {
					selectedID = 'D';
					selectedToCheckAnswer = "D";
					colorStateID = 1;
					isCheckBox = true;
					host_state = 1;

				}
				//Ko³a ratunkowe:
					//G³osowanie publicznoœci:
				else if (ev.mouse.x > 50 && ev.mouse.x < 50 + 113 && ev.mouse.y > 310 && ev.mouse.y < 310 + 75 && !Player.LifebeltAudienceVoteClicked) {
					al_play_sample(sound.LBaudience, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					Player.LifebeltAudienceVoteClicked = true;
					LBaudience = true;
					host_state = 6;
					background_state = 1;
					sLifebelt.stateAudienceLB = 1;
				}
				//Telefon do przyjaciela:
				else if (ev.mouse.x > 50 && ev.mouse.x < 50 + 113 && ev.mouse.y > 390 && ev.mouse.y < 390 + 75 && !Player.LifebelPhoneCallToFriendClicked) {
					al_play_sample(sound.LBfriend, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					Player.LifebelPhoneCallToFriendClicked = true;
					LBfriend = true;
					sLifebelt.stateFriendLB = 3;

				}
				//Pó³ na pó³:
				else if (ev.mouse.x > 50 && ev.mouse.x < 50 + 113 && ev.mouse.y > 470 && ev.mouse.y < 470 + 75 && !Player.LifebelHalfAndHalfClicked) {
					al_play_sample(sound.LB50x50, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					host_state = 4;
					Player.LifebelHalfAndHalfClicked = true;
					LB50x50 = true;
					result = LifebelHalfAndHalf(Question_pointers.head->correct_ans);
					sLifebelt.stateHalfLB = 5;

				}
				//Przycisk menu:
				else if (ev.mouse.x > 25 && ev.mouse.x < 175 && ev.mouse.y > 25 && ev.mouse.y < 75) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					isMenu = true;
					host_state = 6;
				}
			}

			//Rysowanie t³a
			al_draw_bitmap(bitmap.background[background_state], 0, 0, 0);
			//Tworzenie  przycisku menu
			al_draw_bitmap(bitmap.blockSquare[2], 25, 25, 0);
			al_draw_text(font.f_MainSmaler, font.c_Main, 102, 35, ALLEGRO_ALIGN_CENTER, "MENU");
			//Rysowanie prowadzacego
			al_draw_bitmap(bitmap.host[host_state], 0, 0, 0);
			//Rysowanie interfejsu
			DrawMoney(&font, &bitmap, &money, point);
			DrawingGUI(&font, &bitmap, &answerblock, colorStateID, selectedID, questions, Question_pointers.head->correct_ans, LB50x50, result);
			DrawLifeBelt(&sLifebelt, &bitmap);

			//Telefon do przyjaciela funkcja
			if (Player.LifebelPhoneCallToFriendClicked == true && LBfriend == true) {
				LifebeltPhoneCallToFriend_Display(&font, &bitmap, display, LifebelPhoneCallToFriend(Question_pointers.head->correct_ans));
				LBfriend = false;
			}

			//Glosowanie publicznosci
			if (Player.LifebeltAudienceVoteClicked == true && LBaudience == true) {
				Audience(&font, &bitmap, display, Question_pointers.head->correct_ans);
				LBaudience = false;
				host_state = 0;
				background_state = 0;
			}

			//Klikniecie przycisku Menu:
			if (isMenu) {
				al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				short s = miniMenu(&font, &bitmap, &display, &isMenu);
				if (s==EARLYEND) {
					isCheckBox = true;
					if (CheckBox(&font, &bitmap, &sound, display, &isCheckBox, "Chcesz zakonczyc wczesniej gre?")) {
						al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						al_stop_sample_instance(main);
						scene = s;
						al_play_sample(sound.EarlyEnd, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					}
					else {
						al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						host_state = 0;
					}
				}
				else {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					host_state = 0;
				}
			}

			//Sprawdzanie odpowiedzi:
			if (isCheckBox == true) {
				//Pytanie czy chcemy juz udzielic odpowiedzi i ja sprawdziæ
				if (CheckBox(&font, &bitmap, &sound, display, &isCheckBox, "Chcesz sprawdzic odpowiedz?")) {
					//Jezeli chcemy:
					if (strncmp(Question_pointers.head->correct_ans, selectedToCheckAnswer, 1) == 0) {
						//Dobra odpowiedŸ
						point += 1;
						isQC = true;
						colorStateID = 2;
						host_state = 2;
						continue;
					}
					else {
						//Z³a odpowiedŸ
						colorStateID = 3;
						isBad = true;
						host_state = 3;
						continue;

					}
				}
				//Jezeli nie chcemy zaznaczona odpowiedz znika:
				else {
					colorStateID = 0;
					host_state = 0;

				}
			}

			//Informacja ze odpowiedz jest poprawna
			if (isQC == true) {
				al_stop_sample_instance(main);
				al_play_sample(sound.Good, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				InfoBox(&font, &bitmap, &sound, display, &isQC, "Poprawna odpowiedz!");
				LB50x50 = false;
				//Warunki wloaczajace zaladowanie innych trudnosci pytan
				if (point == 2) {
					isLoad = true;
				}
				else if (point == 7) {
					isLoad = true;
				}
				dequeue();
				host_state = 0;
				colorStateID = 0;
				al_play_sample_instance(main);
				if (point == 13)
					al_play_sample(sound.Milion, 1.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			//Zla odpowiedz
			if (isBad == true) {
				al_stop_sample_instance(main);
				al_play_sample(sound.Lost, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				InfoBox(&font, &bitmap, &sound, display, &isBad, "...");
				sDimming = true;
				ScreenDimming(&sDimming);
				scene = LOSTGAME;
			}

			//Informacja o wygraniu miliona
			if (point == 13) {
				al_stop_sample_instance(main);
				InfoBox(&font, &bitmap, &sound, display, &isQC, "!Wygrales Milion!");
				al_play_sample(sound.WinScene, 3.0, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
				scene = WIN;
			}
			break;
		}
			//Wczeœniejsze zakoñczenie gry:
		case EARLYEND: {
			//Rysowanie sceny:
			DrawScene_Earyend(&font, &bitmap, point, money);
			//Interakcja z ekranem - przejœcie do menu
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (ev.mouse.x > 725 && ev.mouse.x < 1075 && ev.mouse.y > 750 && ev.mouse.y < 850) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					//Zapis wyników
					scoreboardFile = fopen("scoreboard.txt", "r+");
					save_score(nick, money[point], scoreboardFile);
					fclose(scoreboardFile);
					//Przyciemnianie ekranu
					sDimming = true;
					ScreenDimming(&sDimming);
					al_play_sample_instance(enter);
					scene = MENU;
				}
			}
			break;
		}
			//Ekran przegranej gry:
		case LOSTGAME: {
			//Wysiwtlanie ekranu 
			al_play_sample(sound.End, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			al_draw_filled_rectangle(0, 0, 1800, 900, al_map_rgb(0, 0, 0));
			InfoBox(&font, &bitmap, &sound, display, &isQC, "Przegrales...");
			//Zapis do pliku z wynikami
			unsigned int win = 0;
			if (point < 2) {
				win = 0;
			}
			else if (point >= 2 && point <= 7) {
				win = 2;
			}
			else {
				win = 7;
			}
			scoreboardFile = fopen("scoreboard.txt", "r+");
			save_score(nick, money[win], scoreboardFile);
			fclose(scoreboardFile);

			sDimming = true;
			ScreenDimming(&sDimming);
			al_attach_sample_instance_to_mixer(re, al_get_default_mixer());
			al_play_sample_instance(re);
			scene = RESULT;
			break;
		}
			//Ekran podsumowania:
		case RESULT: {
			//Rysowanie sceny:
			DrawScene_Result(&font, &bitmap, point);

			//Interakcja z ekranem - przejœcie do menu
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (ev.mouse.x > 725 && ev.mouse.x < 1075 && ev.mouse.y > 750 && ev.mouse.y < 850) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					sDimming = true;
					ScreenDimming(&sDimming);
					al_stop_sample_instance(re);
					al_play_sample_instance(enter);
					scene = MENU;
				}

			}
			break;

		}
			//Ekran wygranej:
		case WIN: {
			//Rysowanie sceny:
			DrawScene_Win(&font, &bitmap, nick);

			//Interakcja z ekranem - przejœcie do menu
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (ev.mouse.x > 1600 && ev.mouse.x < 1760 && ev.mouse.y > 830 && ev.mouse.y < 880) {
					al_play_sample(sound.Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					scoreboardFile = fopen("scoreboard.txt", "r+");
					save_score(nick, money[12], scoreboardFile);
					fclose(scoreboardFile);
					sDimming = true;
					ScreenDimming(&sDimming);
					al_play_sample_instance(enter);
					scene = MENU;
				}
			}
			break;
		}

		}

		//Wyjscie z programu przyciskiem "X" na pasku ekranu
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			al_hide_mouse_cursor(display);
			done = false;
		}
		//Aktualizowanie ekranu
		al_flip_display();

	}

	//Zwolnienie miejsca w pamiêci
	al_destroy_mouse_cursor(cursor);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	destroyBitmaps(&bitmap);
	destroyFont(&font);
	destroySound(&sound);
}

