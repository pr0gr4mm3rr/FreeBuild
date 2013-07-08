//
//  PyConsole.cpp
//  FreeBuild
//
//  Created by Pr0gr4mm3r on 4/16/13.
//
//

#include "PyConsole.h"
#include "PyInterpreter.h"

// This acts as a proxy for any output
void stdioRedirect::Write( std::string const& str ) {
	// Forward the data to all of our streams and flush data
	for(unsigned int i=0; i < streams.size(); i++)
	{
		*streams.at(i) << str;
		streams.at(i)->flush();
	}
}

void stdioRedirect::registerStream(std::ostream* stream){
	streams.push_back(stream);
}

void stdioRedirect::unregisterStream(std::ostream* stream){
	for (unsigned int i=0; i < streams.size(); i++)
		if (streams.at(i) == stream)
			unregisterStream(i);
}

void stdioRedirect::unregisterStream(unsigned int i){
	// TODO any handling/cleanup needed here?
	streams.erase(streams.begin()+i);
}

// 'Part one'

// STDOUT //
void ConsoleClass::registerStdout(std::ostream * output){
	python_stdout_redirector.registerStream(output);
	boost::python::import("sys").attr("stdout") = &python_stdout_redirector;
}

void ConsoleClass::unregisterStdout(int id){
	python_stdout_redirector.unregisterStream(id);
}

void ConsoleClass::unregisterStdout(std::ostream * output){
	python_stdout_redirector.unregisterStream(output);
}

// STDERR //
void ConsoleClass::registerStderr(std::ostream * output){
	python_stderr_redirector.registerStream(output);
	boost::python::import("sys").attr("stderr") = &python_stderr_redirector;
}

void ConsoleClass::unregisterStderr(int id){
	python_stderr_redirector.unregisterStream(id);
}

void ConsoleClass::unregisterStderr(std::ostream * output){
	python_stderr_redirector.unregisterStream(output);
}

// Constructor //
ConsoleClass::ConsoleClass()
{
	// Map boost::python stdout and stderr through us
	object main_module = import("__main__");
	object main_namespace = main_module.attr("__dict__");
	main_namespace["stdioRedirect"] = class_<stdioRedirect>("stdioRedirect", init<>())
    .def("write", &stdioRedirect::Write);

	python_stdout_redirector = stdioRedirect();
	boost::python::import("sys").attr("stdout") = &python_stdout_redirector;
	
	python_stderr_redirector = stdioRedirect();
	boost::python::import("sys").attr("stderr") = &python_stderr_redirector;

	// Also create a redirector that writes from evaluated console stuff
	python_evaluator = stdioRedirect();

	// START OF TESTING STUFF

	// Log file, for demonstration, should be moved later
	logfile.open("log.txt");
	registerStdout(&logfile);
	registerStderr(&logfile);
	python_evaluator.registerStream(&logfile);

	// Run the console
	runConsole(&std::cin);
	
}

// 'Part two'

void ConsoleClass::runConsole(std::istream * stream)
{
	conin = stream;
	consoleRunning = true;
	boost::thread consolethread(boost::bind(&ConsoleClass::pyconsole,this));
}

// Run a thread to manage a console-based interpreter
void ConsoleClass::pyconsole(){
	std::string input, subinput;
	bool outputting;

	// Register python output to std streams
	registerStdout(&std::cout);
	registerStderr(&std::cerr);

	while (true)
	{
		outputting = true;
		// This could be replaced with pythons sys.ps1
		std::cout << ">>> ";

		// Reset stdin to deal with ctrl-c
		// This needs actual handling later
		std::cin.clear();

		std::getline(std::cin, input);
		// Handling for structures (if, while, def, etc)
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
				input += "\n" + subinput;
			}
		}

		// TODO process ; delimited statements?

		// Don't run empty input
		if (input.length() == 0) continue;

		// Aesthetics
		input += "\n";
		
		// Send to anyone listening for evaluated scripts
		python_evaluator.Write(">>>" + input);

		// These strings mean we won't get return/output, there are probably more
		if (input.find("import") != std::string::npos) outputting = false;
		if (input.find("print") != std::string::npos) outputting = false;
		if (input.find("=") != std::string::npos) outputting = false;

		// This is probably wrong
		if (outputting)
			input = "print " + input;
		
		PyRun_SimpleString((char*)input.c_str());
	}
}