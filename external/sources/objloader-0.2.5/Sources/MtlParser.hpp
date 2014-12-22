/*
 *  Parser.hpp
 *  ToolSDL
 *
 *  Created by Seb on 18/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MTLPARSER_HPP__
#define __MTLPARSER_HPP__

#include "Material.hpp"

//////////////////
//
//////////////////
class CMtlParser {
public:
	static void parse(MaterialMap_t& materialMap, const string& strFilePath);
};

#endif // __MTLPARSER_HPP__