#include "stdafx.h"

GameManager g_GameManager;

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{			
	//������ â ��� ����
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	//Window Class Styles
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GameManager::WINDOW_CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	//������ â������� ���
	if ( !RegisterClassEx(&wcex) )
	{
		MessageBox(NULL, L"Call to RegisterClassEx failed!", GameManager::WINDOW_TITLE_CAPTION, MB_OK);

		return 1;
	}
	
	hInst = hInstance; // Store instance handle in our global variable

	//������ ������ ����
	int width = GameManager::RESOLUTION_X;
	int height = GameManager::RESOLUTION_Y;
	HWND hWnd = CreateWindow(
		GameManager::WINDOW_CLASS_NAME,		//������(â)�� �̸�
		GameManager::WINDOW_TITLE_CAPTION,	//Ÿ��Ʋ �κп� ��µǴ� ����
		WS_CAPTION | WS_SYSMENU,			//������(â) ��Ÿ�� ( WS_POPUP���� �ϸ� Ÿ��Ʋ�� ���� ���� )
		CW_USEDEFAULT, CW_USEDEFAULT,		//�⺻ ��ġ
		width, height,						//�⺻ ũ��
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if ( !hWnd )
	{
		MessageBox(NULL, L"Call to CreateWindow failed!", GameManager::WINDOW_TITLE_CAPTION, MB_OK);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	g_GameManager.Initialize(hWnd);		

	
	MSG message = MSG();
	while ( message.message != WM_QUIT )
	{
		if ( PeekMessageW(&message, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			static DWORD prevTime = timeGetTime();
			DWORD nowTime = timeGetTime();

			double tickSecond = ( nowTime - prevTime ) * 0.001f;
			prevTime = nowTime;

			g_GameManager.Loop(tickSecond);
		}
	}

	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch ( message )
	{
		case WM_CREATE:
			{
				RECT wantRect = { 0, 0, GameManager::RESOLUTION_X, GameManager::RESOLUTION_Y };
				AdjustWindowRect(&wantRect, WS_CAPTION | WS_SYSMENU, false); 
				MoveWindow(hWnd, 0, 0, wantRect.right - wantRect.left, wantRect.bottom - wantRect.top, true);
			}
			break;
		case WM_DESTROY:
			g_GameManager.Destroy();
			PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:		
		case WM_MOUSEWHEEL:
			g_GameManager.GameInputProc(hWnd, message, wParam, lParam);
			break;
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}