/*
 *  TooLTestManager.h
 *  ToolSDL
 *
 *  Created by Seb on 06/01/06.
 *  Copyright 2006 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __TOOLTESTMANAGER_H__
#define __TOOLTESTMANAGER_H__

class CTooLTestManager {
public:
	static CTooLTestManager& getInstance();
	int run();

private:
	CTooLTestManager();
	CTooLTestManager(const CTooLTestManager& rhs);
};

#endif//__TOOLTESTMANAGER_H__
