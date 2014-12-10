/*
 *  Exception.cpp
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 12/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include <sstream>

using std::ostringstream;

#include "Exception.hpp"


//
const char* CException::getMessage() const
{
	return m_strMessage.c_str();
}


// Note: a bit heavy for an exception
const char* CParseErrorException::getMessage() const
{
	ostringstream oss("");
	oss << CException::getMessage() << " (line "<< m_lineNumber <<")";
	return oss.str().c_str();
}
