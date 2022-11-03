#include "pieces.h"

int minim(int x, int y){
    if (x>y)    x=y;
    return x;
}

int maxim(int x, int y){
    if (x<y)    x=y;
    return x;
}

piece* creerKing(player* courant, int x, int y){
    piece* king=Malloc(piece);
    king->name = _King;
    king->couleur = courant->couleur;
    king->index[0]= x;  king->index[1]= y;
    king->num = 0;
    king->teritoire= courant->couleur;
    courant->king= king;

    return king;
}

// marquer le territoire du roi
void territ_clash(piece* board[15][15], piece* king, int x, int y){
    if (board[x][y]->teritoire!= king->couleur && board[x][y]->teritoire!= _Vide){
        board[x][y]->teritoire= clash;
    }
    else{
        board[x][y]->teritoire= king->couleur;
    }
}
void case_king(piece* board[15][15], char color, const int x , const int y){
    int i;
    board[x][y]->name = _King;
    board[x][y]->couleur= color;
    board[x][y]->index[0]= x;  board[x][y]->index[1]= y;
    board[x][y]->num = 1;
    for (i=minim(x+2, 13); i>=maxim(0, x-2); i= i-2){
        territ_clash(board, board[x][y], i, y);
        territ_clash(board, board[x][y],i,minim(y+2,13));
        territ_clash(board, board[x][y],i, maxim(y-2,1));
    }
}

int canKingMove(piece* board[15][15], player* courant, piece* king, player* opponent){
    int t=0, x= king->index[0], y= king->index[1];
    if ((board[minim(x+1,14)][y]->name== _Vide && board[minim(13,x+2)][y]->name== _Vide && board[minim(13,x+2)][y]->teritoire!= clash) ||
            (board[maxim(0,x-1)][y]->name== _Vide && board[maxim(1,x-2)][y]->name== _Vide && board[maxim(1,x-2)][y]->teritoire!= clash) ||
            (board[x][minim(14,y+1)]->name== _Vide && board[x][minim(13,2+y)]->name== _Vide && board[x][minim(13,2+y)]->teritoire!= clash) ||
            (board[x][maxim(0,y-1)]->name== _Vide && board[x][maxim(1,y-2)]->name== _Vide && board[x][maxim(1,y-2)]->teritoire!= clash)){
        t=1;
    }
    return t;
}

int move_king (piece* board[15][15], player* courant, const int x, const int y, player* opponent){
    int t= 0;
    if ((abs(courant->king->index[0] -x)== 2 && abs(courant->king->index[1]- y)== 0) ||(abs(courant->king->index[0]-x)== 0 && abs(courant->king->index[1]- y)== 2)){
        if (valide_case(x, y) && board[x][y]->teritoire!= clash &&
                board[(courant->king->index[0]+ x)/2][(courant->king->index[1]+y)/2]->name == _Vide && board[x][y]->name== _Vide){
            case_king(board, _Vide, courant->king->index[0], courant->king->index[1]);
            board[courant->king->index[0]][courant->king->index[1]]->couleur= courant->couleur;
            case_take(board, courant->king->index[0], courant->king->index[1], x, y);
            case_king(board, courant->couleur, x, y);
            courant->king->index[0]= x; courant->king->index[1]= y;
            t= 1;
        }
    }
    return t;
}

int mat(piece* board[15][15], player* cj){
    int i, t=0;
    for (i=-1; i<2; i=i+2){
        if (board[cj->king->index[0] + i][cj->king->index[1]]->couleur != cj->couleur){
            if (board[cj->king->index[0] + i][cj->king->index[1]]->couleur==_Vide){
                t= t-5;
            }
            t=t+2;
        }
        else{
            t=t+1;
        }
         if (board[cj->king->index[0]][cj->king->index[1] + i]->couleur != cj->couleur){
            if (board[cj->king->index[0]][cj->king->index[1] + i]->couleur==_Vide){
                t=t-5;
            }
            t=t+2;
        }
        else{
            t=t+1;
        }
    }
    if (t>4){       // cas de mat
        return 1;
    }
    else{           // king n'est pas en mat
        return 0;
    }
}

int pat(piece* board[15][15], player* courant, player* opponent){
    int i, x, y, t=0;
    if (courant->nb_dame+ courant->nb_pion<4 && opponent->nb_dame+ opponent->nb_pion<4){
        t=1;
    }
    else{
        if (courant->nb_dame> 0){t=0;}
        else{
            for (i=0; i<15; i++){
                x= courant->pions[i]->index[0]; y= courant->pions[i]->index[1];
                if (board[x][y]->couleur== courant->couleur&& board[x][y]->name== _Pion&& board[x][y]->num==i+1 &&canPionMove(board, courant, board[x][y], opponent)){
                    t=1;
                    break;
                }
            }
        }
    }
    printf("%d %d\n",courant->nb_dame+ courant->nb_pion, opponent->nb_dame+ opponent->nb_pion);
    return t;
}
