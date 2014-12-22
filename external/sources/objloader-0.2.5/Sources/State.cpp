/*
 *  State.cpp
 *  ToolSDL
 *
 *  Created by Seb on 08/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "State.hpp"

CState& CState::getInstance()
{
	static CState theState;
	return theState;
}