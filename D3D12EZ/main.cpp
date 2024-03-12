#include <iostream>

#include "WinInclude.h" //<Support/WinInclude.h>
#include "ComPointer.h" // <Support/ComPointer.h>
#include "Window.h" //<Support/Window.h>

#include "DXDebugLayer.h" //<Debug/DXDebugLayer.h>

#include "DXContext.h" // <D3D/DXContext.h>

int main()
{
	DXDebugLayer::Get().Init();
	if (DXContext::Get().Init() && DXWindow::Get().Init())
	{
		while (!DXWindow::Get().ShouldClose())
		{
			DXWindow::Get().Update();
			auto* cmdList = DXContext::Get().InitCommandList();

			// a lot of setup
			// a draw

			DXContext::Get().ExecuteCommandList();

			// Show me the stuff
		}

		DXWindow::Get().Shutdown();
		DXContext::Get().Shutdown();
	}
	DXDebugLayer::Get().Shutdown();
}
