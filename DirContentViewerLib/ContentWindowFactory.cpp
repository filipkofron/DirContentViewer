#include "ContentWindowFactory.h"

#ifdef _WIN32
#include "ContentWindowWIN32.h"
#endif

namespace DirContentViewer
{
	ContentWindow *ContentWindowFactory::CreateContentWindow()
	{
#ifdef _WIN32
		return new ContentWindowWIN32();
#endif
	}
}