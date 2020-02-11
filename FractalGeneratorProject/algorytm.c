#include "fraktal.h"

/*
Funkcja void algorytm(struct kolejka_fraktali *fraktale) jest algorytmem
odpowiedzialnym za generowanie fraktalu.

Parametry funkcji:
__________________
struct kolejka_fraktali *fraktale - glowa dynamicznej struktury listy przetrzymujacej informacje na temat fraktalu

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void algorytm(struct kolejka_fraktali *fraktale)
{
	while (TRUE) //wywolywanie algorytmu tyle razy, ile jest odczytanych fraktali
	{
		clock_t start, stop; /* Start pomiaru czasu generowania fraktalu */
		start = clock();

		double poprawka = 0.001; //poprawka, by nie wyjsc poza tablice do ktorej zapisywane sa ustalone punkty fraktalu
		int indeks_tablicy; //zmienna przechowujaca indeks tablicy
		double granica_left = 0, granica_right = 0, granica_up = 0, granica_down = 0; //maksymalne i minimalne wartosci uzyskane przez dokonywanie przeksztalcen funkcji w algorytmie
		double x=0, y=0, Xnext = 0, Ynext = 0; //zmienne przechowujace uzyskane x i y funkcji
		double los = 0, prawdopodobienstwo = 0; //los - zmienna przechowujaca wylosowana liczbe, prawdopodobienstwo - zmienna przechowujaca uzyskane prawdopodobienstwo wywolania funkcji
		double *punktyX, *punktyY; //tablica przechowujaca wyliczone x i y z przeksztalcen funkcji
		double czas; //zmienna przechowujaca czas potrzebny na generowanie fraktalu

		puts("----");
		printf("Generowanie fraktalu \"%s\". Prosze czekac!\n", fraktale->nazwa);

		char **tab = malloc((fraktale->rozmiar_fraktalu) * sizeof(char*));
		if (tab == NULL)
			return EXIT_FAILURE;

		for (int i = 0; i < fraktale->rozmiar_fraktalu; i++)
		{
			tab[i] = (double*)malloc(fraktale->rozmiar_fraktalu * sizeof(double));
			if (tab[i] == NULL)
				return EXIT_FAILURE;
		}

		zainicjuj_tablice(tab, fraktale->rozmiar_fraktalu); //wypelnienie przestrzeni tablicy znakami '0'

		punktyX = (double*)malloc(fraktale->ilosc_iteracji * sizeof(double)); /* zainicjowanie tablic przechowujacych punkty x i y */
		if (punktyX == NULL)
			return EXIT_FAILURE;
		punktyY = (double*)malloc(fraktale->ilosc_iteracji * sizeof(double));
		if (punktyY == NULL)
			return EXIT_FAILURE;

		for (int i = 0; i <fraktale->ilosc_iteracji; i++) //algorytm tworzenia fraktalu
		{
			los = losuj_liczbe(los); //wylosowanie liczby zmiennoprzecinkowej z zakresu 0-1
			indeks_tablicy = 0;
			prawdopodobienstwo = 0;

			for (int j = 0; j < fraktale->ilosc_odczytanych_funkcji; j++) /* wylosowanie funkcji na ktorej beda odbywaly sie przeksztalcenia */
			{
				prawdopodobienstwo += fraktale->dane_funkcji[j][6]; //odczyt prawdopodobienstwa
				if (los <= prawdopodobienstwo)
				{
					indeks_tablicy = j;
					break;
				}
			}

			x = fraktale->dane_funkcji[indeks_tablicy][0] * Xnext; /* uzyskanie punktu x oraz y */
			x += fraktale->dane_funkcji[indeks_tablicy][1] * Ynext;
			x += fraktale->dane_funkcji[indeks_tablicy][2];
			y = fraktale->dane_funkcji[indeks_tablicy][3] * Xnext;
			y += fraktale->dane_funkcji[indeks_tablicy][4] * Ynext;
			y += fraktale->dane_funkcji[indeks_tablicy][5];

			Ynext = y; /* nowy x i y to poprzeni x i y */
			Xnext = x;

			punktyX[i] = x; /* wpis do tablicy */
			punktyY[i] = y;

			if (x > granica_right) /* ustalenie skrajnych wartosci */
				granica_right = x;
			if (x < granica_left)
				granica_left = x;
			if (y < granica_down)
				granica_down = y;
			if (y > granica_up)
				granica_up = y;
		}

		granica_right += poprawka; /* zastosowanie poprawki, by podczas konwersji na int nie wyjsc poza tablice */
		granica_left -= poprawka;
		granica_up += poprawka;
		granica_down -= poprawka;

		for (int i = 0; i < fraktale->ilosc_iteracji; i++) //wpisanie znaku 255 do poprzednio wypelnionej tablicy wartosciami '0'
			tab[(int)((punktyX[i] - granica_left) / ((granica_right - granica_left) / (fraktale->rozmiar_fraktalu * 1.0)))][(int)((punktyY[i] - granica_down) / (granica_up / (fraktale->rozmiar_fraktalu * 1.0)))] = (char)255;

		drukuj_do_pliku_ppm(tab, fraktale); /* zapis do pliku graficznego */
		drukuj_do_pliku_bmp(tab, fraktale);

		wyczysc_tablice(tab, fraktale); /* czyszczenie tablic dynamicznych */
		free(punktyX);
		free(punktyY);

		stop = clock(); //zatrzymanie czasu generowania fraktalu
		czas = (stop - start) / CLK_TCK;

		printf("Czas wykonania fraktalu \"%s\": %.2fs.\n", fraktale->nazwa, czas);

		fraktale = fraktale->nastepny; //przejscie na kolejny element listy

		if (fraktale == NULL)
			break;
	}
}