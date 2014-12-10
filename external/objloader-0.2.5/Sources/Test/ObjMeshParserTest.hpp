/*
 *  ObjMeshParserTest.h
 *  ToolSDL
 *
 *  Created by Seb on 06/01/06.
 *  Copyright 2006 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __OBJMESHPARSERTEST_H__
#define __OBJMESHPARSERTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class CMesh;


//
class CObjMeshParserTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CObjMeshParserTest);
	CPPUNIT_TEST(testParse);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

protected:
	void testParse();
	
	shared_ptr<CMesh> m_pMesh;
};

#endif
