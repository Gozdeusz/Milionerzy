#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "bitmap.h"

void LoadBitmaps(Bitmap* structBitmap) {

	structBitmap->blockAnswer[0] = al_load_bitmap("textures/block/answer-block-basic.png");
	structBitmap->blockAnswer[1] = al_load_bitmap("textures/block/answer-block-marked.png");
	structBitmap->blockAnswer[2] = al_load_bitmap("textures/block/answer-block-good.png");
	structBitmap->blockAnswer[3] = al_load_bitmap("textures/block/answer-block-bad.png");
	structBitmap->blockAnswer[4] = al_load_bitmap("textures/block/answer-block-lifebelt-galf-and-half-marked.png");

	structBitmap->blockSquare[0] = al_load_bitmap("textures/block/block-square-800x500.png");
	structBitmap->blockSquare[1] = al_load_bitmap("textures/block/block-square-800x300.png");
	structBitmap->blockSquare[2] = al_load_bitmap("textures/block/button-box-square.png");
	structBitmap->blockSquare[3] = al_load_bitmap("textures/block/button-box-square-400x100.png");
	structBitmap->blockSquare[4] = al_load_bitmap("textures/block/block-square-500x400.png");

	structBitmap->blockEllipsepe[0] = al_load_bitmap("textures/block/block-box-ellipse.png");
	structBitmap->blockEllipsepe[1] = al_load_bitmap("textures/block/button-box-ellipse.png");

	structBitmap->blockLost[0] = al_load_bitmap("textures/block/block-square-lost-800x400.png");
	structBitmap->blockLost[1] = al_load_bitmap("textures/block/button-lost.png");

	structBitmap->blockMoney[0] = al_load_bitmap("textures/block/money-block-basic.png");
	structBitmap->blockMoney[1] = al_load_bitmap("textures/block/money-block-now.png");
	structBitmap->blockMoney[2] = al_load_bitmap("textures/block/money-block-guaranted.png");

	structBitmap->blockQuestion = al_load_bitmap("textures/block/question-block.png");

	structBitmap->blockMenu = al_load_bitmap("textures/block/menu-button-block.png");

	structBitmap->blockScoreboard = al_load_bitmap("textures/block/block-table.png");

	structBitmap->blockFriendLB = al_load_bitmap("textures/block/lifebelt-block-half-and-half.png");

	structBitmap->host[0] = al_load_bitmap("textures/host/host-basic.png");
	structBitmap->host[1] = al_load_bitmap("textures/host/host-check-answer.png");
	structBitmap->host[2] = al_load_bitmap("textures/host/host-good-answer.png");
	structBitmap->host[3] = al_load_bitmap("textures/host/host-bad-answer.png");
	structBitmap->host[4] = al_load_bitmap("textures/host/host-lifebelt-half-and-half.png");
	structBitmap->host[5] = al_load_bitmap("textures/host/host-lifebelt-call-to-friend.png");
	structBitmap->host[6] = al_load_bitmap("textures/host/host-lifebelt-audience.png");

	structBitmap->lifebelt[0] = al_load_bitmap("textures/lifebelt/lifebelt-audience-enabled.png");
	structBitmap->lifebelt[1] = al_load_bitmap("textures/lifebelt/lifebelt-audience-disabled.png");
	structBitmap->lifebelt[2] = al_load_bitmap("textures/lifebelt/lifebelt-call-to-friend-enabled.png");
	structBitmap->lifebelt[3] = al_load_bitmap("textures/lifebelt/lifebelt-call-to-friend-disabled.png");
	structBitmap->lifebelt[4] = al_load_bitmap("textures/lifebelt/lifebelt-half-and-half-enabled.png");
	structBitmap->lifebelt[5] = al_load_bitmap("textures/lifebelt/lifebelt-half-and-half-disabled.png");

	structBitmap->background[0] = al_load_bitmap("textures/background/background-basic.png");
	structBitmap->background[1] = al_load_bitmap("textures/background/background-lifebelt-audience.png");
	structBitmap->background[2] = al_load_bitmap("textures/background/background-lost-game-scene.png");
	structBitmap->background[3] = al_load_bitmap("textures/background/background-early-end.png");
	structBitmap->background[4] = al_load_bitmap("textures/background/display-filtr.png");
	structBitmap->background[5] = al_load_bitmap("textures/background/background-win.png");

	structBitmap->lines = al_load_bitmap("textures/background/filtr-lines.png");

	structBitmap->icon = al_load_bitmap("textures/icon.png");

}

void destroyBitmaps(Bitmap* bitmap) {
	int i;

	for (i = 0; i < 7; i++) {
		al_destroy_bitmap(bitmap->host[i]);
	}

	for (i = 0; i < 6; i++) {
		al_destroy_bitmap(bitmap->lifebelt[i]);
		al_destroy_bitmap(bitmap->background[i]);
	}

	for (i = 0; i < 5; i++) {
		al_destroy_bitmap(bitmap->blockAnswer[i]);
		al_destroy_bitmap(bitmap->blockSquare[i]);
	}

	for (i = 0; i < 3; i++) {
		al_destroy_bitmap(bitmap->blockMoney[i]);
	}

	for (i = 0; i < 2; i++) {
		al_destroy_bitmap(bitmap->blockEllipsepe[i]);
		al_destroy_bitmap(bitmap->blockLost[i]);
	}

	al_destroy_bitmap(bitmap->blockQuestion);
	al_destroy_bitmap(bitmap->blockMenu);
	al_destroy_bitmap(bitmap->blockFriendLB);
	al_destroy_bitmap(bitmap->blockScoreboard);
	al_destroy_bitmap(bitmap->lines);
	al_destroy_bitmap(bitmap->icon);

}