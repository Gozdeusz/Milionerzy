#ifndef SOUND_H
#define SOUND_H

//Struktura przchowujaca dzwieki
typedef struct {
	ALLEGRO_SAMPLE* Good;
	ALLEGRO_SAMPLE* bQ;
	ALLEGRO_SAMPLE* Click;
	ALLEGRO_SAMPLE* Lost;
	ALLEGRO_SAMPLE* End;
	ALLEGRO_SAMPLE* Enter;
	ALLEGRO_SAMPLE* Main;
	ALLEGRO_SAMPLE* Result;
	ALLEGRO_SAMPLE* EarlyEnd;
	ALLEGRO_SAMPLE* LB50x50;
	ALLEGRO_SAMPLE* LBfriend;
	ALLEGRO_SAMPLE* LBaudience;
	ALLEGRO_SAMPLE* Milion;
	ALLEGRO_SAMPLE* WinScene;
} Sound;

//Zaladowanie dzwiekow
void LoadSounds(Sound* sound);
//Zwolnienie pamieci
void destroySound(Sound* sound);

#endif 