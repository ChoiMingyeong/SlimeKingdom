// D2D_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "stdafx.h"

int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
)
{
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			if (SUCCEEDED(MyProcess->Initialize()))
			{
				MyProcess->RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}