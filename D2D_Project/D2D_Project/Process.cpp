#include "stdafx.h"
#include "Process.h"

HRESULT Process::Initialize()
{
	HRESULT hr;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.

		// Register the window class.
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Process::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"D2D_Demo";

	RegisterClassEx(&wcex);


	// Create the window.
	m_hWnd = CreateWindow(
		L"D2D_Demo",
		L"Direct2D Demo App",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	hr = m_hWnd ? S_OK : E_FAIL;

	MyEngine->Initialize(m_hWnd);
	MyGP->Start();

	if (SUCCEEDED(hr))
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);
	}

	return hr;
}

void Process::RunMessageLoop()
{
	MSG msg;

	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (MyEngine->FrameCheck())
			{
				MyEngine->Update();
				MyGP->Update();
			}
		}
	}
}

LRESULT Process::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MyEngine->Initialize(hWnd);
	}
	break;

	case WM_DESTROY:
		MyEngine->Finalize();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
