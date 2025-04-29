#ifndef SCENES_H
#define SCENES_H

//Rysowanie menu
void DrawScene_Menu(Font* font, Bitmap* bitmap);

//Rysowanie sceny podsumowanie
void DrawScene_Result(Font* font, Bitmap* bitmap, short p);

//Rysowanie sceny wygranej
void DrawScene_Win(Font* font, Bitmap* bitmap, char* nick);

//Rysowanie sceny wczeœniejszego zakoñczenia gry
void DrawScene_Earyend(Font* font, Bitmap* bitmap, short p, unsigned int money[13]);

//Rysowanie sceny tablicy wyników
void DrawScene_Scoreboard(Font* font, Bitmap* bitmap);

#endif 