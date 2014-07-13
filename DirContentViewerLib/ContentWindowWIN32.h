#ifndef _CONTENTWINDOWWIN32_H_
#define _CONTENTWINDOWWIN32_H_

namespace DirContentViewer
{
	class ContentWindowWIN32;
}

#include "ContentWindow.h"

namespace DirContentViewer
{
	/// <summary>
	/// Header for implementation of ContentWindow for Windows 32
	/// </summary>
	class ContentWindowWIN32 : public ContentWindow
	{
	public:
		/// <summary>
		/// Opens the content window with the specified content provider.
		/// </summary>
		virtual void OpenWindow(IContentProvider *contentProvider);
	};
}

#endif
