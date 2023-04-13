# Teoria grafów - projekt

*Autor: Kamil Barszczak*

## Część analityczna

Rozwiązania do części analitycznej oraz opis wykorzystania algorytmu Bellmana-Forda znajdują się w pliku "Kamil_Barszczak.pdf" w folderze "Czesc_analityczna". Pliki pomocnicze tj. "macierz_incydencji.xlsx" oraz "macierz_incydencji.csv" również znajdują się we wspomnianym folderze. 

## Część programistyczna

#### Instalacja i uruchomienie programu

1. Na początku należy sklonować repozytorium:
```
mkdir graph
cd graph
git clone https://github.com/kbarszczak/Graph_project .
```

2. Aby uruchomić program z zaimplementowanym algorytmem Bellmana-Forda należy uruchomić plik "Ford_Bellman.exe", który znajduje się w folderze "Czesc_programistyczna":
```
.\Czesc_programistyczna\Ford_Bellman.exe
```
Program został napisany w taki sposób, że po zakończeniu jego działania będzie czekał na dowolny znak z klawiatury, który go wyłączy. Aby wprowadzić graf, należy umieścić go w pliku w tym samym folderze co plik "Ford_Bellman.exe". Program za każdym razem pyta o nazwę pliku z grafem, z którego ma czytać (ścieżka bezwzględna nie działa). Jeżeli odczyt pliku zakończy się powodzeniem to program zapyta o wierzchołek, z którego ma rozpocząć poszukiwania. Po wykonaniu algorytmu wyświetlony zostanie graf oraz wszystkie odnalezione ścieżki wraz z ich wagami. (Jeżeli żadna ścieżka nie zostanie wyświetlona to znaczy, że z danego wierzchołka nie istnieje żadna ścieżka do pozostałych wierzchołków). Graf musi być przedstawiony w postaci listy sąsiedztwa.<br>

## Format pliku z grafem:<br>
"numer_wierzchołka_startowego:( numer_wierzchołka_końcowego waga_krawędzi)"

- () - wyrażenie wewnątrz nawiasów może być powtórzone wielokrotnie
- numer_wierzchołka_startowego oraz numer_wierzchołka_końcowego to nieujemne liczby całkowite
- waga_krawędzi - dowolna liczba typu double.


Przykład poprawnie zapisanej linii: "6: 4 -3.1 8 9.6".

"graph.json" znajdujacy się w folderze "Czesc_programistyczna" to przykład poprawnie zapisanego pliku z grafem. Proszę zwrócić uwagę na ilość spacji. Po znaku ':' jest dokładnie 1 spacja, poźniej każda kolejna liczba oddzielona jest dokładnie 1 spacją. Na końcu każdej linii nie może znajdować się znak spacji. Poprawność wprowadzonych linii testowana jest za pomocą następującego wyrażenia regularnego: "^[0-9]+:( [0-9]+ -?[0-9]+(\.[0-9]+)?)+$", które można przetestować tutaj: [regex](https://regex101.com/)

## Implementacja algorytmu Bellmana-Forda
Implementacja algorytmu zawarta jest w pliku "graph.cpp" od linii 148 do linii 199. Pliku znajduje się w folderze "Czesc_programistyczna".
