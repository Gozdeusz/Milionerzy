#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "sound.h"

void LoadSounds(Sound* sound) {
	sound->Good = al_load_sample("sounds/Good_Answer.wav");
	sound->bQ = al_load_sample("sounds/bQuestion.wav");
	sound->Click = al_load_sample("sounds/Click.wav");
	sound->Lost = al_load_sample("sounds/Lost.wav");
	sound->End = al_load_sample("sounds/End.wav");
	sound->Result = al_load_sample("sounds/Result.wav");
	sound->Enter = al_load_sample("sounds/Enter.mp3");
	sound->Main = al_load_sample("sounds/Main.mp3");
	sound->EarlyEnd = al_load_sample("sounds/Early.wav");
	sound->LB50x50 = al_load_sample("sounds/50x50.wav");
	sound->LBfriend = al_load_sample("sounds/phone.wav");
	sound->LBaudience = al_load_sample("sounds/audience.wav");
	sound->Milion = al_load_sample("sounds/WINGAME.wav");
	sound->WinScene = al_load_sample("sounds/Aplause.wav");
}

void destroySound(Sound* sound) {
    al_destroy_sample(sound->Good);
    al_destroy_sample(sound->bQ);
    al_destroy_sample(sound->Click);
    al_destroy_sample(sound->Lost);
    al_destroy_sample(sound->End);
    al_destroy_sample(sound->Enter);
    al_destroy_sample(sound->Main);
    al_destroy_sample(sound->Result);
    al_destroy_sample(sound->EarlyEnd);
    al_destroy_sample(sound->LB50x50);
    al_destroy_sample(sound->LBfriend);
    al_destroy_sample(sound->LBaudience);
    al_destroy_sample(sound->Milion);
    al_destroy_sample(sound->WinScene);
}