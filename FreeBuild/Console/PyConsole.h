//
//  PyConsole.h
//  FreeBuild
//
//  Created by Pr0gr4mm3r on 4/16/13.
//
//

#ifndef __FreeBuild__PyConsole__
#define __FreeBuild__PyConsole__

#include <boost/python.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "PyInterpreter.h"
#include <string>

using namespace boost;

namespace Console{
	class Console{
	public:
		Console(shared_ptr<Python> *);

		void pyconsole();
	private:
		shared_ptr<Python> pycon;
	};
};


#endif /* defined(__FreeBuild__PyConsole__) */