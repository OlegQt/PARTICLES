#pragma once
#include <windows.h>
#include <iostream>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#include "CLogic.h"

#define ID_BUTTON_A 22
#define TIMER1 1001
#define TIMER_FPS 1002

class Engine
{
public:
	Engine(HINSTANCE);
	~Engine();
	
	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();

	// Process and dispatch messages
	void RunMessageLoop();

	// The windows procedure.
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	LRESULT Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInst;
	HWND hWnd;
	int FPSiter, FPS;

	ID2D1Factory* m_pDirect2dFactory;
	IDWriteFactory* pDWriteFactory;
	IDWriteTextFormat* pTxtFormat;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	ID2D1StrokeStyle* pStroke;
	// Ниже геометрия, для одноразовой отрисовки, наверное в ней нет смысла.
	ID2D1GeometrySink* pSink;
	ID2D1PathGeometry* m_pPathGeometry;

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateTarget();
	HRESULT Render();
	HRESULT RenderTxt(float x, float y, const wchar_t* txt, int number);
	HRESULT RenderTreeBorders(CQuadTree * );
	HRESULT RenderGui();

	void DiscardDeviceResources();

	CLogic* pLogig;

	struct WndButton
	{
		int l;
		int t;
		int h;
		int w;
		int id;
		bool pushed;
	};
	WndButton btnA;

	void SetFPS();
};
