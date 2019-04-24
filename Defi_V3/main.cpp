#include "logique.h"
#include "donnee.h"
#include "vue.h"



//Impl�mentation
//BUT : Jeu d�fis
//ENTREE : L'environnement
//SORTIE : Une fen�tre
int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO); // D�marrage de la SDL (ici : chargement du syst�me vid�o)
    TTF_Init();


    //Partie d�clarations des variables
    //====================================================================
    SDL_Window *pWindow = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool blCont=true;
    int nScene = 0, nSeq = 0, nPosX = 50;
    position clic;
    //====================================================================

    pWindow = SDL_CreateWindow("L'etrange collection de M.Strikovic",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    clic.nX=ZERO;
    clic.nY=ZERO;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_Music *musique; //Cr�ation du pointeur de type Mix_Music
    musique = Mix_LoadMUS("musique.wav"); //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

    if( pWindow ) // D�s que la fen�tre est cr��e
    {
        while(blCont == true)  // Tant que le jeu continue
        {
            while (SDL_PollEvent(&event)) // Stockage des �v�nements :
            {
                switch(event.type)
                {
                    case SDL_QUIT:  // Pour fermer la fen�tre
                        blCont = false;
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        clic.nX = event.button.x;
                        clic.nY = event.button.y;
                        break;
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_SPACE) // Pour passer du menu au jeu
                        {
                            if (nScene==MENU)
                            {
                                nScene = CORRIDOR;
                            }
                        }
                        break;
                }
            }


            // Boucle de jeu :
            if (nScene==MENU)
            {
                renduMenu(&renderer);
            }
            else if (nScene==CORRIDOR)
            {
                SDL_Delay(DELAI);
                renduScene1(&renderer);
                SeqCorridor(&clic, &nSeq);
                renduSeqCorridor(nSeq, &renderer, nPosX);
                if (nSeq == 2)
                {
                    if (nPosX < POSXMAX)
                    {
                        nPosX += INCRX;
                    }
                }
                else if (nSeq == 3)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==CORDE)
            {
                SDL_Delay(DELAI);
                renduSalleCorde(&renderer);
                SeqCorde(&clic, &nSeq);
                renduSeqCorde(nSeq, &renderer);
                if (nSeq == 8)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==CORDE2)
            {
                SDL_Delay(DELAI);
                renduSalleCordeDeux(&renderer);
                SeqCordeDeux(&clic, &nSeq);
                //renduSeqCordeDeux(nSeq, &renderer);
                if (nSeq == 5)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==PERCU)
            {
                SDL_Delay(DELAI);
                renduSallePercu(&renderer);
                SeqPercu(&clic, &nSeq);
                renduSeqPercu(nSeq, &renderer);
                if (nSeq == 8)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==PERCU2)
            {
                SDL_Delay(DELAI);
                renduSallePercuDeux(&renderer);
                SeqPercuDeux(&clic, &nSeq);
                //renduSeqPercuDeux(nSeq, &renderer);
                if (nSeq == 3)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==VENT)
            {
                SDL_Delay(DELAI);
                renduSalleVent(&renderer);
                SeqVent(&clic, &nSeq);
                renduSeqVent(nSeq, &renderer);
                if (nSeq == 8)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==VENT2)
            {
                SDL_Delay(DELAI);
                renduSalleVentDeux(&renderer);
                SeqVentDeux(&clic, &nSeq);
                //renduSeqVentDeux(nSeq, &renderer);
                if (nSeq == 6)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }
            else if (nScene==SALON)
            {
                SDL_Delay(DELAI);
                renduSalon(&renderer);
                SeqSalon(&clic, &nSeq);
                //renduSeqSalon(nSeq, &renderer);
                if (nSeq == 3)
                {
                    redirectScene(&clic, &nScene, &nSeq);
                }
            }



            SDL_RenderPresent(renderer);


        }
    }
    Mix_FreeMusic(musique); //Lib�ration de la musique
    Mix_CloseAudio();
    TTF_Quit();
    SDL_DestroyWindow(pWindow); // Destruction de la fen�tre
    SDL_Quit(); // Arr�t de la SDL (lib�ration de la m�moire)
    return 1;
}


//TO DO � faire en urgence!!
// - Mettre des sons
// - Faire les �nigmes des salles 2

