/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "def.h"
#include <math.h>
#include <irrlicht.h>
#include <string>

class Piece
{
    public :
        // Constructeur
        // Constructor
        Piece(irr::video::IVideoDriver* driver, unsigned int adv);

        // Destructeur
        // Desctructor
        virtual ~Piece();

        // Affichage de la pièce
        // Display the piece
        void affichage(irr::video::IVideoDriver* driver);

        // Fonction d'affichage de la pièce (texte)
        // Display piece (console)
        std::string getInfo();

        // Renvoie type de pièce
        // Get piece type
        char getTypePiece();
        // Renvoie joueur possesseur de la pièce
        // Get player who owns the piece
        unsigned int getAdv();


        // Fonction de vérification de la position (la pièce connait ses déplacements)
        // La fonction prend un tableau de positions des possesseurs de toutes les pièces présentes sur l'échiquier
        // Function who checks the position (the piece knows where it can go)
        // The function takes an array of the positions of the owners of all the pieces on the chessboard
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);

        // Renvoie un pointeur vers le membre texture de la classe (image affichée)
        // Get pointer to the texture member of the class (picture)
        irr::video::ITexture * getTexture();

        // Change la position interne de la pièce (cas pièce dans la réserve)
        // Change internal position of the piece (case of the piece in the stocks)
        void setPosRes(Coord & pos);

        // Renvoie les coordonnées de la pièce (cas de la pièce dans la réserve)
        // Get coordinates of the piece (case of the piece in the stocks)
        Coord & getPosRes();

        // Renvoie position graphique de la pièce
        // Get graphical position of the piece
        Coord & getIrrlichtPos();

        // Change la position graphique de la pièce sur l'écran utilisé lors de l'affichage avec irrlicht (cas pièces sur l'échiquier)
        // Change graphical position of the piece on the screen (pieces on the chessboard)
        void setIrrlichtPos(Coord & pos);

        // Change la position graphique de la pièce sur l'écran utilisé lors de l'affichage avec irrlicht (cas réserve)
        // Change graphical position of the piece on the screen (case stocks)
        void setIrrlichtPosRes(int posX, unsigned int adv);

        // Change la couleur de la pièce selon si elle est sélectionnée ou non
        // Change colour of the piece (if it is selected or not)
        void setStandardColor();
        void setSelectedColor();
        // Change la couleur du roi si il est en échec
        // Change the color of the king if it is on check state
        void setEchecColor();
        // Change la couleur du roi si il est en échec et mat
        // Change the color of the king if it is on checkmate state
        void setEchecMatColor();

        /* Fonctions spécifiques a la classe pion */
        /* Specific functions for the pion class */
        // Getter pour l'attribut m_first_move
        virtual bool getFirstMove();
        // Setter pour l'attribut m_first_move
        virtual void setFirstMove(bool first);

        /* Fonctions spécifiques aux classes tour et roi */
        /* Specific functions for the tour & roi class */
        // Getter pour l'attribut m_pos_init
        virtual bool getPosInit();
        // Setter pour l'attribut m_pos_init
        virtual void setPosInit(bool init);


    protected :
        // Type de pièce
        // Piece type
        char m_type;
        // Pièce appartient à l'un ou l'autre des joueurs
        // Owner of the piece
        unsigned int m_adv;

        // Membres d'affichage graphique (irrlicht) : texture pièce, taille texture, driver video, couleur de la pièce
        // Graphical display members (irrlicht) : piece texture, texture size, video driver, piece color
        irr::video::ITexture * m_texture;
        irr::core::rect<irr::s32> m_texture_rect;
        irr::video::IVideoDriver * driver;
        irr::video::SColor m_couleur_piece;

    private :
        // Position pièce sur l'échiquier (cas réserve)
        // Position of the piece on the chessboard (stocks)
        Coord m_pos;

        // Position sur l'échiquier
        // Postion on the chessboard
        Coord m_irr_pos;
};

class Pion : virtual public Piece
{
    public :
        Pion(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);
        // Getter/setter pour l'attribut m_first_move
        virtual bool getFirstMove();
        virtual void setFirstMove(bool first);

    private :
        // Booléen qui indique le premier mouvement du pion (cas de la prise en passant)
        // Boolean for first move (En passant)
        bool m_first_move;
};


class Cavalier : virtual public Piece
{
    public :
        Cavalier(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);

    private :
};

class Fou : virtual public Piece
{
    public :
        Fou(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);

    private :
};

class Tour : virtual public Piece
{
    public :
        Tour(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);
        // Getter/setter pour l'attribut m_pos_init
        virtual bool getPosInit();
        virtual void setPosInit(bool init);


    private :
        // Booléen qui indique si la pièce est a sa position initiale (cas du roque)
        // Boolean for initial position (castling)
        bool m_pos_init;
};

// La Dame hérite des propriétés du fou et de la tour concernant les déplacements
// The Queen inherits the properties of the bishop and rook concerning its movements
class Dame : public Tour, public Fou
{
    public :
        Dame(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);

    private :
};

class Roi : virtual public Piece
{
    public :
        Roi(irr::video::IVideoDriver* driver, unsigned int adv);
        virtual bool checkPos(Coord & posDep, Coord & posArr, unsigned int tab[8][8]);
        // Getter/setter pour l'attribut m_pos_init
        virtual bool getPosInit();
        virtual void setPosInit(bool init);

    private :
        // Booléen qui indique si la pièce est a sa position initiale (cas du roque)
        // Boolean for the intial position (castling)
        bool m_pos_init;
};


#endif // PIECE_H_INCLUDED
