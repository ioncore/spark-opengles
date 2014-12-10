/*
 *  MouseController.h
 *  The OpenGL Obj Loader
 *
 *  Contains mouse related logic.
 *
 *  Created by Seb on 15/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __MOUSECONTROLLER_H__
#define __MOUSECONTROLLER_H__


//	singleton pattern
class CMouseController {
public:
	//	singleton pattern
	static CMouseController& getInstance() {
		static CMouseController theMouseController;
		return theMouseController;
	}

	void buttonDown(int x, int y);
	void buttonUp();
	void motion(int x,  int y);

private:
	//	singleton pattern
	CMouseController() : m_bButtonDown(false) {}
	CMouseController(const CMouseController& rhs);	//	don't define copy ctor so the compiler prevents calls
	
	int m_x, m_y;
	bool m_bButtonDown;
};

#endif //__MOUSECONTROLLER_H__
