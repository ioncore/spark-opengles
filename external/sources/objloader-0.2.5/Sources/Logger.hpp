/*
 *  Logger.h
 *  ToolSDL
 *
 *  Created by Seb on 09/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "stable.pch"
//
class CLogger
{
public:
	static CLogger& get();

	//	Template member functions
	template<class T>
	CLogger& operator<<(const T& info);

	CLogger& operator<<(ostream& (*pFunc)(ostream&));	//	endl, flush...
	bool m_isOn;

private:
	CLogger() : m_isOn(true), m_os(std::cerr.rdbuf()) {}
	CLogger(const CLogger& rhs);
	
	ostream m_os;
};


//
template<class T>
CLogger& CLogger::operator<<(const T& info)
{
#ifndef NDEBUG
	if (m_isOn) {
		m_os << info;
	}
#endif //NDEBUG
	return *this;
}

#endif //__LOGGER_HPP__
