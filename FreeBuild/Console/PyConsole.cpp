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
#include <string>
#include <iostream>
#include <signal.h>

Console::Console::Console(shared_ptr<Python> * pcon)
{
	// Local copy of the python stuff
	pycon = *pcon;
	// Start our thread
	boost::thread foo(boost::bind(&Console::pyconsole,this));
}

void Console::Console::pyconsole(){
	std::string input, subinput;
	bool outputting;

	while (true)
	{
		outputting = true;
		// This could be replaced with pythons sys.ps1
		std::cout << ">>> ";
		std::getline(std::cin, input);
		// Handling for structures (if, while, def)
		if (input[input.length()-1] == ':')
		{
			outputting = false;
			while (true)
			{
				// This could be replaced with pythons sys.ps2
				std::cout << "... ";
				std::getline(std::cin, subinput);
				// When we get an empty line we are ready to run the input
				if (subinput.length() == 0) break;
				input += "\r\n" + subinput;
			}
		}

		// Don't run empty input
		if (input.length() == 0) continue;
		
		// These strings mean we won't get return/output, there are probably more
		if (input.find("import") != std::string::npos) outputting = false;
		if (input.find("print") != std::string::npos) outputting = false;
		if (input.find("=") != std::string::npos) outputting = false;

		if (outputting)
			input = "print " + input;
		
		PyRun_SimpleString((char*)input.c_str());
	}
}