#pragma once

#include "WinInclude.h" //<Support/WinInclude.h>
#include "ComPointer.h" //<Support/ComPointer.h>

class DXContext
{
public:
	bool Init();
	void Shutdown();

	void SignalAndWait();
	ID3D12GraphicsCommandList7* InitCommandList();
	void ExecuteCommandList();

	inline void Flush(size_t count)
	{
		for (size_t i = 0; i < count; i++)
			SignalAndWait();
	}

		inline ComPointer<IDXGIFactory7>& GetFactory()
		{
			return m_dxgiFactory;
		}
		inline ComPointer<ID3D12Device8>& GetDevice()
		{
			return m_device;
		}
		inline ComPointer<ID3D12CommandQueue>& GetCommandQueue()
		{
			return m_cmdQueue;
		}

	private:
		ComPointer<IDXGIFactory7> m_dxgiFactory;

		ComPointer<ID3D12Device8> m_device;		// In the original tutorial project, D3D12Ez, m_device is declared to be
												//		an ID3D12Device10.  However, this results in a _com_error on my 
												//		system.  So I rolled back the interface number to ID3D12Device9,
												//		but this was also unsuccessful. So I tried ID3D12Device8, thinking 
												//		that perhaps my old hardware on a 4th Gen Dell Latitude E5440 was
												//		not sufficient for the later features. Seems to have worked!  Not 
												//		sure if this will cause problems later, but it's Ok for now.
												//		https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nn-d3d12-id3d12device8
												//		-- NDG 20240316
		ComPointer<ID3D12CommandQueue> m_cmdQueue;

		ComPointer<ID3D12CommandAllocator> m_cmdAllocator;
		ComPointer<ID3D12GraphicsCommandList7> m_cmdList;

		ComPointer<ID3D12Fence1> m_fence;
		UINT64 m_fenceValue = 0;
		HANDLE m_fenceEvent = nullptr;

		// Singleton
	public:
		DXContext(const DXContext&) = delete;
		DXContext& operator = (const DXContext&) = delete;

		inline static DXContext& Get()
		{
			static DXContext instance;
			return instance;
		}
	private:
		DXContext() = default;
};