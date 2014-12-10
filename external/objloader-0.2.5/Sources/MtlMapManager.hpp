/*
 *  MtlMapManager.hpp
 *  ToolSDL
 *
 *  Created by Seb on 19/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MTLMAPMANAGER_HPP__
#define __MTLMAPMANAGER_HPP__

#include "Material.hpp"


//////////////////////
//
//////////////////////
class CMtlMapManager {
public:
	CMtlMapManager(MaterialMap_t& mtlMap, path branchPath)
	: m_materialMap(mtlMap), m_pMaterial(NULL), m_mtlBranchPath(branchPath)
	{}
	
	void setMaterial(const string& str)
	{
		m_pMaterial = &m_materialMap[str];
	}
	SMaterial *const getMaterial() const
	{
		assert(NULL != m_pMaterial);
		return m_pMaterial;
	}
	string getFilePath(const string& strFileName) const { return (m_mtlBranchPath/strFileName).string(); }
		// texture files are relative to the ".mtl" file so they need to be completed for the app to find them.

private:
	CMtlMapManager(const CMtlMapManager& rhs);
	MaterialMap_t& m_materialMap;
	SMaterial* m_pMaterial;
	path m_mtlBranchPath;
};

#endif//__MTLMAPMANAGER_HPP__