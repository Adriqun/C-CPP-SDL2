#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string>

namespace deb
{
    std::string toPL( const char * text );
    void setColor( uint8_t i );

    void SDL_InitError();
    void IMG_InitError();
    void MIX_InitError();
    void TTF_InitError();

    void linearFilteringError();
    void createWindowError();
    void createRendererError();

    void loadingSurfaceError( std::string path );
    void loadingSurfaceFromTextError();
    void createTextureFromSurfaceError( std::string path );
    void setTextureError();

    void loadingMusicError( std::string path );
    void loadingChunkError(  std::string path );
    void loadingFontError(  std::string path );
    void loadingFileError( std::string path );
}

#endif // DEBUGGER_H
