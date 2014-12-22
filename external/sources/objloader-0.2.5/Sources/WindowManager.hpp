/*
 *  WindowManager.h
 *  Tool
 *
 *  All the window related ops go here.
 *
 *  Created by Seb on 20/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__


//
class CWindowManager {
public:
	static CWindowManager& get();
	~CWindowManager();

	void createWindow(int x, int y, int w, int h, const string& strTitle);
	void startLoop();
	void stopLoop();
	void printScreen();

private:
	CWindowManager();
	CWindowManager(CWindowManager& rhs);

	int m_windowID;
	SDL_Surface* m_pScreen;
	bool m_bRun;
};

#endif// __WINDOWMANAGER_H__
