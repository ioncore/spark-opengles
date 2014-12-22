/*
 *  PolygonFace.h
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 12/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */

#ifndef __POLYGONFACE_H__
#define __POLYGONFACE_H__


//
struct SPolygonFace {
	SPolygonFace();

	void addVertTexNorm(int vi, int ti, int ni);

	vector<int> v;	//	vertex indices
	vector<int> vt;	//	texture indices
	vector<int> vn;	//	normal indices
};

#endif //__POLYGONFACE_H__
