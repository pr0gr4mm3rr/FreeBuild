//Copyright (C) 2011 by Jason L. McKesson
//This file is licensed by the MIT License.



#include <stdlib.h>
#include <string.h>
#include "gll_gl_ext.h"
#include "gll_gl_ext_base.h"
#ifdef _MSC_VER
#include "../include/glload/gll.hpp"
#else
#include "glload/gll.hpp"
#endif

#ifdef WIN32
#undef APIENTRY
#include <windows.h>
#include "wgll_ext.h"
#include "wgll_ext_base.h"
#define strcasecmp(lhs, rhs) _stricmp((lhs), (rhs))
#endif

#ifdef LOAD_X11
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include "glxl_ext.h"
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#endif

#ifdef _MSC_VER
#include "../include/glload/gll.h"
#else
#include "glload/gll.h"
#endif


namespace glload
{
	int LoadFunctions()
	{
		return ::LoadFunctions();
	}

	int GetMajorVersion()
	{
		return ::GetMajorVersion();
	}

	int GetMinorVersion()
	{
		return ::GetMinorVersion();
	}

	bool IsVersionGEQ( int iMajorVersion, int iMinorVersion )
	{
		return ::IsVersionGEQ(iMajorVersion, iMinorVersion) != 0;
	}

#ifdef WIN32
	int LoadWinFunctions(void *hdc)
	{
		return ::LoadWinFunctions(hdc);
	}
#endif //WIN32

#ifdef LOAD_X11
   	int LoadGLXFunctions(void *display, int screen)
   	{
		return ::LoadGLXFunctions(display, screen);
   	}
#endif //LOAD_X11
}


