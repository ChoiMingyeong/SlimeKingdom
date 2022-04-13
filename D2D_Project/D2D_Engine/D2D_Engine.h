#pragma once

class Renderer;

class D2D_Engine : public Singleton<D2D_Engine>
{
public:
	//엔진 초기화(엔진 사용 전 무조건 한번은 초기화 해주어야 함)
	void Initialize(HWND hwnd);

	void Finalize();

private:
	HWND m_hWnd;		//메인 윈도우 핸들

#pragma region 메인 이벤트
public:
	//엔진 내부의 게임오브젝트들에 관한 업데이트를 실행하는 함수
	void Update();
	bool FrameCheck();
	void SetFrameLimit(unsigned int limit) { m_FrameLimit = limit; }

private:
	unsigned int m_FrameLimit;
#pragma endregion

#pragma region 그래픽 엔진
private:
	HRESULT m_hResult;

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;		// 그리기를 할 대상인 렌더 타겟
	ID2D1SolidColorBrush* m_pBrush;

	IWICImagingFactory* m_pIWICFactory;		// 이미지 사용을 위한 팩토리

	D2D1_SIZE_F m_RenderTargetSize;

	//스프라이트 시트
	std::map<const WCHAR*, ID2D1Bitmap*> m_SpriteSheets;

	// 비트맵 관련
private:
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	// Create a bitmap by loading it from a file.
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

private:
	HRESULT CreateGraphicResoureces();
	void DiscardGraphicResources();

	void OnDraw();
	void BeginRender();
	void Render();
	void EndRender();

public:
	//Brush의 색을 color값으로 바꿔주는 함수
	D2D1_COLOR_F SetBrushColor(D2D1_COLOR_F color);

	//현재 pRenderTarget의 Transform을 matrix를 이용하여 변환해주는 함수
	void SetTransform(D2D1_MATRIX_3X2_F matrix);

#pragma region 도형 그리기

#pragma region 사각형 그리기
	//시작점과 끝점의 정보가 있는 rect로 사각형을 그리는 함수
	void DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F = DefaultBrushColor);

	//시작점(x1, y1)과 끝점(x2, y2)으로 사각형을 그리는 함수
	void DrawRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F = DefaultBrushColor);

	//중심점과 가로 세로 길이로 사각형을 그리는 함수
	void DrawRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F = DefaultBrushColor);
#pragma endregion

#pragma region 직선 그리기
	void DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F = DefaultBrushColor);
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F = DefaultBrushColor);
#pragma endregion

#pragma region 원 그리기
	void DrawEllipse(D2D1_ELLIPSE ellipse, D2D1_COLOR_F = DefaultBrushColor);
	void DrawEllipse(float x1, float y1, float x2, float y2, D2D1_COLOR_F = DefaultBrushColor);
	void DrawEllipse(D2D1_POINT_2F center, float radius, D2D1_COLOR_F = DefaultBrushColor);
#pragma endregion

#pragma endregion

	void DrawTextFormat(const WCHAR* str, float x, float y, D2D1_COLOR_F = DefaultBrushColor);

	void LoadSpriteSheet(const WCHAR* sheet_name, const WCHAR* file_path);

	void DrawBitmap(Renderer* p_renderer);

	bool FindSpriteFromSheet(const WCHAR* sheet_name, ID2D1Bitmap** p_bitmap);

#pragma endregion

};