/*
 *  Camera.cpp
 *  The OpenGL Obj Loader
 *
 *  Contains Camera related logic.
 *
 *  Created by Seb on 14/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include "Camera.hpp"
#include "SceneObject.hpp"


//
void SCamera::pointAt(const CSceneObject& sceneObject)
{
	//	look at the mesh center
	lookAt.set(sceneObject.getCenterX()
		, sceneObject.getCenterY()
		, sceneObject.getCenterZ());
}


//
void SCamera::closeUp(const CSceneObject& sceneObject)
{
	//  position the camera to see the whole mesh
	x = sceneObject.getCenterX();
	y = sceneObject.getCenterY();
	float f = 1/sinf(M_PI*fovY/360);
	float r = sceneObject.getRadius();
	z = sceneObject.getCenterZ()-r*f;
	//  set Z-clipping...
	zNear = r*(f-1);	//	Z-buffer precision depends on this to have the highest possible value
	zFar = (lookAt.z-z)*3;
}