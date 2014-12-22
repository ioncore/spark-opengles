/*
 *  PolygonFace.cpp
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 12/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */

#include "PolygonFace.hpp"


//
SPolygonFace::SPolygonFace()
{
	v.reserve(3); vt.reserve(3); vn.reserve(3);
}


//
void SPolygonFace::addVertTexNorm(int vi, int ti, int ni)
{
	v.push_back(vi);
	vt.push_back(ti);
	vn.push_back(ni);
}
