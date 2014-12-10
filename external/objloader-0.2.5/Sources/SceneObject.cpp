/*
 *  SceneObject.cpp
 *  ToolSDL
 *
 *  Created by Seb on 22/12/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */
#include "SceneObject.hpp"
#include "Mesh.hpp"

//
void CSceneObject::setMesh(const shared_ptr<CMesh>& pMesh)
{
	m_pMesh = pMesh;
}


//
float CSceneObject::getCenterX() const
{
	return (NULL == m_pMesh) ? 0 : (m_pMesh->m_minVert.x+m_pMesh->m_maxVert.x)*.5;
}
//
float CSceneObject::getCenterY() const
{
	return (NULL == m_pMesh) ? 0 : (m_pMesh->m_minVert.y+m_pMesh->m_maxVert.y)*.5;
}
//
float CSceneObject::getCenterZ() const
{
	return (NULL == m_pMesh) ? 0 : (m_pMesh->m_minVert.z+m_pMesh->m_maxVert.z)*.5;
}
//
float CSceneObject::getRadius() const
{
	return (NULL == m_pMesh) ? 0 : sqrtf(powf(m_pMesh->m_maxVert.x-m_pMesh->m_minVert.x, 2)
		+ powf(m_pMesh->m_maxVert.y-m_pMesh->m_minVert.y, 2)
		+ powf(m_pMesh->m_maxVert.z-m_pMesh->m_minVert.z, 2))/2;
}


//
void CSceneObject::resetPosition()
{
	m_translationX = m_translationY = m_translationZ = 0;
	m_rotationX = m_rotationY = m_rotationZ = 0;
}


//
void CSceneObject::animate(const float dt)
{
	if (NULL != m_pMesh)
		m_pMesh->animate(dt);
}


//
void CSceneObject::draw() const
{
	//	Return if there is nothing to draw.
	if (NULL == m_pMesh)
		return;
	//	remember lighting & matrix state
	bool isLightingEnabled = glIsEnabled(GL_LIGHTING);
	glPushMatrix();
	//	move to the object's position
	glTranslatef(m_translationX, m_translationY, m_translationZ);
	glTranslatef(getCenterX(), getCenterY(), getCenterZ());
	glRotatef(m_rotationX, 1, 0, 0);
	glRotatef(m_rotationY, 0, 1, 0);
	glRotatef(m_rotationZ, 0, 0, 1);
	glTranslatef(-getCenterX(), -getCenterY(), -getCenterZ());
	//	disable lighting if the mesh has no normals
	if (!m_pMesh->hasNormals())
		glDisable(GL_LIGHTING);
	// draw the mesh
	m_pMesh->draw();
	//	draw the mesh's bounding box
	if (isLightingEnabled)
		glDisable(GL_LIGHTING);
//	m_pMesh->drawBox();
	//	restore previous lighting & matrix state
	if (isLightingEnabled)
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
