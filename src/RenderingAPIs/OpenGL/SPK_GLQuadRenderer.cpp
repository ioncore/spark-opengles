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


#include "RenderingAPIs/OpenGL/SPK_GLQuadRenderer.h"
#include "Core/SPK_Particle.h"
#include "Core/SPK_Group.h"
#include "Core/SPK_ArrayBuffer.h"

namespace SPK
{
namespace GL
{
	const std::string GLQuadRenderer::GPU_BUFFER_NAME("SPK_GLQuadRenderer_GPU");
	const std::string GLQuadRenderer::TEXTURE_BUFFER_NAME("SPK_GLQuadRenderer_Texture");

	float* GLQuadRenderer::gpuBuffer = NULL;
	float* GLQuadRenderer::gpuIterator = NULL;
	float* GLQuadRenderer::textureBuffer = NULL;
	float* GLQuadRenderer::textureIterator = NULL;

	void (GLQuadRenderer::*GLQuadRenderer::renderParticle)(const Particle&) const = NULL;

	GLQuadRenderer::GLQuadRenderer(float scaleX,float scaleY) :
		GLRenderer(),
		QuadRendererInterface(scaleX,scaleY),
		Oriented3DRendererInterface(),
		GLExtHandler(),
		textureIndex(0)
	{}

	bool GLQuadRenderer::checkBuffers(const Group& group)
	{
		FloatBuffer* fGpuBuffer;

		if ((fGpuBuffer = dynamic_cast<FloatBuffer*>(group.getBuffer(GPU_BUFFER_NAME))) == NULL)
			return false;

		if (texturingMode != TEXTURE_NONE)
		{
			FloatBuffer* fTextureBuffer;

			if ((fTextureBuffer = dynamic_cast<FloatBuffer*>(group.getBuffer(TEXTURE_BUFFER_NAME,texturingMode))) == NULL)
				textureBuffer = createTextureBuffer(group);

			textureIterator = textureBuffer = fTextureBuffer->getData();
		}

		gpuIterator = gpuBuffer = fGpuBuffer->getData();
		return true;
	}

	void GLQuadRenderer::createBuffers(const Group& group)
	{
#if TARGET_OS_IPHONE == 1
		FloatBuffer* fBuffer = dynamic_cast<FloatBuffer*>(group.createBuffer(GPU_BUFFER_NAME,FloatBufferCreator(42),0,false));
#else
		FloatBuffer* fBuffer = dynamic_cast<FloatBuffer*>(group.createBuffer(GPU_BUFFER_NAME,FloatBufferCreator(28),0,false));
#endif
		gpuIterator = gpuBuffer = fBuffer->getData();
		if (texturingMode != TEXTURE_NONE)
			textureIterator = textureBuffer = createTextureBuffer(group);
/*
printf("Create texture coords: \n");
printf("0 %f - %f\n", textureBuffer[0], textureBuffer[1]);
printf("1 %f - %f\n", textureBuffer[2], textureBuffer[3]);
printf("2 %f - %f\n", textureBuffer[4], textureBuffer[5]);
printf("3 %f - %f\n", textureBuffer[6], textureBuffer[7]);
printf("4 %f - %f\n", textureBuffer[8], textureBuffer[9]);
printf("5 %f - %f\n", textureBuffer[10], textureBuffer[11]);
*/
	}

	void GLQuadRenderer::destroyBuffers(const Group& group)
	{
		group.destroyBuffer(GPU_BUFFER_NAME);
		group.destroyBuffer(TEXTURE_BUFFER_NAME);
	}

	float* GLQuadRenderer::createTextureBuffer(const Group& group) const
	{
		FloatBuffer* fbuffer = NULL;

		switch(texturingMode)
		{
		case TEXTURE_2D :
#if TARGET_OS_IPHONE == 1
			fbuffer = dynamic_cast<FloatBuffer*>(group.createBuffer(TEXTURE_BUFFER_NAME,FloatBufferCreator(12),TEXTURE_2D,false));
			if (!group.getModel()->isEnabled(PARAM_TEXTURE_INDEX))
			{
				float t[12] = {1.0f,0.0f, 0.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f, 1.0f,0.0f, 0.0f,1.0f};
				for (size_t i = 0; i < group.getParticles().getNbReserved() * 12; ++i) {
					fbuffer->getData()[i] = t[i % 12];
//printf("Assigning %dth element: from %dth element %f\n", i, fbuffer->getData()[i], (i % 12), t[i % 12]);
                                }
			}
			break;
#else
			fbuffer = dynamic_cast<FloatBuffer*>(group.createBuffer(TEXTURE_BUFFER_NAME,FloatBufferCreator(8),TEXTURE_2D,false));
			if (!group.getModel()->isEnabled(PARAM_TEXTURE_INDEX))
			{
				float t[8] = {1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f};
				for (size_t i = 0; i < group.getParticles().getNbReserved() << 3; ++i)
					fbuffer->getData()[i] = t[i & 7];
			}
			break;
#endif

		case TEXTURE_3D :
			fbuffer = dynamic_cast<FloatBuffer*>(group.createBuffer(TEXTURE_BUFFER_NAME,FloatBufferCreator(12),TEXTURE_3D,false));
			float t[12] =  {1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f};
			for (size_t i = 0; i < group.getParticles().getNbReserved() * 12; ++i)
				fbuffer->getData()[i] = t[i % 12];
			break;
		}

		return fbuffer->getData();
	}

	bool GLQuadRenderer::setTexturingMode(TexturingMode mode)
	{
		if ((mode == TEXTURE_3D)&&(!loadGLExtTexture3D()))
			return false;

		texturingMode = mode;
		return true;
	}

	void GLQuadRenderer::render(const Group& group)
	{
		if (!prepareBuffers(group))
			return;

		float oldModelView[16];
		for (int i = 0; i < 16; ++i)
			oldModelView[i] = modelView[i];
		glGetFloatv(GL_MODELVIEW_MATRIX,modelView);
		for (int i = 0; i < 16; ++i)
			if (oldModelView[i] != modelView[i])
			{
				invertModelView();
				break;
			}

		initBlending();
		initRenderingHints();

		glShadeModel(GL_FLAT);

		switch(texturingMode)
		{
		case TEXTURE_2D :
			if (getTexture3DGLExt() == SUPPORTED)
				glDisable(GL_TEXTURE_3D);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textureIndex);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,getTextureBlending());

			if (!group.getModel()->isEnabled(PARAM_TEXTURE_INDEX))
			{
				if (!group.getModel()->isEnabled(PARAM_ANGLE)) {
					renderParticle = &GLQuadRenderer::render2D;
                                }
				else {
					renderParticle = &GLQuadRenderer::render2DRot;
}
			}
			else
			{
				if (!group.getModel()->isEnabled(PARAM_ANGLE)) {
					renderParticle = &GLQuadRenderer::render2DAtlas;
}
				else {
					renderParticle = &GLQuadRenderer::render2DAtlasRot;
}
			}
			break;

		case TEXTURE_3D :
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_3D);
			glBindTexture(GL_TEXTURE_3D,textureIndex);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,getTextureBlending());

			if (!group.getModel()->isEnabled(PARAM_ANGLE))
				renderParticle = &GLQuadRenderer::render3D;
			else
				renderParticle = &GLQuadRenderer::render3DRot;
			break;

		case TEXTURE_NONE :
			glDisable(GL_TEXTURE_2D);
			if (getTexture3DGLExt() == SUPPORTED)
				glDisable(GL_TEXTURE_3D);
			if (!group.getModel()->isEnabled(PARAM_ANGLE))
				renderParticle = &GLQuadRenderer::render2D;
			else
				renderParticle = &GLQuadRenderer::render2DRot;
			break;
		}

		bool globalOrientation = precomputeOrientation3D(
			group,
			Vector3D(-invModelView[8],-invModelView[9],-invModelView[10]),
			Vector3D(invModelView[4],invModelView[5],invModelView[6]),
			Vector3D(invModelView[12],invModelView[13],invModelView[14]));

		if (globalOrientation)
		{
			computeGlobalOrientation3D();

			for (size_t i = 0; i < group.getNbParticles(); ++i)
				(this->*renderParticle)(group.getParticle(i));
		}
		else
		{
			for (size_t i = 0; i < group.getNbParticles(); ++i)
			{
				const Particle& particle = group.getParticle(i);
				computeSingleOrientation3D(particle);
				(this->*renderParticle)(particle);
			}
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		if (texturingMode == TEXTURE_2D)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2,GL_FLOAT,0,textureBuffer);
		}
		else if (texturingMode == TEXTURE_3D)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(3,GL_FLOAT,0,textureBuffer);
		}

		// interleaves vertex and color data
		glVertexPointer(3,GL_FLOAT,7 * sizeof(float),gpuBuffer);
		glColorPointer(4,GL_FLOAT,7 * sizeof(float),gpuBuffer + 3);
#if TARGET_OS_IPHONE == 1
		glDrawArrays(GL_TRIANGLES,0,group.getNbParticles() * 2 * 3);
/*
printf("Texture coords: \n");
printf("0 %f - %f\n", textureBuffer[0], textureBuffer[1]);
printf("1 %f - %f\n", textureBuffer[2], textureBuffer[3]);
printf("2 %f - %f\n", textureBuffer[4], textureBuffer[5]);
printf("3 %f - %f\n", textureBuffer[6], textureBuffer[7]);
printf("4 %f - %f\n", textureBuffer[8], textureBuffer[9]);
printf("5 %f - %f\n", textureBuffer[10], textureBuffer[11]);
*/
#else
		glDrawArrays(GL_QUADS,0,group.getNbParticles() << 2);
#endif
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		if (texturingMode != TEXTURE_NONE)
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void GLQuadRenderer::render2D(const Particle& particle) const
	{
		scaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
	}

	void GLQuadRenderer::render2DRot(const Particle& particle) const
	{
		rotateAndScaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
	}

	void GLQuadRenderer::render3D(const Particle& particle) const
	{
		scaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
		GLCallTexture3D(particle);
	}

	void GLQuadRenderer::render3DRot(const Particle& particle) const
	{
		rotateAndScaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
		GLCallTexture3D(particle);
	}

	void GLQuadRenderer::render2DAtlas(const Particle& particle) const
	{
		scaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
		GLCallTexture2DAtlas(particle);
	}

	void GLQuadRenderer::render2DAtlasRot(const Particle& particle) const
	{
		rotateAndScaleQuadVectors(particle,scaleX,scaleY);
		GLCallColorAndVertex(particle);
		GLCallTexture2DAtlas(particle);
	}
}}
