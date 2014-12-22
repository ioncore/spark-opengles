/*
 *  MaterialTest.cpp
 *  ToolSDL
 *
 *  Created by Seb on 17/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "MaterialTest.hpp"
#include "Material.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(CMaterialTest);

//
void CMaterialTest::testConstructor()
{
	SMaterial m;
	CPPUNIT_ASSERT("" == m.map_Kd);
}


//	See also: CImageTest::testCopy(), which does the hard work.
void CMaterialTest::testCopy()
{
	SMaterial mat_1;
	{
		SMaterial mat_2;
		mat_2.Ka[1] = 0.5f;
		mat_1 = mat_2;
	}
	//  Check
	CPPUNIT_ASSERT(0.5f == mat_1.Ka[1]);
}
