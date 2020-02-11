#include "fraktal.h"

/*
Funkcja void zainicjuj_tablice(char **tab, int i_rozmiar) tworzy przestrzen,
na ktorej bedzie generowany fraktal. Przestrzen jest generowana o takiej wielkosci,
jaka wprowadzil uzytkownik w odczytanym pliku.

Parametry funkcji:
__________________
char **tab - tablica tablic, ktora bedzie wypelniana znakami '0'
int i_rozmiar - rozmiar odczytany z pliku

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void zainicjuj_tablice(char **tab, int i_rozmiar)
{
	for (int i = 0; i <(i_rozmiar); i++)
	{
		for (int j = 0; j <(i_rozmiar); j++)
		{
			tab[i][j] = '0'; //wpisywanie znakow '0' do tablicy
		}
	}
}