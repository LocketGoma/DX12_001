#pragma once
#include "DXSample.h"
#include "Resource.h"

using namespace DirectX;		//다이렉트 X 네임스페이스 기동
using Microsoft::WRL::ComPtr;	//템플릿 인터페이스 스마트포인터?

class MultiadapterTwit : public DXSample
{
	public :
		MultiadapterTwit(int,int,LPCWSTR);

		//얘들을 암시적으로... DXSample이 상속받게되는건가?
		//아닌데? 그럼 virtural 왜씀?
		//DXSample '을' 상속받는거로.
		virtual void OnInit();
		virtual void OnUpdate();
		virtual void OnRender();
		virtual void OnDestroy();

	private:		
		//Static 변수들
		static const bool AllowDrawDynamicWorkload = false; //샘플에서 도형 개수를 조절할수 있게 해주는...?
		static const bool AllowShaderDynamicWorkload = true; //샘플에서 (생략) 쉐이더 변경..

		static const UINT FrameCount = 3;		//굳이 unsigned int를 써야하는가		
		static const UINT MovingAverageFrameCount = 20;	//평균 프레임 수?
		static const UINT WindowTextUpdateFrequency = 20;	//텍스트 변경 빈도.. 텍스트? 아 이거 윈도우 타이틀 업데이트...
		static const UINT MaxBirdCount = 15000;	//최대 오브젝트 수. 새를 날릴거니까 'Bird' 
		static const float ClearColor[4];		//R G B A
		static const float BirdHalfWidth;		//오브젝트 길이!
		static const float BirdDepth;			//오브젝트의 Z축 값.

		//비 Static 변수들. 

		UINT m_frameIndex;
		UINT m_BirdCount;						//현재 생성된것은 몇개인가?
		UINT m_psLoopCount;
		UINT m_blurPSLoopCount;
		UINT m_currentTimesIndex;
		UINT64 m_drawTimes[MovingAverageFrameCount];
		UINT64 m_blurTimes[MovingAverageFrameCount];
		UINT64 m_drawTimeMovingAverage;
		UINT64 m_blurTimeMovingAverage;


		//구조체
		struct Vertex {
			XMFLOAT3 position;
		};
		struct VertexPositionUV {		//UV?
			XMFLOAT4 position;
			XMFLOAT2 uv;
		};
		// Constant buffer definitions.
		struct SceneConstantBuffer
		{
			XMFLOAT4 velocity;			//속도
			XMFLOAT4 offset;			//offset
			XMFLOAT4 color;				//색상
			XMFLOAT4X4 projection;		//? 투명도?

			// Constant buffers are 256-byte aligned. Add padding in the struct to allow multiple buffers
			// to be array-indexed.
			float padding[36];			//버퍼... 용이라는건 알겠는데... 뭐라구요?
		};
		struct BlurConstantBufferData	//이름부터 블러쪽이네.
		{
			XMFLOAT2 textureDimensions;

			// Controls how much of the render target is blurred along X axis [0.0. 1.0]. 
			// E.g. 1 = all of the RT is blurred, 0.5 = half of the RT is blurred, 0.0 = none of the RT is blurred
			FLOAT offset;

			// Constant buffers are 256-byte aligned. Add padding in the struct to allow multiple buffers
			// to be array-indexed.
			float padding[61];
		};
		struct WorkloadConstantBufferData	//버퍼? 루프버퍼?
		{
			UINT loopCount;

			// Constant buffers are 256-byte aligned. Add padding in the struct to allow multiple buffers
			// to be array-indexed.
			float padding[63];
		};
		enum GraphicsAdapter
		{
			Primary, // Note: Not necessarily the OS's primary adapter (adapter enumerated at index 0).
			Secondary,
			GraphicsAdaptersCount
		};

		//그 외
			// Pipeline objects.
		CD3DX12_VIEWPORT m_viewport;			//니들
		CD3DX12_RECT m_scissorRect;				//뭐냐
		UINT m_rtvDescriptorSizes[GraphicsAdaptersCount];
		UINT m_srvDescriptorSizes[GraphicsAdaptersCount];
		DXGI_ADAPTER_DESC1 m_adapterDescs[GraphicsAdaptersCount];
		ComPtr<IDXGISwapChain3> m_swapChain;
		ComPtr<ID3D12Device> m_devices[GraphicsAdaptersCount];
		ComPtr<ID3D12CommandAllocator> m_directCommandAllocators[GraphicsAdaptersCount][FrameCount];
		ComPtr<ID3D12CommandAllocator> m_copyCommandAllocators[FrameCount];
		ComPtr<ID3D12CommandQueue> m_directCommandQueues[GraphicsAdaptersCount];
		ComPtr<ID3D12CommandQueue> m_copyCommandQueue;
		ComPtr<ID3D12RootSignature> m_rootSignature;
		ComPtr<ID3D12RootSignature> m_blurRootSignature;
		ComPtr<ID3D12PipelineState> m_pipelineState;
		ComPtr<ID3D12PipelineState> m_blurPipelineStates[2];
		ComPtr<ID3D12DescriptorHeap> m_rtvHeaps[GraphicsAdaptersCount];
		ComPtr<ID3D12DescriptorHeap> m_dsvHeap;
		ComPtr<ID3D12DescriptorHeap> m_cbvSrvUavHeap;
		ComPtr<ID3D12GraphicsCommandList> m_directCommandLists[GraphicsAdaptersCount];
		ComPtr<ID3D12GraphicsCommandList> m_copyCommandList;

		// Synchronization objects.
		ComPtr<ID3D12Fence> m_frameFence;
		ComPtr<ID3D12Fence> m_renderFence;
		ComPtr<ID3D12Fence> m_crossAdapterFences[GraphicsAdaptersCount];
		UINT64 m_currentPresentFenceValue;
		UINT64 m_currentRenderFenceValue;
		UINT64 m_currentCrossAdapterFenceValue;
		UINT64 m_frameFenceValues[FrameCount];
		HANDLE m_fenceEvents[GraphicsAdaptersCount];

		// Asset objects.
		ComPtr<ID3D12Resource> m_vertexBuffer;
		ComPtr<ID3D12Resource> m_fullscreenQuadVertexBuffer;
		ComPtr<ID3D12Resource> m_constantBuffer;
		ComPtr<ID3D12Resource> m_workloadConstantBuffer;
		ComPtr<ID3D12Resource> m_blurWorkloadConstantBuffer;
		ComPtr<ID3D12Resource> m_blurConstantBuffer;
		ComPtr<ID3D12Resource> m_depthStencil;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
		D3D12_VERTEX_BUFFER_VIEW m_fullscreenQuadVertexBufferView;
		std::vector<SceneConstantBuffer> m_constantBufferData;
		SceneConstantBuffer* m_pCbvDataBegin;
		BlurConstantBufferData* m_pBlurCbvDataBegin;
		WorkloadConstantBufferData m_workloadConstantBufferData;
		WorkloadConstantBufferData* m_pWorkloadCbvDataBegin;
		WorkloadConstantBufferData m_blurWorkloadConstantBufferData;
		WorkloadConstantBufferData* m_pBlurWorkloadCbvDataBegin;
		ComPtr<ID3D12Heap> m_crossAdapterResourceHeaps[GraphicsAdaptersCount];
		ComPtr<ID3D12Resource> m_crossAdapterResources[GraphicsAdaptersCount][FrameCount];
		BOOL m_crossAdapterTextureSupport;
		ComPtr<ID3D12Resource> m_secondaryAdapterTextures[FrameCount];            // Only used if cross adapter texture support is unavailable.
		ComPtr<ID3D12Resource> m_renderTargets[GraphicsAdaptersCount][FrameCount];
		ComPtr<ID3D12Resource> m_intermediateBlurRenderTarget;
		ComPtr<ID3D12QueryHeap> m_timestampQueryHeaps[GraphicsAdaptersCount];
		ComPtr<ID3D12Resource> m_timestampResultBuffers[GraphicsAdaptersCount];
		UINT64 m_directCommandQueueTimestampFrequencies[GraphicsAdaptersCount];

		//Private 함수부
		HRESULT GetHardwareAdapters(_In_ IDXGIFactory2* pFactory, _Outptr_result_maybenull_ IDXGIAdapter1** ppPrimaryAdapter, _Outptr_result_maybenull_ IDXGIAdapter1** ppSecondaryAdapter);
		void LoadPipeline();
		void LoadAssets();
		float GetRandomFloat(float min, float max);
		void PopulateCommandLists();
		void UpdateWindowTitle();
		void WaitForGpu(GraphicsAdapter adapter);
		void MoveToNextFrame();

		static inline UINT Align(UINT size, UINT alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT)
		{
			return (size + alignment - 1) & ~(alignment - 1);
		}



};

