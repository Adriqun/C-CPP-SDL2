#ifndef CHART_H
#define CHART_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include "debugger.h"
/* GLOWNY PROBLEM
    Edytor map posiadal mozliwosc sterowania klawiszami, wsrod nich byly funkcje
    przesuwania obiektow w lewo badz w prawo ( +1024.x lub -1024.x ) problem pojawil sie
    gdy chcesz w czasie terazniejszym przesunac kamera np +1024.x nastepnie program wczytywal plik spowrtoem z
    wartosciami poczatkowymi jak gdyby nic sie nie zmienilo:
    ROZWIAZANIE:
    Stworzyc zmienna point, podczas wczytywania dodajemy punkt point, koniec koncow edytor map dziala.
*/
class Chart
{
    Uint8 width, height;
    SDL_Texture** texture;
    SDL_Rect** rect;
    Uint16* counter;
    FILE* file;

    SDL_Point point;
    Uint8 type, total;
    SDL_Rect block;

public:

    Chart();
    void free();

    std::string intToString( int path );
    int stringToInt( std::string &path );
    void setRect( std::string &path );
    void setCounter( std::string &path );

    void loadFile();
    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer );

    void render( SDL_Renderer* &renderer, SDL_Point _point );

    void addToFile(); // dodaje nowy blook do pliku
    void setMousePosition(); // ustawia tzw kratke, ulepsza ustawianie blokow
    void controlEditMode( SDL_Event &e ); // sterowanie klawiszami oraz mysza podczas trybu edytowania
    void renderEditMode( SDL_Renderer* &renderer ); // renderuje nie tylko mape z pliku ale aktualny blok
    bool checkCollision( SDL_Rect a );
};

class Wall
{
    SDL_Texture* texture;
    SDL_Rect rect;
    Uint8 vel;

public:

    Wall();
    ~Wall();
    void free();
    void loadTexture( SDL_Renderer* &renderer, char* path );
    void load( SDL_Renderer* &renderer );
    void render( SDL_Renderer* &renderer, Uint8 motion );
};

#endif // CHART_H
