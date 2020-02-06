//DX12 Start : F:\Programing\Usage\VS2019\DirectX-Graphics-Samples-master\Samples\Desktop\D3D12HeterogeneousMultiadapter\src
//https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HeterogeneousMultiadapter
//해당 프로젝트의 그래픽을 삼각형 -> '트위터 새 모양'으로 바꾸기
//1. 그래픽 변경
//2. 코드의 구버전(레거시) 자료를 모던 스타일로 변경하면서 작업.
#pragma once
#include <dxgi1_4.h>	
#include <d3d12.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>		//얘가 있어야 DirectX 네임스페이스 사용 가능.

//Win API
#include <windows.h>
#include <wrl.h>
#include <shellapi.h>


#include <vector>
#include <sstream>

using namespace DirectX;


//참고자료
//https://hannom.tistory.com/121?category=525481
