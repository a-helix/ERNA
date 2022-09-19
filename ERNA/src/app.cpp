#include "app.h"

namespace app
{
	App::App(int32_t argc, char* argv[])
	{
		factory = bioutilities::GeneticCodeFactory();
		_argc = argc;
		_argv = argv;
	}

	App::~App() {};

	void App::WrongArgumentFormat(const int32_t& iteration)
	{
		if (iteration + 1 >= _argc)
		{
			throw std::invalid_argument("ERROR! Wrong arguments format. \n");
		}
	}

	char App::ProcessDelimiter(char& delimiter)
	{
		auto map_parsed_delimiter = comand_line_delimiters.find(delimiter);
		if (map_parsed_delimiter != comand_line_delimiters.end())
		{
			return map_parsed_delimiter->second;
		}
		return delimiter;
	}

	void App::Run()
	{
		if (_argc == 1)
		{
			std::cout << "ERROR! No arguments provided. \n";
			return std::exit(1);
		}

		std::string console_argument;
		try
		{
			for (int32_t i = 1; i < _argc; ++i)
			{
				console_argument = _argv[i];
				if (console_argument.compare("-h") == 0)
				{
					std::cout << "Sorry! I haven't written any help info yet.";
					// TODO: add some help info
				}


				else if (console_argument.compare("-i") == 0)
				{
					WrongArgumentFormat(i);
					input_file = std::format(R"({})", _argv[i + 1]);
					if (!std::filesystem::exists(input_file))
					{
						throw std::invalid_argument(std::format("ERROR! Input file doesn't exhist : {}\n", input_file.string()));
					}
					i++;
				}

				else if (console_argument.compare("-o") == 0)
				{
					WrongArgumentFormat(i);
					output_file = std::format(R"({})", _argv[i + 1]);
					if (!std::filesystem::exists(output_file.parent_path()))
					{
						throw std::invalid_argument(std::format("ERROR! Output folder doesn't exhist : {}\n", output_file.parent_path().string()));
					}
					i++;
				}

				else if (console_argument.compare("-id") == 0)
				{
					WrongArgumentFormat(i);
					input_delimiter = ProcessDelimiter(*_argv[i + 1]);
					i++;
				}

				else if (console_argument.compare("-od") == 0)
				{
					WrongArgumentFormat(i);
					output_delimiter = ProcessDelimiter(*_argv[i + 1]);
					i++;
				}

				else if (console_argument.compare("-wbuorf") == 0)
				{
					input::WormBaseRnaSequencesFile file = input::WormBaseRnaSequencesFile(input_file, input_delimiter, factory);
					file.Save(output_file, output_delimiter);
				}

				else
				{
					std::cout << std::format("ERROR! Unknown argument provided : {}\n", console_argument);
					return std::exit(1);
				}
			}
		}
		catch (const std::bad_alloc& ba)
		{
			std::cout << "ERROR! Check delimiters format.";
			return std::exit(1);
		} 

		catch (const std::exception& e)
		{
			std::cout << e.what();
			return std::exit(1);
		}
		return std::exit(0);
	}
}
