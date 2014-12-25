/*
 *  CImage.hpp
 *  ToolSDL
 *
 *  Created by Seb on 13/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include "stable.pch"

//	C++ wrapper class for SDL C data.
//  Don't use CImages directly, use CTextures instead (welcome to the 3rd dimension).
class CImage {
public:
	CImage(const string& strFilePath);
	~CImage() { SDL_FreeSurface(m_pSurface); m_pSurface = NULL; }
	
	bool isTransparent() const;
		//	PROMISE: return true if the alpha mask or the colorkey is not null.
	void convertPixelFormat();
		//	PROMISE: convert the pixel format to RGBA for OpenGL.
	
	const GLint getWidth() const { testInvariant(); return m_pSurface->w; }
		//	REQUIRE: the image must be loaded.
	const GLint getHeight() const { testInvariant(); return m_pSurface->h; }
		//	REQUIRE: the image must be loaded.
	const void* getPixels() const { testInvariant(); return m_pSurface->pixels; }
		//	REQUIRE: the image must be loaded.
	
	inline void testInvariant() const;

private:
	CImage(const CImage& rhs);
		//  Don't copy ! Use shared_ptr<CImage> and copy shared pointers instead.
	CImage& operator=(const CImage& rhs);
		//  Idem.

	SDL_Surface* m_pSurface;
};


//
void CImage::testInvariant() const
{
	assert(NULL != m_pSurface);
}

#endif // __IMAGE_HPP
