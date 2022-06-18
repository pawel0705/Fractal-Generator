# FractalGenerator-Project
Program generuje fraktale przy pomocy Systemu Funkcji Iterowanych (IFS)

# Opis programu <h1>
 
Problem matematyczny. Program generujący fraktale za pomocą systemu funkcji iterowanych. Funkcje i ich prawdopodobieństwa wystąpienia są doczytywane z pliku.
W projekcie zastosowano algorytm IFS (ang. integrated function system), za pomocą którego konstruuje się fraktale. Został opisany przez John'a Hutchinson'a w 1981 roku, a spopularyzowany przez Micheal'a Barnsley'a.
Wynikiem generowania fraktali jest zapis do dwóch plików graficznych: Portable Anymap oraz Windows Bitmap.
 
# Podstawy teoretyczne <h2>

System funkcji iterowanych (IFS) jest zagadnieniem należącym do dziedziny matematyki. Integrated function system to rodzina funkcji za pomocą których konstruuje się fraktale samopodobne. Sposób ich generowania przedstawił Micheal Barnsley pod nazwą „chaos game”. Startując od punktów startowych (0, 0), wybierana jest losowa funkcja ze zbioru funkcji, odpowiedzialnych za generowanie danego fraktalu. W wylosowanej funkcji za (x, y) przyjmuje się punkt (0, 0). Uzyskane w ten sposób nowe punkty (xn, yn) umieszcza się na dwuwymiarowej płaszczyźnie. Dodatkowo, uzyskane punkty, to nowe punkty startowe. Proces powtarzany jest określoną ilość razy. Im więcej zostanie przeprowadzonych iteracji, tym uzyskany fraktal będzie wyraźniejszy.

Funkcje opisujące fraktal są postaci:

*𝑥𝑛+1 = 𝑎𝑥𝑛 + 𝑏𝑥𝑛 + 𝑐*

*𝑦𝑛+1 = 𝑎𝑥𝑛 + 𝑏𝑥𝑛 + 𝑐* 

# Obsługa programu <h3>

Program jest uruchamiany w linii poleceń przy zastosowaniu odpowiednich parametrów. Obsługiwane są poniższe parametry: 
-h Wywołanie tego parametru w linii poleceń powoduje wyświetlenie krótkiej informacji dla użytkownika jak poprawnie obsługiwać program. 
-p Parametr informujący program, że zaraz po nim użytkownik wprowadził nazwę pliku, z którego mają zostać odczytane dane o fraktalach. 
Przykładowe poprawne uruchomienie programu znajduje się poniżej.

**[ścieżka do pliku wykonywalnego (.exe)] –p [ścieżka do pliku tekstowego (.txt)]**

Przy błędnym wprowadzeniu parametrów, program wyświetli instrukcję dla użytkownika i się zakończy.

# Fortmat danych wejściowych <h4>
 
Dane wejściowe programu są pobierane z pliku. By program przeszedł do poprawnego procesu tworzenia fraktalu, zawartość pliku tekstowego musi być poniższego formatu.

[nazwa_fraktalu] [rozmiar_fraktalu] [ilość_iteracji]

[A11]x+[B11]y+[C11]=0 [A12]x+[B12]y+[C12]=0 p[D1]

[A21]x+[B21]y+[C21]=0 [A22]x+[B22]y+[C22]=0 p[D2]

[An1]x+[Bn1]y+[Cn1]=0 [An2]x+[Bn2]y+[Cn2]=0 p[Dn]

: 

gdzie

[nazwa_fraktalu] – nazwa wyjściowego pliku graficznego

[rozmiar_fraktalu] – wielkość wyjściowego pliku graficznego w pikselach

[ilość_iteracji] – ilość iteracji przeprowadzenia algorytmu (im więcej, tym dokładniejszy obraz fraktalu)

[Ann], [Bnn], [Cnn], [Dnn] – wartości liczbowe parametrów funkcji

: - oznaczenie końca funkcji należących do fraktalu


Przykładowa poprawna zawartość pliku:

Spirala 500 100000

0.787879x-0.424242y+1.758647=0 0.242424x+0.859848y+1.408065=0 p0.895652

-0.121212x+0.257576y-6.721654=0 0.151515x+0.053030y+1.377236=0 p0.052174

0.181818x-0.136364y+6.086107=0 0.090909x+0.181818y+1.568035=0 p0.052174

: 

W przypadku kiedy zawartość pliku będzie błędnie sformatowana, program pokaże stosowny komunikat i zamknie program, lub za błędnie wprowadzone parametry przyjmie wartość 0.

# Komunikaty generowane przez program <h5>

„Generowanie fraktalu [nazwa fraktalu z pliku]. Proszę czekać.” – Program jest w trakcie generowania danego fraktalu. Użytkownik powinien zaczekać na zakończenie się operacji i nie przerywać pracy programu. 

„Czas wykonania fraktalu [nazwa_fraktalu] [czas]” – Fraktal został wygenerowany i jego obraz został zapisany do pliku graficznego znajdującego się w folderze roboczym z programem. 

„Plik nie został odczytany.” – Wykryto błąd powiązany z plikiem. Program zostaje zakończony. 

„Program generuje fraktale…(itd.)” – Instrukcja dla użytkownika. Jeżeli została wyświetlona, to program został zakończony i należy uruchomić go ponownie. 

„Niewłaściwy format pliku! Program zostanie zakończony!” – Wykryto błąd w zawartości pliku. Program zostanie zakończony. 

„Nie wprowadziłeś parametrów!” – Użytkownik błędnie wprowadził parametry. Program zostanie zakończony. 

„Program został zakończony.” – Program zakończył swoje działanie i już nic nie będzie robił. 

# Przykładowe fraktale utworzone przez program <h6>

### Barnsley

![img|512x512](/images/Barnsley.bmp)

### Dragon

![img|512x512](/images/Smok.bmp)

### Spiral

![img|512x512](/images/Spirala.bmp)
