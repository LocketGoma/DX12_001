#include "MultiadapterTwit.h"


//Public

//�ƴ� �̰� ���� ���̷�?
//= �⺻ ������ ��Ÿ����.
//�ʹݿ��� ������ �����ڸ� '�⺻�� ����' (�̴ϼȶ�����) ���ִ� �۾�.
//�ٵ� ������ �̷��Ե� ���ϰ� �̴ϼȶ����� �Լ��� ���� ���� ���ٴ���?
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
//�̹� ����Ǿ��ִٱ���? �ƴѵ�?
_Use_decl_annotations_
HRESULT MultiadapterTwit::GetHardwareAdapters(IDXGIFactory2* pFactory, IDXGIAdapter1** ppPrimaryAdapter, IDXGIAdapter1** ppSecondaryAdapter)
{
    if (pFactory == nullptr)
    {
        return E_POINTER;
    }
    //�� E_POINTER �� ������ �����ڰ�...

    // Adapter 0 is the adapter that Presents frames to the display. It is assigned as
    // the "secondary" adapter because it is the adapter that performs the second set
    // of operations (the blur effect) in this sample.
    // Adapter 1 is an additional GPU that the app can take advantage of, but it does
    // not own the presentation step. It is assigned as the "primary" adapter because
    // it is the adapter that performs the first set of operations (rendering triangles)
    // in this sample.

    ThrowIfFailed(pFactory->EnumAdapters1(0, ppSecondaryAdapter));
    ThrowIfFailed(pFactory->EnumAdapters1(1, ppPrimaryAdapter));

    //���� = ���� �� 0
    return S_OK;
}