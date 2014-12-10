/*
 *  KeyboardController.cpp
 *  The OpenGL Obj Loader
 *
 *  Contains keyboard related logic.
 *
 *  Created by Seb on 19/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include "KeyboardController.hpp"
#include "MeshViewer.hpp"
#include "WindowManager.hpp"

//
void CKeyboardController::keyDown(SDLKey key) const
{
	if (SDLK_RETURN == key)
		CMeshViewer::getInstance().resetScene();
	else if (SDLK_F12 == key)
		CWindowManager::get().printScreen();
	else if (SDLK_q == key
		|| SDLK_ESCAPE == key)
		CWindowManager::get().stopLoop(); // Q, or ESC to quit...
}

//
bool CKeyboardController::getCtrlState()
{
	Uint8* pKeyStates = SDL_GetKeyState(NULL);
	bool bRet = (pKeyStates[SDLK_LCTRL] != 0) || (pKeyStates[SDLK_RCTRL] != 0);
	return bRet;
}
//
bool CKeyboardController::getAltState()
{
	Uint8* pKeyStates = SDL_GetKeyState(NULL);
	bool bRet = (pKeyStates[SDLK_LALT] != 0) || (pKeyStates[SDLK_RALT] != 0);
	return bRet;
}
//
bool CKeyboardController::getShiftState()
{
	Uint8* pKeyStates = SDL_GetKeyState(NULL);
	bool bRet = (pKeyStates[SDLK_LSHIFT] != 0) || (pKeyStates[SDLK_RSHIFT] != 0);
	return bRet;
}
