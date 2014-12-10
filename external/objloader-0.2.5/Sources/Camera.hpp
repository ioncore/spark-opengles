/*
 *  Camera.h
 *  The OpenGL Obj Loader
 *
 *  Contains Camera related logic.
 *
 *  Created by Seb on 14/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "Vertex.hpp"

class CSceneObject;


//
struct SCamera {
	SCamera()
	: x(0), y(0), z(0)
	, fovY(45)
	, lookAt(0, 0, 0)
	, zNear(1), zFar(100)
	{}
	void init(const CSceneObject& sceneObject) { pointAt(sceneObject); closeUp(sceneObject);}
		//  REQUIRE: the given mesh must be fully loaded at this point.
		//  PROMISE: the camera position, orientation, and Z-clipping planes allow to see the whole mesh.
	void pointAt(const CSceneObject& sceneObject);
		//  REQUIRE: the given mesh must be fully loaded at this point.
		//  PROMISE: the camera is looking at the center of the mesh.
	void closeUp(const CSceneObject& sceneObject);
		//  REQUIRE: the given mesh must be fully loaded at this point.
		//  PROMISE: the camera position and Z-clipping planes allow to see the whole mesh.

	float x, y, z;
	float fovY; // camera angle (degrees)
	SVertex lookAt;
	float zNear, zFar; // Z-clipping planes
};

#endif //__CAMERA_H__
