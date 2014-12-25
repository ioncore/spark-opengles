/*
 *  Exception.h
 *  The OpenGL Obj Loader
 *
 *  The project exceptions
 *
 *  Created by Seb on 11/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include "stable.pch"


//	Root exception for the project
class CException : public std::exception {
public:
	CException() throw() {}
	CException(const string& str) : m_strMessage(str) {}
	virtual ~CException() throw() {} 
	virtual const char* getMessage() const;

private:
	string m_strMessage;
};


//	If a file is not found
class CFileNotFoundException : public CException {
public:
	CFileNotFoundException(const string& strFileName) : CException("file \""+strFileName+"\" not found")
	{}
};


//	simple exception types
class CEmptyFileException : public CException {
public:
	CEmptyFileException() : CException("empty file")
	{}
};
//
class CNullMeshPointerException : public CException {
public:
	CNullMeshPointerException() : CException("mesh pointer not set before starting the viewer")
	{}
};
//
class CWindowManagerInitFailedException : public CException {
public:
	CWindowManagerInitFailedException(const string& strError) : CException("couldn't initialize SDL (\""+strError+"\")")
	{}
};
//
class CWindowCreationFailedException : public CException {
public:
	CWindowCreationFailedException(const string& strError) : CException("window creation failed, "+strError)
	{}
};
//
class CImageLoadException : public CException {
public:
	CImageLoadException(const string& strFileName) : CException("failed to load image (\""+strFileName+"\")")
	{}
};


//	If a line cannot be parsed, throw a CParseErrorException
//  Note: a bit heavy for an exception.
class CParseErrorException : public CException {
public:
	CParseErrorException(const string& strFileName, int lineNumber)
	: CException("parse error in file \""+strFileName+"\"")
	, m_lineNumber(lineNumber)
	{}

	virtual const char* getMessage() const;

private:
	int m_lineNumber;
};

#endif //__EXCEPTION_H__
