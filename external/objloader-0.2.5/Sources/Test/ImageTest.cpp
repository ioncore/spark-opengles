/*
 *  ImageTest.cpp
 *  ToolSDL
 *
 *  Created by Seb on 16/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ImageTest.hpp"
#include "Image.hpp"
#include "Exception.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CImageTest);


//
void CImageTest::testConstructor()
{
	shared_ptr<CImage> pImage(new CImage("Data/Images/Test.jpg"));
	CPPUNIT_ASSERT(NULL != pImage);
}


//
void CImageTest::testFileNotFoundThrows()
{
	shared_ptr<CImage> pImage(new CImage("NotAFile"));
}


//
void CImageTest::testCopy()
{
	shared_ptr<CImage> pImage(new CImage("Data/Images/Test.jpg"));
	shared_ptr<CImage> pOtherImage(new CImage("Data/Images/Test.jpg"));

	// Check
	CPPUNIT_ASSERT(1 == pImage.use_count());
	{
		//	test that the copy ctor increments use_count
		shared_ptr<CImage> pImageCopy(pImage);
		CPPUNIT_ASSERT(2 == pImage.use_count());
		//	test equality
		CPPUNIT_ASSERT(pImageCopy == pImage);
	}
	//	test that the dtor decrements use_count
	CPPUNIT_ASSERT(1 == pImage.use_count());

	shared_ptr<CImage> pImageCopy(pImage);
	CPPUNIT_ASSERT(2 == pImage.use_count());
	CPPUNIT_ASSERT(1 == pOtherImage.use_count());
	pImageCopy = pOtherImage;
	//	test that the assignment operator decrements the old value and increments the new one
	CPPUNIT_ASSERT(1 == pImage.use_count());
	CPPUNIT_ASSERT(2 == pOtherImage.use_count());
	//	test equality
	CPPUNIT_ASSERT(pImageCopy == pOtherImage);
}
