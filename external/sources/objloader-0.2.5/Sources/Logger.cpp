/*
 *  Logger.cpp
 *  ToolSDL
 *
 *  Created by Seb on 09/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "Logger.hpp"


//	REMEMBER: don't put static code in a precompiled header...
CLogger& CLogger::get()
{
	static CLogger theLogger;
	return theLogger;
}


//
CLogger& CLogger::operator<<(ostream& (*pFunc)(ostream&))
{
#ifndef NDEBUG
	if (m_isOn)
		m_os << pFunc;
#endif //NDEBUG
	return *this;
}
