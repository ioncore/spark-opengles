/*
 *  ObjMeshParserTest.cpp
 *  ToolSDL
 *
 *  Created by Seb on 06/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "ObjMeshParserTest.hpp"
#include "ObjMeshParser.hpp"
#include "Mesh.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CObjMeshParserTest);


//
void CObjMeshParserTest::setUp()
{
	m_pMesh.reset(new CMesh());
}
//
void CObjMeshParserTest::tearDown()
{
}


//
void CObjMeshParserTest::testParse()
{
	CObjMeshParser::parse(m_pMesh, "Data/Cube.obj");
}

