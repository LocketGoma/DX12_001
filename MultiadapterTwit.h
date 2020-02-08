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
		static const bool AllowDrawDynamicWorkload = false; //샘플에서 도형 개수를 조절할수 있게 해주는...?
		static const bool AllowShaderDynamicWorkload = true; //샘플에서 (생략) 쉐이더 변경..

		

};

