#include "MultiadapterTwit.h"


//Public

//아니 이거 구조 왜이래?
//= 기본 생성자 스타일임.
//초반에서 각각의 생성자를 '기본값 설정' (이니셜라이즈) 해주는 작업.
//근데 요즘은 이렇게도 안하고 이니셜라이즈 함수를 새로 만들어서 쓴다던데?
MultiadapterTwit::MultiadapterTwit(int width, int height, LPCWSTR name) :
    DXSample(width, height, name),
    m_frameIndex(0),
    m_BirdCount(MaxBirdCount / 2),
    m_psLoopCount(0),
    m_blurPSLoopCount(0),
    m_currentTimesIndex(0),
    m_drawTimeMovingAverage(0),
    m_blurTimeMovingAverage(0),
    m_viewport(0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height)),
    m_scissorRect(0, 0, static_cast<LONG>(width), static_cast<LONG>(height)),
    m_currentPresentFenceValue(1),
    m_currentRenderFenceValue(1),
    m_currentCrossAdapterFenceValue(1),
    m_workloadConstantBufferData(),
    m_blurWorkloadConstantBufferData(),
    m_crossAdapterTextureSupport(false),
    m_rtvDescriptorSizes{},
    m_srvDescriptorSizes{},
    m_drawTimes{},
    m_blurTimes{},
    m_frameFenceValues{}
{
    m_constantBufferData.resize(MaxBirdCount);
}

void MultiadapterTwit::OnInit() {
    LoadPipeline();
    LoadAssets();
    UpdateWindowTitle();       
}
//이미 선언되어있다구요?
//_Use_decl_annotations_
//HRESULT MultiadapterTwit::GetHardwareAdapters(IDXGIFactory2* pFactory, IDXGIAdapter1** ppPrimaryAdapter, IDXGIAdapter1** ppSecondaryAdapter)
