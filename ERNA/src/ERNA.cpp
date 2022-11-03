#include <iostream>
#include <format>
#include "input.hpp"
#include "app.hpp"


int main(int32_t argc, char* argv[])
{
	app::App launcer = app::App(argc, argv);
	launcer.Run();
	return 0;
	//.\ERNA.exe -i C:/path/input.tsv -o C:/path/output.tsv -id t -od t -wbuorf
}
