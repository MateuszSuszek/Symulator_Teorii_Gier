# Symulator_Teorii_Gier
W ramach projektu stworzę symulator gier z kombinatorycznej teorii gier przy użyciu GTK oraz Glade.
	Program umożliwi użytkownikowi grę w wybrane gry przeciwko komputerowi lub innemu graczowi. 
	
	Dla każdej gry gracz będzie miał możliwość:
		-Dostosować rozmiar planszy,
		-Zdecydować o tym, kto rozpocznie grę,
	  -Wybrać, czy przeciwnikiem steruje komputer,
		-Zapisać oraz wczytać stan gry, który zostanie zachowany pomiędzy sesjami.
	 
	Obsługiwane gry:
		-Nim oraz jego warianty,
		-Uproszczona wersja gry Obstruction (http://www.lkozma.net/game.html),
		-Domineerig.

	
	Obliczanie strategii wygrywającej oraz reprezentacja graficzna każdej z tych gier jest podobna, zatem podzielenie kodu na odpowiednie moduły odpowiedzialne za poszczególne zadania umożliwi znacznie szybsze dodawanie nowych gier do programu, wymagające jedynie niewielkich modyfikacji.
