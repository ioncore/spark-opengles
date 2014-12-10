/*
 *  MtlParser.cpp
 *  ToolSDL
 *
 *  Created by Seb on 19/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "MtlParser.hpp"
#include "MtlGrammar.hpp"
#include "Exception.hpp"

////////////////////////////////////////////////////////////////////////////////
//  Parse a ".mtl" file and add its materials to the given map.
void CMtlParser::parse(MaterialMap_t& materialMap, const string& strFilePath)
{
	//	setup the file
	iterator_t first(strFilePath);
	if (!first)
		throw CFileNotFoundException(strFilePath);
	iterator_t last = first.make_end();
	//  lookup the branch path and pass the material map to a manager
	path branchPath = path(strFilePath).branch_path();
	CMtlMapManager mtlMapManager(materialMap, branchPath);
	// setup the actions and grammar
	CMtlActions mtlActions(mtlMapManager);
	CMtlGrammar mtlGrammar(mtlActions);
	//  process
	parse_info<iterator_t> parseInfo = boost::spirit::parse(first, last, mtlGrammar);
	if (!parseInfo.full)
		throw CParseErrorException(strFilePath, -1);
}
