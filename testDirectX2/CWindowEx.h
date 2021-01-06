#pragma once
#include "define.h"
#include "MyDirectX.h"
class CWindowEx
{
private:
    HINSTANCE m_hInstance;
    HWND hWnd;
public:
	CWindowEx(HINSTANCE hInstance) {
        m_hInstance = hInstance;
        hWnd = NULL;
        // ��Ʋ�ע�ᴰ����
        WNDCLASSEX wce = {0};
        wce.cbSize = sizeof(wce);
        wce.cbClsExtra = 0;
        wce.cbWndExtra = 0;
        wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wce.hCursor = NULL;
        wce.hIcon = NULL;
        wce.hIconSm = NULL;
        wce.hInstance = m_hInstance;
        wce.lpfnWndProc = WndProc;
        wce.lpszClassName = WND_CLASS_NAME;
        wce.lpszMenuName = NULL;
        wce.style = CS_HREDRAW | CS_VREDRAW;
        RegisterClassEx(&wce);
	}
	~CWindowEx() {
        // ע��������
        UnregisterClass(WND_CLASS_NAME, m_hInstance);
	}
public:
    // ���ڴ����������ص�������
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    // main �������
    BOOL main(int width, int height) {
        // ����������
        hWnd = CreateWindowEx(0,
            WND_CLASS_NAME,
            WND_NAME,
            WS_OVERLAPPEDWINDOW,
            WND_X,
            WND_Y,
            width,
            height,
            NULL, NULL, m_hInstance, NULL);
        if (!hWnd)
            return FALSE;
        // ��ʾ����
        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);
        // ��ʼ��DirectX
        MyDirectX::Get()->InitD3D(hWnd, false);
        // ��Ϣѭ��
        MSG uMsg = {0};
        while (uMsg.message != WM_QUIT)
        {
            //PM_REMOVE -- PeekMessage��������Ϣ�Ӷ����������
            //�����Ϣ�ɵõ������ط���ֵ�����û����Ϣ�ɵõ�������ֵ���㡣
            if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&uMsg);
                DispatchMessage(&uMsg);
            }
            else {
                //DirectX��Ⱦ
                MyDirectX::Get()->Render();
            } 
        }
        return TRUE;
    }
};
