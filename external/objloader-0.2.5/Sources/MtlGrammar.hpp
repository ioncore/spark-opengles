/*
 *  MtlGrammar.hpp
 *  ToolSDL
 *
 *  Created by Seb on 18/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MTLGRAMMAR_HPP__
#define __MTLGRAMMAR_HPP__

using boost::spirit::grammar;
using boost::spirit::rule;
using boost::spirit::symbols;
using boost::spirit::parse_info;
using boost::spirit::space_p;
using boost::spirit::blank_p;
using boost::spirit::eol_p;
using boost::spirit::comment_p;
using boost::spirit::str_p;
using boost::spirit::ch_p;
using boost::spirit::anychar_p;
using boost::spirit::real_p;
using boost::spirit::assign_a;
using boost::spirit::file_iterator;

typedef char                   char_t;
typedef file_iterator<char_t>  iterator_t;

#include "MtlActions.hpp"


//////////////////////////////////////////////////
//	The mtl grammar.
//////////////////////////////////////////////////
class CMtlGrammar : public grammar<CMtlGrammar> {
public:
	CMtlGrammar(CMtlActions& actions) : m_actions(actions)
	{}

	template<typename ScannerT>
	struct definition {
		//	material rules
		rule<ScannerT> mtlLib;
		rule<ScannerT> newmtlAssignation, ambientAssignation, diffuseAssignation, specularAssignation, shininessAssignation
			, diffuseTextureAssignation, unsuportedAssignations;
		rule<ScannerT> comment, stringRule, assignSpace;
		//	symbols
		symbols<>	unsuportedKeywords;

		//
		definition(CMtlGrammar const& self) 
		{
			CMtlActions& actions = self.m_actions;
			//	main rule
			mtlLib
				=	*space_p
					>> comment
					>> newmtlAssignation
					>> *(	comment
						|	newmtlAssignation
						|	ambientAssignation
						|	diffuseAssignation
						|	specularAssignation
						|	shininessAssignation
						|	diffuseTextureAssignation
						|	unsuportedAssignations
						)
				;
			//	comment rule
			comment
				=	+(comment_p("#") >> *space_p)
				;
			//  new material
			newmtlAssignation
				=	"newmtl"
					>> assignSpace
					>> stringRule[actions.setMtl]
					>> *space_p
				;
			//	ambient coefficients assignation
			ambientAssignation
				=	(	"Ka"
						>> assignSpace
						>> real_p[actions.setAmbientRed]
						>> assignSpace
						>> real_p[actions.setAmbientGreen]
						>> assignSpace
						>> real_p[actions.setAmbientBlue]
					)
					>> *space_p
				;
			//	diffuse coefficients assignation
			diffuseAssignation
				=	(	"Kd"
						>> assignSpace
						>> real_p[actions.setDiffuseRed]
						>> assignSpace
						>> real_p[actions.setDiffuseGreen]
						>> assignSpace
						>> real_p[actions.setDiffuseBlue]
					)
					>> *space_p
				;
			//	specular coefficients assignation
			specularAssignation
				=	(	"Ks"
						>> assignSpace
						>> real_p[actions.setSpecularRed]
						>> assignSpace
						>> real_p[actions.setSpecularGreen]
						>> assignSpace
						>> real_p[actions.setSpecularBlue]
					)
					>> *space_p
				;
			shininessAssignation
				=	"Ns"
					>> assignSpace
					>> real_p[actions.setShininess]
					>> *space_p
				;
			diffuseTextureAssignation
				=	"map_Kd"
					>> assignSpace
					>> stringRule[actions.setDiffuseTexture]
					>> *space_p
				;

			//  char grouping rules
			assignSpace
				=	*(blank_p)
				;
			stringRule
				=	*(anychar_p-space_p)
				;
			unsuportedAssignations
				=	unsuportedKeywords		//	recognize valid but unsuported keywords
					>> *(anychar_p-eol_p)	//	go to the end of the line
					>> *(space_p)			//	eat up spaces till next relevant line
				;

			//	symbols
			unsuportedKeywords
				=	"Ni", "d", "illum", "sharpness", "map_Ka", "map_Ks", "map_Bump", "map_d", "refl"
				;
		}
		//
		rule<ScannerT> const& start() const { return mtlLib; }
	};

private:
	CMtlActions& m_actions;
};

#endif // __MTLGRAMMAR_HPP__