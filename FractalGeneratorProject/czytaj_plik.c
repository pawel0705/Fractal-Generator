#include "fraktal.h"

/*
Funkcja void czytaj_plik(char *nazwa_pliku) jest odpowiedzialna za odczytanie zawartosci pliku.
Po poprawnym odczycie przekazuje odpowiednie parametry do dalszej pracy programu.

Parametry funkcji:
__________________
char *nazwa_pliku - wskaznik na pierwszy element tablicy przechowujacej nazwe pliku wprowadzona przez uzytkownika

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void czytaj_plik(char *nazwa_pliku)
{
	char tmp = '\0'; //tymczasowy znak pomocniczy, w nim sa chwilowo przetrzymywane znaki z pliku
	char nazwa_fraktalu[MAX_ROZMIAR]; //tablica przechowujaca nazwe fraktalu odczytana z pliku
	char ilosc_iteracji[MAX_ROZMIAR]; //tablica przechowujaca ilosc iteracji odczytana z pliku
	char rozmiar_fraktalu[MAX_ROZMIAR]; //tablica przechowujaca rozmiar fraktalu odczytany z pliku
	char cyfra_TMP[MAX_ROZMIAR]; //tablica przechowujaca chwilowo cala odczytana liczbe
	int nr_komorki = 0, rozmiar_tablicy = 0, i_rozmiar_fratalu, i_ilosc_iteracji; /*
																				  nr_komorki - zmienna pomocnicza pozwalajaca wprowadzac poprawnie znaki do tablic przechowujacych informacje
																				  rozmiar_tablicy - zmienna przechowujaca rozmiar tabclicy
																				  i_rozmiar_fraktalu - zmienna przechowujaca rozmiar fraktalu
																				  i_ilosc_iteracji - zmienna przechowujaca ilosc iteracji
																				  */
	double parametry_funkcji[PARAMETRY]; //tablica przechowujaca parametry odczytanych funkcji z pliku
	double **dane_funkcji; //tablica przechowujaca parametry i prawdopodobienstwa wystapienia funkcji z pliku
	int pozycja_w_pliku = 0; //zmienna informujaca o pozycji w pliku
	int ilosc_funkcji = 0; //zmienna informujaca ile fraktal posiada funkcji

	struct kolejka_fraktali *fraktale_start = NULL; //utworzenie glowy listy strukury przechowujacej informacje o odczytamych fraktalach

	FILE *plik;
	plik = fopen(nazwa_pliku, "r");

	if (plik != NULL) //warunek spelniony, jezeli plik zostal otwarty
	{
		while (tmp != EOF)
		{
			if (tmp == EOF)
				break;

			memset(nazwa_fraktalu, '\0', sizeof(nazwa_fraktalu)); /* Czyszczenie zmiennych pomocniczych, by przypadkiem nie pomieszac odczytanych parametrow. */
			memset(ilosc_iteracji, '\0', sizeof(ilosc_iteracji));
			memset(rozmiar_fraktalu, '\0', sizeof(rozmiar_fraktalu));
			memset(cyfra_TMP, '\0', sizeof(cyfra_TMP));
			memset(parametry_funkcji, '\0', sizeof(parametry_funkcji));

			while ((tmp = fgetc(plik)) != '\n' && tmp != 32) //odczytywanie nazwy fraktalu
			{
				if (tmp == EOF)
					break;
				if ((tmp > 64 && tmp < 91) || (tmp > 96 && tmp < 123) || (tmp > 47 && tmp < 58))
				{
					nazwa_fraktalu[nr_komorki] = tmp;
					nr_komorki++;
				}
				else
				{
					help_plik();
					usun_liste(&fraktale_start);
					return EXIT_FAILURE;
				}
			}
			nr_komorki = 0;

			while ((tmp = fgetc(plik)) != '\n' && tmp != 32) //odczytywanie rozmiaru fraktalu
			{
				if (tmp == EOF)
					break;
				if (tmp > 47 && tmp < 58)
				{
					rozmiar_fraktalu[nr_komorki] = tmp;
					nr_komorki++;
				}
				else
				{
					help_plik();
					usun_liste(&fraktale_start);
					return EXIT_FAILURE;
				}
			}
			i_rozmiar_fratalu = atoi(rozmiar_fraktalu); //konwersja odczytanych znakow na liczbe calkowita
			nr_komorki = 0;

			while ((tmp = fgetc(plik)) != '\n' && tmp != 32) //odczytywanie ilosc iteracji, ktora ma byc przeprowadzona w algorytmie odpowiedzialnym za generowanie fraktalu
			{
				if (tmp == EOF)
					break;
				if (tmp > 47 && tmp < 58)
				{
					ilosc_iteracji[nr_komorki] = tmp;
					nr_komorki++;
				}
				else
				{
					help_plik();
					usun_liste(&fraktale_start);
					return EXIT_FAILURE;
				}
			}
			i_ilosc_iteracji = atoi(ilosc_iteracji); //konwersja odczytanych znakow na liczbe calkowita
			nr_komorki = 0;

			if (tmp == EOF)
				break;

			pozycja_w_pliku = ftell(plik); //zapisanie pozycji w pliku

			while ((tmp = fgetc(plik)) != ':' && tmp != EOF) //sprawdzenie ilosci funkcji w fraktalu
			{
				if (tmp == '\n')
					ilosc_funkcji++;
			}

			fseek(plik, pozycja_w_pliku, SEEK_SET); //przejscie do poprzedniej pozycji w pliku i dalsze odczytywanie parametrow
			tmp = '\0';
			dane_funkcji = (double*)malloc(ilosc_funkcji * sizeof(double)); //utworzenie tablicy dynamicznej przechowujacej parametry i prawdopodobienstwa funkcji

			if (dane_funkcji == NULL)
			{
				usun_liste(&fraktale_start);
				return EXIT_FAILURE;
			}

			for (int i = 0; i < ilosc_funkcji; i++)
			{
				dane_funkcji[i] = (double*)malloc(PARAMETRY * sizeof(double));

				if (dane_funkcji[i] == NULL)
				{
					usun_liste(&fraktale_start);
					return EXIT_FAILURE;
				}
			}

			while (tmp != ':' && tmp != EOF) //odczyt parametrow funkcji i ich prawdopodobienstwa wystapienia
			{
				if (tmp == EOF)
					break;

				for (int i = 0; i < PARAMETRY; i++)
				{
					while (TRUE)
					{
						tmp = fgetc(plik);

						if (tmp == 'x' || tmp == 'y' || tmp == '\n' || tmp == ':' || tmp == EOF)
							break;

						if (tmp == '=')
						{
							getc(plik);
							break;
						}

						if (tmp == 'p')
						{
							tmp = getc(plik);
						}
						cyfra_TMP[nr_komorki] = tmp;
						nr_komorki++;
					}

					if (tmp != ':')
					{
						parametry_funkcji[i] = atof(cyfra_TMP); //konwersja odczytanych znakow na liczbe zmiennoprzecinkowa
						memset(cyfra_TMP, '\0', sizeof(cyfra_TMP));
						nr_komorki = 0;
					}
					else
						break;
				}

				if (tmp == ':')
					break;

				rozmiar_tablicy++;

				for (int i = 0; i < PARAMETRY; i++)
				{
					dane_funkcji[rozmiar_tablicy - 1][i] = parametry_funkcji[i]; //wpisanie z tablicy tymczasowej przechowujacej parametry do glownej, ktora bedzie wprowadzona do struktury listy fraktali
				}
			}

			if (tmp == EOF)
				break;

			stworz_element(&fraktale_start, dane_funkcji, nazwa_fraktalu, rozmiar_tablicy, i_ilosc_iteracji, i_rozmiar_fratalu, ilosc_funkcji); //utworzenie kolejnego etapu struktury lisy przechowujacej informacje na temat danego fraktalu

			for (int i = 0; i < ilosc_funkcji; i++) //usuniecie tablicy przechowujacej parametry fraktalu
				free(dane_funkcji[i]);
			free(dane_funkcji);

			rozmiar_tablicy = 0; /* zresetowanie zmiennych pomocniczych */
			i_ilosc_iteracji = 0;
			i_rozmiar_fratalu = 0;
			ilosc_funkcji = 0;
			fgetc(plik);
		}
		fclose(plik);
	}
	else
	{
		perror("Plik nie zostal odczytany!\n");
		return;
	}

	algorytm(fraktale_start); //wywolanie algorytmu odpowiedzialnego za utworzenie fraktalu
	usun_liste(&fraktale_start); //po wygenerowaniu fraktali, zostaje wywolana funkcja odpowiedzialna za usuniecie dynamicznej struktury listy
}