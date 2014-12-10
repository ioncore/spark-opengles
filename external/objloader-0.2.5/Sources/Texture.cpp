/*
 *  Texture.cpp
 *  ToolSDL
 *
 *  Created by Seb on 10/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
// // Usage exemple:
// GLuint objectID;
// objetID = glGenLists (1);
// glNewList (objetID, GL_COMPILE);
// glEnable (GL_TEXTURE_2D);
// glBindTexture (GL_TEXTURE_2D, texture.getID());
// glBegin (GL_QUADS);
// glTexCoord2f (0.0, 0.0); glNormal3f (1.0, 1.0, 0.0); glVertex3f (1.0, 1.0, -2.0);
// ...
// glEnd ();
// glDisable (GL_TEXTURE_2D);
// glEndList ();
#include "Texture.hpp"
#include "Image.hpp"


const GLuint CTexture::INVALID_ID = ~1;

//
CTexture::CTexture(const string& strFilePath)
: m_textureID(INVALID_ID)
, m_pImage(new CImage(strFilePath))
{
	m_isTransparent = m_pImage->isTransparent();
}

//
const bool CTexture::operator==(const CTexture& rhs) const
{
	return (m_pImage == rhs.m_pImage) && (getID() == rhs.getID());
}


//
void CTexture::registerGL()
{
	testInvariant();

	glGenTextures (1, &m_textureID);
	glBindTexture (GL_TEXTURE_2D, m_textureID);
	// Paramétrage de la texture.
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Jonction entre OpenGL et SDL.
	m_pImage->convertPixelFormat();
	const int w = m_pImage->getWidth();
	const int h = m_pImage->getHeight();
	//	if w and h are powers of 2, just create the texture
	if (((w & (w-1)) == 0) && ((h & (h-1)) == 0))
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pImage->getPixels());
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, m_pImage->getPixels());

	//	we don't need the image anymore
	m_pImage.reset();
	
	testInvariant();
}
