#include "fraktal.h"

/*
Funkcja void stworz_element(struct kolejka_fraktali **fraktale_start, double **dane_funkcji, char* nazwa_fraktalu, int ilosc_odczytanych_funkcji, int i_ilosc_iteracji, int i_rozmiar_fraktalu, int ilosc_funkcji)
wpisuje dane odczytane z pliku o fraktalu do dynamicznej struktury listy,
przetrzymujacej informacje na temat fraktalu

Parametry funkcji:
__________________
struct kolejka_fraktali **fraktale_start - glowa listy
double **dane_funkcji - tablica przechowujaca parametry i prawdopodobienstwa funkcji fraktalu
char* nazwa_fraktalu - tablica przechowujaca nazwe fraktalu
int ilosc_odczytanych_funkcji - ilosc funkcji odpowiedzialnych za generowanie fraktalu
int i_ilosc_iteracji - ilosc iteracji, ktora zostanie wykonana w algorytmie
int i_rozmiar_fraktalu - rozmiar fraktalu odczytany z pliku uzytkownika

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

struct kolejka_fraktali *stworz_element(struct kolejka_fraktali **fraktale_start, double **dane_funkcji, char* nazwa_fraktalu, int ilosc_odczytanych_funkcji, int i_ilosc_iteracji, int i_rozmiar_fraktalu, int ilosc_funkcji)
{
	struct kolejka_fraktali *fraktale_start_TMP = (struct kolejka_fraktali*)malloc(sizeof(struct kolejka_fraktali)); //utworzenie kubelka struktury
	struct kolejka_fraktali *poprzedni = *fraktale_start;
	strcpy(fraktale_start_TMP->nazwa, nazwa_fraktalu); //skopiowanie nazwy fraktalu do struktury
	fraktale_start_TMP->ilosc_odczytanych_funkcji = ilosc_odczytanych_funkcji; //skopiowanie ilosci odczytanych funkcji do struktury

	for (int i = 0; i < ilosc_funkcji; i++) /* dane o parametrach funkcji i ich prawdopodobienstwach */
	{
		for (int j = 0; j < PARAMETRY; j++)
		{
			fraktale_start_TMP->dane_funkcji[i][j] = dane_funkcji[i][j];
		}
	}

	fraktale_start_TMP->rozmiar_fraktalu = i_rozmiar_fraktalu; // skopiowanie rozmiaru fraktalu do struktury
	fraktale_start_TMP->ilosc_iteracji = i_ilosc_iteracji; // skopiowanie ilosci iteracji algorytmu do struktury
	fraktale_start_TMP->nastepny = NULL; //ustawienie wskaznika na nastepny element na NULL

	if (*fraktale_start == NULL) //jezeli nic wczesniej jeszcze nie bylo dodane do listy
	{
		*fraktale_start = fraktale_start_TMP;
		return;
	}

	while (poprzedni->nastepny != NULL) //przejscie na ostatni wolny element
		poprzedni = poprzedni->nastepny;
	poprzedni->nastepny = fraktale_start_TMP;
}