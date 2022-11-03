#include "pieces.h"

void sdl_exit(const char* message){
    SDL_Log("erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void create_window_render(SDL_Window** window, SDL_Renderer** renderer){
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, window, renderer)!= 0)
        sdl_exit("window and renderer creation");
}

void chargerImage(SDL_Surface** image, char* adressImage, SDL_Renderer** renderer, SDL_Window** window){
    *image =SDL_LoadBMP(adressImage);
    if(*image ==NULL)
    {
        char msg[100];
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        strcpy(msg, "impossible de charger image ");
        sdl_exit(strcat(msg,adressImage));
    }
}

void chargerTexture(SDL_Texture** texture, SDL_Surface** image, SDL_Renderer** renderer, SDL_Window** window, SDL_Rect* rectangle){
    *texture= SDL_CreateTextureFromSurface(*renderer,*image);
    SDL_FreeSurface(*image);
    if(*texture ==NULL)
    {
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        sdl_exit("impossible de charger texture");
    }
    if(  SDL_QueryTexture(*texture,NULL,NULL,&rectangle->w, &rectangle->h)!=0)
    {
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        sdl_exit("impossible de charger texture");
    }
}

void putOnWindow(SDL_Texture** texture, SDL_Window** window, SDL_Renderer** renderer, int x, int y, SDL_Rect* rectangle){
    rectangle->x= x+1;
    rectangle->y= y+1;

    if(SDL_RenderCopy(*renderer ,*texture,NULL,rectangle)!=0)
    {
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        sdl_exit("impossible de afficher la texture");

    }
    SDL_RenderPresent(*renderer);
    SDL_DestroyTexture(*texture);
}

void coordToPos(int x,int y,int *i,int *j){
	//utiliser x pour determiner la colonne
        double n= WINDOW_WIDTH/29.0;
        *i= ((int) x/n);
        *j= ((int) y/n);
        if (*i%4== 0)   *i/=2;
        else *i= (*i/4)*2 +1;
        if (*j%4== 0)   *j/=2;
        else *j= (*j/4)*2 +1;
}

void posToCoord(int i, int j, int* x, int *y){
        double m, n= WINDOW_WIDTH/29.0;
        if (i%2==0) m= 2*i*n;
        else m= 2*i*n- n;
        *x=(int) m;
        if (j%2==0) m= 2*j*n;
        else m= 2*j*n- n;
        *y=(int) m;
}

void quitter(piece* board[15][15], player* courant, player* opponent, SDL_Renderer* renderer, SDL_Window* window){
    free_player(courant);   free_player(opponent);
    free_board(board);  free(courant);  free(opponent);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void selectioner(SDL_Event event, int* i, int* j, SDL_Renderer* renderer, SDL_Window* window){
    int quit= 0;
    while (!quit){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_MOUSEBUTTONDOWN){
                coordToPos(event.button.x, event.button.y, i, j);
                quit =1;
            }
            else {
                if (event.type== SDL_QUIT){
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    exit(0);
                }
            }
        }
    }
}

int y_select(SDL_Event event, SDL_Renderer* renderer, SDL_Window* window){
    int y= 0, quit= 0;
    while (!quit){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_MOUSEBUTTONDOWN){
                y= event.button.y;
                quit =1;
            }
            else {
                if (event.type== SDL_QUIT){
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    exit(0);
                }
            }
        }
    }
    return y;
}

void showBoard(piece* board[15][15], SDL_Renderer* renderer, SDL_Window* window, char couleur){
    int i, j, x, y;
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    rectangle.h= rectangle.w= WINDOW_WIDTH;
    // netoyer la fenetre
    SDL_RenderClear(renderer);

    //afficher le plateau
    if (couleur== _Blanc)
        chargerImage(&image, plateauB, &renderer, &window);
    else
        chargerImage(&image, plateauN, &renderer, &window);

    chargerTexture(&texture,&image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, -1, -1, &rectangle);

    for (i=0; i<15; i++){
        for (j=0; j<15; j++){
            if (i%2== 0){
                if (j%2== 1){
                    posToCoord(i, j, &x, &y);
                    if (board[i][j]->name== _Dame){
                        if (board[i][j]->couleur== _Blanc){
                            chargerImage(&image, hDameB, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                        else{
                            chargerImage(&image, hDameN, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                    }
                    else if(board[i][j]->name== _Pion){
                        if (board[i][j]->couleur== _Blanc){
                            chargerImage(&image, hPionB, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                        else{
                            chargerImage(&image, hPionN, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                    }
                }
            }
            else{
                if (j%2== 0){
                    posToCoord(i, j, &x, &y);
                    if (board[i][j]->name== _Dame){
                      if (board[i][j]->couleur== _Blanc){
                            chargerImage(&image, vDameB, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                        else{
                            chargerImage(&image, vDameN, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                    }
                    else if(board[i][j]->name== _Pion){
                       if (board[i][j]->couleur== _Blanc){
                            chargerImage(&image, vPionB, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                        else{
                            chargerImage(&image, vPionN, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                    }
                }
                else{
                    posToCoord(i, j, &x, &y);
                    if (board[i][j]->name== _King){
                        if (board[i][j]->couleur== _Blanc){
                            chargerImage(&image, kingB, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                        else{
                            chargerImage(&image, kingN, &renderer, &window);
                            chargerTexture(&texture,&image, &renderer, &window, &rectangle);
                            putOnWindow(&texture, &window, &renderer, y, x, &rectangle);
                        }
                    }
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}


int menu_principal(SDL_Event event, SDL_Renderer* renderer, SDL_Window* window){
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    // netoyer la fenetre
    SDL_RenderClear(renderer);

    //afficher le menu
    chargerImage(&image, menuP, &renderer, &window);
    chargerTexture(&texture,&image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, -1, -1, &rectangle);

    SDL_RenderPresent(renderer);

    int y= y_select(event, renderer, window);

    return y;
}
void fin_parti(piece* board[15][15], SDL_Event event, SDL_Renderer* renderer, SDL_Window* window, player* courant, player* opponent, int* retour, int* newGame, int* sauver){

    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    showBoard(board, renderer, window, courant->couleur);
    int x, y, matC= mat(board, courant), matO= mat(board, opponent), patt= pat(board, courant, opponent);

    do{
        if (matC== 1){
            if (courant->couleur== _Noir){
                chargerImage(&image, blancG, &renderer, &window);
            }
            else{
                chargerImage(&image, noirG, &renderer, &window);
            }
        }
        else if (matO== 1){
            if (opponent->couleur== _Noir){
                chargerImage(&image, blancG, &renderer, &window);
            }
            else{
                chargerImage(&image, noirG, &renderer, &window);
            }
        }
        else if(patt== 1){
            chargerImage(&image, egalite, &renderer, &window);
        }


        //afficher le menu
        chargerTexture(&texture,&image, &renderer, &window, &rectangle);
        putOnWindow(&texture, &window, &renderer, -1, WINDOW_WIDTH, &rectangle);

        SDL_RenderPresent(renderer);


        selectioner(event, &x, &y, renderer, window);
        if (x>12 && y>14)
            game_menu(board, event, renderer, window, courant, opponent, retour, newGame, sauver);

    }
    while (*newGame== 0 && *retour== 0 && *sauver== 0);
}

// point rouge pour signaler la selection
void selectPiece(SDL_Renderer* renderer, SDL_Window* window){
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    chargerImage(&image, selectP, &renderer, &window);
    chargerTexture(&texture, &image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, 0, WINDOW_WIDTH, &rectangle);
    SDL_RenderPresent(renderer);
}

// afficher qu il y a une capture becessaire
void captureNecessaire(SDL_Renderer* renderer, SDL_Window* window, char choix){
    if (choix== _Pion || choix== _Dame){
        SDL_Surface* image= NULL;
        SDL_Texture* texture= NULL;
        SDL_Rect rectangle;
        if (choix== _Pion)
            chargerImage(&image, captureP, &renderer, &window);
        else
            chargerImage(&image, captureD, &renderer, &window);
        chargerTexture(&texture, &image, &renderer, &window, &rectangle);
        putOnWindow(&texture, &window, &renderer, 0, WINDOW_WIDTH, &rectangle);
        SDL_RenderPresent(renderer);
        SDL_Delay(1200);
    }
}


void show_credit(SDL_Event event, SDL_Renderer* renderer, SDL_Window* window){
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    SDL_RenderClear(renderer);
    chargerImage(&image, credit, &renderer, &window);
    chargerTexture(&texture, &image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, 0, 0, &rectangle);
    SDL_RenderPresent(renderer);
    int quit= 0;
    while (!quit){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.x>540 && event.button.y>653)
                    quit =1;
            }
            else {
                if (event.type== SDL_QUIT){
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    exit(0);
                }
            }
        }
    }

}


void show_rules(SDL_Event event, SDL_Renderer* renderer, SDL_Window* window){
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    SDL_RenderClear(renderer);
    chargerImage(&image, rules, &renderer, &window);
    chargerTexture(&texture, &image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, 0, 0, &rectangle);
    SDL_RenderPresent(renderer);
    int quit= 0;
    while (!quit){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.x>540 && event.button.y>653)
                    quit =1;
            }
            else {
                if (event.type== SDL_QUIT){
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    exit(0);
                }
            }
        }
    }
}


void lire_ligne(FILE* data, char* ligne){
    char caractere;
    int i=0;
     do
    {
        caractere=fgetc(data);
        ligne[i]= caractere;
        i++;
    }
    while (!feof(data) && caractere!='\n');
    if (feof(data)) {
        printf("fin fich");
        exit(2);
    }
}


void save_piece(piece* cas, FILE* data){
    fwrite(&(cas->couleur), 1, sizeof(char), data);
    fwrite(&(cas->name), 1, sizeof(char), data);
    fwrite(&(cas->teritoire), 1, sizeof(char), data);
    fwrite(&(cas->index[0]), 1, sizeof(int), data);
    fwrite(&(cas->index[1]), 1, sizeof(int), data);
    fwrite(&(cas->num), 1, sizeof(int), data);
}

void charger_piece(piece* cas, FILE* data){
    fread(&(cas->couleur), 1, sizeof(char), data);
    fread(&(cas->name), 1, sizeof(char), data);
    fread(&(cas->teritoire), 1, sizeof(char), data);
    fread(&(cas->index[0]), 1, sizeof(int), data);
    fread(&(cas->index[1]), 1, sizeof(int), data);
    fread(&(cas->num), 1, sizeof(int), data);
}

void save_player(player* courant, FILE* data){
    fwrite(&(courant->couleur), 1, sizeof(char), data);
    fwrite(&(courant->nb_dame), 1, sizeof(int), data);
    fwrite(&(courant->nb_pion), 1, sizeof(int), data);
    save_piece(courant->king, data);
    int i;
    for (i=0; i<15; i++){
        save_piece(courant->pions[i], data);
    }
    for (i=0; i<23; i++){
        save_piece(courant->dames[i], data);
    }
}

void charger_player(player* courant, FILE* data){
    fread(&(courant->couleur), 1, sizeof(char), data);
    fread(&(courant->nb_dame), 1, sizeof(int), data);
    fread(&(courant->nb_pion), 1, sizeof(int), data);
    charger_piece(courant->king, data);
    int i;
    for (i=0; i<15; i++){
        charger_piece(courant->pions[i], data);
    }
    for (i=0; i<23; i++){
        charger_piece(courant->dames[i], data);
    }
}

void save_board(piece* board[15][15], FILE* data){
    int i, j;
    for (i=0; i<15; i++){
        for (j=0; j<15; j++){
            save_piece(board[i][j], data);
        }
    }
}

void charger_board(piece* board[15][15], FILE* data){
    int i, j;
    for (i=0; i<15; i++){
        for (j=0; j<15; j++){
            charger_piece(board[i][j], data);
        }
    }
}

void save_partie(piece* board[15][15], player* courant, player* opponent){
    FILE *gamer=NULL, *plat= NULL, *copie, *data;
    gamer= fopen(saveP, "wb");
    save_player(courant, gamer); save_player(opponent, gamer);
    fclose(gamer);
    plat= fopen(saveB, "wb");
    if (plat== NULL)exit(EXIT_FAILURE);
    save_board(board, plat);
    fclose(plat);
    data= fopen(match, "rb");
    copie= fopen(dernier, "wb");
    copy_doc(data, copie);
    fclose(data);
    fclose(copie);
}


void charger_partie(piece* board[15][15], player* courant, player* opponent){
    FILE *gamer, *plat, *copie, *data;
    gamer= fopen(saveP, "rb");
    charger_player(courant, gamer);    charger_player(opponent, gamer);
    fclose(gamer);
    plat= fopen(saveB, "rb");
    charger_board(board, plat);
    fclose(plat);
    data= fopen(dernier, "rb");
    copie= fopen(match, "wb");
    copy_doc(data, copie);
    fclose(data);
    fclose(copie);
}

void move (piece* board[15][15], int ii, int ij, int fi, int fj){
    int sign;
    if (ii== fi){
        sign= (ij-fj)/abs(ij-fj);
        for (ij= ij ; abs(ij-fj)>0; ij=ij+sign*2){
            case_take(board, ii, ij, fi, fj);
        }
    }
    else if (ij==fj){
        sign= (ii-fi)/abs(ii-fi);
        for (ii= ii ; abs(ii-fi)>0; ii=ii+sign*2){
            case_take(board, ii, ij, fi, fj);
        }
    }
    else{
        case_take(board, ii, ij, fi, fj);
    }
}

void copy_doc(FILE* source, FILE* copie){
    int t[4];
    while (!feof(source)){
        fread(t, 4, sizeof(int), source);
        fwrite(t, 4, sizeof(int), copie);
    }
}

void replay(SDL_Renderer* renderer, SDL_Window* window){
    FILE* data;
    int ii, ij, fi, fj, sign;
    data= fopen(match,"rb");
    piece* board[15][15];
    printf("a");
    creerboard(board);
    printf("b");
    char temp1= _Blanc, temp2= _Noir, temp3=_Blanc;
    printf("c");
    int t[4], k;
    printf("d");
    while (!feof(data)){
        showBoard(board, renderer, window, temp1);
        fread(t, 4, sizeof(int), data);
        ii= t[0]; ij= t[1]; fi= t[2]; fj = t[3];
        if (ii== fi){
            sign= (ij-fj)/abs(ij-fj);
            for (k= ij ; sign*(k-fj)>0; k=k-sign*2){
                case_take(board, ii, k, fi, k-sign*2);
                printf("oO");
            }
        }
        else if (ij==fj){
            sign= (ii-fi)/abs(ii-fi);
            printf("sig %d ", sign);
            for (k= ii ; sign*(k-fi)>0; k=k-sign*2){
                case_take(board, k, ij, k-sign*2, fj);
                printf("po");
            }
        }
        else{
            case_take(board, ii, ij, fi, fj);
        }
        printf("f");
        temp1= temp2;
        temp2 =temp3;
        temp3=temp1;
        SDL_Delay(700);
    }
    fclose(data);
    free_board(board);
}


void game_menu(piece* board[15][15], SDL_Event event, SDL_Renderer* renderer, SDL_Window* window, player* courant, player* opponent, int* retour, int* newGame, int* sauver){
    SDL_Surface* image= NULL;
    SDL_Texture* texture= NULL;
    SDL_Rect rectangle;
    // netoyer la fenetre
    SDL_RenderClear(renderer);

    //afficher le menu
    chargerImage(&image, gameMenu, &renderer, &window);
    chargerTexture(&texture,&image, &renderer, &window, &rectangle);
    putOnWindow(&texture, &window, &renderer, -1, -1, &rectangle);

    SDL_RenderPresent(renderer);

    int y;
    do{
        y= y_select(event, renderer, window);
    }
    while (y<100);
    if (y>100 && y< 225){
        *newGame= 1;
        *sauver= 0;
    }
    // replay
    else if (y> 225 && y< 350){
       save_partie(board, courant, opponent);
       *sauver= 1;
       *newGame= 0;
    }
    else if (y>350 && y< 475){
        //replay
        replay(renderer, window);

    }
    // retour au menu pricipal
    else if (y>475 && y<600){
        *retour= 1;
        *sauver= 0;
    }
    //retour au jeu sinn
    else if (y>600){
        SDL_RenderClear(renderer);
        showBoard(board, renderer, window, courant->couleur);
    }
}
