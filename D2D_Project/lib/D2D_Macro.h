#pragma once

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

#define DefaultBrushColor	D2D1::ColorF(D2D1::ColorF::White)
#define DefaultBGColor		D2D1::ColorF(D2D1::ColorF::Black)
#define CollisionColor		D2D1::ColorF(D2D1::ColorF::Green)

#define MyEngine		D2D_Engine::GetInstance()
#define MySceneManager	SceneManager::GetInstance()
#define MyCamera		MySceneManager->GetNowScene()->m_pCamera

#define PI 3.14159f
#define DegreeToRad(angle)	(angle * PI / 180.0f)

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define Distance(x,y,a,b)	sqrtf((x-a)*(x-a) + (y-b)*(y-b))