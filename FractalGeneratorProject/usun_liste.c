#include "fraktal.h"

/*
Funkcja void usun_liste(struct kolejka_fraktali** fraktal_start) jest odpowiedzialna
za usuniecie dynamicznej struktury listy przechowujacej dane na temat fraktali.

Parametry funkcji:
__________________
struct kolejka_fraktali** fraktal_start - glowa struktury kolejka_fraktali

Wartosc zwracana:
________________
brak

Uwagi:
_____
brak

@autor Pawel Salicki
@data 2018-05-05
*/

void usun_liste(struct kolejka_fraktali** fraktal_start)
{
	struct kolejka_fraktali *pomoc = *fraktal_start; //przechowanie do zmiennej tymczasowej
	struct kolejka_fraktali *dalej; //wskaznik pomocniczy

	while (pomoc != NULL) //zwalnianie listy
	{
		dalej = pomoc->nastepny; //przejscie na nastepny element
		free(pomoc);
		pomoc = dalej;
	}
	*fraktal_start = NULL;
}