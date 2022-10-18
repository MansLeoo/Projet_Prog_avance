#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
int main(int argc, char *argv[])
{
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "textures/fond.bmp", ecran );

    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* obj = charger_image_transparente("textures/obj.bmp", ecran,r,g,b);
    //Récupérer largeur et hargeur de la texture avec SDL_QueryTexture
    int objetW ,objetH ;
    SDL_QueryTexture(obj,NULL, NULL, &objetW, &objetH);
    SDL_Rect SrcR, DestR;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = objetW; // Largeur de l’objet en pixels de la texture
    SrcR.h = objetH; // Hauteur de l’objet en pixels de la texture
    DestR.x = 350;
    DestR.y = 350;
    DestR.w = objetW/3;
    DestR.h = objetH/3;

    SDL_Texture* spr = charger_image_transparente("textures/sprites.bmp", ecran,0,g,b);

    SDL_Rect SrcR_sprite[6];
    int j = 0 ;
        for(int i = 0 ; i<6 ; i++){
            printf("i :%i, j :%i",i,j);
            SrcR_sprite[i].x = 0+(i/(j+1))*95;
            SrcR_sprite[i].y = 0+j*125;
            SrcR_sprite[i].w = 95;
            SrcR_sprite[i].h = 125;
            if (i==2){  j=j+1;} 
        }

    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++)
    {
        DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
        DestR_sprite[i].y = i > 2 ? 60 : 120;
        DestR_sprite[i].w = 95; // Largeur du sprite
        DestR_sprite[i].h = 125; // Hauteur du sprite
    }
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./font/arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char msg[] = "TP sur Makefile et SDL";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    int  texteW,texteH ;
    SDL_QueryTexture(texte,NULL, NULL, &texteW, &texteH);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW; // Largeur du texte en pixels (à récupérer)
    text_pos.h = texteH; // Hauteur du texte en pixels (à récupérer)
    // Boucle principale
    while(!terminer){
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_RenderCopy(ecran, obj, &SrcR, &DestR);
        for (int i = 0; i < 6; i++)
        {
                SDL_RenderCopy(ecran,spr,&SrcR_sprite[i],&DestR_sprite[i]);
        }
        //Appliquer la surface du texte sur l’écran
        SDL_RenderCopy(ecran,texte,NULL,&text_pos);
        //SDL_PollEvent ...
        SDL_PollEvent( &evenements );
        switch(evenements.type)
        {
        case SDL_QUIT:
            terminer = true; break;
        case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_q:
                terminer = true; break;
            }
        }
        SDL_RenderPresent(ecran);
    }
    // Libérer de la mémoire
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ecran);
    TTF_CloseFont( font );
    TTF_Quit();
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}