/*
 *  ObjMeshParser.h
 *  The OpenGL Obj Loader
 *
 *  Contains parsing logic.
 *
 *  Created by Seb on 13/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */

#ifndef __OBJMESHPARSER_H__
#define __OBJMESHPARSER_H__

class CMesh;
struct SMaterial;


//////////////////////
//	".obj" file parser
//////////////////////
class CObjMeshParser {
public:
	static void	parse(shared_ptr<CMesh>& pMesh, const string& strFileName);
		//  REQUIRE: given file must contain one and only one mesh object (first iteration requirement).
		//  PROMISE: param. "mesh" contains the parsed content.
	static void	parseMtlLib(const string& strFileName);
		//	REQUIRE: the ".mtl" file must be fully valid, unsupported keywords are ignored but recognized.
		//	REQUIRE: the .mtl file may contain more than one material.
		//	PROMISE: every material contained in the file is added to the material map, identified by its name.
	static bool	processLine(shared_ptr<CMesh>& pMesh, istream& is);
		//  PROMISE: return false at end of stream.

private:
	static void	skipLine(istream& is);
	static bool	skipCommentLine(istream& is);

	static path	m_branchPath;
	static map<string, SMaterial>	m_materialMap;
};



#endif //__OBJMESHPARSER_H__
