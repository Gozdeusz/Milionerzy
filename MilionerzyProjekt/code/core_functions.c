#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "core_functions.h"


void read_question(struct Question* q, FILE* f) {
	fgets(q->question, max_lenght, f);
	q->question[strcspn(q->question, "\n")] = '\0';

	for (int i = 0; i < 4; i++) {
		fgets(q->answers[i], max_lenght, f);
		q->answers[i][strcspn(q->answers[i], "\n")] = '\0';
	}

	fgets(q->correct_ans, max_lenght, f);
	q->correct_ans[strcspn(q->correct_ans, "\n")] = '\0';
}

void read_score(struct Score* s, FILE* f) {
	fgets(s->nick, max_lenght, f);
	s->nick[strcspn(s->nick, "\n")] = '\0';
	fgets(s->points, max_lenght, f);
	s->points[strcspn(s->points, "\n")] = '\0';
}

void save_score(char* nick, char* point, FILE* scoreboardFile) {
	//Przesuwanie wskaznika na koniec
	fseek(scoreboardFile, 0, SEEK_END);

	//Pobieranie rozmiaru pliku
	long file_size = ftell(scoreboardFile);

	//Bufor
	char* buffer = malloc(file_size);

	//Przesuwanie wskaznika na poczatek
	fseek(scoreboardFile, 0, SEEK_SET);

	//Odczyt pliku do bufora
	fread(buffer, 1, file_size, scoreboardFile);

	fclose(scoreboardFile);

	scoreboardFile = fopen("scoreboard.txt", "w");

	//zapis
	fprintf(scoreboardFile, "%s\n", nick);
	fprintf(scoreboardFile, "%d\n", point);
	fwrite(buffer, 1, file_size, scoreboardFile);

	free(buffer);
}

void enqueue(struct Question* new_question) {
	if (NULL != new_question) {

		if (NULL == Question_pointers.head) {
			Question_pointers.head = Question_pointers.tail = new_question;
		}
		else {
			Question_pointers.tail->nxt = new_question;
			Question_pointers.tail = new_question;
		}
	}
	else printf("Nie udalo sie dodac pytania");
};

bool checkReps(int* repArray, int arrayLen, int checkValue) {
	for (int i = 0; i < arrayLen; i++) {
		if (repArray[i] == checkValue) {
			return false;
		}
	}
	return true;
}

void setQuestionQueue(struct Question* tab) {
	int settedId[14], a = 0; // a - wartosc kontrolna
	srand(time(NULL));

	for (int i = 0; i < 14; i++) {
		int randId = rand() % 19;
		if (checkReps(&settedId, 12, randId)) {
			settedId[a] = randId;
			enqueue(&tab[randId]);
			a++;
		}
		else {
			//w przypadku duplikatow pêtla wykonuje sie jeszcze raz
			i--;
		}
	}
}

struct Question* dequeue() {
	if (NULL != Question_pointers.head->nxt) {
		struct Question* tmp = Question_pointers.head->nxt;
		Question_pointers.head = tmp;
		if (NULL == tmp) {
			Question_pointers.tail = NULL;
		}
		return Question_pointers.head;
	}
	printf("Kolejka jest pusta");
};

char* LifebelPhoneCallToFriend(char* correctAns) {
	char* listAns[9] = { "A","B","C","D",correctAns,correctAns,correctAns,correctAns,correctAns };
	srand(time(NULL));
	int random = rand() % 9;
	return listAns[random];
}

char* LifebelHalfAndHalf(char* correctAns) {
	char* listAns[4] = { "A","B","C","D" };
	static char Answer[40];
	int random = 0, n = 0;
	do {
		srand(time(0) + n);
		random = rand() % 4;
		n += 2;
	} while (!strncmp(listAns[random], correctAns, 1));
	return listAns[random];
}

void LifebeltAudienceVote(char* correctAns, int * pp) {
	char* listAns[4] = { "A","B","C","D" };
	static char text[256];
	int remPercent = 100, correctAnswerPercents = 0;
	srand(time(0));
	correctAnswerPercents = 50 + rand() % 30;
	remPercent -= correctAnswerPercents;

	for (int i = 0; i < 4; i++) {
		if (!strncmp(listAns[i], correctAns, 1)) {
			pp[i] = correctAnswerPercents;
		}
		else {
			pp[i] = rand() % remPercent;
		}
	}
}
