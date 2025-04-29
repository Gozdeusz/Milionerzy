#include <allegro5/allegro_font.h>
#include "bitmap.h"
#include "fonts.h"

void DrawScene_Menu(Font* font, Bitmap* bitmap) {

	for (int i = 0; i < 3; i++) {
		al_draw_bitmap(bitmap->blockMenu, 600, 480 + i * 140, 0);
	}
	al_draw_text(font->f_Title, font->c_Main, 900, 150, ALLEGRO_ALIGN_CENTER, "MILIONERZY");
	al_draw_text(font->f_Main, font->c_Main, 900, 510, ALLEGRO_ALIGN_CENTER, "START");
	al_draw_text(font->f_Main, font->c_Main, 900, 650, ALLEGRO_ALIGN_CENTER, "TABLICA WYNIKOW");
	al_draw_text(font->f_Main, font->c_Main, 900, 790, ALLEGRO_ALIGN_CENTER, "WYJSCIE");
	al_draw_bitmap(bitmap->lines, 0, 0, 0);
	al_draw_bitmap(bitmap->background[4], 0, 0, 0);
}

void DrawScene_Result(Font* font, Bitmap* bitmap, short p) {
	al_draw_bitmap(bitmap->background[2], 0, 0, 0);
	al_draw_bitmap(bitmap->blockLost[1], 725, 750, 0);
	al_draw_text(font->f_Main, font->c_Lost, 900, 780, ALLEGRO_ALIGN_CENTER, "MENU");
	al_draw_bitmap(bitmap->blockLost[0], 500, 300, 0);

	//Skontrolowanie gwarantowanej nagrody
	unsigned int win = 0;
	if (p < 2) {
		win = 0;
	}
	else if (p >= 2 && p <= 7) {
		win = 1000;
	}
	else {
		win = 40000;
	}

	al_draw_text(font->f_Main, font->c_Lost, 900, 400, ALLEGRO_ALIGN_CENTER, "TWOJA WYGRANA");
	al_draw_textf(font->f_Win, font->c_Lost, 900, 470, ALLEGRO_ALIGN_CENTER, "%d", win);
}

void DrawScene_Win(Font* font, Bitmap* bitmap, char* n) {
	al_draw_bitmap(bitmap->background[5], 0, 0, 0);
	al_draw_bitmap(bitmap->blockEllipsepe[1], 1600, 830, 0);
	al_draw_text(font->f_MainSmaler, font->c_Main, 1684, 840, ALLEGRO_ALIGN_CENTER, "MENU");

	al_draw_text(font->f_WinGAME, font->c_WinGAME, 900, 210, ALLEGRO_ALIGN_CENTER, "1000000");
	al_draw_textf(font->f_Main, font->c_WinGAME, 900, 600, ALLEGRO_ALIGN_CENTER, "%s", n);
}

void DrawScene_Earyend(Font* font, Bitmap* bitmap, short p, unsigned int money[13]) {
	al_draw_bitmap(bitmap->background[3], 0, 0, 0);
	al_draw_bitmap(bitmap->blockLost[1], 725, 750, 0);
	al_draw_text(font->f_Main, font->c_Lost, 900, 780, ALLEGRO_ALIGN_CENTER, "MENU");
	al_draw_bitmap(bitmap->blockLost[0], 500, 200, 0);

	al_draw_text(font->f_Main, font->c_Lost, 900, 300, ALLEGRO_ALIGN_CENTER, "TWOJA WYGRANA");

	al_draw_textf(font->f_Win, font->c_Lost, 900, 370, ALLEGRO_ALIGN_CENTER, "%d", money[p]);
}

void DrawScene_Scoreboard(Font* font, Bitmap* bitmap) {
	al_draw_text(font->f_Title, font->c_Main, 900, 10, ALLEGRO_ALIGN_CENTER, "WYNIKI");
	al_draw_bitmap(bitmap->blockMenu, 600, 760, 0);
	al_draw_text(font->f_Main, font->c_Main, 900, 790, ALLEGRO_ALIGN_CENTER, "POWROT");

	al_draw_bitmap(bitmap->lines, 0, 0, 0);
	al_draw_bitmap(bitmap->background[4], 0, 0, 0);
}