#include "DirContentViewer.h"
#include "FileContentProvider.h"
#include "DirectoryFileProvider.h"
#include "ContentWindowFactory.h"
#include <iostream>

namespace DirContentViewer
{
	void InvokeDirContentViewerForPath(const wchar_t *path)
	{
		std::wcout << L"InvokeDirContentViewerForPath called for path '" << path << L"'" << std::endl;

		FileContentProvider fileContentProvider;
		DirectoryFileProvider directoryFileProvider(path);

		directoryFileProvider.ProvideFiles(fileContentProvider);

		ContentWindow *window = ContentWindowFactory::CreateContentWindow();

		window->OpenWindow(&fileContentProvider);

		delete window;
	}
}
