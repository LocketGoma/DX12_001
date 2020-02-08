#pragma once
#include "DXSample.h"
#include "Resource.h"

using namespace DirectX;		//���̷�Ʈ X ���ӽ����̽� �⵿
using Microsoft::WRL::ComPtr;	//���ø� �������̽� ����Ʈ������?

class MultiadapterTwit : public DXSample
{
	public :
		MultiadapterTwit(int,int,LPCWSTR);

		//����� �Ͻ�������... DXSample�� ��ӹްԵǴ°ǰ�?
		//�ƴѵ�? �׷� virtural �־�?
		//DXSample '��' ��ӹ޴°ŷ�.
		virtual void OnInit();
		virtual void OnUpdate();
		virtual void OnRender();
		virtual void OnDestroy();

	private:		
		static const bool AllowDrawDynamicWorkload = false; //���ÿ��� ���� ������ �����Ҽ� �ְ� ���ִ�...?
		static const bool AllowShaderDynamicWorkload = true; //���ÿ��� (����) ���̴� ����..

		

};

