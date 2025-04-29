#ifndef BITMAP_H
#define BITMAP_H
//Typ strukturalny zawierający wszytskie używane bitmapy
typedef struct {

	ALLEGRO_BITMAP* blockAnswer[5];
	ALLEGRO_BITMAP* blockSquare[5];
	ALLEGRO_BITMAP* blockEllipsepe[2];
	ALLEGRO_BITMAP* blockLost[2];
	ALLEGRO_BITMAP* blockQuestion;
	ALLEGRO_BITMAP* blockMenu;
	ALLEGRO_BITMAP* blockMoney[3];
	ALLEGRO_BITMAP* blockScoreboard;
	ALLEGRO_BITMAP* blockFriendLB;
	ALLEGRO_BITMAP* host[7];
	ALLEGRO_BITMAP* lifebelt[6];
	ALLEGRO_BITMAP* background[6];
	ALLEGRO_BITMAP* lines;
	ALLEGRO_BITMAP* icon;

} Bitmap;

//Typ strukturalny zawierający stany blokow odpowiedzi
typedef struct {
	ALLEGRO_BITMAP* blockA;
	ALLEGRO_BITMAP* blockB;
	ALLEGRO_BITMAP* blockC;
	ALLEGRO_BITMAP* blockD;
} AnswerBlock;

//Funkcja ładująca wszytskie bitmapy
void LoadBitmaps(Bitmap* structBitmap);

//Zwolnienie pamieci
void destroyBitmaps(Bitmap* bitmap);

#endif 
