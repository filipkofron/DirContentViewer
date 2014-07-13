#ifndef _ICONTENTPROVIDER_H_
#define _ICONTENTPROVIDER_H_

namespace DirContentViewer
{
	class IContentProvider;
}

#include <ostream>

namespace DirContentViewer
{
	/// <summary>
	/// Provides content.
	/// </summary>
	class IContentProvider
	{
	public:
		/// <summary>
		/// Retrieves the content size.
		/// </summary>
		virtual long int GetSize() const = 0;

		/// <summary>
		/// Reads an exact amount of content into given array.
		/// </summary>
		virtual void Read(long int pos, long int size, char *dest) = 0;
	};
}

#endif
