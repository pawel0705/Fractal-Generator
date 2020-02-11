/*** @file */

#ifndef fraktal_h
#define fraktal_h

#define _CRT_SECURE_NO_WARNINGS

#define MAX_ROZMIAR 100
#define PARAMETRY 7
#define MAX_ILOSC 15
#define TRUE 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct kolejka_fraktali
{
	char nazwa[MAX_ROZMIAR];
	int ilosc_odczytanych_funkcji;
	int rozmiar_fraktalu;
	int ilosc_iteracji;
	double dane_funkcji[MAX_ILOSC][PARAMETRY];
	struct kolejka_fraktali *nastepny;
};

void help(void);
void czytaj_plik(char *nazwa_pliku);
void usun_liste(struct kolejka_fraktali** fraktal_start);
void zainicjuj_tablice(char **tab, int i_rozmiar);
void wyczysc_tablice(char **tab, struct kolejka_fraktali *fraktale);
double losuj_liczbe(double los);
void drukuj_do_pliku_bmp(const char **tab, struct kolejka_fraktali *fraktale);
void drukuj_do_pliku_ppm(const char **tab, struct kolejka_fraktali *fraktale);
void algorytm(struct kolejka_fraktali *fraktale);
struct kolejka_fraktali *stworz_element(struct kolejka_fraktali **fraktale_start, double **dane_funkcji, char* nazwa_fraktalu, int ilosc_odczytanych_funkcji, int i_ilosc_iteracji, int i_rozmiar_fraktalu, int ilosc_funkcji);
void help_plik(void);

#endif