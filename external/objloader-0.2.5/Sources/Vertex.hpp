/*
 *  Vertex.h
 *  The OpenGL Obj Loader
 *
 *  Created by Seb on 07/12/05.
 *  Copyright 2005 The Old Game Factory. All rights reserved.
 *
 */

#ifndef __VERTEX_H__
#define __VERTEX_H__


// Vertex est minimal, car on est ammenŽé àˆ en stocker un grand nombre.
struct SVertex {
	//  Constructeur simple
	SVertex(float f1, float f2, float f3) : x(f1), y(f2), z(f3)
	{}

	//	utile pour la lisibilité des affectations.
	void set(float f1, float f2, float f3);
	//	utile pour la lisibilité des appels OpenGL.
	float const * getVertex3fv() const { return &x; }
		//  REQUIRE: this Vertex must contain valid data.
		//  PROMISE: returns a pointer to a const float array containing three valid float values.

	float x, y, z;
};

#endif //__VERTEX_H__
