#pragma once

class Renderer;

class D2D_Engine : public Singleton<D2D_Engine>
{
public:
	//���� �ʱ�ȭ(���� ��� �� ������ �ѹ��� �ʱ�ȭ ���־�� ��)
	void Initialize(HWND hwnd);

	void Finalize();

private:
	HWND m_hWnd;		//���� ������ �ڵ�

#pragma region ���� �̺�Ʈ
public:
	//���� ������ ���ӿ�����Ʈ�鿡 ���� ������Ʈ�� �����ϴ� �Լ�
	void Update();
	bool FrameCheck();
	void SetFrameLimit(unsigned int limit) { m_FrameLimit = limit; }

private:
	unsigned int m_FrameLimit;
#pragma endregion

#pragma region �׷��� ����
private:
	HRESULT m_hResult;

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;

	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;		// �׸��⸦ �� ����� ���� Ÿ��
	ID2D1SolidColorBrush* m_pBrush;

	IWICImagingFactory* m_pIWICFactory;		// �̹��� ����� ���� ���丮

	D2D1_SIZE_F m_RenderTargetSize;

	//��������Ʈ ��Ʈ
	std::map<const WCHAR*, ID2D1Bitmap*> m_SpriteSheets;

	// ��Ʈ�� ����
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
	//Brush�� ���� color������ �ٲ��ִ� �Լ�
	D2D1_COLOR_F SetBrushColor(D2D1_COLOR_F color);

	//���� pRenderTarget�� Transform�� matrix�� �̿��Ͽ� ��ȯ���ִ� �Լ�
	void SetTransform(D2D1_MATRIX_3X2_F matrix);

#pragma region ���� �׸���

#pragma region �簢�� �׸���
	//�������� ������ ������ �ִ� rect�� �簢���� �׸��� �Լ�
	void DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F = DefaultBrushColor);

	//������(x1, y1)�� ����(x2, y2)���� �簢���� �׸��� �Լ�
	void DrawRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F = DefaultBrushColor);

	//�߽����� ���� ���� ���̷� �簢���� �׸��� �Լ�
	void DrawRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F = DefaultBrushColor);
#pragma endregion

#pragma region ���� �׸���
	void DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F = DefaultBrushColor);
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F = DefaultBrushColor);
#pragma endregion

#pragma region �� �׸���
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