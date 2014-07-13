#include "ContentWindowWIN32.h"
#include "WindowWIN32.h"

namespace DirContentViewer
{
	void ContentWindowWIN32::OpenWindow(IContentProvider *contentProvider)
	{
		WindowWIN32 window(800, 600, L"Dir content viewer", contentProvider);

		window.InitInstance();
	}
}
