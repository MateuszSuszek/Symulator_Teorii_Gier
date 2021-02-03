## Symulator_Teorii_Gier
	
W ramach projektu stworzę symulator gry Nim z kombinatorycznej teorii gier przy użyciu GTK oraz Glade.
Program umożliwi użytkownikowi grę w Nim przeciwko komputerowi. 
	
### Funkcje programu i punktacja zastępowalnych części projektu:  
1. Menu w GTK umożliwiające: **(20p)**  
		a) wybór gry,  
		b) dostosowanie rozmiarów planszy,    
		c) wybór kto rozpoczyna grę.     

2. Logika pozwalająca obliczać pozycję wygrywającą dla gry Nim: **(20p)**  
	
3. Wizualizacja stanu gry przy użyciu biblioteki ncurses **(20p)**  
	
### Aby zainstalować program należy:
Zainstalować gtk oraz ncurses:
>sudo apt-get install libgtk-3-dev

>sudo apt-get install libncurses5-dev libncursesw5-dev

Następnie skompilować za pomocą:
>gcc -o SG main.c nim.c -Wall \`pkg-config --cflags --libs gtk+-3.0\` -export-dynamic -lncurses

Lub użyć skryptu make.sh.

Uruchomić:
>./SG

### Dokumentacja:
Zasady gry Nim:
Ruchy wykonywane są sekwencyjnie, dozwolonym ruchem jest zebranie dowolnej liczby kamieni z dowolnej kolumny. Wygrywa gracz, który wykona ostatni możliwy ruch.  
Obsługa programu:
Aby wykonać ruch należy zaznaczyć wybrane kamienie za pomocą klawiszy wasd a następnie zatwierdzić wybór wciskając enter.

### Opis struktury programu:

W pliku main.c znajdują się funkcje obsługujące główne menu programu.  

W pliku nim.c znajduje się główna logika gry Nim.  
bool GameEnd(int brd[], int colNum) - Zwraca true, jeżeli plansza jest pusta   
void InitializeBoard(int brd[], int colNum, int colHgt) - Losuje planszę na podstawie parametrów wprowadzonych w Nim Setup Menu.  
void PlayerMove(int brd[], int colNum) - Przyjmuje input użytkownika, pozwala na zaznaczenie i zatwierdzenie ruchu.  
void AIMove(int brd[], int colNum) - Oblicza i wykonuje ruch wygrywający.  
void DisplayBoard(int brd[], int colNum) - Rysuje planszę przy wykorzystaniu biblioteki ncurses.  
void ColourMarked(int brd[], int colNum, int x, int y, int colour_id) - Koloruje na wybrany kolor pierwsze x kamieni z kolumny  
o indeksie y.  
bool IsWinningPosition(int brd[], int colNum) - Sprawdza, czy aktualny stan gry pozwala graczowi wykonującemu następny ruch na wygraną, przy założeniu, że będzie on grał optymalnie.  
int PlayNim(bool isAI, int colNum, int colHgt) - Główna funkcja programu  

