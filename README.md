## Symulator_Teorii_Gier
	
W ramach projektu stworzę symulator gier z kombinatorycznej teorii gier przy użyciu GTK oraz Glade.
Program umożliwi użytkownikowi grę w wybrane gry przeciwko komputerowi lub innemu graczowi. 
	
### Funkcje programu i punktacja zastępowalnych części projektu:  
1. Menu w GTK umożliwiające: **(20p)**  
		a) wybór gry,  
		b) dostosowanie rozmiarów planszy,    
		c) wybór kto rozpoczyna grę.  
		
2. ~~Możliwość wczytania oraz zapisu stanu gry do pliku, **(10p)**~~   

3. ~~Wykorzystanie kodowania UTF-8, **(10p)**~~  

4. Logika pozwalająca obliczać pozycję wygrywającą dla gier: **(20p)**  
	a) Nim,  
	b) ~~Obstruction (http://www.lkozma.net/game.html),~~  
	c) ~~Domineering.~~ 
	
5. Wizualizacja stanu gry przy użyciu biblioteki ncurses **(20p)**  

	
Obliczanie strategii wygrywającej oraz reprezentacja graficzna każdej z tych gier jest podobna, 
zatem podzielenie kodu na odpowiednie moduły odpowiedzialne za poszczególne zadania umożliwi
znacznie szybsze dodawanie nowych gier do programu, wymagające jedynie niewielkich modyfikacji.
	
### Aby zainstalować program należy:
Zainstalować gtk oraz ncurses:
>sudo apt-get install libgtk-3-dev

>sudo apt-get install libncurses5-dev libncursesw5-dev

Następnie skompilować za pomocą:
>gcc -o SG main.c nim.c -Wall \`pkg-config --cflags --libs gtk+-3.0\` -export-dynamic -lncurses

Lub użyć skryptu make.sh.

Uruchomić:
>./SG
