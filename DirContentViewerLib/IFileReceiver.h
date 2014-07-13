#ifndef _IFILERECEIVER_H_
#define _IFILERECEIVER_H_

namespace DirContentViewer
{
	class IFileReceiver;
}

namespace DirContentViewer
{
	/// <summary>
	/// Receiver of files.
	/// </summary>
	class IFileReceiver
	{
	public:
		/// <summary>
		/// called when the given name of a file is received
		/// </summary>
		virtual void OnFileReceived(const wchar_t *filename) = 0;
	};
}

#endif
