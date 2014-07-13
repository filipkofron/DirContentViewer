#ifndef _FILEPROVIDER_H_
#define _FILEPROVIDER_H_

namespace DirContentViewer
{
	class IFileProvider;
}

#include "IFileReceiver.h"

namespace DirContentViewer
{
	/// <summary>
	/// File provider, is responsible for sending files it provides
	/// to a receiver.
	/// </summary>
	class IFileProvider
	{
	public:
		/// <summary>
		/// Provides files to the given receiver.
		/// </summary>
		virtual void ProvideFiles(IFileReceiver &fileReceiver) = 0;
	};
}

#endif
