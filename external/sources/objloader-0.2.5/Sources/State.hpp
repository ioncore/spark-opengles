/*
 *  State.h
 *  ToolSDL
 *
 *  Created by Seb on 08/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __STATE_H__
#define __STATE_H__

#include "stable.pch"
//
class CState {
public:
	static CState& getInstance();
	
	bool isTesting_;

private:
	CState() : isTesting_(false) {}
	CState(const CState& rhs);
};

#endif //__STATE_H__
