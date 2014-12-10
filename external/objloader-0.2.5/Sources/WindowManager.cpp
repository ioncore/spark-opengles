/*
 *  WindowManager.cpp
 *  Tool
 *
 *  All the window related ops go here.
 *
 *  Created by Seb on 20/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include "WindowManager.hpp"
#include "Exception.hpp"
#include "MeshViewer.hpp"
#include "KeyboardController.hpp"
#include "MouseController.hpp"


//  ctor
CWindowManager::CWindowManager()
: m_pScreen(NULL)
{}


//	dtor
CWindowManager::~CWindowManager()
{
	// Clean up.
	SDL_FreeSurface(m_pScreen);	//	calling SDL_FreeSurface() on a NULL pointer is safe
	SDL_Quit();
}

//
CWindowManager& CWindowManager::get()
{
	static CWindowManager theWindowManager;
	return theWindowManager;
}


// SDL init job
void CWindowManager::createWindow(int x, int y, int w, int h, const std::string& strTitle)
{
	if (NULL != m_pScreen)
		throw CException();
	
	CLogger::get() << "Creating display...\n"; // Remove me: dev. info.
	// Init SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw CWindowManagerInitFailedException(SDL_GetError());

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

    Uint32 flags = SDL_OPENGL;
    // Create window
    m_pScreen = SDL_SetVideoMode(w, h, 0, flags);
	
    if (m_pScreen == NULL) {
		SDL_Quit();
		throw CWindowCreationFailedException(SDL_GetError());
	}
	SDL_WM_SetCaption(strTitle.c_str(), NULL);

 	//  setting OpenGL state
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_BLEND);
	glEnable (GL_LINE_SMOOTH);
	glCullFace(GL_NONE);
	glEnable (GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


//
void CWindowManager::startLoop()
{
	// starting loop
	CLogger::get() << "Starting loop...\n";
	SDL_Event event;
	float fps = 25;
	float msDelay = 1000/fps;
    int thenTicks = -1;
    int nowTicks;
	m_bRun = true;
	while (m_bRun)
	{
		/* Check for events */
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					CMouseController::getInstance().motion(event.motion.x, event.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					CMouseController::getInstance().buttonDown(event.button.x, event.button.y);
					break;
				case SDL_MOUSEBUTTONUP:
					CMouseController::getInstance().buttonUp();
					break;
				case SDL_KEYDOWN:
					CKeyboardController::getInstance().keyDown(event.key.keysym.sym);
					break;
				case SDL_QUIT:
					stopLoop();
					break;
				default:
					break;
			}
		}
        // Draw at 24 hz
        //     This approach is not normally recommended - it is better to
        //     use time-based animation and run as fast as possible
		CMeshViewer::getInstance().animate(0);
		CMeshViewer::getInstance().draw();
        SDL_GL_SwapBuffers ();

        // Time how long each draw-swap-delay cycle takes
        // and adjust delay to get closer to target framerate
        if (thenTicks > 0) {
            nowTicks = SDL_GetTicks ();
            msDelay += (1000/fps - (nowTicks-thenTicks));
            thenTicks = nowTicks;
            if (msDelay < 0)
                msDelay = 1000/fps;
        }
        else {
            thenTicks = SDL_GetTicks ();
        }
        SDL_Delay(static_cast<int>(msDelay));
	}
}


//
void CWindowManager::stopLoop()
{
	CLogger::get() << "Leaving loop.\n";
	m_bRun = false;
}


//
void CWindowManager::printScreen()
{
	assert(NULL != m_pScreen);
//	SDL_LockSurface(m_pScreen);
	if (NULL != SDL_SaveBMP(m_pScreen, "TooLScreenCapture.bmp"))
		CLogger::get() << "Error while saving screenshot...";
//	SDL_UnlockSurface(m_pScreen);
}
