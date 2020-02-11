#include "fraktal.h"

/*
Funkcja void drukuj_do_pliku_bmp(const char **tab, struct kolejka_fraktali *fraktale)
jest odpowiedzialna za zapis wygenerowanego fraktalu do pliku graficznego o rozszerzeniu .bmp.

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


void drukuj_do_pliku_bmp(const char **tab, struct kolejka_fraktali *fraktale)
{
	FILE* plik;
	char kolor[3]; //tablica kolorow odpowiednio czerwony, niebieski, zolty

	char *obraz; //tablica przechowujaca informacje na temat obrazu fraktalu
	int rozmiar_pliku = 54 + 3 * (fraktale->rozmiar_fraktalu)*(fraktale->rozmiar_fraktalu); //przechowuje rozmiar pliku

	obraz = (char*)malloc(3 * (fraktale->rozmiar_fraktalu)*(fraktale->rozmiar_fraktalu)); //zarezerwowanie odpowiedniej ilosci pamieci
	if (obraz == NULL)
	{
		return EXIT_FAILURE;
	}
	memset(obraz, 0, 3 * (fraktale->rozmiar_fraktalu)*(fraktale->rozmiar_fraktalu));

	for (int i = 0; i<(fraktale->rozmiar_fraktalu); i++)
	{
		for (int j = 0; j<(fraktale->rozmiar_fraktalu); j++)
		{
			int y = ((fraktale->rozmiar_fraktalu) - 1) - j;
			kolor[0] = tab[i][j] % 255;
			kolor[1] = tab[i][j] % 1;
			kolor[2] = tab[i][j] % 1;
			obraz[(i + y * (fraktale->rozmiar_fraktalu)) * 3 + 2] = kolor[0];
			obraz[(i + y * (fraktale->rozmiar_fraktalu)) * 3 + 1] = kolor[1];
			obraz[(i + y * (fraktale->rozmiar_fraktalu)) * 3 + 0] = kolor[2];
		}
	}

	char naglowek_pliku[14] = { 'B','M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 }; //przechowuje najwazniejsze informacje o pliku, 'B''M' - Windows 3.1x, 95, NT, ... itd.
	char naglowekDIB[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 }; //przechowuje informacje o obrazie i definiuje format piksela
	char maska_bitowa[3] = { 0, 0, 0 }; //definiuje format piksela

	naglowek_pliku[2] = (char)(rozmiar_pliku); /* Przesuniecia bitowe i wprowadzenie informacji o pliku, ktory bedzie zapisywany */
	naglowek_pliku[3] = (char)(rozmiar_pliku >> 8);
	naglowek_pliku[4] = (char)(rozmiar_pliku >> 16);
	naglowek_pliku[5] = (char)(rozmiar_pliku >> 24);
	naglowekDIB[4] = (char)((fraktale->rozmiar_fraktalu));
	naglowekDIB[5] = (char)((fraktale->rozmiar_fraktalu) >> 8);
	naglowekDIB[6] = (char)((fraktale->rozmiar_fraktalu) >> 16);
	naglowekDIB[7] = (char)((fraktale->rozmiar_fraktalu) >> 24);
	naglowekDIB[8] = (char)((fraktale->rozmiar_fraktalu));
	naglowekDIB[9] = (char)((fraktale->rozmiar_fraktalu) >> 8);
	naglowekDIB[10] = (char)((fraktale->rozmiar_fraktalu) >> 16);
	naglowekDIB[11] = (char)((fraktale->rozmiar_fraktalu) >> 24);

	char *nazwa_tmp[MAX_ROZMIAR]; //tablica przechowujaca nazwe z rozszerzeniem .bmp
	strcpy(nazwa_tmp, fraktale->nazwa); //skopiowanie nazwy z listy struktury fraktali do tablicy
	char *bmp = ".bmp"; //rozszerzenie grafiki bitmapowej
	char *nazwa_bmp = strcat(nazwa_tmp, bmp); //zlaczenie nazwy fraktalu z rozszerzeniem bmp

	plik = fopen(nazwa_bmp, "wb"); /* pisanie do pliku */
	fwrite(naglowek_pliku, 1, 14, plik);
	fwrite(naglowekDIB, 1, 40, plik);

	for (int i = 0; i<(fraktale->rozmiar_fraktalu); i++)
	{
		fwrite(obraz + ((fraktale->rozmiar_fraktalu)*((fraktale->rozmiar_fraktalu) - i - 1) * 3), 3, (fraktale->rozmiar_fraktalu), plik);
		fwrite(maska_bitowa, 1, (4 - ((fraktale->rozmiar_fraktalu) * 3) % 4) % 4, plik);
	}

	free(obraz); //usuniecie tablicy
	fclose(plik); //zamkniecie pliku
}