#pragma once

#include "WinInclude.h"	// <Support/WinInclude.h>
#include "ComPointer.h"	// <Support/ComPointer.h>

class DXWindow
{
public:
	bool Init();
	void Update();
	void Shutdown();

	inline bool ShouldClose() const
	{
		return m_shouldClose;
	}

private:
	static LRESULT CALLBACK OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	ATOM m_wndClass = 0;
	HWND m_window = nullptr;
	bool m_shouldClose = false;

	// Singleton
public:
	DXWindow(const DXWindow&) = delete;
	DXWindow& operator = (const DXWindow&) = delete;

	inline static DXWindow& Get()
	{
		static DXWindow instance;
		return instance;
	}
private:
	DXWindow() = default;
};