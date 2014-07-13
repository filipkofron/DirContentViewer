#ifndef _WINDOWWIN32_H_
#define _WINDOWWIN32_H_

#ifdef _WIN32

namespace DirContentViewer
{
	class WindowWIN32;
}

#include <string>
#include <windows.h>

#include "IContentProvider.h"

namespace DirContentViewer
{
	/// <summary>
	/// Encapsulates Windows32 window with an edit box for showing the text content.
	/// </summary>
	class WindowWIN32
	{
	public:
		/// <summary>
		/// Creates new instance of window with specified width, height, title name and content
		/// provider.
		/// </summary>
		WindowWIN32(const int &width, const int &height, const std::wstring &name, IContentProvider *contentProvider);

		/// <summary>
		/// Initializes the window and shows it up.
		/// This method will block until the window is closed.
		/// </summary>
		virtual void InitInstance();
	protected:
		/// window width
		int m_Width;

		/// window height
		int m_Height;

		/// the window handle
		HWND m_WindowHandle;

		/// the edit box handle
		HWND m_EditHandle;

		/// the content provider
		IContentProvider *m_ContentProvider;

		/// static instance of window (single instance is possible only)
		static WindowWIN32 *m_Instance;

		/// window title name
		std::wstring m_Name;

		/// <summary>
		/// Window procedure entry.
		/// </summary>
		static LRESULT CALLBACK WndProc(
			HWND windowHandle,
			UINT msgNumber,
			WPARAM wordParam,
			LPARAM longParam);

		static WindowWIN32 *GetInstance();

		/// <summary>
		/// Creates controls of the window.
		/// </summary>
		virtual void CreateControls(HWND windowHandle);

		/// <summary>
		/// Resizes control when the window is resized.
		/// </summary>
		virtual void ResizeControls(HWND windowHandle);

		/// <summary>
		/// Updates the content (window must be opened)
		/// </summary>
		virtual void UpdateContent();

		/// <summary>
		/// Retrieves the window handle.
		/// </summary>
		HWND GetWindowHandle();
	};
}

#endif // _WIN32

#endif // _WINDOWWIN32_H_
