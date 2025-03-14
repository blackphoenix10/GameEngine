// DirectX12Renderer.h
#ifndef DIRECTX12RENDERER_H
#define DIRECTX12RENDERER_H

#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

using Microsoft::WRL::ComPtr;

class DirectX12Renderer {
public:
    DirectX12Renderer(HWND hwnd);
    ~DirectX12Renderer();

    bool Initialize();
    bool LoadShaders();
    bool CreatePipelineStateObject();
    void Cleanup();
    bool CreateVertexBuffer();
    void Render();
    void SetupInputLayout();

private:
    bool CreateDevice();
    bool CreateRootSignature();
    bool CreateCommandQueue();
    bool CreateSwapChain();
    bool CreateRenderTarget();

    HWND hwnd;
    ComPtr<ID3D12Device> device;
    ComPtr<ID3D12CommandQueue> commandQueue;
    ComPtr<IDXGISwapChain4> swapChain;
    ComPtr<ID3D12DescriptorHeap> rtvHeap;
    ComPtr<ID3D12Resource> renderTargets[2];
    UINT rtvDescriptorSize;
    UINT frameIndex;

    ComPtr<ID3D12CommandAllocator> commandAllocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;

    ComPtr<ID3D12Resource> vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

    ComPtr<ID3D12PipelineState> pipelineState;

    ComPtr<ID3DBlob> vertexShader;
    ComPtr<ID3DBlob> pixelShader;

    ComPtr<ID3D12RootSignature> rootSignature;

    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
};

#endif // DIRECTX12RENDERER_H