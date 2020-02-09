#include "MultiadapterTwit.h"


//Public

//아니 이거 구조 왜이래?
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
