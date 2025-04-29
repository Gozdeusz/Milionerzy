#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "fonts.h"

void LoadFonts(Font *structFont) {
	structFont->f_Main = al_load_font("fonts/font-ttf/font_3.ttf", 50, 0);
	structFont->f_MainSmaler = al_load_font("fonts/font-ttf/font_3.ttf", 40, 0);
	structFont->f_MainSmalest = al_load_font("fonts/font-ttf/font_3.ttf", 25, 0);
	structFont->f_MainMoney = al_load_font("fonts/font-ttf/font_14.ttf", 20, 0);
	structFont->f_SideButtons = al_load_font("fonts/font-ttf/font_18.ttf", 20, 0);
	structFont->f_Title = al_load_font("fonts/font-ttf/font_14.ttf", 190, 0);
	structFont->f_Win = al_load_font("fonts/font-ttf/font_14.ttf", 130, 0);
	structFont->f_WinGAME = al_load_font("fonts/font-ttf/font_14.ttf", 200, 0);

	structFont->c_Main = al_map_rgb(59, 180, 122);
	structFont->c_AnswerLetter = al_map_rgb(16, 193, 46);
	structFont->c_Box = al_map_rgb(111, 168, 138);
	structFont->c_Lost = al_map_rgb(130, 169, 148);
	structFont->c_WinGAME = al_map_rgb(70, 114, 91);
}

void destroyFont(Font* font) {
    al_destroy_font(font->f_Main);
    al_destroy_font(font->f_MainSmaler);
    al_destroy_font(font->f_SideButtons);
    al_destroy_font(font->f_MainSmalest);
    al_destroy_font(font->f_MainMoney);
    al_destroy_font(font->f_Title);
    al_destroy_font(font->f_Win);
    al_destroy_font(font->f_WinGAME);
}