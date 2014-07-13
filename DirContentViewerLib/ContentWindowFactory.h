#ifndef _CONTENTWINDOWFACTORY_H_
#define _CONTENTWINDOWFACTORY_H_

namespace DirContentViewer
{
	class ContentWindowFactory;
}

#include "ContentWindow.h"

namespace DirContentViewer
{
	/// <summary>
	/// Creates the content window, independent from the current platform.
	/// </summary>
	class ContentWindowFactory
	{
	public:
		/// <summary>
		/// Returns a new instance of content window.
		/// </summary>
		static ContentWindow *CreateContentWindow();
	};
}

#endif