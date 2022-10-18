#include <SDL2/SDL.h>
#include "fonctions_SDL.h"
#include <SDL2/SDL_ttf.h>

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    // Créer un contexte de rendu (renderer) pour l’image
    SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags) ;
    // Charger une image
    SDL_Surface* surface = SDL_LoadBMP(nomfichier) ;
    // Convertir la surface de l’image au format texture avant de l’appliquer
    SDL_Texture*  texture = SDL_CreateTextureFromSurface(renderer,surface) ;
    return texture ;
}

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b) {
    SDL_Surface* surface = SDL_LoadBMP(nomfichier) ;
    
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,r,g,b)) ;
    return SDL_CreateTextureFromSurface(renderer,surface) ;
 
}
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,TTF_Font *font, SDL_Color color) {
    // Écrire le texte sur une surface SDL
    SDL_Surface* surface = TTF_RenderText_Solid(font,message,color) ;
    SDL_Texture*  texture = SDL_CreateTextureFromSurface(renderer,surface) ;
    return texture ;
}
