#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "universal.h"
#include "character.h"

Character::Character()
{
    //ustawianie wartosci startowych
    coorChar.x=-400;
    coorChar.y=621;
    character=NULL;
    spriteCoor=NULL;
}
Character::~Character()
{
    //prypisanie wskaznikowi NULL'a
    character=NULL;
    spriteCoor=NULL;
}
bool Character::loadMedia(SDL_Renderer* &render)
{
    bool success=true;

    //wczytywanie grafiki postaci
    character=uni.loadTexture("images/man.png",render);
    if(character==NULL)
    {
        printf("Nie odnaleziono man.png! SDL Error: %s\n",SDL_GetError());
        success=false;
    }

    //dynamiczne alokowanie pamieci dla wspolrzednych postaci i ustawianie ich
    coorChar.w=124;
    coorChar.h=179.3;
    spriteCoor=new SDL_Rect[4];

    for(int i=0; i<4; i++)
    {
        spriteCoor[i].y=0;
        spriteCoor[i].w=372;
        spriteCoor[i].h=538;
        spriteCoor[i].x=372*i;
    }

    return success;
}
void Character::present(SDL_Point motion, SDL_Renderer* &renderer)
{
    SDL_RenderCopy(renderer,character,&spriteCoor[uni.counter(3,12)/12],&coorChar);

    //przypisywanie wspolrzednych
    coorChar.x=motion.x;
    coorChar.y=motion.y;
}
void Character::close()
{
    //niszczenie wskaznikow
    SDL_DestroyTexture(character);
    delete [] spriteCoor;
}

