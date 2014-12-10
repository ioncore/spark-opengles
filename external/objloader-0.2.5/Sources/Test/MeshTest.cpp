/*
 *  MeshTestCase.cpp
 *  ToolSDL
 *
 *  Created by Seb on 02/01/06.
 *  Copyright 2006 The Old Game Factory. All rights reserved.
 *
 */
#include "MeshTest.hpp"
#include "Mesh.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CMeshTest);


//
void CMeshTest::setUp()
{
	pMesh_ = new CMesh();
}
//
void CMeshTest::tearDown()
{
	delete pMesh_;
}


//
void CMeshTest::testConstructor()
{
	//  Check
	CPPUNIT_ASSERT(0 == pMesh_->getNumVertices());
	CPPUNIT_ASSERT(0 == pMesh_->getNumNormals());
	CPPUNIT_ASSERT(0== pMesh_->getNumFaces());
	CPPUNIT_ASSERT(false == pMesh_->hasNormals());
	CPPUNIT_ASSERT((numeric_limits<float>::max() == pMesh_->m_minVert.x)
		&& (numeric_limits<float>::max() == pMesh_->m_minVert.y)
		&& (numeric_limits<float>::max() == pMesh_->m_minVert.z));
	CPPUNIT_ASSERT((-numeric_limits<float>::max() == pMesh_->m_maxVert.x)
		&& (-numeric_limits<float>::max() == pMesh_->m_maxVert.y)
		&& (-numeric_limits<float>::max() == pMesh_->m_maxVert.z));
}


//
void CMeshTest::testAddVertex()
{
	//  Process
	const float fMin = 3;
	const float fMax = 5;
	pMesh_->addVertex(SVertex(fMin, fMin, fMin));
	pMesh_->addVertex(SVertex(fMax, fMax, fMax));
	
	//  Check
	CPPUNIT_ASSERT(2 == pMesh_->getNumVertices());
	CPPUNIT_ASSERT((fMin == pMesh_->m_minVert.x) && (fMax == pMesh_->m_maxVert.x));
	CPPUNIT_ASSERT((fMin == pMesh_->m_minVert.y) && (fMax == pMesh_->m_maxVert.y));
	CPPUNIT_ASSERT((fMin == pMesh_->m_minVert.z) && (fMax == pMesh_->m_maxVert.z));
}


//
void CMeshTest::testClear()
{
	//  Process
	const float fMin = 3;
	const float fMax = 5;
	pMesh_->addVertex(SVertex(fMin, fMin, fMin));
	pMesh_->addVertex(SVertex(fMax, fMax, fMax));
	pMesh_->clear();
	
	//  Check
	CPPUNIT_ASSERT(0 == pMesh_->getNumVertices());
	CPPUNIT_ASSERT(0 == pMesh_->getNumVertices());
	CPPUNIT_ASSERT(0 == pMesh_->getNumNormals());
	CPPUNIT_ASSERT(0== pMesh_->getNumFaces());
	CPPUNIT_ASSERT(false == pMesh_->hasNormals());
	CPPUNIT_ASSERT((numeric_limits<float>::max() == pMesh_->m_minVert.x)
		&& (numeric_limits<float>::max() == pMesh_->m_minVert.y)
		&& (numeric_limits<float>::max() == pMesh_->m_minVert.z));
	CPPUNIT_ASSERT((-numeric_limits<float>::max() == pMesh_->m_maxVert.x)
		&& (-numeric_limits<float>::max() == pMesh_->m_maxVert.y)
		&& (-numeric_limits<float>::max() == pMesh_->m_maxVert.z));
}
