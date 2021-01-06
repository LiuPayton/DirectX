#include "MyDirectX.h"

MyDirectX::MyDirectX() {
	m_pD3D = NULL;	// ���ڴ���D3D�豸
	m_pd3dDevice = NULL;	// ���ǵ���Ⱦ�豸
}

//-----------------------------------------------------------------------------
	// Name: InitD3D()
	// Desc: ��ʼ�� Direct3D
//-----------------------------------------------------------------------------
BOOL MyDirectX::InitD3D(HWND hWnd, BOOL isFull) {
	//�ú����Ĳ���������D3D_SDK_VERSION,ֻ����˷��ܱ�֤Ӧ�ó���ʹ����ȷ��ͷ�ļ���
	//����ú�������ʧ�ܣ�������һ��NULLָ��
	//�ú����ķ���ֵ��һ��ָ��ӿ�IDirect3D9��ָ��
	//ע�⣺���������ʹ����Ҫ�п��ļ���d3d9.lib���Ĵ��ڡ�
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D)
		return FALSE;
	//�����Կ���ʾģʽ
	D3DDISPLAYMODE displayMode;
	//����Կ�����ʾģʽ ����1���Կ���(һ��ΪD3DADAPTER_DEFAULT)
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		return FALSE;
	//�����̨�������Ĳ������������ģ�建���Ƿ�������ظ�ʽ)
	D3DPRESENT_PARAMETERS d3dpp;	 //������������������豸����
	//ʹ�ýṹǰ����
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//��0�����d3dpp�ڴ�����Ҳ���ǳ�ʼ���ڴ�
	//�Ƿ񴰿ڻ�
	if (isFull) {
		//ȫ��
		d3dpp.Windowed = false;
		d3dpp.BackBufferHeight = WND_H;	//�������ĺ�̨��������ظ߶�
		d3dpp.BackBufferWidth = WND_W;	//�������ĺ�̨��������ؿ��
	}
	else {
		d3dpp.Windowed = TRUE;	//����Ϊ����ģʽ
		//��������֧�ֵ�Ч�����ͣ�ָ�������ڽ�����������α������ġ�
		//����趨Ϊ D3DSWAPEFFECT_DISCARD��
		//��󱸻������Ķ��������Ƶ���Ļ�Ϻ󣬺󱸻������Ķ�����û��ʲô���ˣ����Զ�����discard���ˡ�
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//����Ϊ�󱸵Ļ������֮���ɾ����
		//�󱸻���ĸ�ʽ���������D3DFORMAT����Ϥ�Ļ������԰�����ΪD3DFMT_UNKNOWN����ʱ������ʹ������ĸ�ʽ��
		//d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		//��������ʹ���Լ�����ģ���ʵ������һ��������0
		d3dpp.BackBufferFormat = displayMode.Format;	//��ʾģʽ

		//����Direct3D �豸
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//Ĭ�����������Կ���
			D3DDEVTYPE_HAL,	//Ӳ������ 
			hWnd,	//�豸��ʹ�õĴ���
			//D3DCREATE_PUREDEVICE, //�������豸
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//����������Ⱦ��ʽ
			&d3dpp,	//����
			&m_pd3dDevice	//�����豸
		))) {
			return FALSE;
		}
	}

	return TRUE;
}
//-----------------------------------------------------------------------------
	// Name: Render()
	// Desc: ���Ƴ���
//-----------------------------------------------------------------------------
void MyDirectX::Render() {
	if (NULL == m_pd3dDevice)
		return;
	//����������沢��������Ϊ��ɫ
	m_pd3dDevice->Clear(0,	// pRects�еľ���������� pRectsΪNULL�Ÿò�������Ϊ0
		NULL,	//һ��ָ��D3DRECT�ṹ���ָ��
		D3DCLEAR_TARGET,	//D3DCLEAR��־������Ϊ��յ�ǰ����Ⱦ��
		D3DCOLOR_XRGB(0, 0, 255),	//��ɫ    
		1.0f,	// depth buffer����zֵ
		0	//ģ��
	);
	// ��ʼ��Ⱦ����
	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		// ������������Ⱦ����

		// ������Ⱦ
		m_pd3dDevice->EndScene();
	}

	// ��յ�ǰ�����е�����
	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------------------------------------------------------------------
	// Name: CleanUp()
	// Desc: �ͷ�Ԥ�ȳ�ʼ���Ķ���
//-----------------------------------------------------------------------------
void MyDirectX::CleanUp() {
	if (m_pd3dDevice != NULL) {
		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}
		
	if (m_pD3D != NULL) {
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

MyDirectX::~MyDirectX() {

}