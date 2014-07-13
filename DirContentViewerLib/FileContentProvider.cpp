#include "FileContentProvider.h"
#include <exception>
#include <iostream>

namespace DirContentViewer
{
	FileContentProvider::FileContentProvider()
		: m_Size(0)
	{
	}

	FileContentProvider::~FileContentProvider()
	{
		ClearAll();
	}

	long int FileContentProvider::GetSize() const
	{
		return m_Size;
	}

	void FileContentProvider::Read(long int pos, long int size, char *dest)
	{
		long int cycleThrough = 0;

		long int offset = 0;
		long int remain = size;

		long int currEnd = 0;
		long int currBeg = 0;

		while (remain > 0)
		{
			while (currEnd <= offset && cycleThrough < (long int) m_FileSizes.size())
			{
				currBeg = currEnd;
				currEnd += m_FileSizes[cycleThrough];
				cycleThrough++;
			}

			long int fileToRead = cycleThrough - 1;
			if (fileToRead < 0)
				fileToRead = 0;

			std::ifstream *ifs = m_Files[cycleThrough - 1];
			ifs->seekg(offset - currBeg);

			long int grab = currEnd - currBeg;
			if (grab > remain)
				grab = remain;

			while (grab--)
			{
				if (ifs->fail())
					throw std::exception("Error while reading file.");

				dest[size - remain] = ifs->get();

				offset++;
				remain--;
			}
		}
	}

	void FileContentProvider::OnFileReceived(const wchar_t *filename)
	{
		std::ifstream *ifs = new std::ifstream(filename, std::ios::binary | std::ios::ate);

		if (ifs->fail())
		{
			delete ifs;
			throw std::exception("Could not open file.");
		}
		m_Files.push_back(ifs);

		long int fileSize = GetFileSize(*ifs);
		m_FileSizes.push_back(fileSize);
		m_Size += fileSize;
		std::wcout << L"Opened file: " << filename << " size: " << fileSize << " B / " << m_Size << std::endl;
	}

	void FileContentProvider::ClearAll()
	{
		for (std::vector<std::ifstream *>::iterator it = m_Files.begin(); it != m_Files.end(); ++it)
		{
			(*it)->close();
			delete *it;
		}
		m_Files.clear();
	}

	long int FileContentProvider::GetFileSize(std::ifstream &ifs)
	{
		std::streampos originalPosition = ifs.tellg();

		ifs.seekg(0, std::ios::end);
		std::streampos res = ifs.tellg();
		ifs.seekg(originalPosition);

		return (long int) res;
	}
}