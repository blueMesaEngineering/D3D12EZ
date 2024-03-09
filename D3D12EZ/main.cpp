#include <iostream>

#include "WinInclude.h" //<Support/WinInclude.h>
#include "ComPointer.h" // <Support/ComPointer.h>

#include "DXDebugLayer.h" //<Debug/DXDebugLayer.h>

#include "DXContext.h" // <D3D/DXContext.h>

int main()
{
	DXDebugLayer::Get().Init();
	if (DXContext::Get().Init())
	{
		while (true)
		{
			auto* cmdList = DXContext::Get().InitCommandList();



			DXContext::Get().ExecuteCommandList();
		}

		DXContext::Get().Shutdown();
	}
	DXDebugLayer::Get().Shutdown();
}
