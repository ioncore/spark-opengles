/*
 *  TextureTest.hpp
 *  ToolSDL
 *
 *  Created by Seb on 16/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __TEXTURETEST_HPP__
#define __TEXTURETEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

class CImageLoadException;

//
class CTextureTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CTextureTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST_EXCEPTION(testFileNotFoundThrows, CImageLoadException);
	CPPUNIT_TEST(testCopy);
	CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp();
	void tearDown();
	
protected:
	void testConstructor();
	void testFileNotFoundThrows();
	void testCopy();
};

#endif
