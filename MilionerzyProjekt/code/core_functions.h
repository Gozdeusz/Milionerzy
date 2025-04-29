#ifndef MECHANIC_FUNCTIONS_H
#define MECHANIC_FUNCTIONS_H

#define max_lenght 256

//Struktura przchowujaca pytania
struct Question {
	char question[max_lenght];
	char answers[4][max_lenght];
	char correct_ans[max_lenght];
	struct Question* nxt;
}typedef Question;

//Struktura przechowujaca 5 ostatnich wynikow
struct Score {
	char nick[max_lenght];
	char points[max_lenght];
}typedef Score;

//Lista przchowujaca pytania
struct Question_pointers {
	struct Question* head, * tail;
}Question_pointers;

//Za³adowanie pytañ
void read_question(struct Question* q, FILE* f);

//zapisywanie wynikow
void save_score(char* nick, char* point, FILE* scoreboardFile);

//Za³adowanie 5 ostatnich wyników
void read_score(struct Score* s, FILE* f);

//dodaje pytanie na koniec kolejki
void enqueue(struct Question* new_question);

//sprawdza czy dana liczba wystapila juz w danej tablicy
bool checkReps(int* repArray, int arrayLen, int checkValue);

//ustawienie kolejki pytan
void setQuestionQueue(struct Question* tab);

//usuniecie z kolejki pierwszego elementu
struct Question* dequeue();

//Kolo ratunkowe: telefon do przyjaciela
char* LifebelPhoneCallToFriend(char* correctAns);

//Kolo ratunkowe: pol na pol
char* LifebelHalfAndHalf(char* correctAns);

//Kolo ratunkowe: publicznosc
void LifebeltAudienceVote(char* correctAns, int* pp);

#endif 
