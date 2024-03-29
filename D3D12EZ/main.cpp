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
			// Process pending window message
			DXWindow::Get().Update();

			// Handle resizing
			if (DXWindow::Get().ShouldResize())
			{
				DXContext::Get().Flush(DXWindow::GetFrameCount());
				DXWindow::Get().Resize();
			}

			// Begin drawing
			auto* cmdList = DXContext::Get().InitCommandList();

			// TODO: Draw

			// Finish drawing and present
			DXContext::Get().ExecuteCommandList();
			DXWindow::Get().Preset();
		}

		// Flushing
		DXContext::Get().Flush(DXWindow::GetFrameCount());

		DXWindow::Get().Shutdown();
		DXContext::Get().Shutdown();
	}
	DXDebugLayer::Get().Shutdown();
}
