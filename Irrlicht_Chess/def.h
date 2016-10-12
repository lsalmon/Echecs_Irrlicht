/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

/*
 * Fichier de définition de types et structures communes aux classes
 * File containing the definitions of types and structures common to classes
 */
// Délai : 30 secondes
// Delay : 30 secondes
#define DELAI_TOUR 30

// Décalage des pièces sur le plateau (cas du plateau ne commencant pas en (0,0) sur la fenêtre principale)
// BORDER_OFFSET correspond au liseré de l'échiquier
// Offset of the pieces on the chessboard (case of the chessboard not starting at (0,0) on the main window)
// BORDER_OFFSET is the border of the chessboard
#define X_OFFSET 250
#define Y_OFFSET 30
#define BORDER_OFFSET 27

// Taille du plateau
// Size of the chessboard
#define BOARD_SIZE_X 540
#define BOARD_SIZE_Y 540

// Taille des cases sur l'échiquier (utilisé pour passer des coordonnées pointées sur le plateau aux coordonnées internes)
// Cases de 60x60
// Size of the squares on the chessboard (used to get from the user coordinates to the internal coordinates)
// 60x60 squares
#define SQUARE_SIZE 60

// Macros pour la détection de la mise en échec ou échec et mat du roi
// Macros for the check / checkmate state detection
#define ERR_CHECK -1
#define NO_CHECK 0
#define CHECK 1
#define CHECKMATE 2

// Macros pour le choix de fonctions a appeler après avoir choisi un fichier (context manager)
// Macros for the function to call after choosing a file (context manager)
#define GAME_LOAD 1
#define GAME_SAVE 2

/*
 * Classe position pièce
 */
class Coord{
    public:
    unsigned int x, y;

    Coord() : x(0),y(0){}
};


/*
 * Fonction de vérification de deux coordonnées (vérification du non dépassement des bornes de l'échiquier)
 * Function used to check two coordinates (when checking for non going beyond the chessboard borders)
 */
static bool verifierSet(Coord & dep, Coord & arr){
    if(((dep.x > 7 || dep.x < 0) || (dep.x > 7 || dep.x < 0)) || ((dep.y > 7 || dep.y < 0) || (dep.y > 7 || dep.y < 0))
    || ((arr.x > 7 || arr.x < 0) || (arr.x > 7 || arr.x < 0)) || ((arr.y > 7 || arr.y < 0) || (arr.y > 7 || arr.y < 0)))
        return false;
    else
        return true;
}

/*
 * Fonction de vérification d'une seule coordonnée (vérification du non dépassement des bornes de l'échiquier)
 * Function used to check one coordinates (when checking for non going beyond the chessboard borders)
 */
static bool verifier(Coord & c){
    if(((c.x > 7 || c.x < 0) || (c.x > 7 || c.x < 0)) || ((c.y > 7 || c.y < 0) || (c.y > 7 || c.y < 0)))
        return false;
    else
        return true;
}


#endif // DEF_H_INCLUDED
