#include "fraktal.h"

/*
Funkcja wyswietlajaca komunikat pomocy na urzadzenie zewnetrzne.

parametry funkcji:
__________________
brak

Wartosc zwracana:
________________
brak

uwagi:
_____
W zaleznosci od rozmiaru okienka konsoli, zdania moga byc zle poobcinane.

@autor Pawel Salicki
@data 2018-05-05
*/

void help(void)
{
	puts("Program generuje fraktale.\n By wygenerowac fraktal,\n nalezy w linii polecen po parametrze -p wpisac nazwe pliku.\n Plik musi zawierac odpowiednio zapisane funkcje\n wraz z ich prawdopodobienstwem.\n Przyklad poprawnego zapisania funkcji mozna znalezc\n w pliku DATA lub sprawozdaniu.");
}