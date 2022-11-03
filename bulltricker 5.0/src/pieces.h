#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#define NCase 15
#define _King 'K'
#define  _Dame 'D'
#define _Pion 'P'
#define _Vide ' '
#define _CarreBute '#'
#define _Noir 'b'
#define _Blanc 'w'
#define clash 'x'
#define _Droit 1
#define _Gauche 2
#define _Avant 3
#define Malloc(type) (type *)malloc(sizeof(type))
#define match "enregistrement.o"
#define dernier "dernier.o"
#define WINDOW_WIDTH 653
#define WINDOW_HEIGHT 700
#define menuP "images/menuPrincipal.bmp"
#define gameMenu "images/gameMenu.bmp"
#define plateauN "images/boardN.bmp"
#define plateauB "images/boardB.bmp"
#define noirG "images/noirGagne.bmp"
#define blancG "images/blancGagne.bmp"
#define egalite "images/matchNull.bmp"
#define vPionN "images/vPionN.bmp"
#define vPionB "images/vPionB.bmp"
#define hPionN "images/hPionN.bmp"
#define hPionB "images/hPionB.bmp"
#define vDameN "images/vDameN.bmp"
#define vDameB "images/vDameB.bmp"
#define hDameN "images/hDameN.bmp"
#define hDameB "images/hDameB.bmp"
#define kingB  "images/kingB.bmp"
#define kingN  "images/kingN.bmp"
#define selectP "images/selectPiece.bmp"
#define captureP "images/capturePion.bmp"
#define captureD "images/captureDame.bmp"
#define credit "images/credit.bmp"
#define rules "images/rules.bmp"
#define saveP "savePlayer.o"
#define saveB "saveBoard.o"

typedef struct piece{
    char name;
    char couleur;
    int index [2];
    int num;
    char teritoire;
}piece;


typedef struct joueur_pieces{
    char couleur;
    piece *king;
    int nb_dame, nb_pion;   // nombre de pion et de dame que le joueur possede
    piece* pions[15];
    piece* dames[23];
}player;

    // fonctions king
piece* creerKing(player* , int , int );
int mat(piece*(*)[15], player*);
int pat(piece*(*)[15], player*, player*);
int move_king(piece*(*)[15], player*, const int , const int, player*);
void case_king(piece*(*)[15], char, const int , const int );

    // fonctions dame
piece* creerDame (player*, int , int );
int take_above(piece*(*)[15], piece*);              //see if there is a compulsary taking of a piece above
int take_bellow(piece*(*)[15], piece*);             //see if there is a compulsary taking of a piece bellow
int take_left(piece*(*)[15], piece*);
int take_right(piece*(*)[15], piece*);
int move_dame(piece*(*)[15], player*, int, int, int, int, player*);
char capture_obligatoire(piece*(*)[15], player*, player*);

    //fonctions pion
piece* creerPion(player* , int , int );
//void damer(piece*(*)[15], player*, int, int);   // khdit ta7ti o creeit hadi hhhh ta tel 3liha m3a l commentaire
int move_pion(piece*(*)[15], player*, int, int, int, int, player*);
int capture_necessaire_blanc(piece*(*)[15], player*, int, int, player*);
int capture_necessaire_noir(piece*(*)[15], player*, int, int, player*);
int canPionMove(piece*(*)[15],player*, piece*, player*);
void damer(piece*(*)[15], player*, int, int);

    //fonctions board
void creerboard(piece*(*)[15]);  // re-initialiser le plateau
void initialiser_player(player*, char);
void copy_board(piece*(*)[15], piece*(*)[15]);
int valide_case(int, int);
int move_piece(piece*(*)[15], player*, int, int, int, int, player*, SDL_Renderer*, SDL_Window*);
void case_take(piece*(*)[15], int, int, int, int);
int case_royal(int, int);
void sauvegarder(int, int, int, int);
void create_player(player*);
void free_board(piece*(*)[15]);
void free_player(player*);

//graphique
void create_window_render(SDL_Window** , SDL_Renderer** );
void selectioner(SDL_Event, int*, int*, SDL_Renderer*, SDL_Window*);
void showBoard(piece*(*)[15], SDL_Renderer*, SDL_Window*, char);
void replay (SDL_Renderer*, SDL_Window*);
void game_menu(piece*(*)[15], SDL_Event, SDL_Renderer*, SDL_Window*,player*, player*, int*, int*, int*);
int menu_principal(SDL_Event, SDL_Renderer*, SDL_Window*);
void fin_parti(piece*(*)[15],SDL_Event, SDL_Renderer*, SDL_Window*, player*, player*, int*, int*, int*);
void selectPiece(SDL_Renderer* renderer, SDL_Window* window);
void captureNecessaire(SDL_Renderer*, SDL_Window*, char);
void show_credit(SDL_Event, SDL_Renderer*, SDL_Window*);
void show_rules(SDL_Event, SDL_Renderer*, SDL_Window*);
void save_partie(piece*(*)[15], player*, player*);
void charger_partie(piece*(*)[15], player*, player*);
void quitter(piece*(*)[15], player*, player*, SDL_Renderer*, SDL_Window*);
void copy_doc(FILE*, FILE*);
