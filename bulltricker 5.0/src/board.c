#include "pieces.h"

void creerboard(piece* board[15][15]){
    int i, j;
    //initialiser le plateau
    for (i=0; i<15; i++){
        for(j=0; j<15; j++){
            board[i][j]=Malloc(piece);
            board[i][j]->couleur=_Vide;
            board[i][j]->name= _Vide;
            board[i][j]->num =0;
            board[i][j]->index[0]= i;
            board[i][j]->index[1]= j;
            board[i][j]->teritoire= _Vide;
        }
    }

    //blocks non  utilisable du plateau: #
    for (i=0; i<15; i=i+2){
        for (j=0; j<15; j=j+2){
            board[i][j]->index[0]= i;  board[i][j]->index[1]= j;
            board[i][j]->name =_CarreBute;
        }
    }

    //initialisaton block dames
    for (i=0; i<15; i=i+2){
        board[1][i]->num = i/2 +1;
        board[1][i]->couleur = _Noir;
        board[1][i]->index[0]=1;   board[1][i]->index[1]= j;
        board[1][i]->name = _Dame;

        board[13][i]->num = i/2 +1;
        board[13][i]->couleur = _Blanc;
        board[13][i]->index[0]=13;   board[13][i]->index[1]= i;
        board[13][i]->name = _Dame;
    }

    //initialisation blocks pion
    for (i=2; i<4; i++){
        for (j=(i+1)%2; j<15; j=j+2){
            board[i][j]->num = (i-2)*8 + (j+1)/2 ;
            board[i][j]->couleur = _Noir;
            board[i][j]->index[0]=i;   board[1][i]->index[1]= j;
            board[i][j]->name = _Pion;

            board[14-i][j]->num = (i-2)*8 + (j+1)/2 ;
            board[14-i][j]->couleur = _Blanc;
            board[14-i][j]->index[0]=14-i;   board[13][i]->index[1]= j;
            board[14-i][j]->name = _Pion;
            }
        }

    //initialisation des rois
    case_king(board, _Noir, 1, 7);

    case_king(board, _Blanc, 13, 7);

}

void copy_board(piece* board[15][15], piece* copie[15][15]){
    int i, j;
    for (i=0; i<15; i++){
        for(j=0; j<15; j++){
            copie[i][j]->couleur= board[i][j]->couleur;
            copie[i][j]->name= board[i][j]->name;
            copie[i][j]->index[0] = i;  copie[i][j]->index[1]= j;
            copie[i][j]->num= board[i][j]->num;
            copie[i][j]->teritoire= board[i][j]->teritoire;
        }
    }
}

// si les coordonnes sont dans le cadre du plateau
int valide_case(int i, int j){
    int t=1;
    if (i<0 || i>14 || j<0 || j>14 ||(i%2== 0 && j%2== 0)){
        t=0;
    }
    return t;
}

void case_take(piece* board[15][15], int ii, int ij, int fi, int fj){
    int i;
    board[fi][fj]->name= board[ii][ij]->name; board[ii][ij]->name= _Vide;
    board[fi][fj]->couleur= board[ii][ij]->couleur; board[ii][ij]->couleur= _Vide;
    i= board[ii][ij]->num; board[ii][ij]->num = board[fi][fj]->num;board[fi][fj]->num = i;
}

void create_player(player* courant){
    int i;

    courant->king= Malloc(piece);

    for (i=0; i<23; i++){
        courant->dames[i]= Malloc(piece);
    }

    for (i=0; i<15; i++){
        courant->pions[i]= Malloc(piece);
    }
}

void initialiser_player(player* courant, char couleur){
    int i, j;
    courant->couleur= couleur;
    courant->nb_dame= 0;
    courant->nb_pion= 0;
    if (couleur== _Blanc){
        courant->king= creerKing(courant, 13, 7);
    }
    else{
        courant->king= creerKing(courant, 1, 7);
    }

    for (i=0; i<23; i++){
        if (i< 8){
            if (couleur== _Blanc)
                courant->dames[i]= creerDame(courant, 13, 2*i);
            else if(couleur== _Noir)
                courant->dames[i]= creerDame(courant, 1, 2*i);
        }
        else
            courant->dames[i]->name= _Vide;
    }


    for (i=2; i<4; i++){
        for (j=(i+1)%2; j<15; j=j+2){
            if (couleur== _Blanc){
                courant->pions[(i-2)*8 + j/2]= creerPion(courant, 14-i, j);
            }
            else{
                courant->pions[(i-2)*8 + j/2]= creerPion(courant, i, j);
            }
        }
    }

}

int case_royal(int i, int j){
    int t=0;
    if (i%2==1 && j%2==1){
        t=1;
    }
    return t;
}

int dame_capture_obligatoire(piece* board[15][15], player* courant, piece* dame, player* opponent){
    int t=0;
    if ((dame->index[0]%2== 0 &&(take_above(board, dame) || take_bellow(board, dame)))|| (dame->index[0]%2==1 &&(take_left(board, dame) || take_right(board, dame))) ) t=1;
    return t;
}

char capture_obligatoire(piece *board [15][15], player* courant, player* opponent){
    char p= _Vide;
    int i;
    for(i=0; i<23; i++){
        if (courant->dames[i]->name== _Dame && board[courant->dames[i]->index[0]][courant->dames[i]->index[1]]->name== _Dame && board[courant->dames[i]->index[0]][courant->dames[i]->index[1]]->couleur== courant->couleur){
            if (dame_capture_obligatoire(board, courant, board[courant->dames[i]->index[0]][courant->dames[i]->index[1]], opponent)){
                p= _Dame;
            }
        }
        else {
            if (courant->dames[i]->name== _Vide)break;
        }
    }
    if (p== _Vide){
        for(i=0; i<15; i++){
            if (board[courant->pions[i]->index[0]][courant->pions[i]->index[1]]->name== _Pion && board[courant->pions[i]->index[0]][courant->pions[i]->index[1]]->couleur== courant->couleur){
                if((courant->couleur== _Blanc && capture_necessaire_blanc(board, courant, courant->pions[i]->index[0], courant->pions[i]->index[1], opponent)==1) ||
                   (courant->couleur== _Noir && capture_necessaire_noir(board, courant, courant->pions[i]->index[0], courant->pions[i]->index[1], opponent)==1)) p= _Pion;
            }
        }
    }
    return p;
}

int move_piece(piece* board[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent, SDL_Renderer* renderer, SDL_Window* window){
    int t=0;
    char cap_ob;
    if (valide_case(ii, ij) && valide_case(fi, fj) && courant->couleur == board[ii][ij]->couleur){
        cap_ob= capture_obligatoire(board, courant, opponent);
        switch(board[ii][ij]->name){
            case _King:
                if (cap_ob!= _Vide){printf("capture '%c' necessaire .\n", capture_obligatoire(board, courant, opponent));}
                else{
                    printf("king: ");
                    t= move_king(board, courant, fi, fj, opponent);
                }
                break;

            case _Dame:
                if (cap_ob== _Vide || (cap_ob== _Dame && dame_capture_obligatoire(board, courant, board[ii][ij], opponent))){
                    printf("dame: ");
                    t= move_dame(board, courant, ii, ij, fi, fj, opponent);
                    }
                else printf("capture '%c' necessaire .\n", capture_obligatoire(board, courant, opponent));
                break;

            case _Pion:
                if (cap_ob== _Vide ||(cap_ob== _Pion && ((courant->couleur== _Blanc && capture_necessaire_blanc(board, courant, ii, ij, opponent))
                                                         ||(courant->couleur== _Noir && capture_necessaire_noir(board, courant, ii, ij, opponent))))){
                    printf("pion: ");
                    t= move_pion(board, courant,ii, ij, fi, fj, opponent);
                }
                else printf("capture '%c' necessaire .\n", capture_obligatoire(board, courant, opponent));
            break;
        }
        if (cap_ob!= _Vide && t==0)
            captureNecessaire(renderer, window, cap_ob);
    }
    else{
        printf("case invalide %d! ",t);
    }
    return t;
}

void enregistrer(FILE* data, const int ii, const int ij, const int fi, const int fj){
    data= fopen(match, "a");
    fprintf(data, "%d %d\t%d %d\n", ii, ij, fi, fj);
    fclose(data);
}

int canPionMove(piece *board[15][15],player* courant, piece* pion, player* opponent){
    int t=0, x= pion->index[0], y= pion->index[1];
    if ((pion->couleur== _Noir &&(capture_necessaire_noir(board, courant, x ,y, opponent) || (board[x+2][y]->name== _Vide && board[x+1][y]->name== _Vide)||
        board[x+1][y+1]->name== _Vide || board[x+1][y-1]->name== _Vide)) || (pion->couleur== _Blanc &&(capture_necessaire_blanc(board, courant, x ,y, opponent)||
        (board[x-2][y]->name== _Vide && board[x-1][y]->name== _Vide)|| board[x-1][y+1]->name== _Vide || board[x-1][y-1]->name== _Vide))){
        t=1;
    }
    return t;
}

void free_player(player* courant){
    int i;
    for (i=0; i<15; i++){
        free(courant->pions[i]);
    }
    for (i=0; i<23; i++){
        free(courant->dames[i]);
    }
    free(courant->king);
}

void free_board(piece* board[15][15]){
    int i, j;
    for (i=0; i<15; i++){
    for(j=0; j<15; j++){
        free(board[i][j]);
        }
    }
}

void sauvegarder(int ii, int ij, int fi, int fj){
    int t[]={ii, ij, fi, fj};
    FILE* data;
    data= fopen(match, "ab");
    fwrite(t, 4, sizeof(int), data);
    fclose(data);
}
