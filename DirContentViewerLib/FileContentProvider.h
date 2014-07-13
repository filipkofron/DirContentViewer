#ifndef _FILECONTENTPROVIDER_H_
#define _FILECONTENTPROVIDER_H_

namespace DirContentViewer
{
	class FileContentProvider;
}

#include "IContentProvider.h"
#include "IFileProvider.h"
#include <vector>
#include <fstream>

namespace DirContentViewer
{
	/// <summary>
	/// Provides content from multiple files mapped as a single memory.
	/// </summary>
	class FileContentProvider : public IContentProvider, public IFileReceiver
	{
	public:
		/// <summary>
		/// Creates the file provider.
		/// </summary>
		FileContentProvider();
		virtual ~FileContentProvider();

		/// <summary>
		/// Tells the size of the whole content.
		/// </summary>
		virtual long int GetSize() const;

		/// <summary>
		/// Reads a given amount from a specified position into a given array.
		/// </summary>
		virtual void Read(long int pos, long int size, char *dest);

		/// <summary>
		/// Closes all files and removes them from list (resets the instance).
		/// </summary>
		virtual void ClearAll();

		/// <summary>
		/// Implemented method of receiver. Adds the given file to the list
		/// and updates the whole size.
		/// </summary>
		virtual void OnFileReceived(const wchar_t *filename);
	protected:
		/// opened files
		/// TODO: Cache the opened files!
		std::vector<std::ifstream *> m_Files;

		/// file sizes
		std::vector<long int> m_FileSizes;

		/// size of the whole content of all files
		long int m_Size;

		/// <summary>
		/// returns the exact byte size of given file
		/// </summary>
		long int GetFileSize(std::ifstream &ifs);
	};
}

#endif
