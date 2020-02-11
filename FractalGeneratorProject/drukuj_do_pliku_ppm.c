#include "fraktal.h"

/*
Funkcja drukuj_do_pliku_ppm zapisuje fraktal do formatu grafiki rastrowej ppm.

Parametry funkcji:
__________________
const char **tab - tablica tablic na ktorej zostal wygenerowany fraktal
struct kolejka_fraktali *fraktale - glowa struktury listy przechowujacej odczytane z pliku informacje o fraktalach

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void drukuj_do_pliku_ppm(const char **tab, struct kolejka_fraktali *fraktale)
{
	FILE* plik;
	int odcien = 255; //odcien koloru
	char kolor[3]; //tablica kolorow odpowiednio czerwony, niebieski, zolty

	if ((plik = fopen(fraktale->nazwa, "wb")) == NULL)
	{
		return EXIT_FAILURE;
	}
	else
	{
		fprintf(plik, "P6\n%d %d\n%d\n", fraktale->rozmiar_fraktalu, fraktale->rozmiar_fraktalu, odcien); //umieszczenie niezbetnych informacji na poczatku pliku "magiczna liczba P6", rozmiar obrazu

		for (int i = 0; i < fraktale->rozmiar_fraktalu; i++)
		{
			for (int j = 0; j < fraktale->rozmiar_fraktalu; j++)
			{
				kolor[0] = tab[i][j] % 255;
				kolor[1] = tab[i][j] % 1;
				kolor[2] = tab[i][j] % 1;
				fwrite(kolor, 1, 3, plik); //wprowadzenie danych do pliku
			}
		}
	}
	fclose(plik); //zamkniecie pliku
}