/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Piece.h"
#include "def.h"
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

/*** Pion : pawn, Dame : queen, Tour : rook, Cavalier : knight, Fou : bishop, Roi : king ***/
/*** Echiquier : chessboard ***/

// Renvoie un pointeur sur l'image stockée dans la classe Piece (membre m_texture)
// Returns a pointer on the stored picture in the Piece class (m_texture member)
irr::video::ITexture * Piece::getTexture()
{
    return m_texture;
}

// Constructeur
// Constructor
Piece::Piece(irr::video::IVideoDriver* driver, unsigned int adv) : m_type('N'), m_adv(adv), driver(driver) { setStandardColor(); }

// Destructeur
// Destructor
Piece::~Piece()
{
    // On supprime les textures des pièces déja chargées pour pouvoir les recharger
    // Delete textures of already loaded pieces to load them again
    driver->removeTexture(m_texture);
}

// Retourne type de pièce
// Get piece type
char Piece::getTypePiece()
{
    return m_type;
}

// Renvoie joueur
// Get player number
unsigned int Piece::getAdv()
{
    return m_adv;
}

// Fonction d'affichage de la pièce, prend les attributs graphiques de la classe pièce
// Function displaying the piece, takes members from Pieces class
void Piece::affichage(irr::video::IVideoDriver* driver)
{
    driver->enableMaterial2D();
    driver->draw2DImage(getTexture(), irr::core::position2d<irr::s32>(m_irr_pos.x, m_irr_pos.y),
                        m_texture_rect, 0,
                        m_couleur_piece, true);
    driver->enableMaterial2D(false);
}


// Initialise les coordonnées de la pièce dans le cas ou celle ci est mise dans la réserve
// Initialize coordinates of the piece in the case of putting it in the stocks
void Piece::setPosRes(Coord & pos)
{
    m_pos = pos;
}

// Renvoie les coordonnées de la pièce dans le cas ou la pièce est dans la réserve
// Get coordinates of the pieces (case of the piece being in the stocks)
Coord & Piece::getPosRes()
{
    return m_pos;
}

// Change la position graphique de la pièce sur l'écran utilisé lors de l'affichage avec irrlicht (cas pièces sur l'échiquier)
// (Voir def.h pour les macros)
// Change graphical position of the piece on the chessboard
// (See def.h for macros)
void Piece::setIrrlichtPos(Coord & pos)
{
    Coord graphicalPos = pos;
    graphicalPos.x = graphicalPos.x*SQUARE_SIZE + X_OFFSET + BORDER_OFFSET;
    graphicalPos.y = graphicalPos.y*SQUARE_SIZE + Y_OFFSET + BORDER_OFFSET;

    m_irr_pos = graphicalPos;
}

// Change la position graphique de la pièce sur l'écran utilisé lors de l'affichage avec irrlicht (cas réserve)
// Change graphical position of the piece on the chessboard (case of stocks)
void Piece::setIrrlichtPosRes(int posVectorX, unsigned int adv)
{
    Coord graphicalPos;

    // Si l'élément peut être mis sur le première ligne de la réserve
    // If the element ca be put on the first line of the stocks
    if(posVectorX < 3)
    {
        // Selon le joueur, on le place d'un coté ou de l'autre du plateau
        // According to the players number, it is put on one side of the board or the other
        if(adv == 1)
        {
            graphicalPos.x = posVectorX*SQUARE_SIZE + X_OFFSET + BOARD_SIZE_X;
        }
        else if(adv == 2)
        {
            graphicalPos.x = posVectorX*SQUARE_SIZE;
        }
        else
        {
            return ;
        }

        // L'ordonnée est mise à la valeur de l'offset
        // Set y to offset value
        graphicalPos.y = Y_OFFSET + 25;
    }
    // Sinon
    // else
    else
    {
        // On utilise un modulo pour obtenir l'abscisse
        // We use a modulo to get x
        if(adv == 1)
        {
            graphicalPos.x = (posVectorX % 3)*SQUARE_SIZE + X_OFFSET + BOARD_SIZE_X;
        }
        else if(adv == 2)
        {
            graphicalPos.x = (posVectorX % 3)*SQUARE_SIZE;
        }
        else
        {
            return ;
        }

        // On utilise une division arrondie pour obtenir l'ordonnée
        // We use a division to get y
        graphicalPos.y = floor(posVectorX / 3)*SQUARE_SIZE + Y_OFFSET + 25;
    }

    // On met à jour les coordonnées graphiques
    // Update the graphical coordinates
    m_irr_pos = graphicalPos;
}

// Renvoie position graphique de la pièce
// Get graphical position of the piece
Coord & Piece::getIrrlichtPos()
{
    return m_irr_pos;
}


// Renvoie le type et le possesseur (joueur 1 ou 2) d'une pièce, sous forme d'une string
// Get type and owner (player 1 or 2) of a piece, as a string
std::string Piece::getInfo()
{
    std::string info;
    stringstream ss;

    info += m_type;
    ss << m_adv;
    info += ss.str();

    return info;
}

// Colore la pièce de façon standard (simple affichage de la texture)
// Standard piece color
void Piece::setStandardColor()
{
    m_couleur_piece.set(255, 255, 255, 255);
}

// Colore la pièce de façon a montrer qu'elle est sélectionnée (coloration de la texture et légère transparence)
// Selected piece color (blue and slightly transparent)
void Piece::setSelectedColor()
{
    m_couleur_piece.set(50, 75, 200, 255);
}

// Colore la pièce de façon a montrer qu'elle est en echec
// Check state piece color (orange)
void Piece::setEchecColor()
{
    m_couleur_piece.set(255, 255, 165, 0);
}

// Colore la pièce de façon a montrer qu'elle est en echec et mat
// Checkmate state piece color (red)
void Piece::setEchecMatColor()
{
    m_couleur_piece.set(255, 255, 0, 0);
}


// Vérification des déplacements possibles de la pièce et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check possible moves of the piece and compare it with an array containing the owner of the chessboard pieces
bool Piece::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]){}


/*
 *  Fonctions héritées par la classe pion
 *  Functions inherited by the pion (pawn) class
 */
// Getter pour l'attribut m_first_move
// Getter for m_first_move member
bool Piece::getFirstMove(){}
// Setter pour l'attribut m_first_move
// Setter for m_first_move member
void Piece::setFirstMove(bool first){}


/*
 *  Fonctions héritées par les classes roi et tour
 *  Functions inherited by the roi and tour (king and rook) classes
 */
// Getter pour l'attribut m_pos_init
// Getter for m_pos_init member
bool Piece::getPosInit(){}
// Setter pour l'attribut m_pos_init
// Setter for m_pos_init member
void Piece::setPosInit(bool init){}


// Constructeurs des différentes classes héritant de Piece
// Builders for classes inheriting from Piece
Pion::Pion(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver, adv)
{
    Piece::m_type = 'P';

    // Position de départ ; ce n'est pas le premier mouvement du pion
    // Initial position ; not the pawn's first move
    m_first_move = false;

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhitePawn.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackPawn.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}

Cavalier::Cavalier(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver, adv)
{
    Piece::m_type = 'C';

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhiteKnight.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackKnight.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}

Fou::Fou(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver, adv)
{
    Piece::m_type = 'F';

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhiteBishop.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackBishop.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}

Tour::Tour(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver, adv)
{
    Piece::m_type = 'T';

    // On est sur la position de départ a la création de la pièce
    // We are on the starting position at the creation of the piece
    m_pos_init = true;

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhiteRook.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackRook.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}

Dame::Dame(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver, adv), Tour(driver, adv), Fou(driver, adv)
{
    Piece::m_type = 'D';

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhiteQueen.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackQueen.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}


Roi::Roi(irr::video::IVideoDriver* driver, unsigned int adv) : Piece(driver,adv)
{
    Piece::m_type = 'R';

    // On est sur la position de départ a la création de la pièce
    // We are on the starting position at the creation of the piece
    m_pos_init = true;

    if(adv == 1)
        m_texture = driver->getTexture("img/White/WhiteKing.png");
    else if(adv == 2)
        m_texture = driver->getTexture("img/Black/BlackKing.png");

    m_texture_rect = irr::core::rect<irr::s32>(0,0,SQUARE_SIZE,SQUARE_SIZE);
}


// Vérification des déplacements possibles du pion et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the pawn and compare it with an array containing the owner of the chessboard pieces
bool Pion::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Coordonnée possibles de la pièce déplacée
    // Possible coordinates of the moved piece
    Coord deplP = posDep;

    // Masque des déplacements autorisés
    // Authorized moves mask
    unsigned int depl[8][8] = {0};

    // Si une pièce se trouve a gauche ou a droite du pion, le pion est autorisé a se déplacer vers ces coordonnées
    // Selon le joueur, les déplacements se font vers le bas ou vers le haut
    // If a piece is on the left or on the right of the pawn, the pawn is authorized to move at theses coordinates
    // The moves are going up or down depending on the player
    if(m_adv == 1)
    {
        // Deplacement a droite
        // Right move
         deplP.y--;
         deplP.x++;

         // Si les coordonnées sont valides
         // If coordinates are valid
         if(verifier(deplP))
         {
            // Si une pièce adverse se trouve sur l'emplacement, la trajectoire est valide
            // If there's an opponent's piece on the targeted square, the move is valid
            if(tab[deplP.x][deplP.y] != m_adv && tab[deplP.x][deplP.y] != 0)
            {
                depl[deplP.x][deplP.y] = 1;
            }
         }

        // RAZ
        // Reset
         deplP = posDep;

        // Deplacement a gauche
        // Left move
         deplP.y--;
         deplP.x--;

         // Si les coordonnées sont valides
         // If coordinates are valid
         if(verifier(deplP))
         {
            // Si une pièce adverse se trouve sur l'emplacement, la trajectoire est valide
            // If there's an opponent's piece on the targeted square, the move is valid
            if(tab[deplP.x][deplP.y] != m_adv && tab[deplP.x][deplP.y] != 0)
            {
                depl[deplP.x][deplP.y] = 1;
            }
         }
    }
    else if(m_adv == 2)
    {
        // Deplacement a droite
        // Right move
         deplP.y++;
         deplP.x++;

         // Si les coordonnées sont valides
         // If coordinates are valid
         if(verifier(deplP))
         {
            // Si une pièce adverse se trouve sur l'emplacement, la trajectoire est valide
            // If there's an opponent's piece on the targeted square, the move is valid
            if(tab[deplP.x][deplP.y] != m_adv && tab[deplP.x][deplP.y] != 0)
            {
                depl[deplP.x][deplP.y] = 1;
            }
         }

        // RAZ
        // Reset
         deplP = posDep;

        // Deplacement a gauche
        // Left move
         deplP.y++;
         deplP.x--;

         // Si les coordonnées sont valides
         // If coordinates are valid
         if(verifier(deplP))
         {
            // Si une pièce adverse se trouve sur l'emplacement, la trajectoire est valide
            // If there's an opponent's piece on the targeted square, the move is valid
            if(tab[deplP.x][deplP.y] != m_adv && tab[deplP.x][deplP.y] != 0)
            {
                depl[deplP.x][deplP.y] = 1;
            }
         }
    }


    // RAZ
    // Reset
    deplP = posDep;


    // Vérification pion sur position de départ (si déplacement d'un pion pour la première fois : deux cases de déplacement accordées)
    // Check if pawn is on its starting position (if the pawn is moved for the first time, we can move it two squares ahead)
    if(posDep.y == 1 || posDep.y == 6)
    {
        // Selon le joueur, les déplacements se font vers le bas ou vers le haut
        // The moves are going up or down depending on the player
        if(m_adv == 1)
        {
             depl[deplP.x][deplP.y-1] = 1;
             depl[deplP.x][deplP.y-2] = 1;
        }
        else if(m_adv == 2)
        {
             depl[deplP.x][deplP.y+1] = 1;
             depl[deplP.x][deplP.y+2] = 1;
        }


        // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles du pion
        // Case of the arrival position not belonging to the possible moves
        if(depl[posArr.x][posArr.y] == 0)
        {
            ////cout << "Le déplacement n'est pas autorisé Pion" << endl;
            return false;
        }



        // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
        // Parcours du masque des trajectoires possibles
        // Check if the arrival coordinates belong to the possible ccordinates
        // Processing mask of possible moves
        for( unsigned int i = 0; i <= 7; i++ ){
            for( unsigned int j = 0; j <= 7; j++ ){

                if(depl[i][j] == 1 && tab[i][j] != 0)
                {
                        // Cas d'une pièce n'appartenant pas au joueur sur la trajectoire du pion (hors prise d'une pièce)
                        // Case of a piece not belonging to the player on the pawn's trajectory (outside of a piece being taken)
                        if(tab[i][j] != m_adv && posDep.x == posArr.x)
                        {
                            // Si joueur 1 : si la pièce est au dessus du pion (y pion > y pièce) => erreur
                            // Si joueur 2 : si la pièce est au dessous du pion (y pion < y pièce) => erreur
                            // If player 1 : if the piece is above the pawn (y pawn > y piece) => error
                            // If player 2 : if the piece is below the pawn (y pawn < y piece) => error
                            if(m_adv == 1)
                            {
                                // La pièce bloquante peut se trouver une ou deux cases devant le pion a bouger, a la verticale du pion
                                // Si la pièce de l'adversaire se trouve :
                                // - A la verticale du pion
                                // - Une ou deux cases devant lui
                                // - Et que le déplacement va au dela de ou sur la position de la pièce de l'adversaire
                                // Alors le mouvement est impossible
                                // The blocking piece can be one or two square ahead the moving pawn, over the pawn
                                // If the opponent's piece is :
                                // - Over the pawn
                                // - One or two squares ahead
                                // - And the move goes beyond the position or on the position of the opponent's piece
                                // Then the move is forbidden
                                if((j == posDep.y-1 || j == posDep.y-2) && i == posDep.x && posArr.y <= j)
                                {
                                    //cout << "Pièce appartenant a l'adversaire sur la trajectoire 1 " << i << " " << j << endl;
                                    return false;
                                }
                            }
                            else if(m_adv == 2)
                            {
                                // La pièce bloquante peut se trouver une ou deux cases devant le pion a bouger, a la verticale du pion
                                // Si la pièce de l'adversaire se trouve :
                                // - A la verticale du pion
                                // - Une ou deux cases devant lui
                                // - Et que le déplacement va au dela de ou sur la position de la pièce de l'adversaire
                                // Alors le mouvement est impossible
                                // The blocking piece can be one or two square ahead the moving pawn
                                // If the opponent's piece is :
                                // - Over the pawn
                                // - One or two squares ahead
                                // - And the move goes beyond the position or on the position of the opponent's piece
                                // Then the move is forbidden
                                if((j == posDep.y+1 || j == posDep.y+2) && i == posDep.x && posArr.y >= j)
                                {
                                    //cout << "Pièce appartenant a l'adversaire sur la trajectoire 2" << endl;
                                    return false;
                                }
                            }
                        }


                        // Cas d'une pièce appartenant au joueur sur la trajectoire du pion (hors prise d'une pièce)
                        // Case of a piece belonging to the player on the pawn's trajectory (outside of a piece being taken)
                        if(tab[i][j] == m_adv && posDep.x == posArr.x)
                        {
                            // Si joueur 1 : si la pièce est au dessus du pion (y pion > y pièce) => erreur
                            // Si joueur 2 : si la pièce est au dessous du pion (y pion < y pièce) => erreur
                            // If player 1 : if the piece is above the pawn (y pawn > y piece) => error
                            // If player 2 : if the piece is below the pawn (y pawn < y piece) => error
                            if(m_adv == 1)
                            {
                                // La pièce bloquante peut se trouver une ou deux cases devant le pion a bouger, a la verticale du pion (cas de la prise de pièce a droite / gauche)
                                // Vérification similaire a celle effectué pour un adversaire dans la trajectoire
                                // The blocking piece can be one or two square ahead the moving pawn, over the pawn
                                // Check the move the same way as before
                                if((j == posDep.y-1 || j == posDep.y-2) && i == posDep.x && posArr.y <= j)
                                {
                                    //cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                    return false;
                                }
                            }
                            else if(m_adv == 2)
                            {
                                // La pièce bloquante peut se trouver une ou deux cases devant le pion a bouger, a la verticale du pion (cas de la prise de pièce a droite / gauche)
                                // Vérification similaire a celle effectué pour un adversaire dans la trajectoire
                                // The blocking piece can be one or two square ahead the moving pawn, over the pawn
                                // Check the move the same way as before
                                if((j == posDep.y+1 || j == posDep.y+2) && i == posDep.x && posArr.y >= j)
                                {
                                    //cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                    return false;
                                }
                            }
                        }
                }
            }
        }

    }

    // Vérification pion sur position standard (déplacement d'une seule case)
    // Check if the pawn is on the standard position (1 square move)
    else
    {
        // RAZ
        // Reset
        deplP = posDep;

        // Selon le joueur, les déplacements se font vers le bas ou vers le haut
         // The moves are going up or down depending on the player
        if(m_adv == 1)
        {
             deplP.y--;

             // Vérification non dépassement de l'échiquier
             // Check if we don't go beyond the chessboard
             if(verifier(deplP))
             {
                depl[deplP.x][deplP.y] = 1;
             }
        }
        else if(m_adv == 2)
        {
             deplP.y++;

             // Vérification non dépassement de l'échiquier
             // Check if we don't go beyond the chessboard
             if(verifier(deplP))
             {
                depl[deplP.x][deplP.y] = 1;
             }
        }

        // Si les coordonnées dépassent de l'échiquier après avoir rempli le tableau de marque, le mouvement est impossible
        // If the coordinates go beyond the chessboard after filling the mask array, the move is impossible
        if(!verifier(deplP))
        {
            ////cout << "Dépassement de l'échiquier" << endl;
            return false;
        }
        else
        {
            depl[deplP.x][deplP.y] = 1;

            // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
            // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles du pion
            // Check that the arrival coordinates belong to the possible coordinates
            // Case of the arrival position not belonging to the possible moves of the pawn
            if(depl[posArr.x][posArr.y] == 0)
            {
                ////cout << "Le déplacement n'est pas autorisé" << endl;
                return false;
            }

            // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
            // Parcours du masque des trajectoires possibles
            // Check that the arrival coordinates belong to the possible coordinates
            // Go through the mask of possible trajectories
            for( unsigned int i = 0; i <= 7; i++ ){
                for( unsigned int j = 0; j <= 7; j++ ){
                    if(depl[i][j] == 1 && tab[i][j] != 0)
                    {
                        // Cas d'une pièce n'appartenant pas au joueur sur la trajectoire du pion (hors prise pièce)
                        // Le cas d'une pièce appartenant au joueur sur la trajectoire est géré par la fonction deplPiece de l'échiquier
                        // Case of a piece not belonging to the player on the pawn trajectory (not the case of a piece being taken)
                        // The case of a piece belonging to the player on the pawn trajectory is treated in the deplPiece function
                        if(tab[i][j] != m_adv && posDep.x == posArr.x)
                        {
                            // Si joueur 1 : si la pièce est au dessus du pion (y pion > y pièce) => erreur
                            // Si joueur 2 : si la pièce est au dessous du pion (y pion < y pièce) => erreur
                            // If player 1 : if the piece is above the pawn (y pawn > y piece) => error
                            // If player 2 : if the piece is below the pawn (y pawn < y piece) => error
                            if(m_adv == 1)
                            {
                                // Si la pièce bloquante est devant le pion
                                // If the blocking piece if ahead of the pawn
                                if(j == posDep.y-1 && i == posDep.x)
                                {
                                    ////cout << "Pièce appartenant a l'adversaire devant le pion" << endl;
                                    return false;
                                }
                            }
                            else if(m_adv == 2)
                            {
                                // Si la pièce bloquante est devant le pion
                                // If the blocking piece if ahead of the pawn
                                if(j == posDep.y+1 && i == posDep.x)
                                {
                                    ////cout << "Pièce appartenant a l'adversaire devant le pion" << endl;
                                    return false;
                                }
                            }
                        }
                    }
               }
            }
        }
    }

    return true;
}

// Getter m_first_move
bool Pion::getFirstMove()
{
    return m_first_move;
}

// Setter m_first_move
void Pion::setFirstMove(bool first)
{
    m_first_move = first;
}


// Vérification des déplacements possibles du cavalier et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the pawn and compare it with an array containing the owner of the chessboard pieces
bool Cavalier::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Coordonnée possibles de la pièce déplacée
    // Possible coordinate of the moved piece
    Coord deplP = posDep;

    // Masque des déplacements autorisés
    // Authorized deplacement mask
    unsigned int depl[8][8] = {0};


    // Définition de toutes les trajectoires possibles pour le cavalier
    // Definition of all the possible trajectories for the knight
    deplP.x += 2;
    deplP.y++;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    deplP.y -= 2;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    deplP.x -= 2;
    deplP.y++;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    deplP.y -= 2;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    deplP.x++;
    deplP.y += 2;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    deplP.y -= 4;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    deplP.x--;
    deplP.y += 2;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    deplP.y -= 4;
    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


/// Le cas d'une pièce appartenant au joueur sur la trajectoire est géré par la fonction deplPiece de l'échiquier
/// The case of a piece belonging to the player is treated in the deplPiece function

        // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
        // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles du cavalier
        // Check that the arrival coordinates belong to the possible coordinates
        // Case of the arrival position not belonging to the possible moves of the knight
        if(depl[posArr.x][posArr.y] == 0)
        {
            ////cout << "Le déplacement n'est pas autorisé" << endl;
            return false;
        }

    return true;
}

// Vérification des déplacements possibles du fou et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the bishop and compare it with an array containing the owner of the chessboard pieces
bool Fou::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Coordonnée possibles de la pièce déplacée
    // Possible coordinates of the piece
    Coord deplP = posDep;

    // Masque des déplacements autorisés
    // Mask of possible moves
    unsigned int depl[8][8] = {0};


    // Définition de toutes les trajectoires possibles pour le fou
    // Diagonales inférieures
    // Definition of all the possible trajectories for the bishop
    // Low diagonals
    deplP.x++;
    deplP.y++;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x++;
        deplP.y++;
    }

    // RAZ
    // Reset
    deplP = posDep;

    deplP.x--;
    deplP.y++;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x--;
        deplP.y++;
    }


    // RAZ
    // Reset
    deplP = posDep;


    // Diagonales supérieures
    // High diagonals
    deplP.x++;
    deplP.y--;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x++;
        deplP.y--;
    }

    // RAZ
    // Reset
    deplP = posDep;

    deplP.x--;
    deplP.y--;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x--;
        deplP.y--;
    }


        // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
        // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles du fou
        // Check that the coordinates belong to the possible coordinates
        // Case of the arrival coordinates not belonging to the possible coordinates
        if(depl[posArr.x][posArr.y] == 0)
        {
            ////cout << "Le déplacement n'est pas autorisé" << endl;
            return false;
        }


        for( unsigned int i = 0; i <= 7; i++ ){
            for( unsigned int j = 0; j <= 7; j++ ){
                if(depl[i][j] == 1 && tab[i][j] != 0)
                {
                    /// Cas d'une pièce appartenant au joueur sur la trajectoire de la pièce
                    /// Case of a piece belonging to the player in the trajectory
                    if(tab[i][j] == m_adv)
                    {
                        // On regarde si la pièce est intercalée entre la position de départ et d'arrivée
                        // Si la trajectoire est dirigée vers le bas, on regarde si la pièce appartenant au joueur est située plus bas que la position de départ
                        // et plus haut que la position d'arrivée
                        // Check if the piece is between the arrival and starting position
                        // If the trajectory is downwards, we check if the piece belonging to the player is lower than the starting position
                        // and higher than the arrival position
                        if(posArr.y < posDep.y)
                        {
                            if((j < posDep.y && j > posArr.y) && (posArr.x > posDep.x) && (i > posDep.x && i < posArr.x))
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                            if((j < posDep.y && j > posArr.y) && (posArr.x < posDep.x) && (i < posDep.x && i > posArr.x))
                            {
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                        }
                        // Sinon on regarde si la pièce appartenant au joueur est située plus haut que la position de départ
                        // et plus bas que la position d'arrivée
                        // Else, we check if the piece belonging to the player is higher than the starting position
                        // and lower than the arrival position
                        else
                        {
                            if((j > posDep.y && j < posArr.y) && (posArr.x > posDep.x) && (i > posDep.x && i < posArr.x))
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                            if((j > posDep.y && j < posArr.y) && (posArr.x < posDep.x) && (i < posDep.x && i > posArr.x))
                            {
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                        }
                    }

                    /// Cas d'une pièce appartenant a l'adversaire sur la trajectoire de la pièce
                    /// Case of a piece belonging to the opponent on the trajectory
                    if(tab[i][j] != m_adv && tab[i][j] != 0)
                    {
                        // On regarde si la pièce est intercalée entre la position de départ et d'arrivée
                        // Si la trajectoire est dirigée vers le bas, on regarde si la pièce appartenant a l'adversaire est située plus bas que la position de départ
                        // et plus haut que la position d'arrivée
                        // Check if the piece is between the arrival and starting position
                        // If the trajectory is downwards, we check if the piece belonging to the opponent is lower than the starting position
                        // and higher than the arrival position
                        if(posArr.y < posDep.y)
                        {
                            if((j < posDep.y && j > posArr.y) && (posArr.x > posDep.x) && (i > posDep.x && i < posArr.x))
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant a l'adversaire devant le fou" << endl;
                                return false;
                            }
                            if((j < posDep.y && j > posArr.y) && (posArr.x < posDep.x) && (i < posDep.x && i > posArr.x))
                            {
                                ////cout << "Pièce appartenant a l'adversaire devant le fou" << endl;
                                return false;
                            }
                        }
                        // Sinon on regarde si la pièce appartenant a l'adversaire est située plus haut que la position de départ
                        // et plus bas que la position d'arrivée
                        // Else, we check if the piece belonging to the opponent is higher than the starting position
                        // and lower than the arrival position
                        else
                        {
                            if((j > posDep.y && j < posArr.y) && (posArr.x > posDep.x) && (i > posDep.x && i < posArr.x))
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant a l'adversaire devant le fou" << endl;
                                return false;
                            }
                            if((j > posDep.y && j < posArr.y) && (posArr.x < posDep.x) && (i < posDep.x && i > posArr.x))
                            {
                                ////cout << "Pièce appartenant a l'adversaire devant le fou" << endl;
                                return false;
                            }
                        }
                    }

                }
            }
        }

    return true;
}

// Vérification des déplacements possibles de la tour et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the rook and compare it with an array containing the owner of the chessboard pieces
bool Tour::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Coordonnée possibles de la pièce déplacée
    // Possible coordinates of the piece
    Coord deplP = posDep;

    // Masque des déplacements autorisés
    // Mask of possible moves
    unsigned int depl[8][8] = {0};


    // Définition de toutes les trajectoires possibles pour la tour
    // Ligne inférieure
    // Definition of all the possible trajectories for the rook
    // Low row
    deplP.x--;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x--;
    }

    // RAZ
    // Reset
    deplP = posDep;

    // Ligne supérieure
    // High row
    deplP.x++;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.x++;
    }

    // RAZ
    // Reset
    deplP = posDep;

    // Colonne inférieure
    // Low column
    deplP.y++;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.y++;
    }

    // RAZ
    // Reset
    deplP = posDep;

    // Colonne supérieure
    // High column
    deplP.y--;

    while(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;

        deplP.y--;
    }


        // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
        // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles de la tour
        // Check that the coordinates belong to the possible coordinates
        // Case of the arrival coordinates not belonging to the possible coordinates
        if(depl[posArr.x][posArr.y] == 0)
        {
            ////cout << "Le déplacement n'est pas autorisé" << endl;
            return false;
        }

        for( unsigned int i = 0; i <= 7; i++ ){
            for( unsigned int j = 0; j <= 7; j++ ){
                if(depl[i][j] == 1 && tab[i][j] != 0)
                {
                    /// Cas d'une pièce appartenant au joueur sur la trajectoire de la pièce
                    /// Case of a piece belonging to the player in the trajectory
                    if(tab[i][j] == m_adv)
                    {
                        // On regarde si la pièce est intercalée entre la position de départ et d'arrivée
                        // Cas d'une colonne
                        // Check if the piece is between the starting position and the arrival position
                        // Case of a column
                        if(i == posArr.x && i == posDep.x)
                        {
                            // Mouvement de bas en haut
                            // Upward move
                            if(posArr.y < posDep.y && j < posDep.y && j > posArr.y)
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                            // Mouvement de haut en bas
                            // Downward move
                            if(posArr.y > posDep.y && j > posDep.y && j < posArr.y)
                            {
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                        }

                        // Cas d'une ligne
                        // Case of a row
                        if(j == posArr.y && j == posDep.y)
                        {
                            // Mouvement de droite a gauche
                            // Right to left move
                            if(posArr.x < posDep.x && i < posDep.x && i > posArr.x)
                            {
                                ////cout << "Pièce dans la traj " << i << " " << posDep.x << " " << posArr.x << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                            // Mouvement de gauche a droite
                            // Left to right move
                            if(posArr.x > posDep.x && i > posDep.x && i < posArr.x)
                            {
                                ////cout << "Pièce appartenant au joueur sur la trajectoire" << endl;
                                return false;
                            }
                        }
                    }

                    /// Cas d'une pièce appartenant a l'adversaire sur la trajectoire de la pièce
                    /// Case of a piece belonging to the opponent in the trajectory
                    if(tab[i][j] != m_adv && tab[i][j] != 0)
                    {
                        // On regarde si la pièce est intercalée entre la position de départ et d'arrivée
                        // Cas d'une colonne
                        // Check if the piece is between the starting position and the arrival position
                        // Case of a column
                        if(i == posArr.x && i == posDep.x)
                        {
                            // Mouvement de bas en haut
                            // Upward move
                            if(posArr.y < posDep.y && j < posDep.y && j > posArr.y)
                            {
                                ////cout << "Pièce dans la traj " << j << " " << posDep.y << " " << posArr.y << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant a l'adversaire devant la tour" << endl;
                                return false;
                            }
                            // Mouvement de haut en bas
                            // Downward move
                            if(posArr.y > posDep.y && j > posDep.y && j < posArr.y)
                            {
                                ////cout << "Pièce appartenant a l'adversaire devant la tour" << endl;
                                return false;
                            }
                        }

                        // Cas d'une ligne
                        // Case of a line
                        if(j == posArr.y && j == posDep.y)
                        {
                            // Mouvement de droite a gauche
                            // Right to left move
                            if(posArr.x < posDep.x && i < posDep.x && i > posArr.x)
                            {
                                ////cout << "Pièce dans la traj " << i << " " << posDep.x << " " << posArr.x << " " << tab[i][j] << endl;
                                ////cout << "Pièce appartenant a l'adversaire devant la tour" << endl;
                                return false;
                            }
                            // Mouvement de gauche a droite
                            // Left to right move
                            if(posArr.x > posDep.x && i > posDep.x && i < posArr.x)
                            {
                                ////cout << "Pièce appartenant a l'adversaire devant la tour" << endl;
                                return false;
                            }
                        }
                    }


                }
            }
        }

    return true;
}

// Getter m_pos_init
bool Tour::getPosInit()
{
    return m_pos_init;
}

// Setter m_pos_init
void Tour::setPosInit(bool init)
{
    m_pos_init = init;
}


// Vérification des déplacements possibles de la dame et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the queen and compare it with an array containing the owner of the chessboard pieces
bool Dame::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Appel aux fonctions checkPos de la tour et du fou : la dame possède les propriétés de déplacement de la tour et du fou
    // Call the related functions for the bishop and the rook
    if(!Tour::checkPos(posDep, posArr, tab))
    {
        return Fou::checkPos(posDep, posArr, tab);
    }
    else
    {
        return Tour::checkPos(posDep, posArr, tab);
    }
}


// Vérification des déplacements possibles du roi et comparaison avec un tableau représentant les possesseurs des pièces de l'échiquier
// Check the possible moves of the queen and compare it with an array containing the owner of the chessboard pieces
bool Roi::checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8])
{
    // Coordonnée possibles de la pièce déplacée
    // Possible coordinates of the piece
    Coord deplP = posDep;

    // Masque des déplacements autorisés
    // Mask of possible moves
    unsigned int depl[8][8] = {0};


    // Définition de toutes les trajectoires possibles pour le roi : 8 cases
    // Definition of all possible trajectories for the king : 8 squares

    /* Cases situées a droite de la pièce courante */
    /* Squares on the right */
    // Case a droite du roi
    // Immediate right
    deplP.x++;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Case en bas a droite du roi
    // Down right
    deplP.x++;
    deplP.y++;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Case en haut a droite du roi
    // Up right
    deplP.x++;
    deplP.y--;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    /* Cases situées a gauche de la pièce courante */
    /* Squares on the left */
    // Case a gauche du roi
    // Immediate left
    deplP.x--;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Case en bas a gauche du roi
    // Down left
    deplP.x--;
    deplP.y++;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Case en haut a gauche du roi
    // Up left
    deplP.x--;
    deplP.y--;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    /* Cases situées au dessus et au dessous de la pièce courante */
    /* Immediate up and down squares */
    // Case en bas du roi
    // Immediate down
    deplP.y++;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Case en haut du roi
    // Immediate up
    deplP.y--;

    if(verifier(deplP))
    {
        depl[deplP.x][deplP.y] = 1;
    }

    // RAZ
    // Reset
    deplP = posDep;


    // Vérification que les coordonnées d'arrivée font partie de l'ensemble des coordonnées possibles
    // Cas de la position d'arrivée n'appartenant pas aux trajectoires possibles du roi
    // Check that the coordinates belong to the possible coordinates
    // Case of the arrival coordinates not belonging to the possible coordinates
    if(depl[posArr.x][posArr.y] == 0)
    {
        ////cout << "Le déplacement n'est pas autorisé" << endl;
        return false;
    }

}

// Getter m_pos_init
bool Roi::getPosInit()
{
    return m_pos_init;
}

// Setter m_pos_init
void Roi::setPosInit(bool init)
{
    m_pos_init = init;
}
