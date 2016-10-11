/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

#include "ContextManager.h"
#include "Piece.h"
#include "Echiquier.h"


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int const ContextManager::GUI_ADD_DAME=1;
int const ContextManager::GUI_ADD_TOUR=2;
int const ContextManager::GUI_ADD_FOU=3;
int const ContextManager::GUI_ADD_CAVALIER=4;

int const ContextManager::GUI_CANCEL_MOVE=10;

int const ContextManager::GUI_LOAD=7;
int const ContextManager::GUI_SAVE=8;


MyEventReceiver::MyEventReceiver(ContextManager * manager)
{
    m_manager=manager;
}

bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
    // Si on est dans un état d'échec et mat, tout est bloqué
    // If checkmate case : we can't move anything
    if(m_manager->getEchecMatBool())
    {
        return false;
    }

    // Remember whether each key is down or up
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        // Si on est dans le cas d'une promotion, les mouvements sur l'échiquier sont bloqués momentanément
        // If a piece is being promoted, temporarily disable movements on the chessboard
        if(event.MouseInput.isLeftPressed(  ) && !m_manager->getPromotionBool())
        {
            left=true;
        }
        else
        {
            left=false;
        }
    }
    else if (event.EventType == EET_GUI_EVENT)
    {
        s32 id = event.GUIEvent.Caller->getID();

        switch(event.GUIEvent.EventType)
        {
        case EGET_BUTTON_CLICKED:
            switch(id)
            {
            case ContextManager::GUI_ADD_DAME:

                if(m_manager->getPromotionBool())
                {
                    m_manager->ajouterPiecePromotion('d');
                    // Vérification de l'échec suite a la promotion
                    // Checking if we are in a checkmate case after promotion
                    m_manager->verifierEchec();
                }
                return true;

            case ContextManager::GUI_ADD_TOUR:

                if(m_manager->getPromotionBool())
                {
                    m_manager->ajouterPiecePromotion('t');
                    // Vérification de l'échec suite a la promotion
                    // Checking if we are in a checkmate case after promotion
                    m_manager->verifierEchec();
                }
                return true;

            case ContextManager::GUI_ADD_FOU:

                if(m_manager->getPromotionBool())
                {
                    m_manager->ajouterPiecePromotion('f');
                    // Vérification de l'échec suite a la promotion
                    // Checking if we are in a checkmate case after promotion
                    m_manager->verifierEchec();
                }
                return true;

            case ContextManager::GUI_ADD_CAVALIER:

                if(m_manager->getPromotionBool())
                {
                    m_manager->ajouterPiecePromotion('c');
                    // Vérification de l'échec suite a la promotion
                    // Checking if we are in a checkmate case after promotion
                    m_manager->verifierEchec();
                }
                return true;

            /// Ce bouton bug, utiliser la touche R a la place (même fonctionnalité : annuler le dernier mouvement fait)
            /// This button is not working, use the R key instead (same functionality : cancel the last move)
            case ContextManager::GUI_CANCEL_MOVE:
            {
                // Annulation du mouvement possible uniquement si aucun mouvement n'est en cours
                // The move can only be cancelled if no other pieces are being moved
                if(m_manager->getFinTourBool())
                {
                    // Si l'annulation est effective, on inverse les tours
                    // If cancellation is done, we switch turns
                    if(m_manager->annulerMvt())
                    {
                        if(m_manager->getTour() == 1)
                            m_manager->setTour(2);
                        else
                            m_manager->setTour(1);

                    }
                }
            }

                return true;

            case ContextManager::GUI_LOAD:
                // Rajout d'une fenêtre de sélection de fichier
                // Add a window to select a file
                m_manager->selectionFichier(L"Select save file to load");

                // Chargement d'une partie
                // Load game
                m_manager->setOuvrirFichier(GAME_LOAD);

                return true;

            case ContextManager::GUI_SAVE:
                // Rajout d'une fenêtre de sélection de fichier
                // Add a window to select a file
                m_manager->selectionFichier(L"Select file to save the game in");

                // Sauvegarde d'une partie
                // Save game
                m_manager->setOuvrirFichier(GAME_SAVE);

                return true;

            default:
                return false;
            }
            break;

        case EGET_FILE_SELECTED:
        {
            // Obtention du chemin d'un fichier sélectionné a partir d'une boite de dialogue de sélection
            // Get filepath from dialog box
            IGUIFileOpenDialog* dialog =
                (IGUIFileOpenDialog*)event.GUIEvent.Caller;

            stringw strw = dialog->getFileName();
            const wchar_t* wch = dialog->getFileName();

            // Conversion de la stringw contenant le chemin en string
            // Converting stringw (containing the path) to string
            int ret;
            char buffer[256] = "";

            // Fonction de la bibliothèque standard
            // Standard library function
            ret = wcstombs ( buffer, wch, sizeof(buffer) );
            // Limitation du chemin a 255 caractères
            // Path is limited to 255 char
            if (ret==256) { buffer[255] = '\0'; }
            if (!ret) { return 0; }


            std::string path = buffer;
            std::cout << "File path : " << path << std::endl;

            // Appel aux fonctions relatives a l'ouverture du fichier sélectionné
            // Calling functions used to open the selected file
            if(m_manager->getOuvrirFichier() == GAME_LOAD)
                m_manager->chargerPartie(path);
            else if(m_manager->getOuvrirFichier() == GAME_SAVE)
                m_manager->sauverPartie(path);
            else
                std::cout << "Operation type error" << std::endl;  return false;

        }
        break;

        default:
            break;
        }
    }
    // Si on appuie sur une touche
    // If the user press a key
    else if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
    {
			switch (event.KeyInput.Key)
			{
                case irr::KEY_KEY_R:

                    // Annulation du mouvement possible uniquement si aucun mouvement n'est en cours
                    // The move can only be cancelled if no other pieces are being moved
                    if(m_manager->getFinTourBool())
                    {
                        // Si l'annulation est effective, on inverse les tours
                        // If the move is cancelled, switch turns
                        if(m_manager->annulerMvt())
                        {
                            if(m_manager->getTour() == 1)
                                m_manager->setTour(2);
                            else
                                m_manager->setTour(1);

                        }
                    }

                    return true;

                case irr::KEY_F7:
                {
                    // Rajout d'une fenêtre de sélection de fichier
                    // Add a window to select a file
                    m_manager->selectionFichier(L"Select save file to load");

                    // Chargement d'une partie
                    // Load game
                    m_manager->setOuvrirFichier(GAME_LOAD);

                    return true;
                }

               case irr::KEY_F8:
                {
                    // Rajout d'une fenêtre de sélection de fichier
                    m_manager->selectionFichier(L"Select file to save the game in");

                    // Sauvegarde d'une partie
                    // Save game
                    m_manager->setOuvrirFichier(GAME_SAVE);

                    return true;
                }


                default:
                    return false;
			}
    }
    return false;
}



ContextManager::ContextManager()
{
    m_event_receiver = new MyEventReceiver(this);
}

ContextManager::~ContextManager(){}


void ContextManager::init(irr::IrrlichtDevice* device)
{
    m_device=device;
    m_driver=device->getVideoDriver();
    env = device->getGUIEnvironment();

    // On initialise le membre échiquier dans la classe
    // Initialize chessboard (échiquier) member in the class
    board.init(m_driver);

    // Le joueur 1 commence
    // Player 1 starts
    m_tour = 1;

    // Booléen de séléction des coordonnées d'arrivée initialisé
    // Initialize boolean used for the arrival coordinates
    m_click = false;

    // Pas de déplacement effectué au départ
    // No moves at the start of the game
    m_fin_tour = false;

    // Chargement de partie par défaut
    // Default action is : loading game
    m_ouvrir_fichier = GAME_LOAD;

    // Message d'échec et mat non affiché
    // No checkmate message is displayed
    m_message_echec_mat = false;


    // Fenêtre de promotion
    // Promotion window (Dame : queen, pion : pawn, tour : rook, fou : bishop, cavalier : knight)
    m_promotion_window = env->addWindow(
                            rect<s32>(100, 100, 240 ,180),
                            true, // modal?
                            L"Pawn promotion");
    env->addButton(rect<s32>(5,25,70,50),m_promotion_window, GUI_ADD_DAME,
                   L"Queen", L"Queen" );
    env->addButton(rect<s32>(70,25,135,50),m_promotion_window, GUI_ADD_TOUR,
                   L"Rook", L"Rook" );
    env->addButton(rect<s32>(5,50,70,75),m_promotion_window, GUI_ADD_FOU,
                   L"Bishop", L"Bishop" );
    env->addButton(rect<s32>(70,50,135,75),m_promotion_window, GUI_ADD_CAVALIER,
                   L"Knight", L"Knight" );

    // La fenêtre est déplacable mais non visible par défaut ; elle ne le devient qu'en cas de promotion
    // (Voir fonction afficher dans ContextManager)
    // Window is resizable but invisible (default setting), it becomes visible after a promotion
    // (See function afficher in ContextManager)
    m_promotion_window->setDraggable(true);
    m_promotion_window->setVisible(false);


    // Initialisation du texte utilisé dans la gestion du timer
    // Initializing text used in timer management
    m_str1 = L"Player 1 time : 0 s";
    m_str2 = L"Player 2 time : 0 s";

    m_text_time_J1 = env->addStaticText(m_str1.c_str()
    ,rect<int>(25,0,175,20)
    ,false  // Pas de bordure (no border)
    ,true); // Retour a la ligne (CR, LF)

    m_text_time_J2 = env->addStaticText(m_str2.c_str()
    ,rect<int>(X_OFFSET+BOARD_SIZE_X+25,0,X_OFFSET+BOARD_SIZE_X+175,20)
    ,false  // Pas de bordure (no border)
    ,true); // Retour a la ligne (CR, LF)


    // Initialisation du texte utilisé dans la gestion des scores
    // Initializing text used in score management
    m_str_score1 = L"Player 1 score : 0 pts";
    m_str_score2 = L"Player 2 score : 0 pts";

    m_text_score_J1 = env->addStaticText(m_str_score1.c_str()
    ,rect<int>(25,25,175,45)
    ,false  // Pas de bordure (no border)
    ,true); // Retour a la ligne (CR, LF)

    m_text_score_J2 = env->addStaticText(m_str_score2.c_str()
    ,rect<int>(X_OFFSET+BOARD_SIZE_X+25,25,X_OFFSET+BOARD_SIZE_X+175,45)
    ,false  // Pas de bordure (no border)
    ,true); // Retour a la ligne (CR, LF)


    // Initialisation du texte utilisé dans le décompte de temps total
    // Initializing text used when counting the total time elapsed since the beginning of the game
    m_str_total = L"Total time : ";

    m_text_total_time = env->addStaticText(m_str_total.c_str()
    ,rect<int>(X_OFFSET+(BOARD_SIZE_X/2)-75,0,X_OFFSET+(BOARD_SIZE_X/2)+75,20)
    ,false  // Pas de bordure (no border)
    ,true); // Retour a la ligne (CR, LF)


    // Initialisation des boutons (annuler mouvement, charger, sauvegarder)
    // Initializing buttons (cancel move, load, save)
    env->addButton(rect<s32>(25, (BOARD_SIZE_Y)+50, X_OFFSET-25, (BOARD_SIZE_Y)+50+32)
                   ,0
                   ,GUI_CANCEL_MOVE
                   ,L"Cancel last move"
                   ,L"");


    env->addButton(rect<s32>(X_OFFSET+(BOARD_SIZE_X/2)-100, (BOARD_SIZE_Y)+50, X_OFFSET+(BOARD_SIZE_X/2)+100, (BOARD_SIZE_Y)+50+32)
                   ,0
                   ,GUI_LOAD
                   ,L"Load game"
                   ,L"");

    env->addButton(rect<s32>(X_OFFSET+(BOARD_SIZE_X)+25, (BOARD_SIZE_Y)+50, X_OFFSET+(BOARD_SIZE_X)+200, (BOARD_SIZE_Y)+50+32)
                   ,0
                   ,GUI_SAVE
                   ,L"Save game"
                   ,L"");

}


MyEventReceiver * ContextManager::getReceiver()
{
    return m_event_receiver;
}


// Appel aux fonctions d'affichage de l'interface utilisateur et de l'échiquier
// Call to the display functions for the user interface and the chessboard
void ContextManager::afficher()
{
    // Si cas promotion : fenêtre de promotion visible et activée
    // In case of a promotion : promotion window is visible and active
    m_promotion_window->setVisible(getPromotionBool());

    // Si on est dans un cas d'échec et mat et qu'on a pas affiché le message de fin, on l'affiche
    // If we're in a checkmate case and the ending message has not been displayed, it is displayed
    if(board.getEchecMat() && !m_message_echec_mat)
    {
        showEchecMat();
        // Evite d'afficher plusieurs fois le message
        // To prevent from displaying the message multiple times
        m_message_echec_mat = true;
    }

    m_device->getGUIEnvironment()->drawAll();

    // Affichage échiquier
    // Diplay the chessboard
    board.afficheEch(m_driver);
}

// Traitement des coordonnées récupérées
// Processing coordinates taken from the user
void ContextManager::processPosition(Coord & pos)
{
    if(m_event_receiver->left)
    {

        if(!m_click)
        {
            // Mise a jour du delta de temps pour le timer
            // Updating delta time for the timer
            m_delta_temps = m_temps_total;

            std::cout << std::endl;
            std::cout << "Starting point (x, y) : ";
            // Obtention des coordonnées affichées sur le plateau (voir def.h)
            // Get coordinates for the chessboard (see def.h) (IE : A7, H3...)
            std::cout << (char)(truncf((pos.x-X_OFFSET-BORDER_OFFSET) / SQUARE_SIZE) + 97) << " " << 8 - truncf((pos.y-Y_OFFSET) / SQUARE_SIZE) << std::endl;

            // Stockage des coordonnées réelles obtenues (de 0 a 7)
            // Stocking chessboard coordinates (0 to 7)
            m_pos_j.x = truncf((pos.x-X_OFFSET-BORDER_OFFSET) / SQUARE_SIZE);
            m_pos_j.y = truncf((pos.y-Y_OFFSET-BORDER_OFFSET) / SQUARE_SIZE);

            // Verifier que les coordonnées rentrées sont présentes sur l'échiquier
            // Check if the coordinates belong to the chessboard
            if(verifier(m_pos_j))
            {
                std::cout << "Staring piece : ";
                std::cout << board.getPosEch(m_pos_j) << std::endl;

                // On colore la pièce de départ et on passe en attente des coordonnées d'arrivées (voir m_click)
                // Starting piece is colored and we wait for the arrival coordinates
                board.setSelectedPiece(m_pos_j);
                m_click = true;

                // On attend 1/4 de seconde, pour éviter que les coordonnées et le clic de souris ne soient comptabilisés plusieurs fois
                // Wait 250 ms to avoid coordinates and mouse click to be registered multiple times
                m_device->sleep(250);

                // Début d'un tour, impossible d'annuler le mouvement
                // The turn starts, the previous move cannot be cancelled
                m_fin_tour = false;
            }

            return ;
        }
        else if(m_click)
        {
            std::cout << "Arrival point (x, y) : ";
            // Obtention des coordonnées affichées sur le plateau (voir def.h)
            // Get coordinates for the chessboard (see def.h) (IE : A7, H3...)
            std::cout << (char)(truncf((pos.x-X_OFFSET-BORDER_OFFSET) / SQUARE_SIZE) + 97) << " " << 8 - truncf((pos.y-Y_OFFSET) / SQUARE_SIZE) << std::endl;

            // Stockage des coordonnées réelles obtenues (de 0 a 7)
            // Stocking chessboard coordinates (0 to 7)
            m_pos_adv.x = truncf((pos.x-X_OFFSET-BORDER_OFFSET) / SQUARE_SIZE);
            m_pos_adv.y = truncf((pos.y-Y_OFFSET-BORDER_OFFSET) / SQUARE_SIZE);

            // Verifier que les coordonnées rentrées sont présentes sur l'échiquier
            // Check if the coordinates belong to the chessboard
            if(verifier(m_pos_adv))
            {
                std::cout << "Enemy piece : ";
                std::cout << board.getPosEch(m_pos_adv) << std::endl;
                std::cout << std::endl;

                // On remet les couleurs initiales de la pièce de départ et on passe en attente des coordonnées de départ (voir m_click)
                // Put the initial color back on the piece and wait for the start coordinates (see m_click)
                board.setStandardPiece(m_pos_j);
                m_click = false;

                // On attend 1/4 de seconde, pour éviter que les coordonnées et le clic de souris ne soient comptabilisés plusieurs fois
                // Wait 250 ms to avoid coordinates and mouse click to be registered multiple times
                m_device->sleep(250);


                // Déplacement d'une pièce avec les coordonnées sélectionnées
                // Move piece using the selected coordinates
                if(board.deplPiece(m_pos_j, m_pos_adv, m_tour))
                {
                    // Si le mouvement est correct et effectif, on change d'adversaire
                    // If the move is possible and has been done, we switch players
                    if(m_tour == 1)
                        m_tour = 2;
                    else
                        m_tour = 1;

                    // Appel à la fonction de l'échiquier qui vérifie si l'adversaire est en échec a la fin du tour suite au déplacement effectué
                    // Call chessboard function to check is the opponent is in a checkmate case at the end of the current turn
                    board.verifierEchec(m_tour);

                    // Fin d'un tour, mouvement réversible
                    // End of the turn, the move can now be canceled
                    m_fin_tour = true;
                }
            }

            return ;
        }

    }

}

// Gestion du timer
// Timer management
void ContextManager::timerManagement()
{
        // Si les blancs jouent
        // If white pieces are used
        if(m_tour == 1)
        {
                // Mise a jour du temps utilisé par les timers en secondes
                // Update time used by the timers (seconds)
                m_temps_J1 = m_device->getTimer()->getTime()/1000 - m_delta_temps;

                // Réglage du message a afficher
                // Change message to display
                m_str1 = L"Player 1 time : ";
                m_str1 += m_temps_J1;
                m_str1 += " s";

                // Si le delai du tour est fini, ou qu'on change de tour, le temps est mis à 0
                // If turn is over or if we reach the time limit for the turn, the player time is reset to 0
                if(m_temps_J1 >= DELAI_TOUR || m_fin_tour)
                {
                    m_str1 = L"Player 1 time : 0 s";
                }

                // Affichage du message
                // Display message
                m_text_time_J1->setText(m_str1.c_str());
        }
        // Si les noirs jouent
        // If white pieces are used
        else if(m_tour = 2)
        {
                // Mise a jour du temps utilisé par les timers en secondes
                // Update time used by the timers (seconds)
                m_temps_J2 = m_device->getTimer()->getTime()/1000 - m_delta_temps;

                // Réglage du message a afficher
                // Change message to display
                m_str2 = L"Player 2 time : ";
                m_str2 += m_temps_J2;
                m_str2 += " s";

                // Si le delai du tour est fini, ou qu'on change de tour, le temps est mis à 0
                // If turn is over or if we reach the time limit for the turn, the player time is reset to 0
                if(m_temps_J2 >= DELAI_TOUR || m_fin_tour)
                {
                    m_str2 = L"Player 2 time : 0 s";
                }

                // Affichage du message
                // Display the message
                m_text_time_J2->setText(m_str2.c_str());
        }
}

// Gestion du temps total écoulé
// Manager for the total time elapsed
void ContextManager::MAJTemps()
{
    // Mise a jour du temps total en secondes
    // Update total time (seconds)
    m_temps_total = m_device->getTimer()->getTime()/1000;

    // Réglage du texte à afficher
    // Change message to display
    m_str_total = L"Total time : ";
    m_str_total += m_temps_total;
    m_str_total += " s";

    // Affichage du texte
    // Display message
    m_text_total_time->setText(m_str_total.c_str());
}

// Gestion du score J1 et J2
// Score management for player 1 and 2
void ContextManager::MAJScore()
{
    // Obtention de la taille des réserves du joueur adverse
    // Get size of the piece stock for the players
    m_score_J1 = board.getSizeRes(2);
    m_score_J2 = board.getSizeRes(1);

    // Réglage du texte a afficher
    // Update message to display
    m_str_score1 = L"Player 1 score : ";
    m_str_score1 += m_score_J1;
    m_str_score1 += " pts";

    m_str_score2 = L"Player 2 score : ";
    m_str_score2 += m_score_J2;
    m_str_score2 += " pts";

    // Affichage des scores
    // Display score
    m_text_score_J1->setText(m_str_score1.c_str());
    m_text_score_J2->setText(m_str_score2.c_str());
}


// Appel a la fonction de promotion d'un pion avec un caractère représentant la pièce choisie
// Call function that promotes a piece (argument is type of piece to promote to)
void ContextManager::ajouterPiecePromotion(char type)
{
    board.upgradePion(type, m_driver);

    // RAZ coordonnées du pion et booléen
    // Reset pawn coordinates and boolean for the promotion
    board.razPromotedPion();
    board.razPromotionPion();
}

// Fonction getter pour le booléen relatif a la promotion dans la classe échiquier
// Getter for the promotion boolean
bool ContextManager::getPromotionBool()
{
    return board.getPromotionPion();
}

// Fonction getter pour le booléen relatif a la fin d'un tour dans la classe contextmanager
// Getter for the end-of-turn boolean
bool ContextManager::getFinTourBool()
{
    return m_fin_tour;
}


// Getter et setter pour le numéro de tour (utilisation dans l'event receiver)
// Getter and setter for the turn number (used in event receiver)
unsigned int ContextManager::getTour()
{
    return m_tour;
}

void ContextManager::setTour(unsigned int t)
{
    m_tour = t;
}


// Getter et setter pour le type d'opération a effectuer sur le fichier choisi (sauvegarde/chargement, utilisation dans l'event receiver)
// Getter and setter for the operation type for the files (load/save) used in event receiver
unsigned int ContextManager::getOuvrirFichier()
{
    return m_ouvrir_fichier;
}

void ContextManager::setOuvrirFichier(unsigned int attr)
{
    if(attr == GAME_LOAD || attr == GAME_SAVE)
        m_ouvrir_fichier = attr;
}


// Fonction getter pour le booléen relatif a l'échec et mat dans la classe échiquier
// Getter for the checkmate boolean
bool ContextManager::getEchecMatBool()
{
    return board.getEchecMat();
}

// Appel a la fonction verifierEchec de l'échiquier (fonction utilisée dans l'évent receiver)
// Call to the function verifierEchec (check checkmate) (event receiver)
void ContextManager::verifierEchec()
{
    board.verifierEchec(m_tour);
}


// Appel a la fonction d'annulation du dernier mouvement fait
// Call to the cancel move function
bool ContextManager::annulerMvt()
{
    bool tmp;

    // Appel a la fonction d'annulation du mouvement avec l'id du joueur qui a déplacé la pièce
    // Call to the cancel move function with the player id
    tmp = board.revPiece(m_tour, m_pos_j, m_pos_adv);
    board.afficheEch(m_driver);

    // Un seul appel a la fois
    // Can only be called once at the time
    m_fin_tour = false;

    return tmp;
}


// Fonction d'affichage d'un message indiquant l'échec et mat d'un joueur
// Display function (player checkmate)
void ContextManager::showEchecMat()
{
    // Récupération de la string
    // Get string
    std::string str = board.getEchecMatTxt();

    // Taille de la string
    // String size
    size_t size = str.size();

    // Rajoute la taille du caractère de fin de chaine
    // Add char size at the end of the string
    wchar_t *text = new wchar_t[size+sizeof(wchar_t)];
    // on prend le pointeur sur le premier caractère
    // get pointer on first char
    const char *data = &str[0];

    // Conversion en wchar_t*
    // wchar_t* conversion
    mbsrtowcs(text, &data, size, NULL);
    // Rajout du caractère de fin de chaine
    // Add end of string char
    text[size] = L'\0';

    // Passage a une stringw
    // Conversion to stringw
    stringw matTxt = text;

    // Fenêtre d'annonce d'échec et mat
    // Display window
    env->addMessageBox(L"End of the game", matTxt.c_str());
}


// Ouvre une boite de dialogue de sélection de fichier (utilisé dans le chargement / sauvegarde de parties)
// Function opening a dialog box to select a file (load / save game)
void ContextManager::selectionFichier(stringw windowText)
{
    env->addFileOpenDialog(windowText.c_str(), true, 0, -1, true);
}

// Appel a la fonction de chargement d'une partie (classe échiquier)
// Call game loading function (chessboard class)
void ContextManager::chargerPartie(std::string path)
{
    board.chargerPartie(path, m_driver);
}

// Appel a la fonction de sauvegarde d'une partie (classe échiquier)
// Call game saving function (chessboard class)
void ContextManager::sauverPartie(std::string path)
{
    board.sauverPartie(path);
}
