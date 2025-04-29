#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "fonts.h"
#include "bitmap.h"
#include "sound.h"
#include "GUI_functions.h"
#define max_lenght 256


void CreatingDimensionBlocks(struct LifeBeltBlock* sLifebelt, struct Player* Player) {
	//Funkcja pobiera kazdy utworzony blok w strukturze i przypisuje mu wymiary, przypisuje tez wartosci dla ulozenia tekstu liter i tekstu odpowiedzi

	sLifebelt->stateAudienceLB = 0;
	sLifebelt->stateFriendLB = 2;
	sLifebelt->stateHalfLB = 4;

	Player->LifebelHalfAndHalfClicked = false;
	Player->LifebelPhoneCallToFriendClicked = false;
	Player->LifebeltAudienceVoteClicked = false;
}

short miniMenu(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, bool* ptrGuard) {
	ALLEGRO_EVENT_QUEUE* eventMW = al_create_event_queue();
	al_register_event_source(eventMW, al_get_mouse_event_source());

	al_draw_bitmap(bitmap->blockSquare[4], 650, 200, 0);


	al_draw_bitmap(bitmap->blockSquare[3], 700, 265, 0);
	al_draw_text(font->f_MainSmaler, font->c_Box, 905, 298, ALLEGRO_ALIGN_CENTER, "POWROT");
	al_draw_bitmap(bitmap->blockSquare[3], 700, 435, 0);
	al_draw_text(font->f_MainSmaler, font->c_Box, 905, 468, ALLEGRO_ALIGN_CENTER, "ZAKONCZ GRE");

	al_flip_display();

	while (true) {
		ALLEGRO_EVENT evMW;
		al_wait_for_event(eventMW, &evMW);
		if (evMW.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evMW.mouse.x > 700 && evMW.mouse.x < 1300 && evMW.mouse.y > 265 && evMW.mouse.y < 365) {
				*ptrGuard = false;
				al_destroy_event_queue(eventMW);
				return;
			}
			else if (evMW.mouse.x > 700 && evMW.mouse.x < 1300 && evMW.mouse.y > 435 && evMW.mouse.y < 535) {
				*ptrGuard = false;
				al_destroy_event_queue(eventMW);
				return EARLYEND;
			}
		}
	}
}

void DrawingGUI(Font* font, Bitmap* bitmap, AnswerBlock* block,int selID, char chosenID, Question* questions, char* correctAns, bool* ptrGuard, char* result) {

	//Ustawienie podstawowego koloru dla blokow odpowiedzi
	block->blockA = bitmap->blockAnswer[0];
	block->blockB = bitmap->blockAnswer[0];
	block->blockC = bitmap->blockAnswer[0];
	block->blockD = bitmap->blockAnswer[0];
	

	//Skontrolowanie statusu bloku w zaleznosci co sie z nim dzieje: WYBRANY(1), DOBRA ODPOWIEDZ(2), ZLA ODPOWIEDZ(3)
	if (chosenID == 'A') {
		switch (selID) {
		case 1:
			block->blockA = bitmap->blockAnswer[1];
			break;
		case 2:
			block->blockA = bitmap->blockAnswer[2];
			break;
		case 3:
			block->blockA = bitmap->blockAnswer[3];
			break;
		}
	}
	else if (chosenID == 'B') {
		switch (selID) {
		case 1:
			block->blockB = bitmap->blockAnswer[1];
			break;
		case 2:
			block->blockB = bitmap->blockAnswer[2];
			break;
		case 3:
			block->blockB = bitmap->blockAnswer[3];
			break;
		}
	}
	else if (chosenID == 'C') {
		switch (selID) {
		case 1:
			block->blockC = bitmap->blockAnswer[1];
			break;
		case 2:
			block->blockC = bitmap->blockAnswer[2];
			break;
		case 3:
			block->blockC = bitmap->blockAnswer[3];
			break;
		}
	}
	else if (chosenID == 'D') {
		switch (selID) {
		case 1:
			block->blockD = bitmap->blockAnswer[1];
			break;
		case 2:
			block->blockD = bitmap->blockAnswer[2];
			break;
		case 3:
			block->blockD = bitmap->blockAnswer[3];
			break;
		}
	}
	//Zresetowanie koloru blokow po ponownym rozpoczeciu gry
	else if (chosenID == 'R') {
		block->blockA = bitmap->blockAnswer[0];
		block->blockB = bitmap->blockAnswer[0];
		block->blockC = bitmap->blockAnswer[0];
		block->blockD = bitmap->blockAnswer[0];
	}


	//Rysowanie ekranu z odpowiedziami
	if (Question_pointers.head->nxt != NULL) {
		//Wyswietlenie wylosowanego pytania
		al_draw_bitmap(bitmap->blockQuestion, 50, 550, 0);
		if (strlen(Question_pointers.head->question) > 90)
			al_draw_text(font->f_MainSmaler, font->c_Main, 900, 610, ALLEGRO_ALIGN_CENTER, Question_pointers.head->question);
		else
			al_draw_text(font->f_Main, font->c_Main, 900, 600, ALLEGRO_ALIGN_CENTER, Question_pointers.head->question);
		//W³aczenie kola ratunkowego 50 na 50
		if (ptrGuard == true) {
			if (result == "A") {
				block->blockA = bitmap->blockAnswer[4];
			}
			else if (result == "B") {
				block->blockB = bitmap->blockAnswer[4];
			}
			else if (result == "C") {
				block->blockC = bitmap->blockAnswer[4];
			}
			else if (result == "D"){
				block->blockD = bitmap->blockAnswer[4];
				}

			if (strncmp(correctAns, "A",1) == 0) {
				block->blockA = bitmap->blockAnswer[4];
			}
			else if (strncmp(correctAns, "B",1) == 0) {
				block->blockB = bitmap->blockAnswer[4];
			}
			else if (strncmp(correctAns, "C",1) == 0) {
				block->blockC = bitmap->blockAnswer[4];
			}
			else if (strncmp(correctAns, "D",1) == 0) {
				block->blockD = bitmap->blockAnswer[4];
			}

		}

		//Rysowanie blokow z odpowiedziami
		//Uwzglednia tez dlugosc tekstu - jezeli odpowiedz mogla by wychodzic za blok zmniejszny zostanie rozmiar czcionki dla tego bloku
		al_draw_bitmap(block->blockA, 50, 710, 0);
		al_draw_text(font->f_Main, font->c_AnswerLetter, 65, 730, ALLEGRO_ALIGN_LEFT, "A:");
		if(strlen(Question_pointers.head->answers[0]) > 41)
			al_draw_text(font->f_MainSmalest, font->c_Main, 100, 740, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[0]);
		else 
			al_draw_text(font->f_Main, font->c_Main, 100, 730, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[0]);


		al_draw_bitmap(block->blockB, 950, 710, 0);
		al_draw_text(font->f_Main, font->c_AnswerLetter, 965, 730, ALLEGRO_ALIGN_LEFT, "B:");
		if (strlen(Question_pointers.head->answers[1]) > 41)
			al_draw_text(font->f_MainSmalest, font->c_Main, 1000, 740, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[1]);
		else
		al_draw_text(font->f_Main, font->c_Main, 1000, 730, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[1]);


		al_draw_bitmap(block->blockC, 50, 800, 0);
		al_draw_text(font->f_Main, font->c_AnswerLetter, 65, 820, ALLEGRO_ALIGN_LEFT, "C:");
		if (strlen(Question_pointers.head->answers[2]) > 41)
			al_draw_text(font->f_MainSmalest, font->c_Main, 100, 830, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[2]);
		else
		al_draw_text(font->f_Main, font->c_Main, 100, 820, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[2]);


		al_draw_bitmap(block->blockD, 950, 800, 0);
		al_draw_text(font->f_Main, font->c_AnswerLetter, 965, 820, ALLEGRO_ALIGN_LEFT, "D:");
		if (strlen(Question_pointers.head->answers[3]) > 41)
			al_draw_text(font->f_MainSmalest, font->c_Main, 1000, 830, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[3]);
		else
		al_draw_text(font->f_Main, font->c_Main, 1000, 820, ALLEGRO_ALIGN_LEFT, Question_pointers.head->answers[3]);

	}

}

bool CheckBox(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard, char* TextForCheckBox)
{
	//Tworzenie wewnetrznej kolejki zdarzen
	ALLEGRO_EVENT_QUEUE* eventCheckBox = al_create_event_queue();
	al_register_event_source(eventCheckBox, al_get_mouse_event_source());
	
	al_play_sample(sound->bQ, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	//Rysowanie box'u
	al_draw_bitmap(bitmap->blockEllipsepe[0], 540, 300, 0);
	al_draw_textf(font->f_Main, font->c_Box, 900, 380, ALLEGRO_ALIGN_CENTER, "%s", TextForCheckBox);
	al_draw_bitmap(bitmap->blockEllipsepe[1], 700, 460, 0);
	al_draw_text(font->f_MainSmaler, font->c_Box, 782, 469, ALLEGRO_ALIGN_CENTER, "TAK");
	al_draw_bitmap(bitmap->blockEllipsepe[1], 920, 460, 0);
	al_draw_text(font->f_MainSmaler, font->c_Box, 1007, 469, ALLEGRO_ALIGN_CENTER, "NIE");
	al_flip_display();

	//Interakcja z box'em
	while (true) {
		ALLEGRO_EVENT evCB;
		al_wait_for_event(eventCheckBox, &evCB);
		if (evCB.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evCB.mouse.x > 700 && evCB.mouse.x < 860 && evCB.mouse.y > 460 && evCB.mouse.y < 510) {
				al_play_sample(sound->Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				*ptrGuard = false;
				al_destroy_event_queue(eventCheckBox);
				return true;
			}
			else if (evCB.mouse.x > 920 && evCB.mouse.x < 1080 && evCB.mouse.y > 460 && evCB.mouse.y < 510) {
				al_play_sample(sound->Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				*ptrGuard = false;
				al_destroy_event_queue(eventCheckBox);
				return false;
			}
		}
	}
}

void InfoBox(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard, char* TextForInfoBox) {
	//Tworzenie wewnetrznej kolejki zdarzen
	ALLEGRO_EVENT_QUEUE* eventInfoBox = al_create_event_queue();
	al_register_event_source(eventInfoBox, al_get_mouse_event_source());

	//Rysowanie box'u
	al_draw_bitmap(bitmap->blockEllipsepe[0], 540, 300, 0);
	al_draw_textf(font->f_Main, font->c_Box, 900, 380, ALLEGRO_ALIGN_CENTER, "%s", TextForInfoBox);
	al_draw_bitmap(bitmap->blockEllipsepe[1], 815, 470, 0);
	al_draw_text(font->f_MainSmaler, font->c_Box, 899, 479, ALLEGRO_ALIGN_CENTER, "OK");
	al_flip_display();

	//Interakcja z box'em
	while (true) {
		ALLEGRO_EVENT evIB;
		al_wait_for_event(eventInfoBox, &evIB);
		if (evIB.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evIB.mouse.x > 815 && evIB.mouse.x < 975 && evIB.mouse.y > 470 && evIB.mouse.y < 520) {
				*ptrGuard = false;
				al_play_sample(sound->Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_destroy_event_queue(eventInfoBox);
				break;
			}
		}
	}
}

void DrawLifeBelt(struct LifeBeltBlock* sLifebelt, Bitmap* bitmap) {
	//Glosowanie publicznosci
	al_draw_bitmap(bitmap->lifebelt[sLifebelt->stateAudienceLB], 50, 310, 0);
	//Telefon do przyjaciela
	al_draw_bitmap(bitmap->lifebelt[sLifebelt->stateFriendLB], 50, 390, 0);
	//50 na 50
	al_draw_bitmap(bitmap->lifebelt[sLifebelt->stateHalfLB], 50, 470, 0);
}

void LifebeltPhoneCallToFriend_Display(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, char* answer) {
	//Tworzenie wewnetrznej kolejki zdarzen
	ALLEGRO_EVENT_QUEUE* eventCheckBox = al_create_event_queue();
	al_register_event_source(eventCheckBox, al_get_mouse_event_source());

	//Rysowanie kola ratunkowego
	al_draw_bitmap(bitmap->host[5], 0, 0, 0);
	al_draw_bitmap(bitmap->blockFriendLB, 500, 300, 0);
	al_draw_bitmap(bitmap->blockSquare[2], 950, 510, 0);
	al_draw_text(font->f_Main, font->c_Box, 1025, 360, ALLEGRO_ALIGN_CENTER, "Wydaje mi sie ze to bedzie");
	al_draw_textf(font->f_Main, font->c_Box, 1025, 430, ALLEGRO_ALIGN_CENTER, "to odpowiedz %s", answer);
	al_draw_text(font->f_MainSmaler, font->c_Box, 1027, 519, ALLEGRO_ALIGN_CENTER, "OK");
	al_flip_display();

	//Interakcja z kolem
	while (true) {
		ALLEGRO_EVENT evCB;
		al_wait_for_event(eventCheckBox, &evCB);
		if (evCB.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evCB.mouse.x > 950 && evCB.mouse.x < 1100 && evCB.mouse.y > 510 && evCB.mouse.y < 560) {
				al_destroy_event_queue(eventCheckBox);
				return;
			}
		}
	}
}

void Audience(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, char* corr) {
	//Tworzenie wewnetrznej kolejki zdarzen
	ALLEGRO_EVENT_QUEUE* eventCheckBox = al_create_event_queue();
	al_register_event_source(eventCheckBox, al_get_mouse_event_source());

	//Rysowanie kola
	al_draw_bitmap(bitmap->blockSquare[0], 500, 200, 0);
	al_draw_bitmap(bitmap->blockSquare[2], 825, 600, 0);
	al_draw_text(font->f_Main, font->c_Box, 900, 250, ALLEGRO_ALIGN_CENTER, "Wyniki glosowania publicznosci");
	al_draw_text(font->f_MainSmaler, font->c_Box, 902, 609, ALLEGRO_ALIGN_CENTER, "OK");

	//Mechanika kola ratunkowego
	int percentPoints[4] = { 0 };
	LifebeltAudienceVote(corr, percentPoints);
	//Rysowanie wykresu dla kazdej odpowiedzi
	al_draw_filled_rectangle(535, (520 - percentPoints[0] * 2), 670, 520, al_map_rgb(35, 102, 73));
	al_draw_filled_rectangle(735, (520 - percentPoints[1] * 2), 870, 520, al_map_rgb(35, 102, 73));
	al_draw_filled_rectangle(935, (520 - percentPoints[2] * 2), 1070, 520, al_map_rgb(35, 102, 73));
	al_draw_filled_rectangle(1135, (520 - percentPoints[3] * 2), 1270, 520, al_map_rgb(35, 102, 73));
	al_draw_textf(font->f_Main, font->c_AnswerLetter, 540, 540, ALLEGRO_ALIGN_LEFT, "A: %dp.p.", percentPoints[0]);
	al_draw_textf(font->f_Main, font->c_AnswerLetter, 740, 540, ALLEGRO_ALIGN_LEFT, "B: %dp.p.", percentPoints[1]);
	al_draw_textf(font->f_Main, font->c_AnswerLetter, 940, 540, ALLEGRO_ALIGN_LEFT, "C: %dp.p.", percentPoints[2]);
	al_draw_textf(font->f_Main, font->c_AnswerLetter, 1140, 540, ALLEGRO_ALIGN_LEFT, "D: %dp.p.", percentPoints[3]);


	al_flip_display();

	while (true) {
		ALLEGRO_EVENT evCB;
		al_wait_for_event(eventCheckBox, &evCB);
		if (evCB.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (evCB.mouse.x > 825 && evCB.mouse.x < 975 && evCB.mouse.y > 600 && evCB.mouse.y < 650) {
				al_destroy_event_queue(eventCheckBox);
				return;
			}
		}
	}
}

char* GetName(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard) {
	ALLEGRO_EVENT_QUEUE* eventInfoBox = al_create_event_queue();
	al_register_event_source(eventInfoBox, al_get_mouse_event_source());
	al_register_event_source(eventInfoBox, al_get_keyboard_event_source());

	al_draw_bitmap(bitmap->blockSquare[1], 500, 300, 0);
	al_draw_text(font->f_Main, font->c_Box, 900, 340, ALLEGRO_ALIGN_CENTER, "Podaj swoja nazwe");

	char name[100] = "";  // bufor
	int cursor_pos = 0;  // pozycja kursora

	al_flip_display();
	while (true) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(eventInfoBox, &ev);

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (ev.mouse.x > 822 && ev.mouse.x < 972 && ev.mouse.y > 515 && ev.mouse.y < 565) {
				al_play_sample(sound->Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				*ptrGuard = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
				al_play_sample(sound->Click, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				*ptrGuard = false;
				break;
			}
			else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
				//usuwanie liter
				if (cursor_pos > 0) {
					cursor_pos--;
					memmove(&name[cursor_pos], &name[cursor_pos + 1], strlen(name) - cursor_pos);
					al_play_sample(sound->Click, 1.0, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
			else if (ev.keyboard.unichar >= 32 && ev.keyboard.unichar <= 126 && strlen(name) < sizeof(name) - 1) {
				//dodawanie liter do bufora
				int input = ev.keyboard.unichar;
				memmove(&name[cursor_pos + 1], &name[cursor_pos], strlen(name) - cursor_pos + 1);
				name[cursor_pos] = (char)input;
				cursor_pos++;
				al_play_sample(sound->Click, 1.0, 0.0, 3.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}


		al_clear_to_color(al_map_rgb(17, 43, 29));
		al_draw_bitmap(bitmap->blockSquare[1], 500, 300, 0);
		al_draw_text(font->f_Main, font->c_Box, 900, 340, ALLEGRO_ALIGN_CENTER, "Podaj swoja nazwe");
		al_draw_text(font->f_Main, font->c_Box, 900, 430, ALLEGRO_ALIGN_CENTER, name);
		al_draw_bitmap(bitmap->blockSquare[2], 822, 515, 0);
		al_draw_text(font->f_MainSmaler, font->c_Box, 899, 525, ALLEGRO_ALIGN_CENTER, "ZATWIERDZ");

		al_flip_display();
	}

	al_destroy_event_queue(eventInfoBox);

	char* nameCopy = NULL;
	nameCopy = (char*)malloc(strlen(name) + 1);
	if (nameCopy == NULL)
		nameCopy = "<brak nazwy>";
	strcpy(nameCopy, name);
	return nameCopy;
}

void DrawMoney(Font* font, Bitmap* bitmap, unsigned int money[13], short p) {
	for (int i = 1; i < 13; i++) {
		al_draw_bitmap(bitmap->blockMoney[0], 1550, 15 + ((i - 1) * 40), 0);
		if(i == 2 || i == 7)
			al_draw_bitmap(bitmap->blockMoney[2], 1550, 15 + ((i - 1) * 40), 0);
		if(p == i)
			al_draw_bitmap(bitmap->blockMoney[1], 1550, 15 + ((i - 1) * 40), 0);
	}

	for (int j = 12; j >= 1; j--) {
		al_draw_textf(font->f_MainMoney, font->c_Main, 1645, 18 + ((j - 1) * 40), ALLEGRO_ALIGN_CENTER, "%u",money[j]);
	}
	
}

void ScreenDimming(bool* ptrGuard1) {
	if (ptrGuard1) {
		for (float i = 0; i < 200;) {
			al_draw_filled_rectangle(0, 0, 1800, 900, al_map_rgba(0, 0, 0, i));
			i += 0.5;
			al_flip_display();
		}
;
	}
	ptrGuard1 = false;
}

