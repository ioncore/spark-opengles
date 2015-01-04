//
//  BasicDemo.h
//  test1
//
//  Created by t28a on 12/27/14.
//  Copyright (c) 2014 t28a. All rights reserved.
//

#ifndef __test1__BasicDemo__
#define __test1__BasicDemo__

#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2009 - Julien Fryer - julienfryer@gmail.com				//
//																				//
// This software is provided 'as-is', without any express or implied			//
// warranty.  In no event will the authors be held liable for any damages		//
// arising from the use of this software.										//
//																				//
// Permission is granted to anyone to use this software for any purpose,		//
// including commercial applications, and to alter it and redistribute it		//
// freely, subject to the following restrictions:								//
//																				//
// 1. The origin of this software must not be misrepresented; you must not		//
//    claim that you wrote the original software. If you use this software		//
//    in a product, an acknowledgment in the product documentation would be		//
//    appreciated but is not required.											//
// 2. Altered source versions must be plainly marked as such, and must not be	//
//    misrepresented as being the original software.							//
// 3. This notice may not be removed or altered from any source distribution.	//
//////////////////////////////////////////////////////////////////////////////////


#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#if __APPLE__ == 1
#  include <TargetConditionals.h>
#  if TARGET_IPHONE_SIMULATOR == 1
#    include <OpenGLES/ES1/gl.h>
#    include <FTGL/ftgles.h>
#  elif TARGET_OS_IPHONE == 1
#    include <OpenGLES/ES1/gl.h>
#    include <FTGL/ftgles.h>
#  elif TARGET_OS_MAC == 1
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#    include <FTGL/ftgl.h>
#  else
#    error "Undefined Platform"
#  endif
#else
#  error "Undefined OS"
#endif

// external libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles.h>

// SPARK lib
#include <SPARK/SPK.h>
#include <SPARK/SPK_GL.h>

std::string int2Str(int a);

bool loadTexture(GLuint& index,char* path,GLuint type,GLuint clamp,bool mipmap);

void drawBoundingBox(const SPK::Group& group);

void renderFirstFrame();

void render();

#endif /* defined(__test1__BasicDemo__) */
