#ifndef _DIRCONTENTVIEWER_H_
#define _DIRCONTENTVIEWER_H_

namespace DirContentViewer
{
	/// <summary>
	/// Opens compiled content of a given directory path.
	/// (the path is platform dependant)
	/// </summary>
	void InvokeDirContentViewerForPath(const wchar_t *path);
}

#endif
