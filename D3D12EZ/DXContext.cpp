#include "DXContext.h"
#include <iostream>
#include "comdef.h"
#include "string.h"
#include "cstring"
#include <system_error>

bool DXContext::Init()
{
	if (FAILED(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_dxgiFactory))))
	{
		return false;
	}

	HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));
	//_com_error err(hr);

	//LPCTSTR errMessage = err.ErrorMessage();
	std::string errorMessage = std::system_category().message(hr);

	if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
	{
		std::cout << "D3D12CreateDevice failed.";
		std::cout << std::endl;
		std::cout << "Error message from HRESULT: " << errorMessage;
		std::cout << std::endl;
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	if (FAILED(m_device->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&m_cmdQueue))))
	{
		return false;
	}

	if (FAILED(m_device->CreateFence(m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
	{
		return false;
	}

	m_fenceEvent = CreateEvent(nullptr, false, false, nullptr);
	if (!m_fenceEvent)
	{
		return false;
	}

	if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_cmdAllocator))))
	{
		return false;
	}

	//if (FAILED(m_device->CreateCommandList1(0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_cmdList))))
	HRESULT hr2 = m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_cmdAllocator, nullptr, IID_PPV_ARGS(&m_cmdList));
	std::string errorMessage2 = std::system_category().message(hr2);
	_com_error err(hr2);
	LPCTSTR errMessage = err.ErrorMessage();
	if (FAILED(hr2))
	{
		std::cout << "CreateCommandList failed.";
		std::cout << std::endl;
		std::cout << "Error message from HRESULT: ";
		std::wcout << errMessage;
		std::cout << std::endl;
		return false;
	}

	return true;
}

void DXContext::Shutdown()
{
	m_cmdList.Release();
	m_cmdAllocator.Release();
	if (m_fenceEvent)
	{
		CloseHandle(m_fenceEvent);
	}
	m_fence.Release();
	m_cmdQueue.Release();
	m_device.Release();

	m_dxgiFactory.Release();
}

void DXContext::SignalAndWait()
{
	m_cmdQueue->Signal(m_fence, ++m_fenceValue);
	if (SUCCEEDED(m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent)))
	{
		if (WaitForSingleObject(m_fenceEvent, 20000) != WAIT_OBJECT_0)
		{
			exit(-1);	// This was std::exit(-1); but such line generated an error. So I removed std:: and used exit(-1)
			//	with no problems.  NDG 20240309
		}
	}
	else
	{
		exit(-1);
	}
}

ID3D12GraphicsCommandList7* DXContext::InitCommandList()
{
	m_cmdAllocator->Reset();
	m_cmdList->Reset(m_cmdAllocator, nullptr);
	return m_cmdList;
}

void DXContext::ExecuteCommandList()
{
	if (SUCCEEDED(m_cmdList->Close()))
	{
		ID3D12CommandList* lists[] = { m_cmdList };
		m_cmdQueue->ExecuteCommandLists(1, lists);
		SignalAndWait();
	}
}
