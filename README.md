# GIPF_Game
Projekt stanowi implementację silnika oraz solwera gry GIPF w wersji uogólnionej, opartej na czterech parametrach:
S – rozmiar planszy,
K – liczba pionów potrzebna do zbicia,
GW / GB – liczba pionów w rezerwie graczy (biały/czarny).

Silnik umożliwia:

  -wczytanie i walidację stanu gry,

  -wykonanie ruchu i ocenę jego poprawności,

  -drukowanie planszy i stanu gry,

  -generowanie wszystkich możliwych posunięć,

  -detekcję wygrywających ruchów.


----------------------------------------------------------------------------------------------

Solver obsługuje:

  -pełną analizę końcowych stanów gry,

  -ustalenie, który gracz ma strategię wygrywającą.

  -Sterowanie odbywa się za pomocą zestawu komend tekstowych (np. LOAD_GAME_BOARD, DO_MOVE, PRINT_GAME_STATE, itp.).
