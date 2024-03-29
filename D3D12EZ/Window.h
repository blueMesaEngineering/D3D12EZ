#pragma once

#include "WinInclude.h"	// <Support/WinInclude.h>
#include "ComPointer.h"	// <Support/ComPointer.h>
#include "DXContext.h"  // <D3D/DXContext.h>

class DXWindow
{
public:
	bool Init();
	void Update();
	void Preset();
	void Shutdown();
	void Resize();

	inline bool ShouldClose() const
	{
		return m_shouldClose;
	}

	inline bool ShouldResize() const
	{
		return m_shouldResize;
	}

	static constexpr size_t GetFrameCount()
	{
		return 2;
	}

private:
	static LRESULT CALLBACK OnWindowMessage(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	ATOM m_wndClass = 0;
	HWND m_window = nullptr;
	bool m_shouldClose = false;

	bool m_shouldResize = false;
	UINT m_width = 1920;
	UINT m_height = 1080;

	ComPointer<IDXGISwapChain3> m_swapChain;

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