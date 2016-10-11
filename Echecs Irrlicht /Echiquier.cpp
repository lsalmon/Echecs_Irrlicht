/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#include "Echiquier.h"
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

// Renvoie un pointeur sur l'image stockée dans la classe Echiquier (membre m_texture)
// Return pointer to the image stored in the chessboard (Echiquier) class (member m_texture)
irr::video::ITexture * Echiquier::getTexture()
{
    return m_texture;
}

// Constructeur
// Builder
Echiquier::Echiquier(){}

// Initialisation : crée les pièces, remplit le tableau de pointeurs sur Piece en attribut de la classe Echiquier
// et règle leur position graphique initiale sur le plateau.
// Règle aussi les membres booléens de cas spéciaux de la classe Echiquier : promotion d'un pion, échec, échec et mat
// Initialization : create pieces, fill the pointer array in the Echiquier class wit pointers on the pieces and
// give them an initial position on the chessboard (graphical)
// Initialize booleans for special cases (promotion, check, checkmate)
void Echiquier::init(irr::video::IVideoDriver* driver)
{
    unsigned int i,j;

    // Initialise le tableau a NULL
    // Initialize array to NULL
    for(j = 0; j <= 7; j++){
        for(i = 0; i <= 7; i++){
            ech[i][j] = NULL;
        }
    }

    // Variable temporaire utilisée pour régler la place des pièces sur l'échiquier graphique
    // Temp variable to place pieces on the graphical chessboard
    Coord graphicalPos;

    // Constructeur Echiquier : construit toutes les pièces et les pose a leur emplacement de départ
    // Echiquier builder : build all the pieces and put them at their starting place
    // Joueur 2 : Pièces noires
    // Player 2 : black pieces
    Pion *pionN1, *pionN2, *pionN3, *pionN4, *pionN5, *pionN6, *pionN7, *pionN8;
    pionN1 = new Pion(driver,2);
    pionN2 = new Pion(driver,2);
    pionN3 = new Pion(driver,2);
    pionN4 = new Pion(driver,2);
    pionN5 = new Pion(driver,2);
    pionN6 = new Pion(driver,2);
    pionN7 = new Pion(driver,2);
    pionN8 = new Pion(driver,2);

    ech[0][1] = pionN1;
    ech[1][1] = pionN2;
    ech[2][1] = pionN3;
    ech[3][1] = pionN4;
    ech[4][1] = pionN5;
    ech[5][1] = pionN6;
    ech[6][1] = pionN7;
    ech[7][1] = pionN8;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.y = 1;

    for(i = 0; i < 8; i++)
    {
        graphicalPos.x = i;
        ech[i][1]->setIrrlichtPos(graphicalPos);
    }


    Tour *tN1, *tN2;
    tN1 = new Tour(driver,2);
    tN2 = new Tour(driver,2);

    ech[0][0] = tN1;
    ech[7][0] = tN2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.y = 0;
    graphicalPos.x = 0;

    ech[0][0]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 7;

    ech[7][0]->setIrrlichtPos(graphicalPos);



    Cavalier *cN1, *cN2;
    cN1 = new Cavalier(driver,2);
    cN2 = new Cavalier(driver,2);

    ech[1][0] = cN1;
    ech[6][0] = cN2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 1;

    ech[1][0]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 6;

    ech[6][0]->setIrrlichtPos(graphicalPos);



    Fou *fN1, *fN2;
    fN1 = new Fou(driver,2);
    fN2 = new Fou(driver,2);

    ech[2][0] = fN1;
    ech[5][0] = fN2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 2;

    ech[2][0]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 5;

    ech[5][0]->setIrrlichtPos(graphicalPos);



    Dame *dN;
    dN = new Dame(driver,2);

    ech[3][0] = dN;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 3;

    ech[3][0]->setIrrlichtPos(graphicalPos);



    Roi *rN;
    rN = new Roi(driver,2);

    ech[4][0] = rN;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 4;

    ech[4][0]->setIrrlichtPos(graphicalPos);



    // Joueur 1 : Pièces blanches
    // Player 1 : white pieces
    Pion *pionB1, *pionB2, *pionB3, *pionB4, *pionB5, *pionB6, *pionB7, *pionB8;
    pionB1 = new Pion(driver,1);
    pionB2 = new Pion(driver,1);
    pionB3 = new Pion(driver,1);
    pionB4 = new Pion(driver,1);
    pionB5 = new Pion(driver,1);
    pionB6 = new Pion(driver,1);
    pionB7 = new Pion(driver,1);
    pionB8 = new Pion(driver,1);

    ech[0][6] = pionB1;
    ech[1][6] = pionB2;
    ech[2][6] = pionB3;
    ech[3][6] = pionB4;
    ech[4][6] = pionB5;
    ech[5][6] = pionB6;
    ech[6][6] = pionB7;
    ech[7][6] = pionB8;



// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.y = 6;

    for(i = 0; i < 8; i++)
    {
        graphicalPos.x = i;
        ech[i][6]->setIrrlichtPos(graphicalPos);
    }



    Tour *tB1, *tB2;
    tB1 = new Tour(driver,1);
    tB2 = new Tour(driver,1);

    ech[0][7] = tB1;
    ech[7][7] = tB2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.y = 7;
    graphicalPos.x = 0;

    ech[0][7]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 7;

    ech[7][7]->setIrrlichtPos(graphicalPos);



    Cavalier *cB1, *cB2;
    cB1 = new Cavalier(driver,1);
    cB2 = new Cavalier(driver,1);

    ech[1][7] = cB1;
    ech[6][7] = cB2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 1;

    ech[1][7]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 6;

    ech[6][7]->setIrrlichtPos(graphicalPos);



    Fou *fB1, *fB2;
    fB1 = new Fou(driver,1);
    fB2 = new Fou(driver,1);

    ech[2][7] = fB1;
    ech[5][7] = fB2;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 2;

    ech[2][7]->setIrrlichtPos(graphicalPos);

    graphicalPos.x = 5;

    ech[5][7]->setIrrlichtPos(graphicalPos);



    Dame *dB;
    dB = new Dame(driver,1);

    ech[3][7] = dB;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 3;

    ech[3][7]->setIrrlichtPos(graphicalPos);



    Roi *rB;
    rB = new Roi(driver,1);

    ech[4][7] = rB;

// Règle les positions sur l'échiquier graphique des pièces (les pièces ont un membre lié)
// Adjust piece positions on the chessboard (pieces have a related member in their class)
    graphicalPos.x = 4;

    ech[4][7]->setIrrlichtPos(graphicalPos);

// Booléen de promotion d'un pion a false
// Promotion boolean
    m_promotion_pion = false;

// Booléen d'échec a false
// Check boolean
    m_echec = false;

// Booléen d'échec et mat a false
// Checkmate boolean
    m_echec_mat = false;

// On charge l'image de l'échiquier
// Load the picture of the chessboard
    //m_texture = driver->getTexture("img/Xboard.png");
    m_texture = driver->getTexture("img/GlChessboard.png");
}



// Afficher les réserves : elles contiennent les pièces prises à l'adversaire par le joueur
// Display stock (pieces taken from the opponent)
void Echiquier::afficheRes(irr::video::IVideoDriver* driver)
{
    /// Parcours des Réserves et positionnement graphique des pièces qui sont a l'intérieur (setIrrlichtPosRes),
    /// puis appel a la fonction d'affichage des pièces
    /// Processing stock and putting pieces on the chessboard, then calling the pieces display function
//    cout << "Réserve joueur 1 : ";
    for ( unsigned int i = 0, size = m_res_j1.size(); i < size; ++i )
    {
        // cout << m_res_j1.at(i)->getTypePiece() << m_res_j1.at(i)->getAdv() << '\t';
        m_res_j1.at(i)->setIrrlichtPosRes(i, 1);

        // Appel a la méthode affichage de la pièce
        // Call the display function for the piece
        m_res_j1.at(i)->affichage(driver);
    }

//    cout << endl;

//    cout << "Réserve joueur 2 : ";
    for ( unsigned int i = 0, size = m_res_j2.size(); i < size; ++i )
    {
        // cout << m_res_j2.at(i)->getTypePiece() << m_res_j2.at(i)->getAdv() << '\t';
        m_res_j2.at(i)->setIrrlichtPosRes(i, 2);

        // Appel a la méthode affichage de la pièce
        // Call the display function for the piece
        m_res_j2.at(i)->affichage(driver);
    }
}

// Fonction d'affichage du plateau de jeu
// Function displaying the chessboard
void Echiquier::afficher(irr::video::IVideoDriver* driver)
{
    driver->enableMaterial2D();
        driver->draw2DImage(getTexture(), irr::core::position2d<irr::s32>(X_OFFSET, Y_OFFSET),
            core::rect<s32>(0,0,BOARD_SIZE_X,BOARD_SIZE_Y),
           0, video::SColor(255,255,255,255));
        driver->enableMaterial2D(false);
}

// Affiche l'échiquier complet
// Complete chessboard display
void Echiquier::afficheEch(irr::video::IVideoDriver* driver)
{
    // Affiche le plateau de jeu
    // Display basic chessboard
    afficher(driver);


    for(unsigned int j = 0; j <= 7; j++){
        for(unsigned int i = 0; i <= 7; i++){
            // Si la pièce existe
            // If piece exist
            if(ech[i][j] != NULL)
            {
                // Appel a la méthode affichage de la pièce
                // Call display method for the piece
                 ech[i][j]->affichage(driver);
            }
        }
    }

    // Affichage de la réserve
    // Display stock
    afficheRes(driver);
}

// Fonctions d'appel aux fonctions de coloration des pièces
// (utilisées depuis le contextmanager)
// Functions calling other functions used to color pieces
// (used in the contextmanager)
void Echiquier::setSelectedPiece(Coord & pos)
{
    if(ech[pos.x][pos.y] != NULL)
    {
        ech[pos.x][pos.y]->setSelectedColor();
    }
}

void Echiquier::setStandardPiece(Coord & pos)
{
    if(ech[pos.x][pos.y] != NULL)
    {
        ech[pos.x][pos.y]->setStandardColor();
    }
}


// Renvoie les informations sur la pièce se trouvant sur la case de l'échiquier dont les coordonnées sont passées en paramètre
// Get info on the piece found on the chessboard square (square coordinates as parameter)
std::string Echiquier::getPosEch(Coord & p)
{
    std::string info;

    if(ech[p.x][p.y] == NULL)
    {
        info = " ";
    }
    else
    {
        // Obtention du type et du possesseur de la pièce, sous forme d'une string
        // Get type and player who owns the piece as a string
        info = ech[p.x][p.y]->getInfo();
    }

    return info;
}

// Supprime une pièce et la range dans la réserve
// Delete piece and store it in the stock
void Echiquier::supprPiece(Coord & p)
{
    // Si coordonnées de suppression non valides, pas d'effacage
    // If the coordinates are invalid the piece stays
    if(!verifier(p))
    {
        cout << "Invalid coordinates" << endl;
        return ;
    }
    // Sinon, on change le type de pièce, et on renseigne la position interne de la pièce avant de la mettre dans la réserve
    // Else, we change the piece type and set the internal (not graphical) postion of the piece before putting it in the stock
    else
    {
        // Renseignement position de la pièce dans son champ interne
        // Set piece postion
        ech[p.x][p.y]->setPosRes(p);


        // On choisit la réserve en fonction du champ joueur de la classe pièce
        // Choose the other player's stock
        if(ech[p.x][p.y]->getAdv() == 1)
        {
            // Rangement réserve joueur 1
            // Put the piece in the player 1 stock
            m_res_j1.push_back(ech[p.x][p.y]);

        }
        else if(ech[p.x][p.y]->getAdv() == 2)
        {
            // Rangement réserve joueur 2
            // Put the piece in the player 2 stock
            m_res_j2.push_back(ech[p.x][p.y]);
        }
        else
        {
            // Erreur champ joueur
            // Error on the player number
            cout << "Error : invalid player" << endl;
            return ;
        }

        ech[p.x][p.y] = NULL;
    }
}

// Fonction d'annulation du dernier déplacement effectué (avec prise de pièce ou non)
// Function cancelling the last move (piece taken or not)
bool Echiquier::revPiece(unsigned int player, Coord & posPrec, Coord & posAct)
{
    Piece *joueur;
    Piece *adversaire;
    Coord tmpCoord;

    // Cas d'un déplacement sans prise de pièce
    // Move with no piece taken
    if(m_null_depl)
    {

        ech[posPrec.x][posPrec.y] = ech[posAct.x][posAct.y];
        ech[posAct.x][posAct.y] = NULL;

        // Cas de la mise en échec du roi adverse annulée par l'annulation du mouvement
        // Si on est dans une situation d'échec pour l'adversaire, on appelle la fonction verifierEchec après l'annulation du mouvement
        // pour changer le booléen d'échec m_echec
        // Case of the cancelled checkmate of the king
        // If the opponent is in a check situation, we call the verifierEchec (check check) function after move cancellation
        // to change check boolean
        if(m_echec)
            verifierEchec(player);

        ech[posPrec.x][posPrec.y]->setIrrlichtPos(posPrec);

        return true;
    }

    if(player == 1)
    {
        // On teste si la réserve est vide
        // test if the stock is empty
        if(m_res_j1.empty())
        {
            cout << "Empty stock" << endl;
            return false;
        }

        // Retourne une référence du dernier élément stocké
        // Get reference to last element stored
        adversaire = m_res_j1.back();

        // Retourne les coordonnées de la pièce prise
        // Get the coordinates of the piece taken
        tmpCoord = adversaire->getPosRes();


        // Cas d'une prise en passant (si la pièce prise était un pion et qu'elle se trouvait sur la bonne position lors de son premier mouvement)
        // Case of an en passant move (if the piece was a pawn and was on the correct position in the first move)
        if(adversaire->getTypePiece() == 'P' && adversaire->getFirstMove() && (tmpCoord.y == 3 || tmpCoord.y == 4))
        {
            // La pièce du joueur se trouve au dessus de la pièce prise
            // The player's piece is above the piece taken
            joueur = ech[posAct.x][posAct.y];

            // On remet la pièce du joueur a sa position initiale et celle de l'adversaire a la place du joueur
            // The player's piece is put back to its initial position and the opponent piece is put to the player's position
            ech[tmpCoord.x][tmpCoord.y] = adversaire;
            ech[posPrec.x][posPrec.y] = joueur;

            // Cas de la mise en échec du roi adverse annulée par l'annulation du mouvement
            // Si on est dans une situation d'échec pour l'adversaire, on appelle la fonction verifierEchec après l'annulation du mouvement
            // pour changer le booléen d'échec m_echec
            // Case of a check on the opponent's king cancelled by the move cancellation
            // If we are in a check situation, we call the function verifierEcher after the cancellation to change the check boolean m_echec
            if(m_echec)
                verifierEchec(player);

            ech[posPrec.x][posPrec.y]->setIrrlichtPos(posPrec);
            ech[tmpCoord.x][tmpCoord.y]->setIrrlichtPos(tmpCoord);

            // Supprime le dernier élément stocké
            // Delete the last stored element
            m_res_j1.pop_back();

            return true;
        }
        else
        {
            // On obtient la pièce actuelle a la position de la pièce a remettre dans le jeu (pièce du joueur)
            // Get the current piece at the position of the piece we need to put back on the board (players piece)
            joueur = ech[tmpCoord.x][tmpCoord.y];
        }


        // On remet la pièce du joueur a sa position initiale et celle de l'adversaire a la place du joueur
        // We put back the players piece and put the opponents piece at the players position
        ech[posPrec.x][posPrec.y] = joueur;

        ech[tmpCoord.x][tmpCoord.y] = NULL;
        ech[tmpCoord.x][tmpCoord.y] = adversaire;

        // Cas de la mise en échec du roi adverse annulée par l'annulation du mouvement
        // Si on est dans une situation d'échec pour l'adversaire, on appelle la fonction verifierEchec après l'annulation du mouvement
        // pour changer le booléen d'échec m_echec
        // Case of a check on the opponent's king cancelled by the move cancellation
        // If we are in a check situation, we call the function verifierEcher after the cancellation to change the check boolean m_echec
        if(m_echec)
            verifierEchec(player);

        ech[posPrec.x][posPrec.y]->setIrrlichtPos(posPrec);
        ech[tmpCoord.x][tmpCoord.y]->setIrrlichtPos(tmpCoord);

        // Supprime le dernier élément stocké
        // Delete last stored element
        m_res_j1.pop_back();

    }
    else if(player == 2)
    {
        // On teste si la réserve est vide
        // Test if the stock is empty
        if(m_res_j2.empty())
        {
            cout << "Empty stock" << endl;
            return false;
        }

        // Retourne une référence du dernier élément stocké
        // Get reference to last element stored
        adversaire = m_res_j2.back();

        // Retourne les coordonnées de la pièce prise
        // Get the coordinates of the piece taken
        tmpCoord = adversaire->getPosRes();


        // Cas d'une prise en passant (si la pièce prise était un pion et qu'elle se trouvait sur la bonne position lors de son premier mouvement)
        // Case of an en passant move (if the piece was a pawn and was on the correct position in the first move)
        if(adversaire->getTypePiece() == 'P' && adversaire->getFirstMove() && (tmpCoord.y == 3 || tmpCoord.y == 4))
        {
            // La pièce du joueur se trouve au dessus de la pièce prise
            // The player's piece is above the piece taken
            joueur = ech[posAct.x][posAct.y];

            // On remet la pièce du joueur a sa position initiale et celle de l'adversaire a la place du joueur
            // The player's piece is put back to its initial position and the opponent piece is put to the player's position
            ech[tmpCoord.x][tmpCoord.y] = adversaire;
            ech[posPrec.x][posPrec.y] = joueur;

            // Cas de la mise en échec du roi adverse annulée par l'annulation du mouvement
            // Si on est dans une situation d'échec pour l'adversaire, on appelle la fonction verifierEchec après l'annulation du mouvement
            // pour changer le booléen d'échec m_echec
            // Case of a check on the opponent's king cancelled by the move cancellation
            // If we are in a check situation, we call the function verifierEcher after the cancellation to change the check boolean m_echec
            if(m_echec)
                verifierEchec(player);

            ech[posPrec.x][posPrec.y]->setIrrlichtPos(posPrec);
            ech[tmpCoord.x][tmpCoord.y]->setIrrlichtPos(tmpCoord);

            // Supprime le dernier élément stocké
            // Delete last stored element
            m_res_j2.pop_back();

            return true;
        }
        else
        {
            // On obtient la pièce actuelle a la position de la pièce a remettre dans le jeu (pièce du joueur)
            // Get the current piece at the position of the piece we need to put back on the board (players piece)
            joueur = ech[tmpCoord.x][tmpCoord.y];
        }


        // On remet la pièce du joueur a sa position initiale et celle de l'adversaire a la place du joueur
        // We put back the players piece and put the opponents piece at the players position
        ech[posPrec.x][posPrec.y] = joueur;

        ech[tmpCoord.x][tmpCoord.y] = NULL;
        ech[tmpCoord.x][tmpCoord.y] = adversaire;

        // Cas de la mise en échec du roi adverse annulée par l'annulation du mouvement
        // Si on est dans une situation d'échec pour l'adversaire, on appelle la fonction verifierEchec après l'annulation du mouvement
        // pour changer le booléen d'échec m_echec
        // Case of a check on the opponent's king cancelled by the move cancellation
        // If we are in a check situation, we call the function verifierEcher after the cancellation to change the check boolean m_echec
        if(m_echec)
            verifierEchec(player);

        ech[posPrec.x][posPrec.y]->setIrrlichtPos(posPrec);
        ech[tmpCoord.x][tmpCoord.y]->setIrrlichtPos(tmpCoord);

        // Supprime le dernier élément stocké
        // Delete the last stored element
        m_res_j2.pop_back();
    }
    else
    {
        // Erreur joueur
        // Error player
        cout << "Error : unknown player" << endl;
        return false;
    }
}


// Fonction de promotion d'un pion
// Function promoting a pawn
void Echiquier::upgradePion(char type, irr::video::IVideoDriver* driver)
{
    // On supprime le pion et on le remplace par une autre pièce
    // Variable temporaire indiquant le joueur qui possède le pion
    // Delete pawn and replace it
    // Temporary variable containing the player who owns the pawn
    unsigned int tmpAdv = ech[m_promoted_pion.x][m_promoted_pion.y]->getAdv();

    ech[m_promoted_pion.x][m_promoted_pion.y] = NULL;

    switch(type)
    {
        case 'd':
            Dame *D;
            D = new Dame(driver,tmpAdv);

            ech[m_promoted_pion.x][m_promoted_pion.y] = D;
            ech[m_promoted_pion.x][m_promoted_pion.y]->setIrrlichtPos(m_promoted_pion);

        break;
        case 't':
            Tour *T;
            T = new Tour(driver,tmpAdv);

            ech[m_promoted_pion.x][m_promoted_pion.y] = T;
            ech[m_promoted_pion.x][m_promoted_pion.y]->setIrrlichtPos(m_promoted_pion);

        break;
        case 'f':
            Fou *F;
            F = new Fou(driver,tmpAdv);

            ech[m_promoted_pion.x][m_promoted_pion.y] = F;
            ech[m_promoted_pion.x][m_promoted_pion.y]->setIrrlichtPos(m_promoted_pion);

        break;
        case 'c':
            Cavalier *C;
            C = new Cavalier(driver,tmpAdv);

            ech[m_promoted_pion.x][m_promoted_pion.y] = C;
            ech[m_promoted_pion.x][m_promoted_pion.y]->setIrrlichtPos(m_promoted_pion);

        break;
        default :
        break;
    }
}


// Fonction checkDepl : appel a checkPos dans la classe Piece, qui vérifie avec le tableau de position courant
// (Indique la position de l'ensemble des pièces des joueurs, sans révéler leur type)
// que la pièce peut bouger a cet emplacement (déplacement correct par rapport au type de pièce, pas de pièces sur la trajectoire)
// checkDepl est appelée depuis la fonction deplPiece, checkEchec ou checkSortieEchec, et indirectement depuis les fonctions checkEchecMvt et checkEchecAdv.
// checkDepl function : call checkPos in the piece class, who checks with the current position array
// (Shows the position of all the pieces but not their type)
// that the piece can move to the position (checks the type of piece, and if there's pieces on the way)
// checkDepl is called from the deplPiece, checkEchec or checkSortieEchec function and indirectly from the checkEchecMvt and checkEchecAdv functions
bool Echiquier::checkDepl(Coord & dep, Coord & arr)
{
    // Revérification de la validité des coordonnées (cas appel a la fonction depuis checkSortieEchec)
    // Cas standards uniquement
    // Cas ou les coordonnées de départ et d'arrivée sont identiques
    // Check coordinates again (call from checkSortieEchec case)
    // Standard cases
    // Identical coordinates case
    if(dep.x == arr.x && dep.y == arr.y)
    {
        cout << "Starting and arrival coordinates are identical" << endl;
        return false;
    }

    // Cas ou la pièce visée appartient au possesseur de la pièce déplacée : impossible de déplacer la pièce
    // Opponent own the piece case
    if(ech[arr.x][arr.y] != NULL && (ech[arr.x][arr.y]->getAdv() == ech[dep.x][dep.y]->getAdv()))
    {
        cout << "You cannot move a piece if the opponent owns it" << endl;
        return false;
    }


    // Tableau représentant les possésseurs des pièces sur l'échiquier
    // Array with the owner of the pieces on the chessboard
    unsigned int position[8][8];

    for( int j = 0; j <= 7; j++ ){
        for( int i = 0; i <= 7; i++ ){
            if(ech[i][j] == NULL)
            {
                position[i][j] = 0;
            }
            else
            {
                position[i][j] = ech[i][j]->getAdv();
            }
        }
    }

    // Appel a la fonction de vérification de déplacement de la pièce
    // Call check piece movement function
    return ech[dep.x][dep.y]->checkPos(dep, arr, position);
}


// Fonction de détection du cas de promotion
// Promotion detection function
bool Echiquier::checkPromotion(Coord & posArr)
{
    // Si les coordonnées finales sont sur la dernière rangée de l'échiquier : cas spécial => promotion du pion
    // If final coordinates are on the last row o the chessboard, it's a promotion case
    if(posArr.y == 0 || posArr.y == 7)
        return true;
    else
        return false;
}

// Fonction qui vérifie si un roque est possible (voir appel a la fonction dans deplPiece)
// Function checking castling possibilities (see call to the function in deplPiece)
bool Echiquier::checkRoque(Coord & dep, Coord & arr, unsigned int &xTour)
{
    // Regarde si le roi est a sa position initiale et si le mouvement se fait sur une seule ligne
    // On renvoie false si ce n'est pas le cas
    // Check if the king is in the initial position and if the move is on one line only
    // Return false if it's not the case
    if(dep.x != 4 || (dep.y != 0 && dep.y != 7) || dep.y != arr.y)
        return false;

    // Regarde si le roi a déja fait un mouvement avant le roque ; si c'est le cas, le roque est impossible
    // Check if the king has moved before : if true, then castling is impossible
    if(!ech[dep.x][dep.y]->getPosInit())
        return false;



    unsigned int i,j;

    // Regarde si une tour se trouve a proximité des coordonnées d'arrivée du roi
    // (Deux cas : on avance sur l'axe des x sur l'échiquier, ou bien on recule)
    // Cas avancée sur l'axe des x
    // Check if a rook is near the end position of the king
    // (Two cases : going forward or backward the x axis)
    // Case forward
    if(dep.x < arr.x)
    {
            // On teste la case adjacente (uniquement petit roque dans le cas ou on avance sur l'axe des x)
            // Si on ne dépasse pas du plateau
            // We check nearby square (small castling only)
            // If we're not outside the chessboard
            if(arr.x+1 <= 7)
            {
                // Si il y a une tour aux coordonnées et que celle ci appartient au joueur
                // If there's a rook at the coordinates and the current player owns it
                if(ech[arr.x+1][arr.y] != NULL && ech[arr.x+1][arr.y]->getTypePiece() == 'T'
                    && ech[arr.x+1][arr.y]->getAdv() == ech[dep.x][dep.y]->getAdv())
                {
                    // Si la tour n'est pas a ses coordonnées de départ ou qu'elle a déja fait un mouvement, on retourne false
                    // Return false if the rook is not at its starting position or if it has already moved
                    if(arr.x+1 != 7 || !ech[arr.x+1][arr.y]->getPosInit())
                        return false;
                }
            }
            else
                return false;


        // On teste pour voir si toutes les cases sont vides entre la tour et le roi, et on retourne faux si ce n'est pas le cas
        // Test the squares between king and rook, return false if it's not the case
        j = 1;

        while(dep.x+j < arr.x+1)
        {
            if(ech[dep.x+j][dep.y] != NULL)
                return false;

            j++;
        }


        // On teste pour voir si une pièce adverse peut atteindre le roi, la tour, ou une case entre les deux
        // Coordonnées temporaires de la case visée et de la pièce de l'adversaire
        // Check if an enemy piece can reach the king, the tower or a square between the two
        // Temporray coordinates for the square and the enemy piece
        Coord tmpDep, tmpAdv;
        tmpDep.x = dep.x;
        tmpDep.y = dep.y;

        // Parcours des cases entre les deux pièces, incluant le roi et la tour
        // Going through the squares
        j = 0;

        while(dep.x+j <= arr.x+1)
        {
            // Mise a jour des coordonnées temporaires de la case visée
            // Update temporary coordinates
            tmpDep.x = dep.x+j;


            // Parcours de l'échiquier
            // Processing the chessboard
             for( unsigned int l = 0; l <= 7; l++ ){
                for( unsigned int k = 0; k <= 7; k++ ){

                    // Si la pièce existe et qu'elle appartient au joueur adverse
                    // If piece exist and is an ennemy piece
                    if(ech[k][l] != NULL && ech[k][l]->getAdv() != ech[dep.x][dep.y]->getAdv())
                    {
                        tmpAdv.x = k;
                        tmpAdv.y = l;

                        // On teste si la pièce adverse peut atteindre la case, si c'est le cas, on retourne false
                        // Check if the piece can reach the square, return false if not
                        if(checkDepl(tmpAdv, tmpDep))
                        {
                            return false;
                        }
                    }

                }
              }

            // Passage a la case suivante
            // Next square
            j++;
        }

        // Si toutes les conditions ci dessus sont valides, alors on peut effectuer le roque
        // On renseigne la postion en x de la tour et on renvoie true
        // If all the condition above are true, we can do the castling
        // Set x position of the rook and return true
        xTour = arr.x+1;

        return true;
    }


    // Cas recul sur l'axe des x
    if(dep.x > arr.x)
    {
            // On teste la case située a x-2 (uniquement grand roque dans le cas ou on avance sur l'axe des x)
            // Si on ne dépasse pas du plateau
            if(arr.x-2 <= 7)
            {
                // Si il y a une tour aux coordonnées et que celle ci appartient au joueur
                if(ech[arr.x-2][arr.y] != NULL && ech[arr.x-2][arr.y]->getTypePiece() == 'T'
                    && ech[arr.x-2][arr.y]->getAdv() == ech[dep.x][dep.y]->getAdv())
                {
                    // Si la tour n'est pas a ses coordonnées de départ ou qu'elle a déja fait un mouvement, on retourne false
                    if(arr.x-2 != 0 || !ech[arr.x-2][arr.y]->getPosInit())
                        return false;
                }
            }
            else
                return false;


        // On teste pour voir si toutes les cases sont vides entre la tour et le roi, et on retourne faux si ce n'est pas le cas
        j = 1;


        while(dep.x-j > arr.x-2)
        {
            if(ech[dep.x-j][dep.y] != NULL)
                return false;

            j++;
        }

        // On teste pour voir si une pièce adverse peut atteindre le roi, la tour, ou une case entre les deux
        // Coordonnées temporaires de la case visée et de la pièce de l'adversaire
        Coord tmpDep, tmpAdv;
        tmpDep.x = dep.x;
        tmpDep.y = dep.y;

        // Parcours des cases entre les deux pièces, incluant le roi et la tour
        j = 0;


        while(dep.x-j >= arr.x-2)
        {
            // Mise a jour des coordonnées temporaires de la case visée
            tmpDep.x = dep.x-j;

            // Parcours de l'échiquier
             for( unsigned int l = 0; l <= 7; l++ ){
                for( unsigned int k = 0; k <= 7; k++ ){

                    // Si la pièce existe et qu'elle appartient au joueur adverse
                    if(ech[k][l] != NULL && ech[k][l]->getAdv() != ech[dep.x][dep.y]->getAdv())
                    {
                        tmpAdv.x = k;
                        tmpAdv.y = l;

                        // On teste si la pièce adverse peut atteindre la case, si c'est le cas, on retourne false
                        if(checkDepl(tmpAdv, tmpDep))
                            return false;
                    }

                }
              }

            // Passage a la case suivante
            j++;

            // Si dep.x-j < 0, on sort de la boucle (coordonnées en unsigned int, d'ou bug)
            if(j > dep.x)
                break;
        }

        // Si toutes les conditions ci dessus sont valides, alors on peut effectuer le roque
        // On renseigne la postion en x de la tour et on renvoie true
        xTour = arr.x-2;

        return true;
    }
}


// Fonction renvoyant le booléen indiquant la promotion d'un pion
// Function returning boolean for the pawn promotion
bool Echiquier::getPromotionPion()
{
    return m_promotion_pion;
}
// Fonction remettant à false le booléen indiquant la promotion d'un pion
// Function setting the pawn promotion boolean to false
bool Echiquier::razPromotionPion()
{
    m_promotion_pion = false;
}
// Fonction remettant à zero les coordonnées du pion promu
// Function resetting the coordinates of the promoted pawn
void Echiquier::razPromotedPion()
{
    m_promoted_pion.x = 0;
    m_promoted_pion.y = 0;
}


// Fonction renvoyant la taille de la réserve d'un joueur (utilisation dans la gestion des scores, dans contextManager)
// Function returning the size of a player's stock (used in score management, see contextManager)
unsigned int Echiquier::getSizeRes(unsigned int joueur)
{
    if(joueur == 1)
        return m_res_j1.size();
    else if(joueur == 2)
        return m_res_j2.size();
    // Si erreur dans le numéro de joueur
    // If error in the player's number
    else
        return -1;
}


// Getters booléen d'échec et mat et texte d'échec et mat (voir ContextManager)
// Getters checkmate boolean and checkmate text (see contextManager)
bool Echiquier::getEchecMat()
{
    return m_echec_mat;
}
std::string Echiquier::getEchecMatTxt()
{
    return m_echec_mat_texte;
}


// Regarde si le roi est en échec
// Check if the king is in a check state
bool Echiquier::checkEchec(Coord & pos)
{
    // Booléen pour savoir si la position possible testée est prenable par l'adversaire
    // Boolean used to see if the possible position tested is reachable by the enemy
    bool boolPos = false;


    // Si la pièce sélectionnée n'est pas le roi, erreur
    // (utile si la fonction est appelée en dehors de la fonction checkDepl : cas des pièces cloutées)
    // If the selected piece is not the king : error
    // (useful if the function is called outside the checkDepl function : case of the nailed pieces)
    if(ech[pos.x][pos.y]->getTypePiece() != 'R')
    {
        cout << "Selected piece is not the king" << endl;
        return false;
    }
    else
    {
       Coord dep;
       unsigned int i,j;

         // Parcours de l'échiquier
         // Going through the chessboard
         for( j = 0; j <= 7; j++ ){
            for( i = 0; i <= 7; i++ ){

                // Si la pièce existe et qu'elle appartient au joueur adverse
                // If piece exist and it belongs to the opponent
                if(ech[i][j] != NULL && ech[i][j]->getAdv() != ech[pos.x][pos.y]->getAdv())
                {
                    dep.x = i;
                    dep.y = j;

                    // On teste si la pièce adverse peut atteindre la position du roi
                    // Testing if the piece can reach the kings position
                    if(checkDepl(dep, pos))
                    {
                        boolPos = true;
                    }
                }

            }
          }
    }

    return boolPos;
}


// Regarde si le déplacement effectué par le joueur met le roi du joueur en échec
// Check if a players move put it's king in check position
bool Echiquier::checkEchecMvt(unsigned int advMvt)
{
    int i,j;
    Coord tmp;

    if(advMvt != 1 && advMvt != 2)
    {
        // Erreur joueur
        // Player error
        cout << "Error : unknown player" << endl;
        return false;
    }

    // On cherche le roi du joueur qui possède la pièce déplacée
    // Searching for the king of the player who owns the moved piece
    for( i = 0; i <= 7; i++ ){
        for( j = 0; j <= 7; j++ ){
            // Si la pièce existe et si il s'agit du roi
            // If the piece exist and it's the king
            if(ech[i][j] != NULL && ech[i][j]->getTypePiece() == 'R' && ech[i][j]->getAdv() == advMvt)
            {
                // On regarde si le roi est mis en échec et on renvoie le résultat
                // See if the king is in check position and return the results
                tmp.x = i;
                tmp.y = j;

                return checkEchec(tmp);
            }
        }
    }

    cout << "Error : could not find king" << endl;
    return false;
}


// Regarde si on peut sortir d'une position d'échec
// Check if we can cancel a check state
int Echiquier::checkSortieEchec(Coord & dep, Coord & arr, unsigned int joueur)
{
    unsigned int i,j;

    // Coordonnées temporaires de parcours des déplacements de sortie d'échec possibles
    // Temporary coordinates used to go through the possible moves
    Coord tmpJ;
    Coord tmpAdv;

    // Variable piece temporaire
    // Temporary piece variable
    Piece* tmp;

    // Integer renvoyé par la fonction
    // Mis à CHECKMATE si il s'agit d'un échec et mat, a CHECK si il s'agit d'un simple échec, et a NO_CHECK si pas d'échec
    // Integer returned by the function
    // Set to CHECKMATE, CHECK, or NO_CHECK
    int mat = CHECKMATE;


    // Gestion des mouvements du roi
    // Coordinates for the kings moves
    Coord tmpRoi;


    // On séléctionne toutes les positions possibles et on teste pour voir si bouger le roi a cet emplacement empêche l'échec et mat
    // Select all the possible positions and test to see if the move the king to the position prevent the checkmate
    for( j = 0; j <= 7; j++ ){
        for( i = 0; i <= 7; i++ ){

            tmpRoi.x = i;
            tmpRoi.y = j;

                // Si on peut se déplacer sur la position
                // If we can move to the position
                if(checkDepl(arr, tmpRoi))
                {
                    // On simule sa position sur le tableau des pièces utilisé dans la fonction checkPos
                    // Le roi est déplacé sur le tableau des positions
                    // Variable temporaire pour remettre en place le roi après simulation
                    // Simulate position on the piece array used by the checkPos function
                    // The king is moved on the position array
                    // Temporary variable to set the king to the original position after simulation
                    tmp = ech[i][j];

                    ech[i][j] = ech[arr.x][arr.y];
                    ech[arr.x][arr.y] = NULL;


                    // Si le déplacement compromet la possibilité d'échec a cause de la nouvelle position du roi
                    // If the move prevent the checkmate state
                    if(!checkEchec(tmpRoi))
                    {
                        // On range les coordonnées de départ et d'arrivée dans un vector
                        // Store start and arrival coordinate in a vector
                        m_res_dep.push_back(arr);
                        m_res_arr.push_back(tmpRoi);

                        cout << "King move prevents checkmate" << endl;
                        mat = CHECK;
                    }

                    // On annule le déplacement du roi
                    // Cancel king move
                    ech[arr.x][arr.y] = ech[i][j];
                    ech[i][j] = tmp;
                }
        }
    }



    // Parcours de l'échiquier
    // Go through the chessboard
    for( j = 0; j <= 7; j++ ){
        for( i = 0; i <= 7; i++ ){

            // Pour toutes les pièces du joueur (sauf le roi)
            // For all the player's piece (except the king)
            if(ech[i][j] != NULL && ech[i][j]->getAdv() == joueur && ech[i][j]->getTypePiece() != 'R')
            {
                tmpJ.x = i;
                tmpJ.y = j;

                // Si une pièce peut prendre la pièce de l'adversaire menacant le roi du joueur :
                // Pas d'échec
                // If a piece can take the piece threatening the player's king
                // No check
                if(checkDepl(tmpJ, dep))
                {

                    tmp = ech[i][j];

                    ech[i][j] = ech[dep.x][dep.y];
                    ech[dep.x][dep.y] = NULL;


                    if(!checkEchecMvt(joueur))
                    {
                        // On range les coordonnées de départ et d'arrivée dans un vector
                        // Store starting and arrival coordinates in a vector
                        m_res_dep.push_back(tmpJ);
                        m_res_arr.push_back(dep);

                        cout << "Piece move prevents checkmate" << endl;
                        mat = CHECK;
                    }

                    ech[dep.x][dep.y] = ech[i][j];
                    ech[i][j] = tmp;

                }

                // Ou si une pièce peut s'interposer entre le roi et la pièce de l'adversaire
                // Pas d'échec et mat
                // Le roi ne peut "s'interposer" véritablement : son cas est traité a part.
                // Parcours de tous les déplacements possibles pour toutes les pièces du joueur
                // Or if a piece can move between the king and the opponent's piece
                // No checkmate
                // Processing all the possible moves for all of the player's pieces
                for( unsigned int k = 0; k <= 7; k++ ){
                    for( unsigned int l = 0; l <= 7; l++ ){
                        tmpAdv.x = l;
                        tmpAdv.y = k;

                        // Si la pièce du joueur peut être bougée a la position
                        // If the player's piece can be moved to the position
                        if(checkDepl(tmpJ, tmpAdv))
                        {
                            // On simule sa position sur le tableau des pièces utilisé dans la fonction checkPos
                            // La pièce est déplacée sur le tableau des positions
                            // We simulate its position in the array of the pieces used in the checkPos function
                            // The piece is moved in the array of the positions
                            tmp = ech[l][k];

                            ech[l][k] = ech[i][j];
                            ech[i][j] = NULL;


                            // Si le mouvement de la pièce empêche la prise du roi, pas d'échec et mat
                            // If piece movement prevents checkmate, no checkmate
                            if(!checkEchecMvt(joueur))
                            {
                                // On range les coordonnées de départ et d'arrivée dans un vector
                                // Store the starting and arrival coordinates in a vector
                                m_res_dep.push_back(tmpJ);
                                m_res_arr.push_back(tmpAdv);

                                cout << "Piece moving in front of the king prevent checkmate" << endl;
                                mat = CHECK;

                            }

                            // On annule ensuite le déplacement de la pièce
                            // Cancel piece movement
                            ech[i][j] = ech[l][k];
                            ech[l][k] = tmp;

                        }

                    }
                }
            }
        }
    }


    // Retourne CHECKMATE ou CHECK
    // Return  CHECKMATE or CHECK
    return mat;
}



// Regarde si le déplacement du joueur courant met le roi de l'adversaire en situation d'échec et mat ou juste d'échec
// See if the move of the current player puts the opponent's king in a checkmate situation or just a check situation
int Echiquier::checkEchecAdv(unsigned int adv)
{
    unsigned int i,j;

    // Coordonnées de déplacement de la pièce mettant en échec le roi
    // Les coordonnées d'arrivée de la pièce correspondent au roi
    // Starting coordinates for the piece who threatens the king
    // Arrival coordinates corresponds to the king's position
    Coord dep;
    Coord arr;

    // Coordonnées temporaires correspondant au roi et aux pièces joueur (lors du parcours du tableau)
    // Temporary coordinates for the king and the player's pieces (during the processing of the array)
    Coord tmpRoi;
    Coord tmpPieceJ;

    // Tableau représentant les possésseurs des pièces sur l'échiquier
    // Array containing the owners of the pieces on the chessboard
    unsigned int position[8][8];

    for( j = 0; j <= 7; j++ ){
        for( i = 0; i <= 7; i++ ){
            if(ech[i][j] == NULL)
            {
                position[i][j] = 0;
            }
            else
            {
                position[i][j] = ech[i][j]->getAdv();
            }
        }
    }


    // Cas adversaire inconnu
    // Case of an unknown enemy
    if(adv != 1 && adv != 2)
    {
        // Erreur adversaire
        // Error opponent
        cout << "Error : unknown opponent checkmate case " << adv << endl;
        return ERR_CHECK;
    }


    // On cherche le roi de l'adversaire (qui ne possède pas la pièce déplacée précédemment)
    // Searching for the opponents king (who does not own the previously moved piece)
    for( j = 0; j <= 7; j++ ){
        for( i = 0; i <= 7; i++ ){
            // Si la pièce existe et si il s'agit du roi de l'adversaire
            // If the piece exists and if it's the opponent's king
            if(ech[i][j] != NULL && ech[i][j]->getTypePiece() == 'R' && ech[i][j]->getAdv() == adv)
            {
                // On stocke ses coordonnées dans des coordonnées temporaires
                // Store it's coordinates in temporary coordinates
                tmpRoi.x = i;
                tmpRoi.y = j;
            }
        }
    }


    // Integer renvoyé par la fonction
    // Mis à CHECKMATE si il s'agit d'un échec et mat, a CHECK si il s'agit d'un simple échec, et a NO_CHECK si pas d'échec
    // Integer returned by the function
    int mat = NO_CHECK;


     // Parcours de l'échiquier
     // Processing the chessboard
    for( i = 0; i <= 7; i++ ){
        for( j = 0; j <= 7; j++ ){
            // Si la pièce existe et qu'elle appartient au joueur courant
            // If piece exists and is owned by the current player
            if(ech[i][j] != NULL && ech[i][j]->getAdv() != adv)
            {
                tmpPieceJ.x = i;
                tmpPieceJ.y = j;

                // On teste si la pièce du joueur peut atteindre la position du roi
                // Test if the player's piece can reach the king's position
                if(ech[i][j]->checkPos(tmpPieceJ, tmpRoi, position))
                {
                    // On teste pour voir si l'adversaire peut sortir de la position d'échec
                    // Test if the enemy can cancel the chek state
                    mat = checkSortieEchec(tmpPieceJ, tmpRoi, adv);
                }
            }
      }
    }

    // Si on a un cas d'échec ou d'échec et mat
    // If check or checkmate case
    if(mat == CHECK || mat == CHECKMATE)
    {
        // On stocke les coordonnées du roi en situation d'échec
        // Store coordinates of the king in a check situation
        m_roi_echec = tmpRoi;
        return mat;
    }


    cout << "No piece puts the king a check position" << endl;
    // Cas ou pas de pièces ne menacent le roi du joueur
    // Case of the opponent's king not being in a check or checkmate state
    mat = NO_CHECK;

    return mat;
}


// Appel a checkEchecAdv et interprétation du résultat
// Call checkEchecAdv and results interpretation
void Echiquier::verifierEchec(unsigned int adv)
{
    int res = checkEchecAdv(adv);


    // Cas pas d'échec ou erreur a l'échec
    // Case no check or error on check
    if(res == NO_CHECK || res == ERR_CHECK)
    {
        cout << "No check state" << endl;
        // Pas de situation d'échec : booléen a faux
        // No chess situation : boolean set to false
        if(m_echec)
        {
            ech[m_roi_echec.x][m_roi_echec.y]->setStandardColor();
            m_echec = false;
        }
        else
            m_echec = false;
    }

    // Cas de l'échec simple
    // Case of a simple check situation
    else if(res == CHECK)
    {
        cout << "Simple check" << endl;

        // On met le booléen d'échec a true
        // Put the check boolean to true
        m_echec = true;

        // Le roi est marqué comme en échec (coloré en orange)
        // King is colored in orange (in a check state)
        ech[m_roi_echec.x][m_roi_echec.y]->setEchecColor();
    }

    // Cas de l'échec et mat
    // Case of the checkmate situation
    else if(res == CHECKMATE)
    {
        // Le roi est marqué comme en échec et mat (coloré en rouge)
        // King is colored in red (in a checkmate state)
        ech[m_roi_echec.x][m_roi_echec.y]->setEchecMatColor();

        // Numéro du joueur gagnant
        // Number of the winning player
        int joueur;

        if(adv == 1)
            joueur = 2;
        else
            joueur = 1;

        // Création d'un std::string stream
        // Creation of an std::string stream
        ostringstream oss;

        std::string matTxt = "Checkmate : player ";
        // Rajout du texte et du numéro de l'adversaire dans le stream
        // Get text and player number in stream
        oss << matTxt << joueur << " wins";


        // Booléen d'échec et mat à true (utilisation dans ContexteManager)
        // Checkmate boolean (use in ContexteManager)
        m_echec_mat = true;

        // On régle le texte à afficher
        // Set text to dislay
        m_echec_mat_texte = oss.str();
    }

}


// Fonction qui filtre les déplacement si le roi est en situation d'échec
// Function restricting movements if the king is in a check state (the player can not put himself in a checkmate state)
bool Echiquier::lock(Coord & dep, Coord & arr, unsigned int adv)
{
    unsigned int i;
    unsigned int size = m_res_dep.size();

    if(m_res_dep.size() != m_res_arr.size())
    {
        cout << "Error check state position " << endl;
        return true;
    }

    cout << "List of moves cancelling check state (x, y) :" << endl;
    for ( i = 0; i < size; ++i )
    {
        // On compare les déplacements enregistrés comme annulant la situation d'échec et le déplacement demandé
        // Si un déplacement enregistré correspond au déplacement demandé, le déplacement est autorisé,
        // et les déplacements enregistrés sont supprimés
        // Compare moves cancelling check state and players move
        // If the players move is a cancelling check state move, move is authorized
        // and the cancelling check state moves are deleted
        cout << "Start : " << (char)(m_res_dep.at(i).x + 97) << "|" << 8 - m_res_dep.at(i).y << "  " << "Arrival : " << (char)(m_res_arr.at(i).x + 97) << "|" << 8 - m_res_arr.at(i).y << endl;

        if(m_res_dep.at(i).x == dep.x && m_res_dep.at(i).y == dep.y &&
            m_res_arr.at(i).x == arr.x && m_res_arr.at(i).y == arr.y)
        {
            // Si le déplacement permet de sortir le roi de la position d'échec
            // If the move can cancel the check state
            if(checkEchecMvt(adv))
            {
                // On vide les vectors de déplacements enregistrés
                // Clear vectors containing the saved moves
                m_res_dep.clear();
                m_res_arr.clear();

                return true;
            }
        }
    }

    return false;
}


// Vérifie que le déplacement d'une pièce est correct et déplace ou non la pièce
// Check the movement of a piece and execute it if it's a correct move
bool Echiquier::deplPiece(Coord & dep, Coord & arr, unsigned int adv)
{
    // Variable temporaire utilisée pour régler la place des pièces sur l'échiquier graphique
    // Temporary variable used to set the position of the pieces on the graphical chessboard
    Coord graphicalPos;

    // Variable temporaire utilisée dans le cas d'une prise en passant
    //(pour que le déplacement ne soit pas compté comme sans prise de pièce lors de l'appel à revPiece)
    // Temporary variable for the case of an en passant move
    // (so that the move is still a move with taken pieces)
    bool prisePassant = false;

    // Distance de déplacement (cas premier déplacement du pion)
    // Moving distance (case of a first move with a pawn)
    int distanceDeplPion;

    // On vérifie que les coordonnées données sont présentes sur l'échiquier
    // Verify that the coordinates are on the chessboard
    if(verifierSet(dep, arr))
    {

        // Si la pièce existe a la position
        // If the piece exist at the position
        if(ech[dep.x][dep.y] != NULL)
        {
            // Cas spécifique du roi en situation d'échec : il est recoloré automatiquement tant qu'on est dans une situation d'échec
            // Voir appel à la fonction lock, plus bas
            // Specific case of the king a check state : automatically recolored while we're in a check state
            // See call to lock function below
            if(m_echec)
                ech[m_roi_echec.x][m_roi_echec.y]->setEchecColor();


            // Cas ou la pièce à déplacer n'appartient pas au joueur
            // Case of the piece not belonging to the player
            if(ech[dep.x][dep.y]->getAdv() != adv)
            {
                cout << "The piece does not belong to the player" << endl;

                return false;
            }

            // Cas ou les coordonnées de départ et d'arrivée sont identiques
            // Case of the starting and arrival coordinates being identical
            if(dep.x == arr.x && dep.y == arr.y)
            {
                cout << "Starting and arrival coordinates are identical" << endl;

                return false;
            }

            // Cas ou la pièce visée appartient au possesseur de la pièce déplacée : impossible de déplacer la pièce
            // Case of a piece being taken belonging to the owner of the moved piece
            if(ech[arr.x][arr.y] != NULL && (ech[arr.x][arr.y]->getAdv() == adv && ech[dep.x][dep.y]->getAdv() == adv))
            {
                cout << "The player can not take its own pieces" << endl;

                return false;
            }


            /// Cas du roi d'un des joueurs en situation d'échec (seuls les déplacements le faisant sortir de sa position d'échec sont autorisés)
            /// Case of a king being in a check state (the movements are authorized only if the cancel the check state)
            if(m_echec)
            {
                // Si le déplacement annule la situation d'échec, le déplacement est autorisé
                // If the movement cancel the check situation, it is authorized
                if(lock(dep, arr, adv))
                {
                    // On sort de la situation d'échec
                    // Cancel the check state
                    m_echec = false;
                    // Le roi en position d'échec n'est plus coloré
                    // The king is not colored anymore
                    ech[m_roi_echec.x][m_roi_echec.y]->setStandardColor();

                    // RAZ coordonnées du roi en échec
                    // Reset coordinates of the check state king
                    m_roi_echec.x = 0;
                    m_roi_echec.y = 0;
                }
                // Sinon, le déplacement est interdit
                // Else, the move is forbidden
                else
                {
                    cout << "Forbidden move (checkmate)" << endl;

                    return false;
                }
            }


            /// Cas case d'arrivée vide
            // Si la case visée est vide, on met la pièce dans la case vide
            /// Case of the arrival square being empty
            // The piece is put on the square
            if(ech[arr.x][arr.y] == NULL)
            {
                // Regarde si le déplacement est impossible
                // Check if the move is impossible
                if(!checkDepl(dep, arr))
                {
                    // Coordonnées temporaires pour l'execution de abs dans checkRoque (les coordonnées sont en unsigned int, donc bug si on obtient des nombres négatifs)
                    // Temp coordinates for the abs execution in checkRoque (unsigned int, so no negative numbers)
                    int x = arr.x;
                    int y = dep.x;

                    /// Cas spécial de la prise en passant : le déplacement est possible dans ce cas
                    /// Si la pièce a déplacer est un pion et effectue un déplacement de prise de pièce
                    /// Special case with an en passant move : move is possible
                    /// If the piece to move is a pawn and does a move to take a piece
                    if(ech[dep.x][dep.y]->getTypePiece() == 'P' && (arr.x == dep.x-1 || arr.x == dep.x+1) && (arr.y == dep.y-1 || arr.y == dep.y+1))
                    {
                        // Coordonnée temporaires
                        // Temporary coordinates
                        Coord deplP = arr;

                        deplP.y = dep.y;

                        // On regarde si la pièce en dessous du pion est un pion et si il en est a son premier mouvement
                        // Check if the piece below the pawn is a pawn and if it is its first move
                        if(ech[deplP.x][deplP.y] != NULL && ech[deplP.x][deplP.y]->getTypePiece() == 'P' && ech[deplP.x][deplP.y]->getFirstMove())
                        {
                            // On supprime le pion (prise en passant)
                            // Le déplacement du pion principal se fait plus bas
                            // Delete pawn (en passan)
                            // Moving the main pawn is below
                            supprPiece(deplP);

                            // Cas spécial prise en passant
                            // Special case en passant
                            prisePassant = true;
                        }
                        else
                        {
                            cout << "Forbidden move" << endl;
                            return false;
                        }
                    }
                    /// Cas spécial du roque : on regarde si la pièce est un roi et si il est bougé de deux cases, puis :
                    ///  - si la tour est a proximité
                    ///  - si aucune pièce joueur n'est sur la trajectoire
                    ///  - si le roi et la tour sont a leur position initiale
                    ///  - si aucune pièce adverse ne peut atteindre les cases entre la tour et le roi (incluant les positions du roi et de la tour)
                    /// (Voir checkRoque)
                    /// Castling special case : check if the piece is a king and is moved two squares away, then :
                    ///  - if the rook is near
                    ///  - if no players piece are inbetween
                    ///  - if the king and the rook are at their initial position
                    ///  - if no opponent's pieces can reach the squares between the two (including the positions of the king and the rook)
                    /// (See checkRoque)
                    else if(ech[dep.x][dep.y]->getTypePiece() == 'R' && abs(x - y) == 2)
                    {
                        unsigned int tourX = 0;
                        // Si le roque est possible, on effectue le déplacement de la tour et du roi
                        // avec la position en x de la tour donnée par checkRoque
                        // If the rook is possible, we move the rook and the king
                        // with the x position given by checkRoque
                        if(checkRoque(dep, arr, tourX))
                        {
                            // On déplace le roi
                            // Move the king
                            ech[arr.x][arr.y] = ech[dep.x][dep.y];
                            ech[dep.x][dep.y] = NULL;

                            // On règle les coordonnées sur l'échiquier graphique
                            // Set coordinates on the graphical chessboard
                            ech[arr.x][arr.y]->setIrrlichtPos(arr);


                            // Le mouvement de la tour dépend du sens du déplacement du roi
                            // (avancée ou recul sur l'axe des x)
                            // The rook movement depends on the direction of the king
                            // (going forward or backward on the x axis)
                            if(dep.x < arr.x)
                            {
                                ech[dep.x+1][dep.y] = ech[tourX][dep.y];
                                ech[tourX][dep.y] = NULL;

                                Coord tmp;
                                tmp.x = dep.x+1;
                                tmp.y = dep.y;

                                // On règle les coordonnées sur l'échiquier graphique
                                // Set coordinates on the graphical chessboard
                                ech[dep.x+1][dep.y]->setIrrlichtPos(tmp);
                            }
                            else if(dep.x > arr.x)
                            {
                                ech[dep.x-1][dep.y] = ech[tourX][dep.y];
                                ech[tourX][dep.y] = NULL;

                                Coord tmp;
                                tmp.x = dep.x-1;
                                tmp.y = dep.y;

                                // On règle les coordonnées sur l'échiquier graphique
                                // Set coordinates on the graphical chessboard
                                ech[dep.x-1][dep.y]->setIrrlichtPos(tmp);
                            }

                            return true;
                        }
                        // Sinon, on dit que le mouvement est faux et on sort de checkDepl
                        // Else, the movement is forbidden and we exit checkDepl
                        else
                        {
                            cout << "Forbidden move" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "Forbidden move" << endl;
                        return false;
                    }
                }


                /// Cas spécial du roi : on regarde si le mouvement demandé le met en échec en testant la position finale du roi.
                /// Si oui, le mouvement est impossible
                /// King's special case : check if the move put us in a check state by testing the final position of the king
                /// If true, the movement is not possible
                if(ech[dep.x][dep.y]->getTypePiece() == 'R')
                {
                    // On effectue le déplacement
                    // Execute the movement
                    ech[arr.x][arr.y] = ech[dep.x][dep.y];
                    ech[dep.x][dep.y] = NULL;


                    if(checkEchec(arr))
                    {
                        cout << "Move put the king in a check state" << endl;

                        // Si le mouvement est invalide, on annule le déplacement
                        // La position de la pièce sur l'échiquier n'est pas mise a jour
                        // If invalid move, it is cancelled
                        // The position of the piece on the chessboard isn't updated
                        ech[dep.x][dep.y] = ech[arr.x][arr.y];
                        ech[arr.x][arr.y] = NULL;

                        return false;
                    }

                    /// Le mouvement du roi est effectif, il n'est plus a sa position initiale (cas du roque)
                    /// King's movement is done, it isn't at its initial position (castling case)
                    ech[arr.x][arr.y]->setPosInit(false);

                    // On met a jour la position du roi sur l'échiquier
                    // Update the king position on the chessboard
                    ech[arr.x][arr.y]->setIrrlichtPos(arr);

                    // Booléen de déplacement sans prise de pièce a true
                    // Boolean move without taking pieces set to true
                    m_null_depl = true;

                    return true;
               }
                /// Si la pièce n'est pas un roi, on regarde si le mouvement de celle ci met le roi en échec
                /// If the piece is not a king, check if its move put the king in a check state
                else
                {
                    // On effectue le déplacement
                    // Move the piece
                    ech[arr.x][arr.y] = ech[dep.x][dep.y];
                    ech[dep.x][dep.y] = NULL;


                    if(checkEchecMvt(ech[arr.x][arr.y]->getAdv()))
                    {
                        cout << "Piece move puts the king in a check state" << endl;

                        // Si le mouvement est invalide, on annule le déplacement
                        // La position de la pièce sur l'échiquier n'est pas mise a jour
                        // Move cancelled if forbidden
                        // Piece's position isn't updated
                        ech[dep.x][dep.y] = ech[arr.x][arr.y];
                        ech[arr.x][arr.y] = NULL;

                        return false;
                    }


                        /// Cas du premier déplacement d'un pion (m_first_move est mis à false si autre type de déplacement)
                        /// case of the first move of a pawn (m_first_move is set to false if it is another type of movement)
                        if(ech[arr.x][arr.y]->getTypePiece() == 'P')
                        {
                            if(dep.y == 1 || dep.y == 6)
                            {
                                distanceDeplPion = arr.y - dep.y;

                                if(abs(distanceDeplPion) == 2)
                                {
                                    ech[arr.x][arr.y]->setFirstMove(true);
                                }
                                else
                                {
                                    ech[arr.x][arr.y]->setFirstMove(false);
                                }
                            }
                            else
                            {
                                 ech[arr.x][arr.y]->setFirstMove(false);
                            }
                        }

                        /// Cas du mouvement d'une tour : m_pos_init est a faux
                        /// Case of a rook's movement : m_pos_init is set to false
                        if(ech[arr.x][arr.y]->getTypePiece() == 'T')
                        {
                            ech[arr.x][arr.y]->setPosInit(false);
                        }

                        /// Cas de la promotion (le déplacement est effectué, on affiche les onglets de choix de promotion)
                        /// Case of a promotion (move is done, display the message box to choose)
                        if(ech[arr.x][arr.y]->getTypePiece() == 'P' && checkPromotion(arr))
                        {
                            m_promotion_pion = true;
                            m_promoted_pion = arr;
                        }


                    /// Si on est pas dans le cas d'une prise en passant
                    /// If not in the case of an en passant move
                    if(!prisePassant)
                        // Booléen de déplacement sans prise de pièce a true
                        // Boolean for a move without taking pieces set to true
                        m_null_depl = true;
                    /// Si cas d'une prise en passant
                    /// If case of an en passant move
                    else
                        // Booléen de déplacement sans prise de pièce a false
                        // Boolean for a move without taking pieces set to false
                        m_null_depl = false;

                    // La pièce est affichée a sa position d'arrivée
                    // (si le mouvement est annulé, on sort de la fonction et la position de la pièce sur l'échiquier n'est pas mise a jour)
                    // Piece is display at its arrival position
                    // (if the move is cancelled, we get out of the function and the position of the piece on the chessboard is not updated)
                    ech[arr.x][arr.y]->setIrrlichtPos(arr);

                    return true;
                }
            }

            /// Case d'arrivée non vide
            // Sinon, on efface la case de départ, on supprime la pièce aux coordonnées d'arrivée et de départ
            // et on remplace la pièce supprimée aux coordonnées d'arrivée
            // La pièce supprimée est rangée dans la réserve par la fonction supprPiece
            /// Arrival square non empty
            // Else, we delete the starting square, delete the piece at the arrival and starting coordinate
            // and replace the deleted piece at the arrival coordinates
            // The deleted piece is stored in the stock by the supprPiece function
            else
            {
                    // Vérifie que le déplacement est possible
                    // Check if the move is possible
                    if(!checkDepl(dep, arr))
                    {
                        cout << "Forbidden move" << endl;
                        return false;
                    }


                    // Variable temporaire
                    // Temporary variable
                    Piece *tmp;

                    /// Cas spécial du roi de l'adversaire : la pièce est imprenable
                    /// Le mouvement est donc invalide
                    /// Special case of the opponent's king : the piece can not be taken
                    /// Forbidden move
                    if(ech[arr.x][arr.y]->getTypePiece() == 'R')
                    {
                        return false;
                    }


                    /// Cas spécial du roi du joueur : on regarde si le mouvement demandé le met en échec en testant la position finale du roi.
                    /// Si oui, le mouvement est impossible
                    /// Special case of the player's king : check if the move put it in a check state by testing its final position
                    /// If true, the movement is forbidden
                    if(ech[dep.x][dep.y]->getTypePiece() == 'R')
                    {
                        // On effectue le déplacement des pièces
                        // Variable temporaire pour intervertir
                        // Move the pieces
                        // Temporary variable to invert
                        tmp = ech[arr.x][arr.y];

                        ech[arr.x][arr.y] = ech[dep.x][dep.y];
                        ech[dep.x][dep.y] = NULL;


                        if(checkEchec(arr))
                        {
                            cout << "Move puts the king in a checkmate state" << endl;

                            // Le déplacement est annulé dans tous les cas, pour pouvoir a la place utiliser la fonction de suppression avec le déplacement
                            // La position de la pièce sur l'échiquier n'est pas mise a jour
                            // Move if cancelled in all cases, we use delete function instead
                            // Position of the piece is not updated
                            ech[dep.x][dep.y] = ech[arr.x][arr.y];
                            ech[arr.x][arr.y] = tmp;

                            return false;
                        }


                        // Le déplacement est annulé dans tous les cas, pour pouvoir a la place utiliser la fonction de suppression avec le déplacement
                        // Move if cancelled in all cases, we use delete function instead
                        ech[dep.x][dep.y] = ech[arr.x][arr.y];
                        ech[arr.x][arr.y] = tmp;

                        /// Le mouvement du roi est effectif, il n'est plus a sa position initiale (cas du roque)
                        /// King's move is effective, it isn't at its initial position (castling)
                        ech[dep.x][dep.y]->setPosInit(false);

                    }
                    /// Si la pièce n'est pas un roi, on regarde si le mouvement de celle ci met le roi en échec ou si on vise le roi de l'adversaire
                    /// If the piece isn't a king, we check if its move puts the king in a check state or if we target the opponent's king
                    else
                    {
                         // On effectue le déplacement des pièces
                        // Variable temporaire pour intervertir
                        // Move the pieces
                        // Temporary variable to invert
                        tmp = ech[arr.x][arr.y];

                        ech[arr.x][arr.y] = ech[dep.x][dep.y];
                        ech[dep.x][dep.y] = NULL;



                        if(checkEchecMvt(ech[arr.x][arr.y]->getAdv()))
                        {
                            cout << "Piece's movement puts the king is a check state" << endl;

                            // Le déplacement est annulé dans tous les cas, pour pouvoir a la place utiliser la fonction de suppression avec le déplacement
                            // La position de la pièce sur l'échiquier n'est pas mise a jour
                            // Move if cancelled in all cases, we use delete function instead
                            // Position of the piece is not updated
                            ech[dep.x][dep.y] = ech[arr.x][arr.y];
                            ech[arr.x][arr.y] = tmp;

                            return false;
                        }


                        // Le déplacement est annulé dans tous les cas, pour pouvoir a la place utiliser la fonction de suppression avec le déplacement
                        // Move if cancelled in all cases, we use delete function instead
                        ech[dep.x][dep.y] = ech[arr.x][arr.y];
                        ech[arr.x][arr.y] = tmp;
                    }


                    // Suppression de la pièce aux coordonnées d'arrivée
                    // Delete the piece at the arrival coordinates
                    supprPiece(arr);

                    // Remplacement de la pièce supprimée par la pièce du joueur
                    // Replace the deleted piece by the players piece
                    ech[arr.x][arr.y] = ech[dep.x][dep.y];
                    ech[dep.x][dep.y] = NULL;

                    ech[arr.x][arr.y]->setIrrlichtPos(arr);


                    /// Si il s'agit d'une prise de piece par un pion, m_first_pos est a faux
                    /// If it's a piece taken by a pawn, m_first_pos is set to false
                    if(ech[arr.x][arr.y]->getTypePiece() == 'P')
                    {
                        ech[arr.x][arr.y]->setFirstMove(false);
                    }


                    /// Si il s'agit d'une prise de piece par une tour, m_pos_init est a faux
                    /// If it's a piece taken by a rook, m_pos_init is set to false
                    if(ech[arr.x][arr.y]->getTypePiece() == 'T')
                    {
                        ech[arr.x][arr.y]->setPosInit(false);
                    }


                    /// Cas de la promotion (le déplacement est effectué, on affiche les onglets de choix de promotion)
                    /// Case of a promotion (move is done, display the box to choose)
                    if(ech[arr.x][arr.y]->getTypePiece() == 'P' && checkPromotion(arr))
                    {
                            m_promotion_pion = true;
                            m_promoted_pion = arr;
                    }

                    // Booléen de déplacement sans prise de pièce a false
                    // Boolean for a move without taking piece set to false
                    m_null_depl = false;

                    return true;
            }
        }
        else
        {
            cout << "No piece" << endl;
            return false;
        }
    }
    else
    {
        cout << "Invalid coordinates" << endl;
        return false;
    }
}


// Charge une partie sauvegardée a partir d'une std::string indiquant le chemin du fichier et le driver video pour la MAJ des pièces sur l'échiquier
// Load a saved game from an std::string containing the path of the file and the video driver
void Echiquier::chargerPartie(std::string path, irr::video::IVideoDriver* driver)
{
    // On obtient la position du dernier backslash (correspond au dossier séléctionné)
    // Get the last backslash position (selected folder)
    unsigned found = path.find_last_of("/\\");
    cout << "Path : " << path.substr(0,found) << endl;
    cout << "File : " << path.substr(found+1) << endl;

    // A partir de la position du backslash, on récupère le nom complet du fichier
    // Get complete name of the file from the backslash position
    std::string file = path.substr(found+1);

    // On recherche la position du dernier point du chemin absolu (correspondd a l'extension de fichier)
    // Get last point position (file extension)
    unsigned extension = 0;
    extension = file.find_last_of(".");

    // Si l'extension est incorrecte ou absente, erreur
    // If no extension or invalid extension, error
    if(extension == 0)
    {
        cout << "Error : no extension" << endl;
        return ;
    }
    if(file.substr(extension+1) != "txt")
    {
        cout << "Error : " << file.substr(extension+1) << " is not a valid file extension" << endl;
        return ;
    }


    // Ouverture fichier en lecture
    // Open file in reading mode
    ifstream fichier(path.c_str(), ios::in);

    // Chaine de caractères contenant la ligne lue
    // String containing the line read
    std::string piece;

    // Cas ouverture réussie
    // File successfully opened
    if(fichier)
    {
        // On vide l'échiquier
        // Empty the chessboard
        unsigned int i,j;

        // Détruit les éléments du tableau et l'initialise a NULL
        // Delete array element and initialize it at NULL
        for(j = 0; j <= 7; j++){
            for(i = 0; i <= 7; i++){
                delete ech[i][j];
                ech[i][j] = NULL;
            }
        }


        // On lit une ligne et on la met dans la std::string piece
        // Parcours des lignes du fichier concernant l'échiquier, on s'arrête au délimiteur de la réserve
        // Read line and put it in the std::string piece variable
        // Get info concerning the chessboard, stop at the beginning of the stocks (Réserves) information
        while(getline(fichier, piece) && piece != "###### Réserves ######")
        {
            Coord tmp;
            // Conversion char en int
            // Converting char to int
            tmp.x = piece[0] - '0';
            tmp.y = piece[2] - '0';

            char type = piece[4];


            // Si la pièce n'existe pas (pièce de type N), on supprime la pièce ayant les coordonnées correspondantes sur l'échiquier
            // If the piece doesn't exist (Type N piece), we delete the piece with the corresponding coordinates on the chessboard
            if(type == 'N')
            {
                ech[tmp.x][tmp.y] = NULL;
            }
            // Sinon, on remplace la pièce
            // Else, we replace the piece
            else
            {
                // Conversion char en int
                // Converting char to int
                unsigned int adv = piece[5] - '0';

                switch(type)
                {
                    case 'P' :
                        Pion *p;
                        p = new Pion(driver, adv);

                        // On règle le booléen de premier mouvement (cas prise en passant)
                        // Set first move boolean (En passant case)
                        if(piece[7] == 1)
                            p->setFirstMove(true);
                        else
                            p->setFirstMove(false);

                        ech[tmp.x][tmp.y] = p;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    case 'C' :
                        Cavalier *c;
                        c = new Cavalier(driver, adv);

                        ech[tmp.x][tmp.y] = c;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    case 'F' :
                        Fou *f;
                        f = new Fou(driver, adv);

                        ech[tmp.x][tmp.y] = f;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    case 'T' :
                        Tour *t;
                        t = new Tour(driver, adv);

                        // On règle le booléen de position initiale (cas roque)
                        // Set initial position boolean (castling case)
                        if(piece[7] == 1)
                            t->setPosInit(true);
                        else
                            t->setPosInit(false);

                        ech[tmp.x][tmp.y] = t;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    case 'D' :
                        Dame *d;
                        d = new Dame(driver, adv);

                        ech[tmp.x][tmp.y] = d;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    case 'R' :
                        Roi *r;
                        r = new Roi(driver, adv);

                        // Cas du roi en échec : booléen d'échec a vrai et on met a jour les coordonnées du roi en échec
                        // King in a check state case : check state boolean to true and update king coordinates
                        if(piece[7] == 1)
                        {
                            m_echec = piece[7];
                            m_roi_echec = tmp;
                        }

                        // On règle le booléen de position initiale (cas roque)
                        // Set initial position boolean (castling case)
                        if(piece[9] == 1)
                            r->setPosInit(true);
                        else
                            r->setPosInit(false);

                        ech[tmp.x][tmp.y] = r;

                        ech[tmp.x][tmp.y]->setIrrlichtPos(tmp);
                    break;

                    default :
                    break;
                }

            }

        }


        // On vide les réserves
        // Empty the stocks
        m_res_j1.clear();
        m_res_j2.clear();

        // Parcours des réserves, on s'arrête au délimitateur de fin
        // Going through the stocks information, stop at the ending delimiter
        while(getline(fichier, piece) && piece != "###### Fin ######")
        {
            Coord tmp;
            // Conversion char en int
            // Conversion char to int
            tmp.x = piece[0] - '0';
            tmp.y = piece[2] - '0';

            char type = piece[4];


            // Si la pièce n'existe pas (pièce de type N), on supprime la pièce ayant les coordonnées correspondantes sur l'échiquier
            // If the piece doesn't exist (Type N piece), we delete the piece with the corresponding coordinates on the chessboard
            if(type == 'N')
            {
                ech[tmp.x][tmp.y] = NULL;
            }
            // Sinon, on remplace la pièce
            // Else, we delete the piece
            else
            {
                // Conversion char en int
                // Converstion char to int
                unsigned int adv = piece[5] - '0';

                switch(type)
                {
                    case 'P' :
                        Pion *p;
                        p = new Pion(driver, adv);

                        // On règle le booléen de premier mouvement (cas prise en passant)
                        // Set first movement boolean (En passant case)
                        if(piece[7] == 1)
                            p->setFirstMove(true);
                        else
                            p->setFirstMove(false);

                        // Rangement réserve
                        // Set stocks
                        if(adv == 1)
                            m_res_j2.push_back(p);
                        else if(adv == 2)
                            m_res_j1.push_back(p);
                    break;

                    case 'C' :
                        Cavalier *c;
                        c = new Cavalier(driver, adv);

                        // Rangement réserve
                        // Set stocks
                        if(adv == 1)
                            m_res_j2.push_back(c);
                        else if(adv == 2)
                            m_res_j1.push_back(c);
                    break;

                    case 'F' :
                        Fou *f;
                        f = new Fou(driver, adv);

                        // Rangement réserve
                        // Set stocks
                        if(adv == 1)
                            m_res_j2.push_back(f);
                        else if(adv == 2)
                            m_res_j1.push_back(f);
                    break;

                    case 'T' :
                        Tour *t;
                        t = new Tour(driver, adv);

                        // On règle le booléen de position initiale (cas roque)
                        // Set initial positio boolean (castling case)
                        if(piece[7] == 1)
                            t->setPosInit(true);
                        else
                            t->setPosInit(false);

                        // Rangement réserve
                        // Set stocks
                        if(adv == 1)
                            m_res_j2.push_back(t);
                        else if(adv == 2)
                            m_res_j1.push_back(t);
                    break;

                    case 'D' :
                        Dame *d;
                        d = new Dame(driver, adv);

                        // Rangement réserve
                        // Set stocks
                        if(adv == 1)
                            m_res_j2.push_back(d);
                        else if(adv == 2)
                            m_res_j1.push_back(d);
                    break;

                    default :
                    break;
                }

            }

        }

        // Affichage console de l'échiquier chargé (problème de chargement de textures)
        // Display the loaded chessboard on the console (loading textures issues)
        cout << endl << endl;

        for(j = 0; j <= 7; j++){
            for(i = 0; i <= 7; i++){
                if(ech[i][j] == NULL)
                    cout << "   ";
                else
                    cout << ech[i][j]->getInfo() << " ";
            }
            cout << endl;
        }

        // Fermeture du fichier
        // Close the file
        fichier.close();
    }
    // Cas ou l'ouverture du fichier a échoué
    // Failing to open the file
    else
        cerr << "Cannot open the file !" << endl;

    // On réaffiche l'échiquier
    // Display the chessboard again
    afficheEch(driver);
}


// Sauvegarde une partie a partir d'une std::string indiquant un chemin de fichier
// Save game from an std::string containing the path of the file to save to
void Echiquier::sauverPartie(std::string path)
{
    // On obtient la position du dernier backslash (correspond au dossier séléctionné)
    // Get the last backslash position (selected folder)
    unsigned found = path.find_last_of("/\\");
    cout << "Path : " << path.substr(0,found) << endl;
    cout << "File : " << path.substr(found+1) << endl;

    // A partir de la position du backslash, on récupère le nom complet du fichier
    // Get complete name of the file from the backslash position
    std::string file = path.substr(found+1);

    // On recherche la position du dernier point du chemin absolu (correspond a l'extension de fichier)
    // Get last point position (file extension)
    unsigned extension = 0;
    extension = file.find_last_of(".");

    // Si l'extension est incorrecte ou absente, erreur
    // If no extension or invalid extension, error
    if(extension == 0)
    {
        cout << "Error : no extension" << endl;
        return ;
    }
    if(file.substr(extension+1) != "txt")
    {
        cout << "Erreur : " << file.substr(extension+1) << " is not a valid file extenstion" << endl;
        return ;
    }


    // Ouverture fichier en écriture, écrasement du fichier si il contient déja des données
    // Open file in writing mode, delete previous content
    ofstream fichier(path.c_str(), ios::out | ios::trunc);

    // Cas ouverture réussie
    // File successfully opened
    if(fichier)
    {
        // Parcours de l'échiquier
        // Go through the chessboard
        for( unsigned int j = 0; j <= 7; j++ ){
            for( unsigned int i = 0; i <= 7; i++ ){
                // Si la pièce existe
                // If piece exists
                if(ech[i][j] != NULL)
                {
                    // Coordonnées de la pièce
                    // Piece coordinates
                    fichier << i << " " << j << " " ;

                    // Type et possesseur de la pièce
                    // Piece's type and owner
                    fichier << ech[i][j]->getInfo();

                    // Si la pièce est un pion, on rajoute le premier mouvement
                    // If piece is a pawn, we add the first movement variable
                    if(ech[i][j]->getTypePiece() == 'P')
                    {
                        // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                        // Security
                        if(ech[i][j]->getFirstMove())
                            fichier << " " << 1;
                        else
                            fichier << " " << 0;
                    }

                    // Si la pièce est un roi, on rajoute le cas d'échec et le booléen de position initiale (cas roque)
                    // If the piece is a king, we add the check case and the initial position boolean (castling case)
                    if(ech[i][j]->getTypePiece() == 'R')
                    {
                        // Si on a une situation d'échec et que les coordonnées du roi en échec correspondent aux coordonnées du roi traité, alors le roi est en échec
                        // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                        // If check state and coordinates of the current king are the coordinates of the check state king, then it's the check state king
                        // Security
                        if(m_echec && m_roi_echec.x == i && m_roi_echec.y == j)
                            fichier << " " << 1;
                        else
                            fichier << " " << 0;

                        // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                        // Security
                        if(ech[i][j]->getPosInit())
                            fichier << " " << 1;
                        else
                            fichier << " " << 0;
                    }

                    // Si la pièce est une tour, on rajoute le booléen de position initiale (cas roque)
                    // If the piece is a rook, we add the initial position boolean (castling case)
                    if(ech[i][j]->getTypePiece() == 'T')
                    {
                         // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                        // Security
                        if(ech[i][j]->getPosInit())
                            fichier << " " << 1;
                        else
                            fichier << " " << 0;
                    }

                    // Retour a la ligne
                    // LF, CR
                    fichier << endl;
                }
                // Si la pièce n'existe pas, on enregistre une pièce de type N aux coordonnées, suivie d'un retour a la ligne
                // If there's no piece, we save a N type piece
                else
                {
                    // Coordonnées de la pièce
                    // Piece's coordinate
                    fichier << i << " " << j << " " ;

                    // Pièce de type N (pas de pièce)
                    // Type N piece (no piece)
                    fichier << "N" << endl;
                }
            }
        }

        // Délimitateur des réserves
        // Stocks delimiter
        fichier << "###### Réserves ######" << endl;

        // Coordonnées temporaires
        // Temporary coordinates
        Coord tmp;

        // Parcours des réserves J1 et J2
        // Processing the stocks for player 1 and 2
        for ( unsigned int i = 0, size = m_res_j1.size(); i < size; ++i )
        {
            tmp = m_res_j1.at(i)->getPosRes();

            // Coordonnées de la pièce
            // Piece's coordinate
            fichier << tmp.x << " " << tmp.y << " " ;

            // Type et possesseur de la pièce
            // Piece's type and owner
            fichier << m_res_j1.at(i)->getInfo();

            // Si la pièce est un pion, on rajoute le premier mouvement
            // If piece is a pawn, we add first move variable
            if(m_res_j1.at(i)->getTypePiece() == 'P')
            {
                // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                // Security
                if(m_res_j1.at(i)->getFirstMove())
                    fichier << " " << 1;
                else
                    fichier << " " << 0;
            }

            // Si la pièce est une tour, on rajoute le booléen de position initiale (cas roque)
            // If the piece is a rook, we add the initial position variable (castling case)
            if(m_res_j1.at(i)->getTypePiece() == 'T')
            {
                 // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                // Security
                if(m_res_j1.at(i)->getPosInit())
                    fichier << " " << 1;
                else
                    fichier << " " << 0;
            }

            // Retour a la ligne
            // CR, LF
            fichier << endl;
        }


        for ( unsigned int i = 0, size = m_res_j2.size(); i < size; ++i )
        {
            tmp = m_res_j2.at(i)->getPosRes();

            // Coordonnées de la pièce
            // Piece's coordinates
            fichier << tmp.x << " " << tmp.y << " " ;

            // Type et possesseur de la pièce
            // Piece's type and owner
            fichier << m_res_j2.at(i)->getInfo();

            // Si la pièce est un pion, on rajoute le premier mouvement
            // If the piece is a pawn, we add the first move variable
            if(m_res_j2.at(i)->getTypePiece() == 'P')
            {
                // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                // Security
                if(m_res_j2.at(i)->getFirstMove())
                    fichier << " " << 1;
                else
                    fichier << " " << 0;
            }

            // Si la pièce est une tour, on rajoute le booléen de position initiale (cas roque)
            // If the piece is a rook, we add the initial position variable (castling case)
            if(m_res_j2.at(i)->getTypePiece() == 'T')
            {
                 // Normalement, un booléen ne peut être qu'a 0 ou a 1, mais par mesure de sécurité, on passe par un if
                // Security
                if(m_res_j2.at(i)->getPosInit())
                    fichier << " " << 1;
                else
                    fichier << " " << 0;
            }

            // Retour a la ligne
            // CR, LF
            fichier << endl;
        }


        // Délimitateur de fin
        // Endind delimiter
        fichier << "###### Fin ######";


        // Fermeture du fichier
        // Closing file
        fichier.close();
    }
    // Cas ou l'ouverture du fichier a échoué
    // If fail when opening the file
    else
        cerr << "Cannot open file !" << endl;

}

