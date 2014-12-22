/*
 *  SceneObject.h
 *  ToolSDL
 *
 *  Created by Seb on 22/12/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __SCENEOBJECT_HPP__
#define __SCENEOBJECT_HPP__

class CMesh;


//
class CSceneObject {
public:
	CSceneObject()
	: m_translationX(0)
	, m_translationY(0)
	, m_translationZ(0)
	, m_rotationX(0)
	, m_rotationY(0)
	, m_rotationZ(0)
	{}
	//	compiler generated copy ctor, dtor, and copy assignment apply.

	void setMesh(const shared_ptr<CMesh>& pMesh);
	void animate(const float dt);
	void draw() const;
		//	must be const
	float getCenterX() const;
	float getCenterY() const;
	float getCenterZ() const;
	float getRadius() const;
	void resetPosition();

	float m_translationX;
	float m_translationY;
	float m_translationZ;
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;

private:
	shared_ptr<CMesh> m_pMesh;
		//	the mesh data is always shared, not copied.
};

#endif //__SCENEOBJECT_HPP__