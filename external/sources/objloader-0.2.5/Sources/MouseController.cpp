/*
 *  MouseController.cpp
 *  The OpenGL Obj Loader
 *
 *  Contains mouse related logic.
 *
 *  Created by Seb on 15/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */
#include "MouseController.hpp"
#include "MeshViewer.hpp"


//
void CMouseController::buttonDown(int x, int y)
{
	m_x = x; m_y = y;
	m_bButtonDown = true;
}

void CMouseController::buttonUp()
{
	m_bButtonDown = false;
}


//
void CMouseController::motion(int x, int y)
{
	if (m_bButtonDown) {
		CMeshViewer::getInstance().mouseMotion(x-m_x, y-m_y);
		m_x = x; m_y = y;
	}
}
