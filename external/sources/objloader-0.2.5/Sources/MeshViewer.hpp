/*
 *  MeshViewer.h
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 13/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */

#ifndef __MESHVIEWER_H__
#define __MESHVIEWER_H__

#include "SceneObject.hpp"
#include "Camera.hpp"

class CMesh;


// There can be only one (singleton pattern).
class CMeshViewer {
public:
	~CMeshViewer();

	static CMeshViewer& getInstance(); // static instance access (singleton pattern)

	void setMesh(const shared_ptr<CMesh>& pMesh);
		//  REQUIRE: the OpenGL window must be ready (setMesh adapts the lighting & viewport to the mesh).
		//  REQUIRE: the given mesh must be fully loaded at this point.
		//  PROMISE: after this function returns, the viewer must have adapted its camera
		//           and internal settings to the size and position of the given mesh.
	void resetScene();
		//  REQUIRE: the mesh pointed at must be fully loaded at this point.
		//  PROMISE: the camera is looking at the mesh and positioned at the right distance to see it all.
	void animate(const float dt);
	void draw() const;
		//  Called by the window manager's loop.
		//  REQUIRE: must be const.
	void mouseMotion(int dx, int dy);
		//  Called by the MouseController.
		//  REQUIRE: dx and dy are x and y variations since last frame.
		//  PROMISE: the MeshViewer has responded to this variations and called for a redisplay.
	const int getWidth() const { return m_width; }
	const int getHeight() const { return m_height; }

private:
	//	private constructors (singleton pattern)
	CMeshViewer();
	CMeshViewer(const CMeshViewer& rhs);

	void adaptViewport();
		//  REQUIRES: the camera must be set before calling adaptViewport().
	void setupLights();
		//  REQUIRES: the mesh and camera must be set at this point.
	void drawAxes() const;
		//  REQUIRE: must be const.

	int m_width;
	int m_height;
	int m_x;
	int m_y;
	float m_worldTranslationX;
	float m_worldTranslationY;
	float m_scaleFactor;
	SCamera m_camera;
	CSceneObject m_sceneObject;
};

#endif //__MESHVIEWER_H__
