biblioteka fenv.h zawiera zestaw funkcji i makro z dostêpem do œrodowiska zmiennoprzecinkowego wraz
z konkretnymi typami

feclearexcept - wyraŸne wyj¹tki zmiennoprzecinkowe
feraiseexcept - wy¿szy zmiennoprzecinkowy wyj¹tek
fegetexceptflag - uzyskujesz zmiennoprzecinkowe znaczniki wyjatkow
fesetexceptflag - ustaw zmiennoprzecinkowe znaczniki wyjatkow

fegetround - uzyskaj sposob zaokraglenia
fesetround - ustaw sposob zaokraglenia

fegetenv - uzyskaj zmiennoprzecinkowe srodowisko
fesetenv - ustaw zmiennoprzecinkowe srodowisko
feholdexcept - przetrzymuj wyj¹tki zmiennoprzecinkowe
feupdateenv - aktualizacja srodowiska zmiennoprzecinkowego
fetextexcept - text wyjatkow zmiennoprzecinkowych

fenv_t - zmiennoprzecinkowy typ srodowiska
fexcept_t - zmiennoprzecinkowy typ wyjatku

CONSTANTS - STALE

*Zmiennoprzecinkowe wyjatki*
FE_DIVBYZERO - wyjadtkiem jest dzielenie przez 0
FE_INEXACT - wyjatkiem jest niedokladny wynik
FE_INVALID - wyjatkiem jest nieprawidlowy argument
FE_OVERFLOW - wyjatkiem jest przekroczenie zakresu ( GORNY )
FE_UNDERFLOW - wyjatkiem jest przekroczenie zakresu ( DOLNY )
FE_ALL_EXCEPT - wszystkie wyjatki

*Zaokraglanie - flagi*
FE_DOWNWARD - zaogragla do dolu
FE_TONEAREST - zaogragla do najblizszej liczby calkowitej
FE_TOWARDZERO - zaogragla do najdalszej liczby calkowitej
FE_UPWARD - zaokgragla do gory

*Cale - srodowisko*
FE_DFL_ENV - domyslne srodowisko

Dyrektywy
*PRAGMA*
FENV_ACCESS - dostep do zmiennoprzecinkowych srodowisk 