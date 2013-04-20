//
//  PyConsole.cpp
//  FreeBuild
//
//  Created by Pr0gr4mm3r on 4/16/13.
//
//

#include "PyConsole.h"
#include "PyInterpreter.h"
#include <Python.h>
#include <boost/thread.hpp>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

Console::Console::Console(shared_ptr<Python> * pcon)
{
	// Local copy of the python stuff
	pycon = *pcon;
	// Start our thread
	boost::thread foo(boost::bind(&Console::pyconsole,this));

	pos=0;

	
}

void Console::Console::pyconsole(){
	char input[512];
	char prepend[7] = "print ";
	char parse[512];

	PyRun_SimpleString("nul=open('nul','w')");

	while (true)
	{
		std::cin.getline(input, 512);

		// What we do here is prepend 'print ' to our command
		// If it has something to output, it will, as in a
		// Regular python interpreter
		strcpy(parse, prepend);
		strcat(parse, input);
		// Redirect stderr to nul when attempting to print output
		PyRun_SimpleString("sys._stderr=sys.stderr");
		PyRun_SimpleString("sys.stderr=nul");
		int result = PyRun_SimpleString(parse);
		// Restore stderr
		PyRun_SimpleString("sys.stderr=sys._stderr");
		if (result == -1)
			PyRun_SimpleString(input);
	}
}