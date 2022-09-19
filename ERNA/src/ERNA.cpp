#include <iostream>
#include <format>
#include "input.h"
#include "app.h"


int main(int32_t argc, char* argv[])
{
	app::App launcer = app::App(argc, argv);
	launcer.Run();
	return 0;
}
