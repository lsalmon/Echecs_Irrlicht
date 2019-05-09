/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#ifndef ECHIQUIER_H_INCLUDED
#define ECHIQUIER_H_INCLUDED

#include "Piece.h"
#include "def.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <vector>
#include <cmath>
#include <irrlicht.h>


class Echiquier
{
    public:
        // Constructeur vide, toutes les initialisations se font dans les fonctions d'init
        // Empty builder, all the initializations are done in the init functions
        Echiquier();

        // Initialiser les pièces sur l'échiquier
        // Initialize pieces on the chessboard
        void init(irr::video::IVideoDriver* driver);

        // Affiche le contenu des réserves
        // Display the stocks
        void afficheRes(irr::video::IVideoDriver* driver);
        // Affiche le plateau
        // Display the board
        void afficher(irr::video::IVideoDriver* driver);
        // Affiche l'échiquier complet
        // Display the full chessboard
        void afficheEch(irr::video::IVideoDriver* driver);

        // Modifie la couleur des pièces selon si elles sont sélectionnées ou non
        // Fonctions appelées depuis le contextmanager
        // Change color of the pieces depending on whether they are selected or not
        // Functions called from the contextmanager
        void setSelectedPiece(Coord & pos);
        void setStandardPiece(Coord & pos);
        // Renvoie la pièce a une position de l'échiquier
        // Get the current piece from a position on the chessboard
        std::string getPosEch(Coord & p);
        // Supprime une pièce en fonction de ses coordonnées et la range dans la réserve du joueur a qui elle appartient
        // Delete piece from its coordinates and put it in the enemy's stock
        void supprPiece(Coord & p);
        // Annule le dernier mouvement fait du joueur
        // Cancel the players last move
        bool revPiece(unsigned int adv, Coord & posPrec, Coord & posAct);
        // Effectue la promotion d'un pion
        // Promote a pawn
        void upgradePion(char type, irr::video::IVideoDriver* driver);

        // Renvoie la texture de l'échiquier
        // Get chessboard texture
        irr::video::ITexture * getTexture();

        // Vérification de la validité du déplacement courant
        // Check if the current move is valid
        bool checkDepl(Coord & dep, Coord & arr);
        // Fonction qui détecte si un pion se trouve sur la dernière ligne de l'échiquier a partir de ses coordonnées d'arrivée (cas promotion)
        // Check if a pawn is on the last line of the chessboard from its arrival coordinates
        bool checkPromotion(Coord & posArr);
        // Fonction qui détecte si le roque est possible
        // Prend les coordonnées de déplacement du roi et une reference, qu'on fait pointer sur la position en x de la tour
        // Check if a castling is possible
        // The function takes the move coordinates from the king and a reference pointing on the x position of the rook
        bool checkRoque(Coord & dep, Coord & arr, unsigned int &xTour);
        // Fonction qui détecte la mise en échec du roi suite a un déplacement du roi (prend les coordonnées d'arrivée du roi)
        // Detects the check state of the king after it is moved (takes the arrival coordinates of the king)
        bool checkEchec(Coord & pos);
        // Fonction qui détecte la mise en échec du roi du joueur a la suite d'un déplacement d'une autre pièce que le roi (déplacement effectué par le joueur)
        // Prend le numéro du joueur qui a déplacé la pièce
        // (Cas des pièces clouées)
        // Detects the check state of the king after moving another piece (move made by the current player)
        // Takes the number of the player who moved the piece
        bool checkEchecMvt(unsigned int adv);
        // Fonction d'appel a checkEchecAdv
        // Function who calls checkEchecAdv
        void verifierEchec(unsigned int adv);
        // Regarde si la sortie de la position d'échec est possible (prend le numéro du joueur en échec)
        // Check if we can cancel the check state (takes the number of a player in a check state)
        int checkSortieEchec(Coord & dep, Coord & arr, unsigned int joueur);
        // Fonction qui détecte la mise en échec du roi de l'adversaire (dont le numéro est passé en paramètre) suite a un déplacement du joueur courant
        // Detects the check state of the opponent's king (takes te opponent's number) after a move made by the current player
        int checkEchecAdv(unsigned int adv);

        // Fonction qui filtre les déplacements courants si le roi est en situation d'échec (prend le numéro du joueur en echec)
        // Function that limits the possible moves if the king is in a check state (takes the number of the player who is in check state)
        bool lock(Coord & dep, Coord & arr, unsigned int adv);
        // Déplace une pièce en fonction des coordonnées de la pièce départ et de la cible, et du joueur effectuant le déplacement
        // Moves a piece using its arrival and starting coordinates and the number of the current player

        bool deplPiece(Coord & dep, Coord & arr, unsigned int adv);

        // Charge une partie sauvegardée
        // Load a saved game
        void chargerPartie(std::string path, irr::video::IVideoDriver* driver);
        // Sauvegarde une partie
        // Save a game
        void sauverPartie(std::string file);

        // Fonction renvoyant le booléen indiquant la promotion d'un pion
        // Get boolean indicating the promotion of a pawn
        bool getPromotionPion();
        // Fonction remettant à false le booléen indiquant la promotion d'un pion
        // Set previous boolean to false
        bool razPromotionPion();
        // Fonction remettant à zero les coordonnées du pion promu
        // Set coordinates of the promoted pawn to 0
        void razPromotedPion();

        // Fonction renvoyant la taille de la réserve d'un joueur (utilisation dans la gestion des scores, dans contextManager)
        // Function used to get the size of a player's stock (used in score manager, in contextManager)
        unsigned int getSizeRes(unsigned int joueur);

        // Fonction renvoyant le booléen indiquant l'échec et mat
        // Get a boolean indicating checkmate state
        bool getEchecMat();
        // Fonction renvoyant le texte a afficher en cas d'échec et mat
        // Get text to display in case of a checkmate state
        std::string getEchecMatTxt();

    private:
        // Tableau de pièces
        // Array of pieces
        Piece *ech[8][8];


        // Booléen indiquant la promotion d'un pion (pour l'interface)
        // Boolean indicating the promotion of a pawn (interface)
        bool m_promotion_pion;

        // Coordonnées du pion a promouvoir (pour l'interface)
        // Coordinates of the promoted pawn (interface)
        Coord m_promoted_pion;


        // Booléen indiquant la position d'échec (pas d'échec et mat)
        // Boolean for check state
        bool m_echec;

        // Booléen indiquant la position d'échec et mat (fin de la partie)
        // Boolean for checkmate state
        bool m_echec_mat;

        // Texte a afficher en cas d'échec et mat d'un joueur
        // Text to display in case of a checkmate
        std::string m_echec_mat_texte;

        // Coordonnées du roi en situation d'échec
        // Coordinates of the king in a check state
        Coord m_roi_echec;

        // Booléen indiquant un déplacement sans prise de pièce (pour l'annulation du dernier mouvement fait)
        // Boolean indicating a move without pieces being taken (cancellation of the last move)
        bool m_null_depl;

        // Réserves des joueurs
        // Players stock
        std::vector<Piece*> m_res_j1;
        std::vector<Piece*> m_res_j2;

        // Réserves de coups jouables en cas d'échec
        // Stock of playable moves in case of a check state
        std::vector<Coord> m_res_dep;
        std::vector<Coord> m_res_arr;

        // Textures du plateau et taille a afficher (sous forme d'un rectangle)
        // Board textures and size (rectangle)
        irr::video::ITexture * m_texture;
        irr::core::rect<irr::s32> m_texture_rect;
};

#endif // ECHIQUIER_H_INCLUDED
