#ifndef _CONTENTWINDOW_H_
#define _CONTENTWINDOW_H_

namespace DirContentViewer
{
	class ContentWindow;
}

#include "IContentProvider.h"

namespace DirContentViewer
{
	/// <summary>
	/// Abstract class for a content window, which must be implemented
	/// for each platform dependently.
	/// </summary>
	class ContentWindow
	{
	public:
		/// <summary>
		/// Opens new window with the specified provider of content.
		/// </summary>
		virtual void OpenWindow(IContentProvider *contentProvider) = 0;
	};
}

#endif

