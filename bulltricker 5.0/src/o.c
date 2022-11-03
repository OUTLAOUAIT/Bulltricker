#include "pieces.h"

// creation d'une dame
piece* creerDame(player* courant, int x, int y){
    piece* dame= Malloc(piece);
    // piece noire
    if (courant->couleur== _Noir){
        static int compB = 1;
        if (courant->nb_dame== 0)
            compB= 1;
        dame->num = compB++ ;
    }
    // piece blache
    else{
        static int compW = 1;
        if(courant->nb_dame== 0)
            compW= 1;
        dame->num = compW++ ;
    }
    dame->couleur = courant->couleur;
    dame->index[0]=x;   dame->index[1]= y;
    dame->name = _Dame;

    courant->dames[dame->num-1]= dame;
    courant->nb_dame++;
    dame->teritoire= _Vide;
    return dame;
}

int search_piece_above(piece* board[15][15], piece* piece){
    int i;
    char color;
    for (i= piece->index[0]-1; i>=0; i--){
        color= board[i][piece->index[1]]->couleur;
        // si la case n'est pas vide sortir
        if (color != _Vide){
            break;
        }
    }
    return i;
}

int take_above(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_above(board, dame);
    if (valide_case(i,dame->index[1]) && board[i][dame->index[1]]->couleur!= dame->couleur && board[i][dame->index[1]]->name!=_King){
        if(i>1 && board[i-1][dame->index[1]]->name== _Vide){
            if (board[i-2][dame->index[1]]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int capture_above(piece* boa[15][15], player* courant, int ii, int ij , int fi, int fj, player* opponent){
    int k= ii, t=0;
    piece* board[15][15];
    int nb_d= opponent->nb_dame, nb_p= opponent->nb_pion;
    creerboard(board);
    copy_board(boa, board);
    while (take_above(board,board[k][ij])==1){
        if (board[k-2][ij]->name== _Dame) nb_d--;
        else if (board[k-2][ij]->name== _Pion) nb_p--;
        case_take(board, k, ij, k-2, ij);
        k=k-2;
    }
    if (k>=fi && search_piece_above(board, board[k][ij])<fi){
        t=1;
        opponent->nb_dame= nb_d;    opponent->nb_pion= nb_p;
        case_take(board, k, ij, fi, fj);
        copy_board(board, boa);
    }
    return t;
}


int search_piece_bellow(piece* board[15][15], piece* piece){
    int i;
    char color;
    for (i= piece->index[0]+1; i<15; i++){
        color= board[i][piece->index[1]]->couleur;
        // si la case n'est pas vide sortir
        if (color != _Vide){
            break;
        }
    }
    return i;
}

int take_bellow(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_bellow(board, dame);
    if (valide_case(i, dame->index[1]) && board[i][dame->index[1]]->couleur!= dame->couleur && board[i][dame->index[1]]->name!= _King){
        if(i<13 && board[i+1][dame->index[1]]->name== _Vide){
            if (board[i+2][dame->index[1]]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int capture_bellow(piece* boa[15][15], player* courant, int ii, int ij , int fi, int fj, player* opponent){
    int k= ii, t=0;
    piece* board[15][15];
    int nb_d= opponent->nb_dame, nb_p= opponent->nb_pion;
    creerboard(board);
    copy_board(boa, board);
    while (take_bellow(board,board[k][ij])==1){
        if (board[k+2][ij]->name== _Dame) nb_d--;
        else if(board[k+2][ij]->name== _Pion) nb_p--;
        case_take(board, k, ij, k+2, ij);
        k=k+2;
    }
    if (k<=fi && search_piece_bellow(board, board[k][ij]) >fi){
        t=1;
        opponent->nb_dame= nb_d;    opponent->nb_pion= nb_p;
        case_take(board, k, ij, fi, fj);
        copy_board(board, boa);
    }
    return t;
}

int search_piece_right(piece* board[15][15], piece* piece){
    int i;
    char color ;
    for (i= piece->index[1]+1; i<15; i++){
        color = board[piece->index[0]][i]->couleur;
        //si la case n'est pas vide sortir
        if (color != _Vide){
            break;
        }
    }
    return i;
}

int take_right(piece* board[15][15], piece* dame){
    int i, t=0;
    i= search_piece_right(board, dame);
    if (valide_case(dame->index[0], i) && board[dame->index[0]][i]->couleur!= dame->couleur && board[dame->index[0]][i]->name!= _King){
        if(i<13 && board[dame->index[0]][i+1]->name== _Vide){
            if (board[dame->index[0]][i+2]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int capture_right(piece* boa[15][15], player* courant, int ii, int ij , int fi, int fj, player* opponent){
    int k= ij, t=0;
    piece* board[15][15];
    int nb_d= opponent->nb_dame, nb_p= opponent->nb_pion;
    creerboard(board);
    copy_board(boa, board);
    while (take_right(board,board[ii][k])==1){
        if (board[ii][k+2]->name== _Dame) nb_d--;
        else if(board[ii][k+2]->name== _Pion) nb_p--;
        case_take(board, ii, k, ii, k+2);
        k=k+2;
    }
    if (k<=fj && search_piece_right(board, board[ii][k]) >fj){
        t=1;
        opponent->nb_dame= nb_d;    opponent->nb_pion= nb_p;
        case_take(board, ii, k, fi, fj);
        copy_board(board, boa);
    }
    return t;
}

int search_piece_left(piece* board[15][15], piece* piece){
    int i;
    char color ;
    for (i= piece->index[1]-1; i>=0; i--){
        color= board[piece->index[0]][i]->couleur ;
        //si la case n'est pas vide soritr
        if (color != _Vide){
            break;
        }
    }
    return i;
}

int take_left(piece* board[15][15], piece* dame){
   int i, t=0;
    i= search_piece_left(board, dame);
    if (valide_case(dame->index[0], i) && board[dame->index[0]][i]->couleur!= dame->couleur && board[dame->index[0]][i]->name!= _King){
        if(i>1 && board[dame->index[0]][i-1]->name== _Vide){
            if (board[dame->index[0]][i-2]->name== _Vide){
                t=1;
            }
        }
    }
    return t;
}

int capture_left(piece* boa[15][15], player* courant, int ii, int ij , int fi, int fj, player* opponent){
    int k= ij, t=0;
    int nb_d= opponent->nb_dame, nb_p= opponent->nb_pion;
    piece* board[15][15];
    creerboard(board);
    copy_board(boa, board);
    while (take_left(board,board[ii][k])==1){
        if (board[ii][k-2]->name== _Dame) nb_d--;
        else if(board[ii][k-2]->name== _Pion) nb_p--;
        case_take(board, ii, k, ii, k-2);
        k=k-2;
    }
    if (k>=fj && search_piece_left(board, board[ii][k]) <fj){
        t=1;
        opponent->nb_dame= nb_d;    opponent->nb_pion= nb_p;
        case_take(board, ii, k, fi, fj);
        copy_board(board, boa);
    }
    return t;
}

int move_dame(piece* board[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent){
    int t= 0;
    piece* boa[15][15];
    creerboard(boa);
    copy_board(board, boa);

    if (valide_case(fi, fj)== 0 || boa[fi][fj]->couleur== courant->couleur || courant->couleur!= board[ii][ij]->couleur || case_royal(fi,fj)==1){
        printf("mouvement invalide! \n");
    }
    else{
        // cas dame sur range vertical
        if(ij%2== 1){
            //  capture above or bellow
            if (take_above(boa, boa[ii][ij]) || take_bellow(boa, boa[ii][ij])){
                // mouvement en haut
                if (ij== fj && fi<ii){
                    t= capture_above(boa, courant, ii, ij, fi, fj, opponent);
                }
                //capture bellow
                else {
                    if(ij== fj && fi> ii){
                        t= capture_bellow(boa, courant, ii, ij, fi, fj, opponent);
                    }
                    else{ printf("capture necessaire \n");
                    }
                }
            }
            else{
                // pas de capture necessaire
                //mvt dur meme ligne
                if (ii== fi && ij!= fj){
                    if (fj>=search_piece_left(boa, boa[ii][ij]) && fj <=search_piece_right(boa, boa[ii][ij])){
                        if (board[fi][fj]->couleur == opponent->couleur && abs(ij- fj)!= 2){
                            t=0;
                        }
                        else{
                            if (board[fi][fj]->name== _Dame) opponent->nb_dame--;
                            else if(board[fi][fj]->name== _Pion) opponent->nb_pion--;
                            case_take(boa, ii, ij, fi, fj);
                            t=1;
                        }
                    }
                }
                else{
                    // mvt sur meme collone
                    if (ij== fj && ii!= fi){
                        if (fi<search_piece_bellow(boa, boa[ii][ij]) && fi> search_piece_above(boa, boa[ii][ij])){
                            case_take(boa, ii, ij, fi, fj);
                            t=1;
                        }
                    }
                    // mvt speciaux
                    else{
                        if (abs(ii-fi)==1 && abs(ij- fj)==1 && board[fi][fj]->name== _Vide){
                            case_take(boa, ii, ij, fi, fj);
                            t=1;
                        }
                    }
                }
            }
        }
        else{
            // dame sur range horizontale
            if(ij%2== 0){
                //  capture left or right
                if (take_left(boa, boa[ii][ij]) || take_right(boa, boa[ii][ij])){
                    // mouvement a gauche
                    if (ii== fi && fj<ij){
                        t= capture_left(boa, courant, ii, ij, fi, fj, opponent);
                    }
                    //capture droite
                    else {
                        if(ii== fi && fj> ij){
                            t= capture_right(boa, courant, ii, ij, fi, fj, opponent);
                        }
                        else{ printf("capture necessaire \n");
                        }
                    }
                }

                else{
                    // pas de capture necessaire
                    //mvt dur meme ligne
                    if (ii== fi && ij!= fj){
                        if (fj>search_piece_left(boa, boa[ii][ij]) && fj <search_piece_right(boa, boa[ii][ij])){
                                case_take(boa, ii, ij, fi, fj);
                            t=1;
                        }
                    }
                    else{
                        // mvt sur meme collone
                        if (ij== fj && ii!= fi){
                            if (fi<=search_piece_bellow(boa, boa[ii][ij]) && fi>= search_piece_above(boa, boa[ii][ij])){
                                if (board[fi][fj]->couleur == opponent->couleur && abs (ii- fi)!= 2){
                                    t=0;
                                }
                                else{
                                    if (board[fi][fj]->name== _Dame) opponent->nb_dame--;
                                    else if(board[fi][fj]->name== _Pion) opponent->nb_pion--;
                                    case_take(boa, ii, ij, fi, fj);
                                    t=1;
                                }
                            }
                        }
                        // mvt speciaux
                        else{
                            if (abs(ii-fi)==1 && abs(ij- fj)==1 && board[fi][fj]->name== _Vide){
                                case_take(boa, ii, ij, fi, fj);
                                t=1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (t==1){
        copy_board(boa, board);
        courant->dames[board[fi][fj]->num-1] = board[fi][fj];
    }
    return t;
}
