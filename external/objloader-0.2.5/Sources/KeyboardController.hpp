/*
 *  KeyboardController.h
 *  The OpenGL Obj Loader
 *
 *  Contains keyboard related logic.
 *
 *  Created by Seb on 19/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __KEYBOARDCONTROLLER_H__
#define __KEYBOARDCONTROLLER_H__


//	singleton pattern
class CKeyboardController {
public:
	//	singleton pattern
	static CKeyboardController& getInstance() {
		static CKeyboardController theKeyboardController;
		return theKeyboardController;
	}

	void keyDown(SDLKey key) const;
	bool getCtrlState();
	bool getAltState();
	bool getShiftState();

private:
	//	singleton pattern
	CKeyboardController() {}
	CKeyboardController(const CKeyboardController& rhs);	//	don't define copy ctor so the compiler prevents calls
};


#endif //__KEYBOARDCONTROLLER_H__
