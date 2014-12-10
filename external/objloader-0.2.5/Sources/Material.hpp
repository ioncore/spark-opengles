/*
 *  Material.hpp
 *  ToolSDL
 *
 *  Created by Seb on 16/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

////////////////
//
////////////////
struct SMaterial
{
	string strName;
	GLfloat	Ns;	//	shininess
	GLfloat	Ka[4];	//	ambient color
	GLfloat	Kd[4];	//	diffuse color
	GLfloat	Ks[4];	//	specular color
	int	illum;	//	not supported yet, defines the type of illumination
	float d;	//	not supported yet, defines the opacity of the material
	string	map_Kd;
	
	SMaterial() { reset(); }
	//	compiler generated copy ctor, copy assignment, and dtor apply.
	
	void	reset() {
		Ka[0] = Ka[1] = Ka[2] = 0;
		Ka[3] = Kd[0] = Kd[1] = Kd[2] = Kd[3] = Ks[3] = 1;
		Ks[0] = Ks[1] = Ks[2] = .8;
		Ns = 32;
		illum = 2;	//	fully 
		d = 1;	//	opaque
		map_Kd = "";
	}
};

typedef map<string, SMaterial>	MaterialMap_t;

#endif // __MATERIAL_HPP__
