#include "fraktal.h"

/*
Glowna funkcja programu. Uruchomiony program przechodzi do niej pierwszej.
int main(int argc, char *argv[]) odczytuje parametry wprowadzone przez uzytkownika.
W zaleznosci od ich wprowadzenia wywoluje odpowiednia prace programu.

parametry funkcji:
__________________
int argc - ilosc wprowadzonych argumentow z linii polecen przez uzytkownika
*argv[] - wskaznik do tablicy zawierajacej sciezke wywolania i podane parametry

artosc zwracana:
________________
return 0 - zakonczenie programu

uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

int main(int argc, char *argv[])
{
	const char *POMOC = "-h"; //parametr odpowiadajacy za wyswietlenie pomocy
	const char *PLIK = "-p"; //parametr informujacy program, ze ma odczytac nazwe pliku
	char nazwa_pliku[MAX_ROZMIAR]; //tablica znakow przechowujaca nazwe pliku wprowadzonego przez uzytkownika

	if (argc > 1) /* sprawdzanie parametrow wprowadzonych przez uzytkownika */
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(POMOC, argv[i]) == 0)
			{
				help();
				return 0;
			}
			else if (strcmp(PLIK, argv[i]) == 0)
			{
				if (argc < 3)
					help();
				else
				{
					strcpy(nazwa_pliku, argv[++i]);
					czytaj_plik(nazwa_pliku); //wywolanie dalszej pracy programu, jezeli nazwa pliku zostala odczytana
				}
			}
		}
	}
	else
	{
		puts("Nie wprowadziles parametrow!");
		help();
		return 0;
	}

	puts("Program zostal zakonczony."); //komunikat informujacy uzytkownika, ze program nic nie bedzie juz robic

	return 0;
}