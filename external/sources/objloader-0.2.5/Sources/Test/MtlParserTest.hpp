/*
 *  ParserTest.hpp
 *  ToolSDL
 *
 *  Created by Seb on 18/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __PARSERTEST_HPP__
#define __PARSERTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>


//
class CMtlParserTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CMtlParserTest);
	CPPUNIT_TEST(testParse);
	CPPUNIT_TEST_SUITE_END();
	
protected:
	void testParse();
};

#endif
