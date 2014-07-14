#include "WindowWIN32.h"
#include <exception>
#include <iostream>

#include "Util.h"

#define IDC_MAIN_EDIT	101
#define IDC_MAIN_BUTTON 102

namespace DirContentViewer
{
	WindowWIN32 *WindowWIN32::m_Instance = NULL;

	WindowWIN32::WindowWIN32(const int &width, const int &height, const std::wstring &name, IContentProvider *contentProvider)
	{
		m_Width = width;
		m_Height = height;
		m_Name = name;
		m_Instance = this;
		m_ContentProvider = contentProvider;
	}

	void WindowWIN32::ResizeControls(HWND windowHandle)
	{
		RECT rcClient;

		GetClientRect(windowHandle, &rcClient);

		m_EditHandle = GetDlgItem(windowHandle, IDC_MAIN_EDIT);
		SetWindowPos(m_EditHandle, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
	}

	LRESULT CALLBACK WindowWIN32::WndProc(
		HWND windowHandle,
		UINT msgNumber,
		WPARAM wordParam,
		LPARAM longParam)
	{
		switch (msgNumber)
		{
		case WM_CREATE:
			GetInstance()->CreateControls(windowHandle);
			break;
		case WM_SIZE:
			GetInstance()->ResizeControls(windowHandle);
			break;
		case WM_CLOSE:
			DestroyWindow(windowHandle);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(windowHandle, msgNumber, wordParam, longParam);
		}
		return 0;
	}

	const static wchar_t *g_WindowClass = L"WindowWIN32Class";

	WindowWIN32 *WindowWIN32::GetInstance()
	{
		return m_Instance;
	}

	void WindowWIN32::CreateControls(HWND windowHandle)
	{
		HFONT hfDefault;

		m_EditHandle = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			0, 0, 100, 100, windowHandle, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		if (m_EditHandle == NULL)
			MessageBox(windowHandle, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);

		hfDefault = static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
		SendMessage(m_EditHandle, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));

		UpdateContent();
	}

	void WindowWIN32::InitInstance()
	{
		WNDCLASSEX wc;
		MSG msg;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(NULL);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_WindowClass;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, L"Window Registration Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			
			throw std::exception("Could not register window class.");
		}

		// Step 2: Creating the Window
		m_WindowHandle = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			g_WindowClass,
			m_Name.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
			NULL, NULL, GetModuleHandle(NULL), NULL);

		if (m_WindowHandle == NULL)
		{
			MessageBox(NULL, L"Window Creation Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);

			throw std::exception("Could not create window.");
		}

		ShowWindow(m_WindowHandle, SW_NORMAL);
		UpdateWindow(m_WindowHandle);

		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	static void ReplaceUnprintable(wchar_t replacement, wchar_t *string, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (!iswprint((wint_t)string[i]) || string[i] == L'\0')
			{
				string[i] = replacement;
			}
		}
	}

	static void ReplaceZeros(char replacement, char *string, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (string[i] == '\0')
			{
				string[i] = replacement;
			}
		}
	}

	void WindowWIN32::UpdateContent()
	{
		char *content = new char[m_ContentProvider->GetSize() + 1];

		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx(&statex);

		if (statex.ullAvailPhys / 3 < m_ContentProvider->GetSize())
		{
			MessageBox(NULL, L"Files content too large, cannot fit to RAM!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);

			throw std::exception("Files content too large, cannot fit to RAM.");
		}

		m_ContentProvider->Read(0, m_ContentProvider->GetSize(), content);

		content[m_ContentProvider->GetSize()] = '\0';

		ReplaceZeros('0', content, m_ContentProvider->GetSize());

		wchar_t *wcontent = CharToWChar(content);

		ReplaceUnprintable(L'#', wcontent, wcslen(wcontent));

		SetWindowTextW(m_EditHandle, wcontent);

		delete[] wcontent;
		delete[] content;
	}
}
