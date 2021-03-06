//
//  GFXFramebuffer.h
//  FreeBuild
//
//  Created by Thomas Dickerson on 4/8/13.
//
//

#ifndef __FreeBuild__GFXFramebuffer__
#define __FreeBuild__GFXFramebuffer__

#include "GFXGLObject.h"
#include <iostream>

namespace GFX{
	class Framebuffer : public GLObject{
	protected:
		int w, h;
	public:
		virtual ~Framebuffer();
		Framebuffer(int w, int h);
		
		virtual void deleteObj();
		virtual void handleResize(int w, int h);
		virtual void bind(GLenum target);
		virtual void unbind(shared_ptr<GLObject> rebind=shared_ptr<GLObject>());
	};
};

#endif /* defined(__FreeBuild__GFXFramebuffer__) */
