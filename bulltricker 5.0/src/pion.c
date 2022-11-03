#include "pieces.h"

piece* creerPion(player* courant, int x, int y){
    piece* pion= Malloc(piece);

    if (courant->couleur== _Noir){
        static int compB = 1;
        pion->num = compB++ ;
    }
    else{
        static int compW = 1;
        pion->num = compW++ ;
    }
    pion->couleur = courant->couleur;
    pion->index[0]=x;   pion->index[1]= y;
    pion->name = _Pion;
    courant->pions[pion->num-1]= pion;
    courant->nb_pion++;
    pion->teritoire= _Vide;
    return pion;
}

// hadi fonction zidha mni tkon khedam f move_pion kolama t7erek dirha bach fi 7alat wselti lekher dyal lboard tdami
void damer(piece* board[15][15], player* courant, int i, int j){
    if (board[i][j]->name== _Pion){
        if (courant->couleur== _Blanc){
            if (i==0){
                board[i][j]= creerDame(courant, i, j);
                courant->dames[board[i][j]->num-1]= board[i][j];
            }
        }
        else{
            if (i== 14){
                board[i][j]= creerDame(courant, i, j);
                courant->dames[board[i][j]->num-1]= board[i][j];
            }
        }
    }
}

int capture_necessaire_blanc(piece* board[15][15], player* courant, int x, int y, player* opponent){
    int t= 0;
    if (x%2==0 && y%2== 1 && x>=4 && board[x-1][y]->couleur== _Vide && board[x-2][y]->couleur== opponent->couleur &&
        board[x-3][y]->couleur== _Vide && board[x-4][y]->couleur== _Vide) t=1;
    return t;
}

int move_pion_blanc(piece* boa[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent){
    piece* board[15][15];
    creerboard(board);
    copy_board(boa, board);
    int t=0;
    int nbOdame= opponent->nb_dame, nbOpion= opponent->nb_pion; //pour mettre a jour le nombre de pieces restantes a opponent
       // cas si les case ne sont pas valide ou la destination est pleine
    if (valide_case(ii, ij)==0 || valide_case(fi, fj)==0 || courant->couleur!= board[ii][ij]->couleur || case_royal(fi,fj)==1  || (ii==fi && ij == fj) ){
        printf("mvt non valide! \n");
    }

    else{
        int i= ii;
        // pion sur range avec capture necessaire
        if (ij%2==1 && ii%2 == 0){
            if(capture_necessaire_blanc(board, courant, ii, ij, opponent)){
                while (capture_necessaire_blanc(board, courant, i, ij, opponent)){
                    if (board[i-2][ij]->name== _Dame) nbOdame--;
                    else    nbOpion--;
                    case_take(board, i, ij, i-2, ij);   i= i-2;
                    case_take(board, i, ij, i-2, ij);   i= i-2;
                }
                if (i== fi && ij == fj) t=1 ;
            }
            else{
                if (ii== 12 && ij== fj && ii-fi<=4 ){
                    while (i-2>=fi && board[i-1][ij]->couleur== _Vide && board[i-2][ij]->couleur== _Vide){
                        case_take(board, i, ij, i-2, ij);
                        i=i-2;
                    }
                     if (i== fi && ij == fj) t=1;
                }
                else {
                    if (ii> fi && (( fi==ii-1 && fj==ij+1 )||(fi==ii-2 && fj==ij && board[ii-1][ij]->name!= _King)||(fi==ii-1 && fj==ij-1))  && board[fi][fj]->name== _Vide){
                        case_take(board, ii, ij, fi, fj);

                        t=1;
                    }

                }
            }

        }

       else if ((fi==ii-1 && fj==ij+1)||(fi==ii-1 && fj==ij-1))
   {

         if(board[ii][ij]->name== _Pion && board[ii][ij]->couleur == _Blanc && ( board[fi][fj]->couleur == _Noir || board[fi][fj]->couleur==_Blanc ))
         {
	      t=0;
         }
        else if(board[ii][ij]->name== _Pion && board[ii][ij]->couleur == _Blanc && board[fi][fj]->couleur == _Vide )
        {
        case_take(board, ii, ij, fi, fj);
        t=1;
        }

   }
      else{
            if (ii> fi && (( fi==ii-1 && fj==ij+1 )||(fi==ii-2 && fj==ij)||(fi==ii-1 && fj==ij-1))){
                if (board[fi][fj]->name== _Dame)    nbOdame--;
                if (board[fi][fj]->name== _Pion)    nbOpion--;
                case_take(board, ii, ij, fi, fj);
                t=1;

            }
        }
    }
    if (t== 1){
        opponent->nb_dame= nbOdame;     opponent->nb_pion= nbOpion;
        damer(board, courant, fi, fj);
        copy_board(board, boa);

        courant->pions[board[fi][fj]->num-1] = board[fi][fj];
    }

    return t;
}

int capture_necessaire_noir(piece* board[15][15], player* courant, int x, int y, player* opponent){
    int t= 0;
    if (x%2==0 && y%2== 1 && x<=10 && board[x+1][y]->couleur== _Vide && board[x+2][y]->couleur== opponent->couleur &&
        board[x+3][y]->couleur== _Vide && board[x+4][y]->couleur== _Vide) t=1;
    return t;
}

int move_pion_noir(piece* boa[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent){
    piece* board[15][15];
    creerboard(board);
    copy_board(boa, board);
    int t=0;
    int nbOdame= opponent->nb_dame, nbOpion= opponent->nb_pion; //pour mettre a jour le nombre de pieces restantes a opponent

       // cas si les case ne sont pas valide ou la destination est pleine
    if (valide_case(fi, fj)==0 || courant->couleur!= board[ii][ij]->couleur || board[fi][fj]->name== _CarreBute || case_royal(fi,fj)==1 || (ii==fi && ij == fj)) {
        printf("mvt non valide! \n");
    }


    else{
        // cas on est sur range
        int i= ii;
        // pion sur range avec capture necessaire
        if (ij%2==1 && ii%2 == 0)
            {
            if(capture_necessaire_noir(board, courant, ii, ij, opponent))
                {
                while (capture_necessaire_noir(board, courant, i, ij, opponent)){
                    if (board[i+2][ij]->name== _Dame) nbOdame--;
                    else    nbOpion--;
                    case_take(board, i, ij, i+2, ij);   i= i+2;
                    case_take(board, i, ij, i+2, ij);   i= i+2;
                }
                if (i== fi && ij == fj ) t=1;
               }
            else{
                if (ii== 2 && ij== fj && fi-ii<=4 ){
                    while (i+2<=fi && board[i+1][ij]->couleur== _Vide && board[i+2][ij]->couleur== _Vide){
                        case_take(board, i, ij, i+2, ij);
                        i=i+2;
                    }
                     if (i== fi && ij == fj) t=1;
                }
                else {
                    if (ii< fi && (( fi==ii+1 && fj==ij+1 )||(fi==ii+2 && fj==ij && board[ii+1][ij]->name!=_King)||(fi==ii+1 && fj==ij-1))  && board[fi][fj]->name== _Vide){
                        case_take(board, ii, ij, fi, fj);
                        t=1;
                    }
                }
            }
        }
           else if ((fi==ii+1 && fj==ij+1)||(fi== ii+1&& fj==ij-1))
{

         if((board[ii][ij]->name== _Pion && board[ii][ij]->couleur == _Noir && ( board[fi][fj]->couleur == _Blanc ||  board[fi][fj]->couleur == _Noir )))
    {
	      t=0;
    }
    else if(board[ii][ij]->name== _Pion && board[ii][ij]->couleur == _Noir && board[fi][fj]->couleur == _Vide  )
        {
        case_take(board, ii, ij, fi, fj);
        t=1;
        }

     }


        else
        {
            if (ii< fi && (( fi==ii+1 && fj==ij+1 )||(fi==ii+2 && fj==ij)||(fi==ii+1 && fj==ij-1))){
                if (board[fi][fj]->name== _Dame)    nbOdame--;
                if (board[fi][fj]->name== _Pion)    nbOpion--;
                case_take(board, ii, ij, fi, fj);
                t=1;
            }
        }
    }
    if (t== 1){
        opponent->nb_dame= nbOdame;     opponent->nb_pion= nbOpion ;
        damer(board, courant, fi, fj);
        copy_board(board, boa);

        courant->pions[board[fi][fj]->num-1] = board[fi][fj];

    }

    return t;
}

int move_pion(piece* board[15][15], player* courant, int ii, int ij, int fi, int fj, player* opponent){
    int t=0;
    if (courant->couleur== _Blanc){
        t= move_pion_blanc(board, courant, ii, ij, fi, fj, opponent);
    }
    else if(courant->couleur== _Noir){
        t= move_pion_noir(board, courant, ii, ij, fi, fj, opponent);
    }
    return t;
}
