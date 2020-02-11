#include "fraktal.h"

/*
Funkcja void wyczysc_tablice(char **tab, struct kolejka_fraktali *fraktale) jest odpowiedzialna
za usuniecie tablicy na ktorej byl generowany fraktal.

Parametry funkcji:
__________________
char **tab - tablica tablic, ktora jest do usuniecia
struct kolejka_fraktali *fraktale - stuktura przechowujaca informacje na temat jej wielkosci

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void wyczysc_tablice(char **tab, struct kolejka_fraktali *fraktale)
{
	for (int i = 0; i < fraktale->rozmiar_fraktalu; i++) //kasowanie tablicy tablic
		free(tab[i]);
	free(tab);
}