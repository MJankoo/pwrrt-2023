# Rekrutacja PWR Racing Team 2023

Nie do końca rozumiem w jaki sposób powinien być udokumentowany kod dołączony do poszczególnych zadań, ze względu na to, że charakteryzuje się on dość małą złożonością. Kod został napisany w taki sposób, aby wszelkie nazwy funkcji/zmiennych opisywały to co w rzeczywistości dzieje się w rozwiązaniu. 
Poniżej zamieszczam jedynie opis zastosowanych rozwiązań. 

## Zadanie 1 - regulator PID 
Dla mnie jako laika z dziedziny elektroniki polecenie tego zadania nie było jasne.
Po kilku godzinach szukania przykładów i poznawania zasady działania regulatora PID nie byłem w stanie odpowiedzieć na pytanie jak sygnał sterujący wpływa na obiekt sterowany,
czy zmienna "t" w matematycznej reprezentacji obiektu sterowanego na pewno odpowiada czasowi i wiele innych. Niemniej jednak załączam swoją próbę realizacji tego zadania w pliku `./zad2/pid.c`

Wydawało mi się, że funkcja napisana w tym pliku realizuje działanie tego regulatora,
niestety po próbach związanych ze strojeniem tego regulatora nie jestem pewny czy to na pewno jest dobrze napisane :P

Każda wartość współczynnika Kd różna od zera zamiast wypłaszczać wykres tylko zwiększała rozstrzał pomiędzy kolejnymi wartościami. 

## Zadanie 2 - otoczka wypukła
Kod znajdujący otoczkę wypukłą zbioru punktów znajduje się w pliku `./zad2/quickhull.cpp`

### Konfiguracja:
W linijce 9. znajduje się stała `FILE_PATH`, w której należy ustawić ścieżkę do pliku zawierającego punkty.

### Zastosowany algorytm:
Znajdź dwa punkty o najmniejszej i największej wartości współrzędnej x. Punkty te na pewno należą do otoczki wypukłej. Nazwijmy je A - minimalny x i B - maksymalny x. 
Pozostałe punkty podziel na dwa zbiory. Jeden zbiór będzie zawierał punkty znajdujące się po prawej stronie odcinka AB, drugi zbiór będzie zawierał punkty znajdujące się po lewej stronie odcinka AB.
Kroki 4-6 wykonaj dla każdego ze zbiorów osobno.
Jeżeli zbiór zawiera jeden punkt to należy on do otoczki.
Jeżeli zbiór jest pusty, zakończ funkcję.
Znajdź punkt C który znajduje się najdalej od odcinka AB. Ten punkt należy do otoczki.
Podziel zbiór na dwa zbiory, pierwszy zawierający punkty znajdujące się po prawej stronie odcinka BC i drugi zawierający punkty znajdujące się po lewej stronie odcinka AC.
Wykonaj krok 3. z zadanymi wartościami
Dla odcinka AC: A = A, B = C
	Dla odcinka BC: A = C, B = B

