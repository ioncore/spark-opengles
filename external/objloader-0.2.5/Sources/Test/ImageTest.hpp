/*
 *  ImageTest.hpp
 *  ToolSDL
 *
 *  Created by Seb on 16/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMAGETEST_HPP__
#define __IMAGETEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class CImageLoadException;

//
class CImageTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CImageTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST_EXCEPTION(testFileNotFoundThrows, CImageLoadException);
	CPPUNIT_TEST(testCopy);
	CPPUNIT_TEST_SUITE_END();
	
public:
//	void setUp();
//	void tearDown();
	
protected:
	void testConstructor();
	void testFileNotFoundThrows();
	void testCopy();
};

#endif
