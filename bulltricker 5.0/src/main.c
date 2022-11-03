#include "pieces.h"


/*      *debut main*     */
/*      *debut main*     */

int main(int argc, char** argv){
    // partie logique
    player *courant= Malloc(player), *opponent = Malloc(player);
    piece* board[15][15];
    create_player(courant);  create_player(opponent);
    FILE* data;

    int ii=0, ij=0, fi=0, fj=0, k=0;
    player* temp= Malloc(player);
    data= fopen(dernier, "wb"); fclose(data);
    data= fopen(match, "wb");
    creerboard(board);
    initialiser_player(courant, _Blanc);    initialiser_player(opponent, _Noir);
    save_partie(board, courant, opponent);
    fclose(data);
    //partie graphique
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO)!=0) // Initialisation de la SDL (= 0 si tout est bien passé);(lancement SDL)
    {
        //SDL_Log("erreur d'initialisation SDL >%s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window* window= NULL;
    SDL_Renderer* renderer= NULL;
    create_window_render(&window, &renderer);

    // afficher le plateau

    /*  game loop */
    /*  game loop */
    SDL_bool launch= SDL_FALSE;
    int retour, y, newGame, sauver=0;
    SDL_Event event;

    while (!launch){
        retour= 0;  // retour au menu principal
        newGame= 1;
        y= menu_principal (event, renderer, window);
        // choix: nouvelle partie
        if (y> 100 && y< 340){
            if (y<220){
                newGame=1;
                sauver= 0;
                data= fopen(match, "wb"); fclose(data);
            }
            else{
                newGame= 0;
                charger_partie(board, courant, opponent);
                sauver= 1;
            }
            while (newGame== 1 || sauver== 1){
                if (newGame==1){
                    newGame= 0;
                    free_board(board);
                    creerboard(board);
                    initialiser_player(courant, _Blanc);    initialiser_player(opponent, _Noir);
                }

                while (mat(board, courant)== mat(board, opponent) && pat(board, courant, opponent)==0 && retour== newGame){
                    k=0;
                    while(k==0 && retour== 0 && newGame== 0){
                        showBoard(board, renderer, window, courant->couleur);
                        selectioner(event, &ij, &ii, renderer, window);
                        if (ii > 14 && ij> 12){
                            game_menu(board, event, renderer, window, courant, opponent, &retour, &newGame, &sauver);
                            continue;
                        }
                        selectPiece(renderer, window);

                        selectioner(event, &fj, &fi, renderer, window);
                        k=move_piece(board, courant, ii, ij, fi, fj, opponent, renderer, window);

                    }
                    if (newGame== 1 ) {
                        break;
                    }
                    sauvegarder(ii, ij, fi, fj);
                    temp= opponent;
                    opponent= courant;
                    courant= temp;

                }
                if (newGame== 1)continue;
                if (retour == 1 ){
                    newGame= 0;
                    break;
                }
                fin_parti(board, event, renderer, window, courant, opponent, &retour, &newGame, &sauver);

            }


        }
        else if (y> 340 && y< 460){
            show_rules(event, renderer, window);
        }
        else if (y>460 && y<580) {
            launch= SDL_TRUE;
            quitter(board, courant, opponent, renderer, window);
        }
        else if (y>580){
            show_credit(event, renderer, window);
        }
    }

    free(courant);  free(courant);  free(temp);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

/*      *fin main*       */
/*      *fin main*       */
