#include <iostream>
#include <exception>
#include "DirContentViewer.h"
#include "Util.h"

int main(int argc, char *argv[])
{
	int ret = 0;

	std::cout << "## [Dir content viewer] ##" << std::endl
		<< "By Filip Kofron, filip.kofron.cz@gmail.com " << std::endl;

	try
	{
		if (argc != 2)
		{
			throw std::exception("Invalid arguments");
		}

		wchar_t *wideArg = DirContentViewer::CharToWChar(argv[1]); // will be leaked on exception (not a problem here)

		DirContentViewer::InvokeDirContentViewerForPath(wideArg);

		delete[] wideArg;
	}
	catch (std::exception &ex)
	{
		std::wcerr << "Error: " << ex.what() << std::endl;

		std::cout << std::endl << "Usage: DirContentViewer <DIRECTORY_PATH>" << std::endl;
		ret = 1;
	}

	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();

	return ret;
}
