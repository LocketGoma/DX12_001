#include "Resource.h"
#include "MultiadapterTwit.h"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    MultiadapterTwit sample(1280, 720, L"D3D12 Heterogeneous multiadapter with shared heaps");
    return Win32Application::Run(&sample, hInstance, nCmdShow);
}
