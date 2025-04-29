#ifndef GUI_FUNCTIONS_H
#define GUI_FUNCTIONS_H
#define max_lenght 256
#include "core_functions.h"
#include "sound.h"

//typ numeryczny okreslajacy sceny gry ktore beda wybierane w switchu
enum GAME_SCENE { MENU, SCOREBOARD, MAINGAME, EARLYEND, LOSTGAME, RESULT, WIN };

//Przechowywanie statusu graficznego kola ratunjowego (nie klikniety / klikniety - u¿yty)
struct LifeBeltBlock {
	int stateFriendLB;
	int stateAudienceLB;
	int stateHalfLB;
} sLifebelt;

//Struktura z dzialaniami gracza (czy kolo ratunkowe zostalo juz klikniete i nie mozna go znowu kliknac  wgrze)
struct Player {
	bool LifebelHalfAndHalfClicked;
	bool LifebelPhoneCallToFriendClicked;
	bool LifebeltAudienceVoteClicked;
}Player;

//Struktura przechowujaca stan bloku z odpowiedzia oraz wyglad dla konkretnego stanu
typedef struct {
	short bStateA;
	short bStateB;
	short bStateC;
	short bStateD;

	ALLEGRO_BITMAP* answerblockA ;
	ALLEGRO_BITMAP* answerblockB;
	ALLEGRO_BITMAP* answerblockC;
	ALLEGRO_BITMAP* answerblockD;
} Block;


// Tworzenie danych do plikow danych o graczu i ko³ ratunkowych
void CreatingDimensionBlocks(struct LifeBeltBlock* sLifebelt, struct Player* Player);

//Rysowanie interfejsu
void DrawingGUI(Font* font, Bitmap* bitmap, AnswerBlock* block, int selID, char* chosenID, Question* questions, char* correctAns, bool* ptrGuard, char* result);

//Okno z przyciskami TAK i NIE w ktorym mozna wpisac dowolne pytanie
bool CheckBox(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard, char* TextForCheckBox);

//Rysowanie kol ratunkowych
void DrawLifeBelt(struct LifeBeltBlock* sLifebelt, Bitmap* bitmap);

//Okno z wyskakujaca informacja
void InfoBox(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard, char* TextForInfoBox);

//Funckja do wprowadzania imienia
char* GetName(Font* font, Bitmap* bitmap, Sound* sound, ALLEGRO_DISPLAY* display, bool* ptrGuard);

//Funkcja pokazywania kola ratunkowego
void LifebeltPhoneCallToFriend_Display(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, char* answer);

//Funcja glosowania publicznosci
void Audience(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, char* corr);

//Wyswitlanie ekranu Menu w grze
short miniMenu(Font* font, Bitmap* bitmap, ALLEGRO_DISPLAY* display, bool* ptrGuard);

//Funkcja rysujaca o jaka stawke gramy w grze
void DrawMoney(Font* font, Bitmap* bitmap, unsigned int money[13], short p);

//Efekt przyciemnienia ekarnu
void ScreenDimming(bool* ptrGuard1);
#endif 