#include "Util.h"

#include <cstring>
#include <cstdlib>

namespace DirContentViewer
{
	wchar_t *CharToWChar(const char *text)
	{
		size_t size = strlen(text) + 1;
		wchar_t* wa = new wchar_t[size];
		size_t unused = 0;
		mbstowcs_s(&unused, wa, size, text, size);
		return wa;
	}
}
