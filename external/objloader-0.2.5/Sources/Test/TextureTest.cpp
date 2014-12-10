/*
 *  TextureTest.cpp
 *  ToolSDL
 *
 *  Created by Seb on 16/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "TextureTest.hpp"
#include "Texture.hpp"
#include "Exception.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CTextureTest);

//
void CTextureTest::setUp()
{
}
//
void CTextureTest::tearDown()
{
}


//
void CTextureTest::testConstructor()
{
	CTexture texture("Data/Images/Test.jpg");
}


//
void CTextureTest::testFileNotFoundThrows()
{
	CTexture texture("NotAFile-Hopefully");
}


//	See also: CImageTest::testCopy(), which does the hard work.
void CTextureTest::testCopy()
{
	const CTexture texture_1("Data/Images/Test.jpg");
	CTexture texture_2(texture_1);
	CTexture texture_3("Data/Images/Test.jpg");
	texture_3 = texture_1;
	
	//  Check
	CPPUNIT_ASSERT(texture_1 == texture_2);
	CPPUNIT_ASSERT(texture_1 == texture_3);
}
