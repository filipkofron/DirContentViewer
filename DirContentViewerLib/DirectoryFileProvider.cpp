#include "DirectoryFileProvider.h"

#include <exception>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")
#endif

namespace DirContentViewer
{
	DirectoryFileProvider::DirectoryFileProvider(const wchar_t *dirPath)
		: m_DirPath(dirPath)
	{
	}

#ifdef _WIN32
	static void ProvideFiles_Windows(const std::wstring &dirPath, IFileReceiver &fileReceiver)
	{
		WIN32_FIND_DATA findData;
		const wchar_t *dirPathStr = dirPath.c_str();
		wchar_t dirPathTemp[MAX_PATH];
		HANDLE findHandle = INVALID_HANDLE_VALUE;
		size_t pathLength = 0;

		StringCchLength(dirPathStr, MAX_PATH, &pathLength);

		if (pathLength > (MAX_PATH - 3))
			throw std::exception("Directory path is too long.");

		StringCchCopy(dirPathTemp, MAX_PATH, dirPathStr);
		StringCchCat(dirPathTemp, MAX_PATH, TEXT("\\*"));

		findHandle = FindFirstFile(dirPathTemp, &findData);

		if (INVALID_HANDLE_VALUE == findHandle)
			throw std::exception("Error reading directory.");

		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				size_t cFileNameSize = 0;

				if (pathLength + StringCchLengthW(findData.cFileName, MAX_PATH, &cFileNameSize) > (MAX_PATH - 2))
					throw std::exception("File path is too long.");

				StringCchCopy(dirPathTemp, MAX_PATH, dirPathStr);
				StringCchCat(dirPathTemp, MAX_PATH, TEXT("\\"));
				StringCchCat(dirPathTemp, MAX_PATH, findData.cFileName);

				fileReceiver.OnFileReceived(dirPathTemp);
			}
		}
		while (FindNextFile(findHandle, &findData) != 0);

		if (GetLastError() != ERROR_NO_MORE_FILES)
			throw std::exception("Error reading directory.");

		FindClose(findHandle);
	}
#endif

	void DirectoryFileProvider::ProvideFiles(IFileReceiver &fileReceiver)
	{
#ifdef _WIN32
		ProvideFiles_Windows(m_DirPath, fileReceiver);
#endif
	}
}
