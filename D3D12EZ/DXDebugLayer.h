#pragma once

#include "WinInclude.h" //<Support/WinInclude.h>
#include "ComPointer.h" //<Support/ComPointer.h>

class DXDebugLayer
{
public:
	bool Init();
	void Shutdown();

private:
#ifdef _DEBUG
	ComPointer<ID3D12Debug3> m_d3d12Debug;	// This was ID3D12Debug6, but according to a comment, 
											//	only ED3D12Debug <= 3 is supported on Windows 10, which I am using. 
											//	Comment here: https://www.youtube.com/watch?v=FKTfuKB6LTc
											//	NDG 20240309
	ComPointer<IDXGIDebug1> m_dxgiDebug;
#endif

	// Singleton
public:
	DXDebugLayer(const DXDebugLayer&) = delete;
	DXDebugLayer& operator = (const DXDebugLayer&) = delete;

	inline static DXDebugLayer& Get()
	{
		static DXDebugLayer instance;
		return instance;
	}
private:
	DXDebugLayer() = default;
};
