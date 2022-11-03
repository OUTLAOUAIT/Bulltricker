/*#include "pieces.h"

// creation d'une dame
piece* creerDame(player* courant, int x, int y){
    piece* dame= Malloc(piece);
    // piece noire
    if (courant->couleur== _Noir){
        static int compB = 1;
        dame->num = compB++ ;
    }
    // piece blache
    else{
        static int compW = 1;
        dame->num = compW++ ;
    }
    dame->couleur = courant->couleur;
    dame->index[0]=x;   dame->index[1]= y;
    dame->name = _Dame;

    courant->dames[dame->num-1]= dame;
    courant->nb_dame++;
    return dame;
}

// les fonctions "search_piece_..."
// chercheent une piece sur la meme ligne/ collone
// et retourner l'indice de la ligne/collone ou elle se trouve
// ou -1 sinon
int search_piece_above(piece* board[15][15], piece* piece){
    int i, j = -1;
    char color;
    for (i= piece->index[0]-1; i>=0; i--){
        color= board[i][piece->index[1]]->couleur;
        // si la case n'est pas vide sortir
        if (color != _Vide){
            j= i;
            break;
        }
    }
    return j;
}


int search_piece_bellow(piece* board[15][15], piece* piece){
    int i, j = -1;
    char color ;
    for (i= piece->index[0]+1; i<15; i++){
        color= board[i][piece->index[1]]->couleur;
        // si la case n'est pas vide sortir
        if (color != _Vide){
            j= i;
            break;
        }
    }
    return j;
}

int search_piece_right(piece* board[15][15], piece* piece){
    int i, j = -1;
    char color ;
    for (i= piece->index[1]+1; i<15; i++){
        color = board[piece->index[0]][i]->couleur;
        //si la case n'est pas vide sortir
        if (color != _Vide){
            j= i;
            break;
        }
    }
    return j;
}

int search_piece_left(piece* board[15][15], piece* piece){
    int i, j = -1;
    char color ;
    for (i= piece->index[1]-1; i>=0; i--){
        color= board[piece->index[0]][i]->couleur ;
        //si la case n'est pas vide soritr
        if (color != _Vide){
            j= i;
            break;
        }
    }
    return j;
}

// les foncrion "take_.." cherchent si
// il y a une piece qu'on peut sauter
// rendre 1 au cas favorable et 0 sinon
int take_above(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_above(board, dame);
    if (i!=-1 && board[i][dame->index[1]]->couleur!= dame->couleur && board[i][dame->index[1]]->name!=_King){
        if(i>1 && board[i-1][dame->index[1]]->name== _Vide){
            if (board[i-2][dame->index[1]]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int take_bellow(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_bellow(board, dame);
    if (i!=-1 && board[i][dame->index[1]]->couleur!= dame->couleur && board[i][dame->index[1]]->name!= _King){
        if(i<13 && board[i+1][dame->index[1]]->name== _Vide){
            if (board[i+2][dame->index[1]]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int take_right(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_right(board, dame);
    if (i!=-1 && board[dame->index[0]][i]->couleur!=dame->couleur && board[dame->index[0]][i]->name!= _King){
        if(i<14 && board[dame->index[0]][i+1]->name== _Vide){
            if (board[dame->index[0]][i+2]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int take_left(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_above(board, dame);
    if (i!=-1 && board[dame->index[0]][i]->couleur!= dame->couleur && board[dame->index[0]][i]->name!= _King){
        if(i>1 && board[dame->index[0]][i-1]->name== _Vide){
            if (board[dame->index[0]][i-2]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

//fontion qui cherche si il y a une prise obligatoire
// dans le cas ou la dame est sur rang vertical
int prise_obliga_vertic(piece* board[15][15], piece* dame){
    int t= 0;
    if ((dame->index[0])%2 ==0 && (dame->index[1])%2 == 1){
        if (take_above(board, dame) || take_bellow(board, dame)){
            t=1;
        }
    }
    return t;
}

//fontion qui cherche si il y a une prise obligatoire
// dans le cas ou la dame est sur rang horizontal
int prise_obliga_horizon(piece* board[15][15], piece* dame){
    int t=0;
    if ((dame->index[0])%2==1 && (dame->index[1])%2 == 0){
        if(take_left(board, dame) || take_right(board, dame)){
            t=1;
        }
    }
    return t;
}

// fonction qui cherche si il y a une prise collone horizontale
// return 1 en cas favorable ou 0 sinon
int prise_faculta_left(piece* board[15][15], piece* dame){
    int i, t=0;
    if ((dame->index[0])%2==0 && (dame->index[1])%2 == 1){
        i= search_piece_left(board, dame);
        // si la plus proche piece oppose sur meme ligne est loin d'un bric a gauche
        if (i!=-1 && board[dame->index[0]][i]->couleur!= dame->couleur && dame->index[1]-2 == i){
            t=1;
        }
    }
    return t;
}

int prise_faculta_right(piece* board[15][15], piece* dame){
    int i, t=0;
    if ((dame->index[0])%2==0 && (dame->index[1])%2 == 1){
        i= search_piece_right(board, dame);
        // si il y a une piece oppose sur la meme ligne ligne est qui est loin d'un seul bric
        if (i!=-1 && board[dame->index[0]][i]->couleur!= dame->couleur && dame->index[1]+2== i){
            t= 1;
        }
    }
    return t;
}

// chercher si il y a une prse collone verticale
int prise_faculta_above(piece* board[15][15], piece* dame){
    int i, t=0;
    if ((dame->index[0])%2==1 && (dame->index[1])%2 == 0){
        i= search_piece_above(board, dame);
        if (i!=-1 && board[i][dame->index[1]]->couleur!= dame->couleur && dame->index[0]-1 == i){
            t=1;
        }
    }
    return t;
}

int prise_faculta_bellow(piece* board[15][15], piece* dame){
    int i, t=0;
    if ((dame->index[0])%2==1 && (dame->index[1])%2 == 0){
        i= search_piece_bellow(board, dame);
        if (i!=-1 && board[i][dame->index[1]]->couleur!= dame->couleur && dame->index[0]+1 == i){
            t= 1;
        }
    }
    return t;
}

// fonction move_dame qui effectue le deplacement de la piece donnee
// et retourne 1, ou retourne 0 si le deplacement n'est pas possible

int move_dame(piece* boa[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent){
    piece* board[15][15];
    printf("courant %c;  opponent %c\n", courant->couleur, opponent->couleur);

    creerboard(board);

    copy_board(boa, board);
    printf("courant %c;  opponent %c\n", courant->couleur, opponent->couleur);
    int t=0, fac;
    int nbOdame= opponent->nb_dame, nbOpion= opponent->nb_pion; //pour mettre a jour le nombre de pieces restantes a opponent

       // cas si les case ne sont pas valide ou la destination est pleine
    if (valide_case(ii, ij)==0 || valide_case(fi, fj)==0 || courant->couleur!= board[ii][ij]->couleur || case_royal(fi,fj)==1){
        printf("case non valide! \n");
    }

    else{
        int k=ii;
        // si il y a une prise obligatoire sur rang vertical
        if (prise_obliga_vertic(board, board[ii][ij])){
            // cas il y a piece above a capturer
            if (take_above(board, board[ii][ij])){
                //cas il y a piece en haut et en bas a capturer
                if (take_bellow(board, board[ii][ij])){
                    // si les coordonnes passées ne sont pas compatible avec la capture
                    if((search_piece_above(board, board[ii][ij])< fi && fi< search_piece_bellow(board, board[ii][ij])) || ij!= fj){
                        printf("Capture necessaire !\n");
                    }
                    else{
                        // cas on choisit de prenedre piece above
                        if(fi<search_piece_above(board, board[ii][ij])){
                            do{
                                    if (board[k-2][ij]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    if (board[k-2][ij]->name== _Pion){
                                        nbOpion--;
                                    }
                                }
                                case_take(board,k,ij,k-2,ij);
                                k=k-2;
                            }
                            while(k>=0 && (take_above(board, board[k][ij])==1 ||(k>= fi && board[k-1][ij]->couleur== _Vide && board[k-2][ij]->couleur== _Vide)));
                        }
                            // cas capture bellow
                        else{
                            do{
                                if (board[k+2][ij]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    if (board[k+2][ij]->name== _Pion){
                                        nbOpion--;
                                    }
                                }
                                case_take(board,k,ij,k+2,ij);
                                k=k+2;
                            }
                            while(k<15 && ((k<fi && board[k+1][ij]->couleur== _Vide && board[k+2][ij]->couleur== _Vide) || take_bellow(board, board[k][ij])==1 ));// );
                        }
                        if (k==fi){
                            t=1;
                        }
                    }
                }
                else{
                    // cas il y a saulement piece above a capturer
                        // si les coordonnes ne sont pas compatible avec la capture
                    if(search_piece_above(board, board[ii][ij]) < fi || ij!= fj){
                        printf("Capture necessaire !\n");
                    }
                    else{
                        if(fi<search_piece_above(board, board[ii][ij])){
                            do{
                                if (board[k-2][ij]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    if (board[k-2][ij]->name== _Pion){
                                        nbOpion--;
                                    }
                                }
                                case_take(board,k,ij,k-2,ij);
                                k=k-2;
                            }
                            while(k>=0 && (k>fi || take_above(board, board[k][ij]) || k> search_piece_above(board, board[k][ij])));
                        }
                        if (k==fi){
                            t=1;
                        }
                    }
                }
            }
            else{
                // cas il y a seulement piece bellow
                if (take_bellow(board, board[ii][ij])){
                    // si les coordonnes ne sont pas compatible avec la capture
                    if(fi < search_piece_bellow(board, board[ii][ij])|| ij!= fj){
                        printf("Capture necessaire !\n");
                    }
                    else{
                        do{
                            if (board[k+2][ij]->name== _Dame){
                                nbOdame--;
                            }
                            else{
                                if (board[k+2][ij]->name== _Pion){
                                    nbOpion--;
                                }
                            }
                            case_take(board,k,ij,k+2,ij);
                            k=k+2;
                        }
                        while(k<15 && (k<fi || take_bellow(board, board[k][ij]) || k> search_piece_bellow(board, board[k][ij])));
                        if (k==fi){
                            t=1;
                        }
                    }
                }
            }
            if(t==1 ){
                if(prise_faculta_above(board, board[fi][fj]) && prise_faculta_bellow(board, board[fi][fj])){
                    printf("vous avez deux captures facultatives possibles.\nTapez 1 pour le sense< ou 2 pour -> ou n'importe pour passer: ");
                    scanf("%d", &fac);
                    switch(fac){
                        case 1 :    case_take(board,fi,fj,fi-2,fj);   break;
                        case 2 :    case_take(board,fi,fj,fi+2,fj);   break;
                    }
                }
                else{
                    if (prise_faculta_above(board, board[fi][fj])){
                        printf("vous avez une capture facultative possible.\nTaper 1 pour l'effectuer ou n'importe pour passer");
                        scanf("%d", &fac);
                        if (fac==1){
                            if (board[fi-2][fj]->name== _Dame){
                                nbOdame--;
                            }
                            else{
                                if (board[fi-2][fj]->name== _Pion){
                                    nbOpion--;
                                }
                            }
                            case_take(board,fi,fj,fi-2,fj);
                        }
                    }
                    else{
                        if (prise_faculta_bellow(board, board[fi][fj])){
                            printf("vous avez une capture facultative possible.\nTaper 1 pour l'effectuer ou n'importe pour passer");
                            scanf("%d", &fac);
                            if (fac==1){
                                if (board[fi+2][fj]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    if (board[fi+2][fj]->name== _Pion){
                                        nbOpion--;
                                    }
                                }
                                case_take(board,fi,fj,fi+2,fj);
                            }
                        }
                    }
                }
            }
        }
        else{
            k=ij;
            // prise obligatoire sur rang horizantale
            if (prise_obliga_horizon(board, board[ii][ij])){
                //cas il y a piece left a capturer
                if (take_left(board, board[ii][ij])){
                    //cas il y a piece right et left a capturer
                    if (take_right(board, board[ii][ij])){
                        // si les coordonnes passées ne sont pas compatible avec la capture
                        if((search_piece_left(board, board[ii][ij])< fj && fj< search_piece_right(board, board[ii][ij])) || ii!= fi){
                            printf("Capture necessaire !\n");
                        }
                        else{
                            // cas on choisit de prenedre piece left
                            if(fj<search_piece_left(board, board[ii][ij])){
                                do{
                                    if (board[ii][k-2]->name== _Dame){
                                        nbOdame--;
                                    }
                                    else{
                                        if (board[ii][k-2]->name== _Pion){
                                            nbOpion--;
                                        }
                                    }
                                    case_take(board,ii,k,ii,k-2);
                                    k=k-2;
                                }
                                while(k>=0 && (k> fj || take_left(board, board[ii][k]) || k> search_piece_left(board, board[ii][k])));
                            }
                                // cas capture right
                            else{
                                do{
                                    if (board[ii][k+2]->name== _Dame){
                                        nbOdame--;
                                    }
                                    else{
                                        if (board[ii][k+2]->name== _Pion){
                                            nbOpion--;
                                        }
                                    }
                                    case_take(board,ii,k,ii,k+2);
                                    k=k+2;
                                }
                                while(k<15 && (k<fj || take_right(board, board[ii][k]) || k> search_piece_right(board, board[ii][k])));
                            }
                            if (k==fj){
                                t=1;
                            }
                        }
                    }
                    else{
                        // cas il y a saulement piece left a capturer
                            // si les coordonnes ne sont pas compatible avec la capture
                        if(search_piece_left(board, board[ii][ij]) < fj || ii!= fi){
                            printf("Capture necessaire !\n");
                        }
                        else{
                            if(fj<search_piece_left(board, board[ii][ij])){
                                do{
                                    if (board[ii][k-2]->name== _Dame){
                                        nbOdame--;
                                    }
                                    else{
                                        if (board[ii][k-2]->name== _Pion){
                                            nbOpion--;
                                        }
                                    }
                                    case_take(board,ii,k,ii,k-2);
                                    k=k-2;
                                }
                                while(k>=0 && (k>fj || take_left(board, board[ii][k]) || k> search_piece_left(board, board[ii][k])));
                            }
                            if (k==fj){
                                t=1;
                            }
                        }
                    }
                }
                else{
                    // cas il y a seulement piece right
                    if (take_right(board, board[ii][ij])){
                        // si les coordonnes ne sont pas compatible avec la capture
                        if(fj < search_piece_bellow(board, board[ii][ij]) || ii!= fi){
                            printf("Capture necessaire !\n");
                        }
                        else{
                            do{
                                if (board[ii][k+2]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    if (board[ii][k+2]->name== _Pion){
                                        nbOpion--;
                                    }
                                }
                                case_take(board,ii,k,ii,k+2);
                                k=k+2;
                            }
                            while(k<15 && (k< fj || take_right(board, board[ii][k]) || k> search_piece_right(board, board[ii][k])));
                            if (k==fj){
                                t=1;
                            }
                        }
                    }
                }
                if(t==1 ){
                    if(prise_faculta_left(board, board[fi][fj]) && prise_faculta_right(board, board[fi][fj])){
                        printf("vous avez deux captures facultatifs possibles.\n tapez 1 pour le sense< ou 2 pour -> ou n'importe pour passer: ");
                        scanf("%d", &fac);
                        switch(fac){
                            case 1 :
                                if (board[fi][fj-2]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    nbOpion--;
                                }
                                case_take(board,fi,fj,fi,fj-2);   break;
                            case 2 :
                                if (board[fi][fj+2]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    nbOpion--;
                                }
                                case_take(board,fi,fj,fi,fj+2);   break;
                        }
                    }
                    else{
                        if (prise_faculta_left(board, board[fi][fj])){
                            printf("vous avez une capture facultative possible.\nTaper 1 pour l'effectuer ou n'importe pour passer");
                            scanf("%d", &fac);
                            if (fac==1){
                                if (board[fi][fj-2]->name== _Dame){
                                    nbOdame--;
                                }
                                else{
                                    nbOpion--;
                                }
                                case_take(board,fi,fj,fi,fj-2);
                            }
                        }
                        else{
                            if (prise_faculta_right(board, board[fi][fj])){
                                printf("vous avez une capture facultative possible.\nTaper 1 pour l'effectuer ou n'importe pour passer");
                                scanf("%d", &fac);
                                if (fac==1){
                                    if (board[fi][fj+2]->name== _Dame){
                                        nbOdame--;
                                    }
                                    else{
                                        nbOpion--;
                                    }
                                    case_take(board,fi,fj,fi+2,fj);
                                }
                            }
                        }
                    }
                }
            }
            // aucune capture necessaire
            else{
                    // cas le mouvement est sur la meme ligne
                if (ii== fi){
                    // il n y a pas de mouvement si la case desired est la meme de depart
                    if(ij != fj && (search_piece_left(board, board[ii][ij])==-1 || fj>search_piece_left(board, board[ii][ij])) && ( search_piece_right(board, board[ii][ij])==-1 ||fj< search_piece_right(board, board[ii][ij]))){
                        t=1;
                    }
                    else{
                        if((prise_faculta_left(board, board[ii][ij])==1 || prise_faculta_right(board, board[ii][ij])==1) && abs(ii-fi)==2){
                            t=1;
                        }
                    }
                }
                else{
                        // SI LE MOUVEMENT EST SUR LA MEME COLLONE
                    if(ij== fj){
                        if ((search_piece_above(board, board[ii][ij])==-1 || fi>search_piece_above(board, board[ii][ij])) && ( search_piece_bellow(board, board[ii][ij])==-1 ||fi< search_piece_bellow(board, board[ii][ij]))){
                            t= 1;
                        }
                        else{
                            if((prise_faculta_above(board, board[ii][ij])==1 || prise_faculta_bellow(board, board[ii][ij])==1) && abs(ij-fj)==2){
                                t=1;
                            }
                        }
                    }
                    else{
                            // les mouvements diagonaux
                        if (abs(ii-fi)==1 && abs(ij- fj)==1 && board[fi][fj]->name== _Vide){
                            t=1;
                        }
                    }
                }
                if (t==1){
                    case_take(board,ii,ij,fi,fj);
                }
            }
        }
    }
    // si le deplacement est valide
    if (t==1){
        opponent->nb_dame= nbOdame; opponent->nb_pion= nbOpion;
        courant->dames[board[fi][fj]->num-1] = board[fi][fj];
        copy_board(board, boa);
    }
    else{
        printf("mvt invalide \t");
    }
    return t;
}
*/
