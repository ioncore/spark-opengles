/*
 *  MeshViewer.cpp
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 13/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include "MeshViewer.hpp"
#include "Exception.hpp"
#include "KeyboardController.hpp"
#include "MouseController.hpp"
#include "Mesh.hpp"


//  Singleton pattern
CMeshViewer& CMeshViewer::getInstance()
{
	static CMeshViewer theMeshViewer;
	return theMeshViewer;
}


//  Constructor
CMeshViewer::CMeshViewer()
	: m_width(400), m_height(300)
	, m_x(100), m_y(100)
	, m_worldTranslationX(0)
	, m_worldTranslationY(0)
{}


//  Destructor
CMeshViewer::~CMeshViewer() {}


//
void CMeshViewer::setMesh(const shared_ptr<CMesh>& pMesh)
{
	m_sceneObject.setMesh(pMesh);
	//	evaluate the scale of the object
	m_scaleFactor = ceilf(log10f(m_sceneObject.getRadius()));
	//	point the camera at the mesh
	m_camera.init(m_sceneObject);
	// Remove me: dev.info.
	CLogger::get() << "Camera at (" << m_camera.x << ", " << m_camera.y << ", " << m_camera.z << ").\n";
	CLogger::get() << "  looking at (" << m_camera.lookAt.x << ", " << m_camera.lookAt.y << ", " << m_camera.lookAt.z << ").\n";
	CLogger::get() << "  Z-clipping: near = " << m_camera.zNear << ", far =" << m_camera.zFar << ".\n";

	adaptViewport();
	setupLights();
}

void CMeshViewer::animate(const float dt)
{
	m_sceneObject.animate(dt);
}

//
void CMeshViewer::draw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_camera.x, m_camera.y, m_camera.z
		, m_camera.lookAt.x, m_camera.lookAt.y, m_camera.lookAt.z
		, 0, 1, 0);
	m_sceneObject.draw();
	// remember lighting state and disable lighting
	bool isLightingEnabled = glIsEnabled(GL_LIGHTING);
	bool isTextureEnabled = glIsEnabled(GL_TEXTURE_2D);
	if (isLightingEnabled)
		glDisable(GL_LIGHTING);
	if (isTextureEnabled)
		glDisable(GL_TEXTURE_2D);
	// unlit elements
	glTranslatef(m_worldTranslationX, m_worldTranslationY, 0);
	drawAxes();
	//	restore previous lighting state
	if (isLightingEnabled)
		glEnable(GL_LIGHTING);
	if (isTextureEnabled)
		glEnable(GL_TEXTURE_2D);
}


// draw some space refs
void CMeshViewer::drawAxes() const
{
	//	ref points : the center
	glPointSize(7);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	// other ref points
	glPointSize(5);
	glBegin(GL_POINTS);
	const float range = powf(10, m_scaleFactor);
	const float step = range/10;
	glColor3f(1, 0, 0);
	glVertex3f(step, 0., 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, step, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, step);
	glEnd();

	//	some lines (draw last if antialiased)
	glBegin(GL_LINES);
	//	X
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(step, 0, 0);
	//  Y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0); glVertex3f(0, step, 0);
	//  Z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0); glVertex3f(0, 0, step);
	// ground grid
	glColor3f(.5, .5, .5);
	for (float d = -range ; d <= range; d += step) {
		glVertex3f(range, 0, d);  glVertex3f(-range, 0, d);
		glVertex3f(d, 0, range);  glVertex3f(d, 0, -range);
	}
	glEnd();
}


// call when the view is reshaped
void CMeshViewer::adaptViewport()
{
	glViewport(0, 0, m_width, m_height);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(m_camera.fovY, (0 != m_height) ? m_width/(float)m_height : 10000
		, m_camera.zNear
		, m_camera.zFar);
}


//
void CMeshViewer::resetScene()
{
	m_worldTranslationX = 0;
	m_worldTranslationY = 0;
	m_sceneObject.resetPosition();
	m_camera.init(m_sceneObject);
}


//
void CMeshViewer::setupLights()
{
	// light 0
	float specular[] = {1.0, 1.0, 1.0, 1.0};
	float diffuse[] = {0.8, 0.8, 1.0, 1.0};
	float position[] = { -414, 0, .414, 0.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	// light 1
	diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 0.8;
	position[0] = -position[0];
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glEnable(GL_LIGHT1);
	diffuse[0] = 0.5; diffuse[1] = 0.5; diffuse[2] = 0.8;
	position[0] = 0;
	position[1] = 1;
	position[2] = 0;
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, position);
	glEnable(GL_LIGHT3);
}


//
void CMeshViewer::mouseMotion(int dx, int dy)
{
	float dX = dx*powf(10, m_scaleFactor-3);
	float dY = dy*powf(10, m_scaleFactor-3);
	bool bTrans = false;
	if (CKeyboardController::getInstance().getCtrlState()) {
		bTrans = true;
		m_sceneObject.m_translationX -= dX;
		m_sceneObject.m_translationY -= dY;
	}
	if (CKeyboardController::getInstance().getAltState()) {
		bTrans = true;
		m_camera.x += dX;
		m_camera.y += dY;
	}
	if (CKeyboardController::getInstance().getShiftState()) {
		bTrans = true;
		m_worldTranslationX -= dX;
		m_worldTranslationY -= dY;
	}
	if (!bTrans) {
		m_sceneObject.m_rotationX -= dy;
		m_sceneObject.m_rotationY += dx;
	}
}
