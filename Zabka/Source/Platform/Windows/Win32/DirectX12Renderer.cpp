#include "DirectX12Renderer.h"
#include "d3dx12.h"
#include "Zabka.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>

#ifdef _DEBUG
    #include "dxgidebug.h"
#endif

using namespace DirectX;
struct Vertex {
    XMFLOAT3 position;
    XMFLOAT4 color;
};

static const Vertex triangleVertices[] = {
    {{  0.0f,  0.9f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
    {{  0.9f, -0.9f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
    {{ -0.9f, -0.9f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}}
};


DirectX12Renderer::DirectX12Renderer(HWND hwnd) : hwnd(hwnd), frameIndex(0) {}

DirectX12Renderer::~DirectX12Renderer() {
    Cleanup();
}

bool DirectX12Renderer::Initialize() {
    if (!CreateDevice()) return false;
    if (!CreateCommandQueue()) return false;
    if (!CreateSwapChain()) return false;
    if (!CreateRenderTarget()) return false;
	if (!CreateVertexBuffer()) return false;

	if (!CreateRootSignature()) return false;

    if (!LoadShaders()) return false;
    SetupInputLayout(); 

    if (!CreatePipelineStateObject()) return false;

    // Now it's safe to create the Command Allocator because `device` is valid.
    HRESULT hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(hr) || !commandAllocator) {
        Logger::PrintLog(L"Failed to create command allocator. HRESULT: 0x%08X", hr);
        return false;
    }
    Logger::PrintLog(L"Command allocator created successfully.");

    // Create Command List
    hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(hr) || !commandList) {
        Logger::PrintLog(L"Failed to create command list. HRESULT: 0x%08X", hr);
        return false;
    }
    Logger::PrintLog(L"Command list created successfully.");

    // Close command list initially
    commandList->Close();

    return true;
}

void DirectX12Renderer::SetupInputLayout() {
    // Emplace back two elements: Position (3 floats), Color (4 floats)
    D3D12_INPUT_ELEMENT_DESC positionDesc = {};
    positionDesc.SemanticName = "POSITION";
    positionDesc.SemanticIndex = 0;
    positionDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; // float3
    positionDesc.InputSlot = 0;
    positionDesc.AlignedByteOffset = 0;
    positionDesc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    positionDesc.InstanceDataStepRate = 0;
    inputLayout.push_back(positionDesc);

    D3D12_INPUT_ELEMENT_DESC colorDesc = {};
    colorDesc.SemanticName = "COLOR";
    colorDesc.SemanticIndex = 0;
    colorDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // float4
    colorDesc.InputSlot = 0;
    colorDesc.AlignedByteOffset = 12; // 3 floats * 4 bytes each
    colorDesc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    colorDesc.InstanceDataStepRate = 0;
    inputLayout.push_back(colorDesc);
}

bool DirectX12Renderer::LoadShaders() {
    HRESULT hr = D3DReadFileToBlob(
        L"D:\\GameEngine\\GameEngine\\Zabka\\Source\\Shaders\\Compiled\\VertexShader.cso",
        &vertexShader);
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to load vertex shader. HRESULT: 0x%08X", hr);
        return false;
    }

    hr = D3DReadFileToBlob(
        L"D:\\GameEngine\\GameEngine\\Zabka\\Source\\Shaders\\Compiled\\PixelShader.cso",
        &pixelShader);
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to load pixel shader. HRESULT: 0x%08X", hr);
        return false;
    }

    Logger::PrintLog(L"Shaders loaded successfully.");
    return true;
}

bool DirectX12Renderer::CreatePipelineStateObject() {
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    // Root signature:
    psoDesc.pRootSignature = rootSignature.Get();

    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;

    // Shaders:
    psoDesc.VS = { vertexShader->GetBufferPointer(), vertexShader->GetBufferSize() };
    psoDesc.PS = { pixelShader->GetBufferPointer(), pixelShader->GetBufferSize() };

    // Input layout (POSITION, COLOR):
    psoDesc.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

    // Default states:
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;

    // Render target:
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.NumRenderTargets = 1;
    psoDesc.SampleDesc.Count = 1;

    HRESULT hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create pipeline state object. HRESULT: 0x%08X", hr);
        return false;
    }

    Logger::PrintLog(L"Pipeline state object created successfully.");
    return true;
}

void DirectX12Renderer::Cleanup() {
    // Cleanup DirectX resources
}

bool DirectX12Renderer::CreateVertexBuffer() {
    const UINT vertexBufferSize = sizeof(triangleVertices);

    CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
    CD3DX12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);

    HRESULT hr = device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&vertexBuffer));

    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create vertex buffer. HRESULT: 0x%08X", hr);
        return false;
    }

    void* mappedData;
    CD3DX12_RANGE readRange(0, 0);
    hr = vertexBuffer->Map(0, &readRange, &mappedData);
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to map vertex buffer. HRESULT: 0x%08X", hr);
        return false;
    }
    memcpy(mappedData, triangleVertices, vertexBufferSize);
    vertexBuffer->Unmap(0, nullptr);

    if (!vertexBuffer) {
        Logger::PrintLog(L"ERROR: Vertex buffer was not created properly!");
        return false;
    }

    vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
    vertexBufferView.StrideInBytes = sizeof(Vertex);
    vertexBufferView.SizeInBytes = vertexBufferSize;


    Logger::PrintLog(L"Vertex buffer created successfully.");
    return true;
}

void DirectX12Renderer::Render() {
    FLOAT clearColor[] = { 0.2f, 0.2f, 0.8f, 1.0f }; // Blue 

    // Ensure the command allocator is reset **before** using the command list
    HRESULT hr = commandAllocator->Reset();
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to reset command allocator. HRESULT: 0x%08X", hr);
        return;
    }

    // Reset command list (attach pipeline state!)
    hr = commandList->Reset(commandAllocator.Get(), pipelineState.Get());
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to reset command list. HRESULT: 0x%08X", hr);
        return;
    }

    // Set the root signature **before** issuing draw calls
    commandList->SetGraphicsRootSignature(rootSignature.Get());

    // Transition the back buffer to the render target state
    CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        renderTargets[frameIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET
    );
    commandList->ResourceBarrier(1, &barrier);

    // Set viewport and scissor rect
    D3D12_VIEWPORT viewport = { 0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f };
    commandList->RSSetViewports(1, &viewport);

    D3D12_RECT scissorRect = { 0, 0, 800, 600 };
    commandList->RSSetScissorRects(1, &scissorRect);

    // Clear render target
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart(), frameIndex, rtvDescriptorSize);
    commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // Bind pipeline state and vertex buffer
    commandList->SetPipelineState(pipelineState.Get());
    commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Debug log to ensure vertex buffer is bound
    Logger::PrintLog(L"VertexBufferView GPU Address: %llu", vertexBufferView.BufferLocation);
    Logger::PrintLog(L"VertexBufferView Size: %d, Stride: %d", vertexBufferView.SizeInBytes, vertexBufferView.StrideInBytes);
    Logger::PrintLog(L"Attempting to draw the triangle...");

    // Issue the draw call
    commandList->DrawInstanced(3, 1, 0, 0);

    // Transition back to present state
    barrier = CD3DX12_RESOURCE_BARRIER::Transition(
        renderTargets[frameIndex].Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT
    );
    commandList->ResourceBarrier(1, &barrier);

    // Close the command list **after** all draw calls
    hr = commandList->Close();
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to close command list. HRESULT: 0x%08X", hr);
        return;
    }

    // Execute the command list
    Logger::PrintLog(L"Executing command list...");
    ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(1, ppCommandLists);
    Logger::PrintLog(L"Command list executed.");

    // Present the frame
    swapChain->Present(1, 0);
    frameIndex = swapChain->GetCurrentBackBufferIndex();
}

bool DirectX12Renderer::CreateDevice() {
    ComPtr<IDXGIFactory4> factory;

#if defined(_DEBUG)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->EnableDebugLayer();
            Logger::PrintLog(L"D3D12 Debug Layer Enabled");
        }
    }
#endif
    if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory)))) {
        Logger::PrintLog(L"Failed to create DXGI factory.");
        return false;
    }

    ComPtr<IDXGIAdapter1> adapter;
    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex) {
        DXGI_ADAPTER_DESC1 desc;
        adapter->GetDesc1(&desc);

        Logger::PrintLog(L"Checking GPU: %s", desc.Description);

        // Skip software adapters
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

        // Force the first valid hardware GPU
        if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device)))) {
            Logger::PrintLog(L"Using GPU: %s", desc.Description);
            return true;
        }
    }

    Logger::PrintLog(L"Failed to find a suitable GPU.");
    return false;

}

bool DirectX12Renderer::CreateRootSignature() {
    // Describe a root signature with no parameters.
    CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc;
    rootSigDesc.Init(
        0, nullptr, // No root parameters
        0, nullptr, // No static samplers
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
    );

    // Serialize the root signature
    ComPtr<ID3DBlob> signatureBlob;
    ComPtr<ID3DBlob> errorBlob;
    HRESULT hr = D3D12SerializeRootSignature(
        &rootSigDesc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        &signatureBlob,
        &errorBlob
    );
    if (FAILED(hr)) {
        if (errorBlob) {
            Logger::PrintLog(L"Root signature error: %hs",
                (char*)errorBlob->GetBufferPointer());
        }
        return false;
    }

    // Create the root signature
    hr = device->CreateRootSignature(
        0,
        signatureBlob->GetBufferPointer(),
        signatureBlob->GetBufferSize(),
        IID_PPV_ARGS(&rootSignature)
    );
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create root signature. HRESULT: 0x%08X", hr);
        return false;
    }

    Logger::PrintLog(L"Root signature created successfully.");
    return true;
}

bool DirectX12Renderer::CreateCommandQueue() {
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

    HRESULT hr = device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue));
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create command queue. HRESULT: 0x%08X", hr);

        HRESULT reason = device->GetDeviceRemovedReason();
        Logger::PrintLog(L"Device removal reason: 0x%08X", reason);
    }

#if defined(_DEBUG)
    // Retrieve DXGI Debug messages even if no crash occurs
    ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiInfoQueue)))) {
        UINT64 messageCount = dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
        for (UINT64 i = 0; i < messageCount; ++i) {
            SIZE_T messageLength = 0;
            dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);

            if (messageLength > 0) {
                DXGI_INFO_QUEUE_MESSAGE* message = (DXGI_INFO_QUEUE_MESSAGE*)malloc(messageLength);
                if (message) {
                    dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, message, &messageLength);
                    Logger::PrintLog(L"DXGI Debug Message: %hs", message->pDescription);
                    free(message);
                }
            }
        }
    }
#endif

    if (FAILED(hr)) return false;
    Logger::PrintLog(L"Command queue created successfully.");
    return true;
}

bool DirectX12Renderer::CreateSwapChain() {
    ComPtr<IDXGIFactory4> factory;
    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create DXGI factory.");
            return false;
    }

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Width = 800;
    swapChainDesc.Height = 600;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> tempSwapChain;
    hr = factory->CreateSwapChainForHwnd(commandQueue.Get(), hwnd, &swapChainDesc, nullptr, nullptr, &tempSwapChain);
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create swap chain.");
            return false;
    }
    tempSwapChain.As(&swapChain);
    frameIndex = swapChain->GetCurrentBackBufferIndex();
    return true;
}

bool DirectX12Renderer::CreateRenderTarget() {
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = 2;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    HRESULT hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap));
    if (FAILED(hr)) {
        Logger::PrintLog(L"Failed to create descriptor heap.");
            return false;
    }

    rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());
    for (UINT i = 0; i < 2; ++i) {
        hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
        if (FAILED(hr)) {
            Logger::PrintLog(L"Failed to get buffer from swap chain.");
                return false;
        }
        device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, rtvDescriptorSize);
    }
    return true;
}

