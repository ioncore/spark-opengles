/*
 *  Texture.h
 *  ToolSDL
 *
 *  Created by Seb on 10/01/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class CImage;

//
class CTexture {
public:
	CTexture(const string& strFilePath);
		//	REQUIRE: OpenGL requires that texture image dimensions be powers of 2.
	//	compiler generated copy ctor, dtor, and copy assignment apply.
	
	const bool	operator==(const CTexture& rhs) const;
	
	const GLuint	getID() const { return m_textureID; }
	const bool	isTransparent() const { return m_isTransparent; }
	const bool	isRegistred() const { return NULL == m_pImage; }
	void	registerGL();
	
	inline void	testInvariant() const;
		//  REQUIRE: (pImage is not NULL) OR (the texture has been passed to OpenGL)

	
	
	static const GLuint	INVALID_ID;
	
private:
	GLuint	m_textureID;
	bool	m_isTransparent;
	shared_ptr<CImage>	m_pImage;
		//	the image data is always shared, not copied.
};


//
void CTexture::testInvariant() const
{
	assert(NULL != m_pImage || INVALID_ID != m_textureID);
}

#endif //_TEXTURE_H_