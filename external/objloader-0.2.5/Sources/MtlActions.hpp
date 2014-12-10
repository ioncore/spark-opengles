/*
 *  MtlActions.hpp
 *  ToolSDL
 *
 *  Created by Seb on 19/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MTLACTIONS_HPP__
#define __MTLACTIONS_HPP__

#include "MtlMapManager.hpp"

///////////////////////////////////////////////////////////////////////////
//
//  First we declare the bunch of functors that will perform the tricks
//
///////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//	base class, avoids redefining data member every time.
class CMtlAction {
public:
	CMtlAction(CMtlMapManager& mtlMapManager) : m_mtlMapManager(mtlMapManager)
	{}
	
protected:
	CMtlMapManager& m_mtlMapManager;
};


//////////////////////////////
//
class CSetMtlFun : CMtlAction {
public:
	CSetMtlFun(CMtlMapManager& mtlMapManager) : CMtlAction(mtlMapManager) {}
	template <typename IteratorT>
	void operator()(IteratorT pbeg, IteratorT pend) const
	{
		string str(pbeg, pend);
		m_mtlMapManager.setMaterial(str);
		m_mtlMapManager.getMaterial()->strName = str;
	}
};

///////////////////////
//
enum EAssignationType {
	ambient,
	diffuse,
	specular,
	shininess
};

//////////////////////////////////
//  dispatches RGB components
class CComponentFun : CMtlAction {
public:
	CComponentFun(CMtlMapManager& mmm, EAssignationType type, unsigned index)
	: CMtlAction(mmm), m_type(type), m_index(index) {}
	void operator()(float f) const
	{
		switch(m_type) {
			case ambient:
				m_mtlMapManager.getMaterial()->Ka[m_index] = f;
				break;
			case diffuse:
				m_mtlMapManager.getMaterial()->Kd[m_index] = f;
				break;
			case specular:
				m_mtlMapManager.getMaterial()->Ks[m_index] = f;
				break;
			default:
				assert(false);
		}
	}
private:
	const EAssignationType m_type;
	const unsigned m_index;
};

//////////////////////////////
//
class CFloatFun : CMtlAction {
public:
	CFloatFun(CMtlMapManager& mmm, EAssignationType type) : CMtlAction(mmm), m_type(type) {}
	void operator()(float f) const
	{
		switch(m_type) {
			case shininess:
				m_mtlMapManager.getMaterial()->Ns = f;
				break;
			default:
				assert(false);
		}
	}
protected:
	const EAssignationType m_type;
};

////////////////////////////////////
//  only one type for the time being
class CStringFun : CMtlAction {
public:
	CStringFun(CMtlMapManager& mtlMapManager) : CMtlAction(mtlMapManager) {}
	template <typename IteratorT>
	void operator()(IteratorT pbeg, IteratorT pend) const
	{
		m_mtlMapManager.getMaterial()->map_Kd = m_mtlMapManager.getFilePath(string(pbeg, pend));
	}
};

///////////////////////////////
//	usefull debug functor 
struct SLogFun {
	SLogFun() {}
	void operator()(int n) const
	{
		cout << "Parse caught: \"" << n << "\".\n";
	}
	template <typename IteratorT>
	void operator()(IteratorT pbeg, IteratorT pend) const
	{
		cout << "Parse caught: \"" << string(pbeg, pend) << "\".\n";
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////
//
//  The CMtlActions class declaration.
//  The CMtlActions class is responsible for passing the functors to the grammar while parsing.
//
///////////////////////////////////////////////////////////////////////////////////////////////
class CMtlActions {
private:
	CMtlMapManager& m_mtlMapManager;

public:
	//  ctor
	CMtlActions(CMtlMapManager& mtlMapManager)
	: m_mtlMapManager(mtlMapManager)
	, setMtl(m_mtlMapManager)
	, setAmbientRed(m_mtlMapManager, ambient, 0)
	, setAmbientGreen(m_mtlMapManager, ambient, 1)
	, setAmbientBlue(m_mtlMapManager, ambient, 2)
	, setDiffuseRed(m_mtlMapManager, diffuse, 0)
	, setDiffuseGreen(m_mtlMapManager, diffuse, 1)
	, setDiffuseBlue(m_mtlMapManager, diffuse, 2)
	, setSpecularRed(m_mtlMapManager, specular, 0)
	, setSpecularGreen(m_mtlMapManager, specular, 1)
	, setSpecularBlue(m_mtlMapManager, specular, 2)
	, setShininess(m_mtlMapManager, shininess)
	, setDiffuseTexture(m_mtlMapManager)
	{}

	SMaterial *const getMaterial() const { return m_mtlMapManager.getMaterial(); } 
	
	//  functors
	CSetMtlFun	setMtl;
	CComponentFun	setAmbientRed;
	CComponentFun	setAmbientGreen;
	CComponentFun	setAmbientBlue;
	CComponentFun	setDiffuseRed;
	CComponentFun	setDiffuseGreen;
	CComponentFun	setDiffuseBlue;
	CComponentFun	setSpecularRed;
	CComponentFun	setSpecularGreen;
	CComponentFun	setSpecularBlue;
	CFloatFun	setShininess;
	CStringFun	setDiffuseTexture;
	SLogFun	log;
};

#endif//__MTLACTIONS_HPP__
