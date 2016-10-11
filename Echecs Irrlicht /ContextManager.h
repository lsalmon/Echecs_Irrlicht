/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

#include <irrlicht.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "def.h"
#include "Echiquier.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



class ContextManager;
class MyEventReceiver : public irr::IEventReceiver
{
public:

    MyEventReceiver(ContextManager * manager);

    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event);
    bool left;
private:
    ContextManager * m_manager;
};


class ContextManager
{
    public:
        ContextManager();
        virtual ~ContextManager();

        void init(irr::IrrlichtDevice * device);

        MyEventReceiver * getReceiver();


        // Méthode d'affichage
        // Display method
        void afficher();
        // Traitement de la position entrée par le joueur
        // Processing of the player input (position)
        void processPosition(Coord & m_cible);

        // Gestion du timer
        // Timer managmenent
        void timerManagement();
        // Gestion du temps total écoulé et mise a jour temps timer
        // Total time and update timer management
        void MAJTemps();
        // Gestion du score
        // Score management
        void MAJScore();

        // Appel a la fonction de promotion d'un pion
        // Call to the pawn promotion function
        void ajouterPiecePromotion(char type);
        // Fonction renvoyant le booléen indiquant une promotion
        // Function returning promotion boolean
        bool getPromotionBool();
        // Fonction renvoyant le booléen indiquant une fin de tour
        // (pour l'appel a la fonction d'annulation du dernier mouvement)
        // Function returning end-of-turn boolean
        // (call to the last move cancellation function)
        bool getFinTourBool();
        // Getter et setter pour l'attribut du numéro de joueur effectuant son déplacement
        // (inversion des tours après l'appel a la fonction d'annulation du dernier mouvement)
        // Getter and setter for the current player number
        // (changing turn after calling the last move cancellation function)
        unsigned int getTour();
        void setTour(unsigned int t);
        // Getter et setter pour l'attribut du type d'opération a faire sur le fichier choisi par la boite de dialogue
        // Getter and setter for the type of operation to do on the file selected
        unsigned int getOuvrirFichier();
        void setOuvrirFichier(unsigned int attr);
        // Fonction renvoyant le booléen indiquant un état d'échec et mat
        // Function returning the checkmate boolean
        bool getEchecMatBool();

        // Fonction faisant appel a la fonction de vérification d'échec pour l'adversaire du joueur courant
        // (juste après le changement du tour - passage de la main du joueur courant a l'adversaire)
        // Function for the checkmate verification function
        // (executed right after the turns have been switched)
        void verifierEchec();

        // Appel a la fonction d'annulation du dernier mouvement
        // Call to the last move cancellation function
        bool annulerMvt();

        // Affiche un message de fin de partie en cas d'échec et mat
        // Display end of game message (checkmate)
        void showEchecMat();

        // Ouvre une boite de dialogue de sélection de fichier (utilisé dans le chargement / sauvegarde de parties)
        // Open dialog box for selecting files (load/save games)
        void selectionFichier(irr::core::stringw windowText);

        // Appel a la fonction de chargement d'une partie de l'échiquier
        // Call loading game function
        void chargerPartie(std::string path);

        // Appel a la fonction de sauvegarde d'une partie de l'échiquier
        // Call saving game function
        void sauverPartie(std::string path);


        int static const GUI_ADD_DAME;
        int static const GUI_ADD_TOUR;
        int static const GUI_ADD_FOU;
        int static const GUI_ADD_CAVALIER;
        int static const GUI_CANCEL_MOVE;
        int static const GUI_LOAD;
        int static const GUI_SAVE;


    protected:

    private:

        // L'échiquier
        // Chessboard
        Echiquier board;

        // Temps total écoulé
        // Total time elapsed
        u32 m_temps_total;

        // Temps des timers joueur 1 et 2
        // Player 1 and 2 timers
        u32 m_temps_J1;
        u32 m_temps_J2;
        // Delta pour les temps timer joueur 1 et 2
        // Delat time players 1 and 2
        u32 m_delta_temps;

        // Score joueur 1 et 2
        // Player 1 and 2 scores
        u32 m_score_J1;
        u32 m_score_J2;


        // Booléen (pour prendre une coordonnée de départ et une coordonnée d'arrivée en plusieurs clics)
        // Boolean (for the arrival / starting coordinates)
        bool m_click;

        // Booléen indiquant la fin d'un tour (pour l'appel à annulerMvt)
        // Boolean for the end of a turn (see annulerMvt)
        bool m_fin_tour;

        // Numéro adversaire
        // Number for the opponent
        unsigned int m_tour;

        // Choix de la fonction a appeler après choix de fichier
        // Function to call after file is selected
        unsigned int m_ouvrir_fichier;


        // Booléen qui indique l'apparition d'une messagebox avec un message d'échec et mat
        // Boolean for messagebox (checkmate message)
        bool m_message_echec_mat;

        // Cordonnées rentrées par les deux joueurs
        // Coordinates given by the two players
        Coord m_pos_j;
        Coord m_pos_adv;

        // Attributs texte pour la gestion du timer
        // Text for the timers
        IGUIStaticText *m_text_time_J1;
        IGUIStaticText *m_text_time_J2;

        // Attribut texte pour le temps total écoulé
        // Text for total time
        IGUIStaticText *m_text_total_time;

        // Attributs texte pour la gestion du score
        // Text for score
        IGUIStaticText *m_text_score_J1;
        IGUIStaticText *m_text_score_J2;


        // Display variables

        // Attributs gestion du timer : temps écoulé et chaine de caractère a afficher pour le joueur 1 et le joueur 2
        // Variables for the timer management (time elapsed, string for player 1 and 2)
        stringw m_str1;
        stringw m_str2;

        // Attribut temps total écoulé
        // Variable for total time
        stringw m_str_total;

        // Attributs gestion du score : score et numero de joueur
        // Variable for score management
        stringw m_str_score1;
        stringw m_str_score2;

        // Attribut fenêtre de choix de promotion d'un pion
        // Variable for selection window (pawn promotion)
        IGUIWindow * m_promotion_window;

        // Attributs de gestion de l'environnement
        // General variables (environment)
        IGUIEnvironment * env;
        irr::video::IVideoDriver * m_driver;
        irr::IrrlichtDevice * m_device;
        MyEventReceiver * m_event_receiver;
};

#endif // CONTEXTMANAGER_H
