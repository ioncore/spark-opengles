/*
 *  ParserTest.cpp
 *  ToolSDL
 *
 *  Created by Seb on 18/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "MtlParserTest.hpp"
#include "MtlParser.hpp"
#include "Material.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CMtlParserTest);

/////////////////////////////////
//  Test the ".mtl" files parser

void CMtlParserTest::testParse()
{
	//  Setup
	MaterialMap_t mtlMap;

	//  Process
	CMtlParser::parse(mtlMap, "Data/Test.mtl");
	MaterialMap_t::iterator it = mtlMap.find("testMtl");

	//  Check
	CPPUNIT_ASSERT(mtlMap.end() != it);
	SMaterial& mtl = (*it).second;
	CPPUNIT_ASSERT("testMtl" == mtl.strName);
	CPPUNIT_ASSERT(1.1f == mtl.Ka[0]);
	CPPUNIT_ASSERT(2.1f == mtl.Kd[0]);
	CPPUNIT_ASSERT(3.1f == mtl.Ks[0]);
	CPPUNIT_ASSERT("Data/texture.path" == mtl.map_Kd);
}