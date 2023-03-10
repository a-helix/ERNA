#include <iostream>
#include <format>
#include "iofile.hpp"
#include "app.hpp"


int main(int32_t argc, char* argv[])
{
	app::App launcer = app::App(argc, argv);
	launcer.Run();
	return 0;
	/*
	.\ERNA.exe 
		-if C:/path/input.tsv			(input file)
		-of C:/path/output.tsv			(output file)
		-id t							(input delimiter)
		-od t 							(output delimiter)
		-k 1 							(key)
		-s 3 							(sequence)
		-ap 6 							(additional parameter)
		uorfs 							(type of operation)
	*/
}
