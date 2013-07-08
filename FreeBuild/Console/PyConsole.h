//
//  PyConsole.h
//  FreeBuild
//
//  Created by Pr0gr4mm3r on 4/16/13.
//
//

#ifndef __FreeBuild__PyConsole__
#define __FreeBuild__PyConsole__

#include "PyInterpreter.h"
#include <boost/python.hpp>
#include <boost/thread.hpp>
#include <string>
#include <iostream>
#include <fstream>

using namespace Console;

namespace Console{
	class stdioRedirect{
	public:
		// Internal output catching stuff
		void Write( std::string const& );
		
		void registerStream(std::ostream *);
		void unregisterStream(std::ostream *);
		void unregisterStream(unsigned int id);

	private:
		std::vector<std::ostream*> streams;
	};

	class ConsoleClass{
	public:
		ConsoleClass();

		void runConsole(std::istream *);

		void registerStdout(std::ostream *);
		void unregisterStdout(int id);
		void unregisterStdout(std::ostream *);

		void registerStderr(std::ostream *);
		void unregisterStderr(int id);
		void unregisterStderr(std::ostream *);

		// Testing this
		std::ofstream logfile;

	private:
		boost::shared_ptr<Python> pycon;

		// Thready console interpreter
		void pyconsole();
		bool consoleRunning;
		std::istream * conin;

		stdioRedirect python_stdout_redirector;
		stdioRedirect python_stderr_redirector;
		stdioRedirect python_evaluator;
	};
};


#endif /* defined(__FreeBuild__PyConsole__) */