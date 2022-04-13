﻿// D2D_Engine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "pch.h"
#include "D2D_Engine.h"

// TODO: 라이브러리 함수의 예제입니다.

void D2D_Engine::Initialize(HWND hwnd)
{
	/// Initializes the COM library on the current thread 
	/// and identifies the concurrency model as single-thread apartment (STA).
	HRESULT _hResult = CoInitialize(NULL);

	m_hWnd = hwnd;

	HRESULT hr = S_OK;
	// Direct2D Factory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

	static const WCHAR msc_fontName[] = L"굴림";
	static const FLOAT msc_fontSize = 13;

	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pIWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_pDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&m_pTextFormat
		);
	}

	// 텍스트 정렬 방식
	if (SUCCEEDED(hr))
	{
		// Left-Top the text horizontally and vertically.
		m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}

	m_SpriteSheets.clear();

	m_hResult = CreateGraphicResoureces();

	MySceneManager->Init();

	SetFrameLimit(60);
}

void D2D_Engine::Finalize()
{
	SafeRelease(&m_pD2DFactory);
	DiscardGraphicResources();

	CoUninitialize();
}

void D2D_Engine::Update()
{
	MySceneManager->Update();
	OnDraw();
}

bool D2D_Engine::FrameCheck()
{
	static __int64 prevDTime = GetTickCount64();
	__int64 currDTime = GetTickCount64();
	if (currDTime - prevDTime < (1.0f / (float)m_FrameLimit) * 1000)
	{
		return false;
	}
	prevDTime = currDTime;
	return true;
}

HRESULT D2D_Engine::CreateGraphicResoureces()
{
	HRESULT hr = S_OK;
	if (m_pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, size),
			&m_pRenderTarget);
		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
			hr = m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrush);
		}
	}
	return hr;
}

void D2D_Engine::DiscardGraphicResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBrush);
}

void D2D_Engine::OnDraw()
{
	BeginRender();
	Render();
	EndRender();
}

void D2D_Engine::BeginRender()
{
	m_hResult = CreateGraphicResoureces();

	// 디바이스 종속적 자원들이 문제 없고, 랜더링을 할 수 있는 상황일 때
	if (SUCCEEDED(m_hResult) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		m_RenderTargetSize = m_pRenderTarget->GetSize();

		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(DefaultBGColor));
	}
}

void D2D_Engine::Render()
{
	MySceneManager->Draw();
}

void D2D_Engine::EndRender()
{
	if (SUCCEEDED(m_hResult) && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		m_pRenderTarget->EndDraw();

		// 자원을 복구해야 할 경우
		if (m_hResult == D2DERR_RECREATE_TARGET)
		{
			m_hResult = S_OK;
			DiscardGraphicResources();
		}
	}
}

D2D1_COLOR_F D2D_Engine::SetBrushColor(D2D1_COLOR_F color)
{
	D2D1_COLOR_F originColor = m_pBrush->GetColor();

	SafeRelease(&m_pBrush);
	m_pRenderTarget->CreateSolidColorBrush(color, &m_pBrush);

	return originColor;
}

void D2D_Engine::SetTransform(D2D1_MATRIX_3X2_F matrix)
{
	m_pRenderTarget->SetTransform(matrix);
}

void D2D_Engine::DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	D2D1_COLOR_F originColor = SetBrushColor(color);

	m_pRenderTarget->DrawRectangle(rect, m_pBrush, 2.0f);

	SetBrushColor(originColor);
}

void D2D_Engine::DrawRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F color)
{
	D2D1_RECT_F rect = { x1, y1, x2, y2 };
	DrawRectangle(rect, color);
}

void D2D_Engine::DrawRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F color)
{
	D2D1_RECT_F rect = { center.x - width / 2, center.y - height / 2, center.x + width / 2, center.y + height / 2 };
	DrawRectangle(rect, color);
}

void D2D_Engine::DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F color)
{
	D2D1_COLOR_F originColor = SetBrushColor(color);

	m_pRenderTarget->DrawLine(p1, p2, m_pBrush, 2.0f);

	SetBrushColor(originColor);
}

void D2D_Engine::DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F color)
{
	D2D1_POINT_2F p1 = { x1, y1 };
	D2D1_POINT_2F p2 = { x2, y2 };
	DrawLine(p1, p2, color);
}

void D2D_Engine::DrawEllipse(D2D1_ELLIPSE ellipse, D2D1_COLOR_F color)
{
	D2D1_COLOR_F originColor = SetBrushColor(color);

	m_pRenderTarget->DrawEllipse(ellipse, m_pBrush, 2.0f);

	SetBrushColor(originColor);
}

void D2D_Engine::DrawEllipse(float x1, float y1, float x2, float y2, D2D1_COLOR_F color)
{
	D2D1_ELLIPSE ellipse;
	ellipse.radiusX = x2 - x1;
	ellipse.radiusY = y2 - y1;
	ellipse.point = { (x1 + x2) / 2, (y1 + y2) / 2 };
	DrawEllipse(ellipse, color);
}

void D2D_Engine::DrawEllipse(D2D1_POINT_2F center, float radius, D2D1_COLOR_F color)
{
	D2D1_ELLIPSE ellipse;
	ellipse.point = center;
	ellipse.radiusX = radius;
	ellipse.radiusY = radius;
	DrawEllipse(ellipse, color);
}

void D2D_Engine::DrawTextFormat(const WCHAR* str, float x, float y, D2D1_COLOR_F color)
{
	D2D1_SIZE_F renderTargetSize = m_pRenderTarget->GetSize();
	D2D1_COLOR_F originColor = SetBrushColor(color);

	m_pRenderTarget->DrawText(
		str,
		wcslen(str),
		m_pTextFormat,
		D2D1::RectF(x, y, renderTargetSize.width + x, renderTargetSize.height + y),
		m_pBrush
	);

	SetBrushColor(originColor);
}

void D2D_Engine::LoadSpriteSheet(const WCHAR* sheet_name, const WCHAR* file_path)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	// Create a bitmap by loading it from a file.
	hr = LoadBitmapFromFile(
		m_pRenderTarget,
		m_pIWICFactory,
		file_path,
		0,
		0,
		&pNewBitmap
	);

	if (SUCCEEDED(hr))
	{
		m_SpriteSheets.insert(std::pair<const WCHAR*, ID2D1Bitmap*>(sheet_name, pNewBitmap));
	}
}

void D2D_Engine::DrawBitmap(Renderer* p_renderer)
{
	ID2D1Bitmap* pBitmap = nullptr;
	if (FindSpriteFromSheet(p_renderer->m_pSprite->m_SheetName, &pBitmap))
	{
		Transform transform = p_renderer->m_Parent->GetTransfrom() + p_renderer->m_Transform;
		float x = transform.Position.x - p_renderer->m_Size.m_Width * 1.0f + p_renderer->m_pSprite->m_OriginPos.x;
		float y = transform.Position.y - p_renderer->m_Size.m_Height * 1.0f + p_renderer->m_pSprite->m_OriginPos.y;

		m_pRenderTarget->DrawBitmap(pBitmap
			, D2D1::RectF(x, y, x + p_renderer->m_Size.m_Width, y + p_renderer->m_Size.m_Height)
			, 1
			, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
			, p_renderer->m_pSprite->m_SpriteRect);
	}
}

bool D2D_Engine::FindSpriteFromSheet(const WCHAR* sheet_name, ID2D1Bitmap** p_bitmap)
{
	*p_bitmap = m_SpriteSheets[sheet_name];

	return *p_bitmap != nullptr;
}

HRESULT D2D_Engine::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
		}
		else
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

HRESULT D2D_Engine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}