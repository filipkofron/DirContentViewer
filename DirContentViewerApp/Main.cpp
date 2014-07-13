#include <iostream>
#include <exception>
#include "DirContentViewer.h"

int main(int argc, char *argv[])
{
	int ret = 0;
	try
	{
		DirContentViewer::InvokeDirContentViewerForPath(L"D:\\temp");
	}
	catch (std::exception &ex)
	{
		std::wcerr << "Error: " << ex.what() << std::endl;
		ret = 1;
	}

	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();

	return ret;
}
