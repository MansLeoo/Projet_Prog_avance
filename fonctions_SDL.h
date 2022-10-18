#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \file fonction_SDL.h
 * \brief  Fonction SDL
 * \author  Mans Leo.
 */
#ifndef fonction_SDL
#define fonction_SDL

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);
SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) ;
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) ;
#endif