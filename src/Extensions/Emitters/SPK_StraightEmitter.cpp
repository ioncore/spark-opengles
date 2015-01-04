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


#include "Extensions/Emitters/SPK_StraightEmitter.h"


namespace SPK
{
	void StraightEmitter::generateVelocity(Particle& particle,float speed) const
	{
		particle.velocity() = tDirection;
		particle.velocity() *= speed;
		if(forced2D_)
			particle.velocity().z = 0;
	}

	StraightEmitter::StraightEmitter(const Vector3D& direction) :
		Emitter()
	{
		setDirection(direction);
	}

	void StraightEmitter::setDirection(const Vector3D& direction)
	{
		this->direction = direction;
		this->direction.normalize();
		tDirection = this->direction;
		notifyForUpdate();
	}

	void StraightEmitter::innerUpdateTransform()
	{
		Emitter::innerUpdateTransform();
		transformDir(tDirection,direction);
		tDirection.normalize();
	}
}
