#include "fraktal.h"

/*
Funkcja double losuj_liczbe(double los) losuje liczbe zmiennoprzecinkowa
z przedzialu 0-1;

Parametry funkcji:
__________________
double los - zmienna przechowujaca ostatnio wylosowana liczbe

Wartosc zwracana:
________________
los - zwrot nowo wylosowanej liczby z zakresu 0-1

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

double losuj_liczbe(double los)
{
	los = rand() % 1; /* losowanie liczby zmiennoprzecinkowej z zakresu 0-1 */
	return los = rand() / (RAND_MAX * 1.0);
}