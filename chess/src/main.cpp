/*
 *  Ludovic Salmon
 *  Université de bretagne sud
 *  M1 GEII
 *  2013-2014
 */

/*
The program will show how to use the
basics of the VideoDriver, the GUIEnvironment and the
SceneManager.

To use the engine, we will have to include the header file
irrlicht.h, which can be found in the Irrlicht Engine SDK
directory \include.
*/
#include <irrlicht.h>
#include <IGUIEnvironment.h>
#include "ContextManager.h"
#include "Piece.h"
#include <iostream>
#include <sstream>
#include <string>
#include "driverChoice.h"

/*
In the Irrlicht Engine, everything can be found in the namespace
'irr'. So if you want to use a class of the engine, you have to
write an irr:: before the name of the class. For example to use
the IrrlichtDevice write: irr::IrrlichtDevice. To get rid of the
irr:: in front of the name of every class, we tell the compiler
that we use that namespace from now on, and we will not have to
write that 'irr::'.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look
at them, you can read a detailed description of them in the
documentation by clicking on the top menu item 'Namespace List'
or using this link: http://irrlicht.sourceforge.net/docu/namespaces.html.
Like the irr Namespace, we do not want these 5 sub namespaces now,
to keep this example simple. Hence we tell the compiler again
that we do not want always to write their names:
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

/*
This is the main method. We can use void main() on every platform.
On Windows platforms, we could also use the WinMain method
if we would want to get rid of the console window, which pops up when
starting a program with main(), but to keep this example simple,
we use main().
*/
int main(int argc, char** argv)
{
    /*
    The most important function of the engine is the 'createDevice'
    function. The Irrlicht Device can be created with it, which is the
    root object for doing everything with the engine.
    createDevice() has 7 paramters:
    deviceType: Type of the device. This can currently be the Null-device,
       the Software device, DirectX8, DirectX9, or OpenGL. In this example we use
       EDT_SOFTWARE, but to try out, you might want to change it to
       EDT_NULL, EDT_DIRECTX8 , EDT_DIRECTX9, or EDT_OPENGL.
    windowSize: Size of the Window or FullscreenMode to be created. In this
       example we use 640x480.
    bits: Amount of bits per pixel when in fullscreen mode. This should
       be 16 or 32. This parameter is ignored when running in windowed mode.
    fullscreen: Specifies if we want the device to run in fullscreen mode
       or not.
    stencilbuffer: Specifies if we want to use the stencil buffer for drawing shadows.
    vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen
      mode.
    eventReceiver: An object to receive events. We do not want to use this
       parameter here, and set it to 0.
    */

    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;
    ContextManager manager;
    IrrlichtDevice *device =
        createDevice(driverType, dimension2d<u32>(1024, 600), 32,
            false, false, false, manager.getReceiver());


    device->setWindowCaption(L"Chess game - Irrlicht");


    /*
    Get a pointer to the video driver, the SceneManager and the
    graphical user interface environment, so that
    we do not always have to write device->getVideoDriver(),
    device->getSceneManager() and device->getGUIEnvironment().
    */
    IVideoDriver* driver = device->getVideoDriver();

    // Initialise l'environnement de jeu
    // Initialize game environment
    manager.init(device);
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
    driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;


    // Initialise toutes les polices de caractère de l'environnement graphique
    // Initialize font environment
    guienv->getSkin()->setFont(guienv->getFont("./font/fontlucida.png"));

    // La fenêtre principale est ajustable
    // The main window is resizable
    device->setResizable(true);

    // On démarre le timer du programme
    // Start program timer
    device->getTimer()->start();

    // On affiche une première fois l'environement de jeu
    // Display game environment once
    manager.afficher();

    /*
    Ok, now we have set up the scene, lets draw everything:
    We run the device in a while() loop, until the device does not
    want to run any more. This would be when the user closed the window
    or pressed ALT+F4 in windows.
    */
    while(device->run())
    {
        /*
        Anything can be drawn between a beginScene() and an endScene()
        call. The beginScene clears the screen with a color and also the
        depth buffer if wanted. Then we let the Scene Manager and the
        GUI Environment draw their content. With the endScene() call
        everything is presented on the screen.
        */
        driver->beginScene(true, true, SColor(255,200,200,200));
        core::position2d<s32> m = device->getCursorControl()->getPosition();
        Coord pos;


        // Gestion du timer
        // Timer management
        manager.timerManagement();
        // Gestion du temps total
        // Total time management
        manager.MAJTemps();

        pos.x = m.X;
        pos.y = m.Y;
        manager.processPosition(pos);
        manager.afficher();

        // Mise a jour des scores après un mouvement ou essai de mouvement
        // Update scores after moving or trying to move a piece
        manager.MAJScore();

        guienv->drawAll();

        driver->endScene();
    }

    /*
    After we are finished, we have to delete the Irrlicht Device
    created before with createDevice(). In the Irrlicht Engine,
    you will have to delete all objects you created with a method or
    function which starts with 'create'. The object is simply deleted
    by calling ->drop().
    See the documentation at
    http://irrlicht.sourceforge.net//docu/classirr_1_1IUnknown.html#a3
    for more information.
    */
    device->drop();

    return 0;
}
