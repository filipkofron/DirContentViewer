#ifndef _DIRECTORYFILEPROVIDER_H_
#define _DIRECTORYFILEPROVIDER_H_

namespace DirContentViewer
{
	class DirectoryFileProvider;
}

#include "IFileProvider.h"

#include <string>

namespace DirContentViewer
{
	/// <summary>
	/// Directory implementation of file provider.
	/// Provides files in a given directory.
	/// </summary>
	class DirectoryFileProvider : public IFileProvider
	{
	public:
		/// <summary>
		/// Creates new instance for specified path.
		/// </summary>
		DirectoryFileProvider(const wchar_t *dirPath);

		/// <summary>
		/// Provides files that a given receiver receives.
		/// </summary>
		virtual void ProvideFiles(IFileReceiver &fileReceiver);
	protected:

		/// the working directory
		std::wstring m_DirPath;
	};
}

#endif
