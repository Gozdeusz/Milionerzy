#ifndef FONTS_H
#define FONTS_H

//Typ structuralny ktory przechowuje czcionki i kolory czcionek
typedef struct {
	ALLEGRO_FONT* f_Main;
	ALLEGRO_FONT* f_MainSmaler;
	ALLEGRO_FONT* f_SideButtons;
	ALLEGRO_FONT* f_MainSmalest;
	ALLEGRO_FONT* f_MainMoney;
	ALLEGRO_FONT* f_Title;
	ALLEGRO_FONT* f_Win;
	ALLEGRO_FONT* f_CheckBox;
	ALLEGRO_FONT* f_WinGAME;

	ALLEGRO_COLOR c_Main;
	ALLEGRO_COLOR c_AnswerLetter;
	ALLEGRO_COLOR c_Box;
	ALLEGRO_COLOR c_Lost;
	ALLEGRO_COLOR c_WinGAME;
} Font;

//Ladowanie czcionek i kolorow
void LoadFonts(Font *fontStruct);
//Zwolnienie pamieci
void destroyFont(Font* font);

#endif 
