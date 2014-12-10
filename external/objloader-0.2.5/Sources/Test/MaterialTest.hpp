/*
 *  MaterialTest.hpp
 *  ToolSDL
 *
 *  Created by Seb on 17/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MATERIALTEST_HPP__
#define __MATERIALTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>


//
class CMaterialTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CMaterialTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testCopy);
	CPPUNIT_TEST_SUITE_END();
	
public:
//	void setUp();
//	void tearDown();
	
protected:
	void testConstructor();
	void testCopy();
};

#endif
