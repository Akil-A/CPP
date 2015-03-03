# Oblig 1

### Resultat: 
Lever på nytt


### Checklist:
* [] Begge programmen bygger med `make`.
* [x] Begge programmen starter og kjører under Linux.
* [x] **oppvarming** gir riktig output.
* [/] **blackjack** har det viktigeste funksjonaliteten.
	* [x] En spiller har et saldo og kan satse et beløp.
	* [x] En spiller har valgen "HIT" og "STAND".
	* [] En spiller kan ikke fortsette når den har gått tom for penger.
	* [x] Dealerns handlinger virker riktige.
	* [x] Spillet følger reglene til BlackJack.
* [x] Ingen alvorlige kjøretidsfeil (segfault etc.)
* [x] Ingen minnelekasjer funnet med `valgrind`.
* [x] Repo innholder `RAPPORT.md`.



### Tilbakemelding:
Mangler Makefile.

Et stort pluss for multiplayer - bra! Bra bruk av mange tydlige funksjoner. Bra at du løst oppgaven med klasser. Hadde gjerne sett disse implementert med header-filer.

Noe som jeg synes var lite rart er at man kan fortsette og spille uten noen penger, gjennom å velge stand. Dette gir ikke noen mening, da man hverken vinner eller taper noen penger:

	Player1 bet from 1 to 0 or (s)tand out
	s
	
	
	Player2 bet from 1 to 0 or (s)tand out
	s

	Dealer ♣ 4 ?
	==============================================
	Player1 ♦ 6 ♠ 4  Score: 10
	==============================================
	Player1 (s)tand or (h)it?
	h
	
	Dealer ♣ 4 ?
	==============================================
	Player1 ♦ 6 ♠ 4 ♦ 4  Score: 14
	==============================================
	Player1 (s)tand or (h)it?
	h
	
	==============================================
	Player1 ♦ 6 ♠ 4 ♦ 4 ♥ 9  Score: 23
	==============================================
	Player1 is busted and has lost 0 chips
	
	Dealer ♣ 4 ?
	==============================================
	Player2 ♣ 8 ♣ 10  Score: 18
	==============================================
	Player2 (s)tand or (h)it?
	s
	
	==============================================
	Dealer ♣ 4 ♥ Ace ♦ 9 ♠ 3  Score: 17
	==============================================
	
	Play more? (y)es, (n)o


#### Fix:
* Makefile.
* Fjerne muligheten til å la spilleren fortsette å spille når den har gått tom for penger.