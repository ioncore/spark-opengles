/*
 *  MeshTest.h
 *  ToolSDL
 *
 *  Simple test case.
 *
 *  Created by Seb on 02/01/06.
 *  Copyright 2006 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __MESHTEST_H__
#define __MESHTEST_H__

#include <cppunit/extensions/HelperMacros.h>

class CMesh;

//
class CMeshTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CMeshTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testAddVertex);
	CPPUNIT_TEST(testClear);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

protected:
	void testConstructor();
	void testAddVertex();
	void testClear();
	
	CMesh* pMesh_;
};

#endif
