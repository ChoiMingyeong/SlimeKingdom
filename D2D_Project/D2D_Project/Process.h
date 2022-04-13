#pragma once

class Process : public Singleton<Process>
{
public:
	HWND m_hWnd;

	HRESULT Initialize();
	void RunMessageLoop();

private:
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);
};

