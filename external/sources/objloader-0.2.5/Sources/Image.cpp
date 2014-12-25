/*
 *  CImage.cpp
 *  ToolSDL
 *
 *  Created by Seb on 13/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <SDL_image.h>
#include "Image.hpp"
#include "Exception.hpp"

//
CImage::CImage(const string& strFilePath)
{
	//	load the image file
	m_pSurface = IMG_Load(strFilePath.c_str());
	if (NULL == m_pSurface)
		throw CImageLoadException(SDL_GetError());

	testInvariant();
}


//
bool CImage::isTransparent() const
{
	return (0 != m_pSurface->format->Amask) || (0 != m_pSurface->format->colorkey);
}


//
void CImage::convertPixelFormat()
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif	
	SDL_SetAlpha(m_pSurface, 0, SDL_ALPHA_TRANSPARENT);
	SDL_Surface* pAlphaSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, getWidth(), getHeight(),
													  32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(m_pSurface, NULL, pAlphaSurface, NULL);
	SDL_FreeSurface(m_pSurface);
	m_pSurface = pAlphaSurface;
}
