Dette var en interessant oppgave gjennom hele perioden. 

Begynte å få en del bugs ved spesielle tilfeller som når noen fikk 21 poeng etter 3 eller mer kort 
så ble det regnet som blackjack. Fikset dette ved å sette bool blackjack i player struct og skrive:

if(playerScore == 21 && playerV[x].hand.size() == 2)
                playerV[x].blackjack = true;

 i score() funksjonen.
 
 Dealer fikk også dobbelutskrift når den ble busted pga utksriften i decision() funksjonen der koden sier fra linje 258:
 
 if(playerV[i].busted && !playerV[i].won && playerV[i].name != "Dealer") { // Check if player is busted after hit
                writeHand(playerV, i);
                playerV[i].busted = true;
                cout << playerV[i].name << " is busted and has lost " << playerV[i].bet << " chips" << endl << endl;
                i++;
            }
  
  Dette burde egentlig ikke være mulig fordi jeg har skrevet i while løkka i linje 232:
  i<(playerV.size()-1) 
  Dealer er siste player i playerV vector og derfor burde det ikke være mulig at man kom til Dealer i den metoden, 
  er kanskje pga i++ jeg har gjennom hele metoden, men jeg fant ikke feilen så jeg bare bruteforca ved å skrive:
  playerV[i].name != "Dealer" i linje 258 inne i "if" setningen for at dealer ikke skulle få busted utskrift.
  Utskriften for når Dealer er busted kommer i whoWon() metoden.
  
  
  Jeg kunne kanskje(sikkert) hatt mindre bool variabler i player struct og sjekket på mindre bool verdier i alle
  "if" setninger. Har dessverre ikke tid for å dobbelsjekke alt nå.
  
  Ellers var starten for meg litt treig fordi jeg visste ikke hvordan Card og Deck klasser skulle lages, etter det 
  gikk alt greit. Begynte å få bugs som jeg har forklart overfor og selvfølgelig andre småe som ikke var veldig
  irriterende. 
  
  Jeg leste oppgaven fort (dumt) og trodde at vi måtte lage multiplayer så jeg fikk ikke tid til å gjøre "utfordnende"
  delen av obligen, synes dette var mest interessante oppgave vi har fått på skolen i alle fag til ennå og håper at
  neste obligen handler om å videreutvikle blackjack vi lagde nå så vi kan ta med ting som "double", "split", og 
  noe av det mest interresante funksjon som å telle kort og vise sannsylighet for å buste etter hvert kort.
  
  Jeg tror ikke at jeg kommer til å se noen ulemper på måten jeg løste oppgaven før jeg må videreutvikle, da
  blir det sikkert noen åpenbaringer om noen ting jeg ikke har gjort optimalt.
  
 
 
