#include "CEngine.h"

// Комментарий для компоновщика
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"Dwrite.lib")

Engine::Engine(HINSTANCE h)
{
	hWnd = NULL;
	this->hInst = h;

	this->m_pDirect2dFactory = NULL;
	this->pRenderTarget = NULL;
	this->m_pPathGeometry = NULL;
	this->pBrush = NULL;
	this->pStroke = NULL;
	this->pSink = NULL;

	this->pLogig = new CLogic;

	this->btnA = { 10,10,20,20 };
	this->FPS = 0;
}
Engine::~Engine()
{
	if (this->m_pDirect2dFactory)
	{
		this->m_pDirect2dFactory->Release();
		this->m_pDirect2dFactory = NULL;
	}
	if (this->pBrush)
	{
		this->pBrush->Release();
		this->pBrush = NULL;
	}
	if (this->pRenderTarget)
	{
		this->pRenderTarget->Release();
		this->pRenderTarget = NULL;
	}
	if (this->pLogig)
	{
		this->pLogig->~CLogic();
		this->pLogig = NULL;
	}
	if (this->pStroke)
	{
		this->pStroke->Release();
		this->pStroke = nullptr;
	}
	if (this->m_pPathGeometry)
	{
		this->m_pPathGeometry->Release();
		this->m_pPathGeometry = nullptr;
	}
	if (this->pSink)
	{
		this->pSink->Release();
		this->pSink = nullptr;
	}
	KillTimer(hWnd, TIMER1);
	KillTimer(hWnd, TIMER_FPS);
}

HRESULT Engine::Initialize()
{
	HRESULT hr = S_OK;

	// Initialize device-indpendent resources, such as the Direct2D factory
	hr = this->CreateDeviceIndependentResources();
	if (!SUCCEEDED(hr))return hr;
	else {

		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)this->WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = this->hInst;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"D2DDemoApp";

		if (!RegisterClassEx(&wcex)) return S_FALSE;
	}
	// Create the window.
	this->hWnd = CreateWindow(L"D2DDemoApp", L"app D2D", WS_OVERLAPPED | WS_SYSMENU, 0, 0, 500, 500, NULL, NULL, this->hInst, this);
	if (!this->hWnd) return S_FALSE;
	SetTimer(hWnd, TIMER1, 10, NULL);
	SetTimer(hWnd, TIMER_FPS, 1000, NULL);
	CreateWindow(L"Button", L"but", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		this->btnA.l, this->btnA.t, this->btnA.w, this->btnA.h,
		this->hWnd, (HMENU)ID_BUTTON_A, this->hInst, NULL);

	if (SUCCEEDED(hr))
	{
		ShowWindow(this->hWnd, SW_SHOWNORMAL);
		UpdateWindow(this->hWnd);
		this->RunMessageLoop();
	}
	return hr;
}
void Engine::RunMessageLoop()
{
	MSG msg;
	msg.message = WM_NULL; //initialize variable msg
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			this->Render();
		}
	}

}
LRESULT Engine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Engine* pThis;
	if (message == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<Engine*>(lpcs->lpCreateParams);
		// Put the value in a safe place for future use
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else
	{
		// Recover the "this" pointer from where our WM_NCCREATE handler stashed it.
		pThis = reinterpret_cast<Engine*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pThis) pThis->Procedure(hWnd, message, wParam, lParam);

	return (DefWindowProc(hWnd, message, wParam, lParam));
}
LRESULT Engine::Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(NULL);
		return 0;
	}
	if (message == WM_LBUTTONDOWN)
	{
		// Достаем координаты щелчка
		float Xpos, Ypos;
		Xpos = static_cast<float>LOWORD(lParam);
		Ypos = static_cast<float>HIWORD(lParam);
		this->pLogig->AddArrow(Xpos, Ypos, 0.3f, 0.6f);
	}
	if (message == WM_MOUSEMOVE)
	{
		// Достаем координаты щелчка
		float Xpos, Ypos;
		Xpos = static_cast<float>LOWORD(lParam);
		Ypos = static_cast<float>HIWORD(lParam);
		//this->pLogig->MooveStar(Xpos, Ypos);
		if (this->btnA.pushed) this->pLogig->AddArrow(Xpos, Ypos, 5.0f, 5.0f);
	}
	if (message == WM_COMMAND)
	{
		if (wParam == ID_BUTTON_A)
		{
			this->btnA.pushed = !this->btnA.pushed;
		}
	}
	if (message == WM_TIMER)
	{
		if (wParam == TIMER1);// this->pLogig->SolveArray();
		if (wParam == TIMER_FPS) this->SetFPS();
	}
	return S_OK;
}

HRESULT Engine::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	if (FAILED(hr)) return hr;
	// Create a Direct2D factory.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr)) return hr;
	// Create Stroke. Its independent too
	D2D1_STROKE_STYLE_PROPERTIES strokeStyleProperties = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_ROUND,  // The start cap.
		D2D1_CAP_STYLE_ROUND,  // The end cap.
		D2D1_CAP_STYLE_ROUND, // The dash cap.
		D2D1_LINE_JOIN_ROUND, // The line join.
		10.0f, // The miter limit.
		D2D1_DASH_STYLE_DOT, // The dash style D2D1_DASH_STYLE_DOT
		0.0f // The dash offset.
	);
	hr = this->m_pDirect2dFactory->CreateStrokeStyle(strokeStyleProperties, NULL, 0, &pStroke);
	hr = pDWriteFactory->CreateTextFormat(
		L"Arial",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0f,
		L"en-us",
		&pTxtFormat
	);
	if (FAILED(hr)) return hr;
	if (SUCCEEDED(hr)) hr = this->m_pDirect2dFactory->CreatePathGeometry(&m_pPathGeometry);

	
}
HRESULT Engine::CreateTarget()
{
	if (this->pRenderTarget) return S_FALSE; // If its already exists

	// making new one
	RECT rc;
	GetClientRect(this->hWnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	this->pLogig->SetScreenDpi(rc.right - rc.left, rc.bottom - rc.top);

	// Create a Direct2D render target
	HRESULT hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(this->hWnd, size),
		&this->pRenderTarget
	);
	if (SUCCEEDED(hr)) this->pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	if (SUCCEEDED(hr) && !pBrush) hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pBrush);



	return hr;

}
HRESULT Engine::Render()
{
	this->FPSiter++;
	HRESULT hr = this->CreateTarget();
	if (FAILED(hr)) return hr;
	if (!m_pPathGeometry) return S_FALSE;
	this->pRenderTarget->BeginDraw();
	this->pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	this->pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
	// Draw here
	this->RenderTxt(200, 5, L"txt", this->FPS);
	this->RenderTreeBorders(this->pLogig->GetTree());
	this->RenderGui();
	// up to this end
	hr = this->pRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return S_OK;
}

void Engine::DiscardDeviceResources()
{
	if (this->m_pDirect2dFactory)
	{
		this->m_pDirect2dFactory->Release();
		this->m_pDirect2dFactory = NULL;
	}
	if (this->pBrush)
	{
		this->pBrush->Release();
		this->pBrush = NULL;
	}
	if (this->pRenderTarget)
	{
		this->pRenderTarget->Release();
		this->pRenderTarget = NULL;
	}
	if (this->m_pPathGeometry)
	{
		this->m_pPathGeometry->Release();
		this->m_pPathGeometry = nullptr;
	}
	if (this->pSink)
	{
		this->pSink->Release();
		this->pSink = nullptr;
	}
	if (this->pDWriteFactory)
	{
		pDWriteFactory->Release();
		pDWriteFactory = nullptr;
	}
	if (this->pTxtFormat)
	{
		pTxtFormat->Release();
		pTxtFormat = nullptr;
	}
}


HRESULT Engine::RenderTxt(float x, float y, const wchar_t* txt, int Num)
{
	if (this->pRenderTarget)
	{

		wchar_t buffer[_MAX_ITOSTR_BASE16_COUNT]; //_MAX_ITOSTR_BASE16_COUNT = 16
		_itow_s(static_cast<int>(Num), buffer, 10);
		D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 100.0f, y + 200.0f);
		this->pRenderTarget->DrawText(
			buffer,        // The string to render.
			2,    // The string's length.
			pTxtFormat,    // The text format.
			layoutRect,       // The region of the window where the text will be rendered.
			this->pBrush     // The brush used to draw the text.
		);
	}
	return E_NOTIMPL;
}
HRESULT Engine::RenderGui()
{
	D2D1_RECT_F btnRect = { this->btnA.l,this->btnA.t,this->btnA.l + this->btnA.w,this->btnA.t + this->btnA.h };
	if (this->btnA.pushed) { this->pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::AliceBlue)); }
	else { this->pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray)); }
	this->pRenderTarget->FillRectangle(btnRect, this->pBrush);
	this->pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	this->pRenderTarget->DrawRectangle(btnRect, this->pBrush, 2.0f, NULL);
	return S_OK;
}
HRESULT Engine::RenderTreeBorders(CQuadTree * pTree)
{
	if (pTree->IsSubDevided())
	{
		RenderTreeBorders(pTree->GetChild(0));
		RenderTreeBorders(pTree->GetChild(1));
		RenderTreeBorders(pTree->GetChild(2));
		RenderTreeBorders(pTree->GetChild(3));
	}
	else
	{
		RECT Br = pTree->GetBorder();
		this->pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Coral));
		this->pRenderTarget->DrawRectangle(D2D1::Rect(
			static_cast<int>(Br.left), 
			static_cast<int>(Br.top), 
			static_cast<int>(Br.right), 
			static_cast<int>(Br.bottom)), 
			this->pBrush, 3.0f, NULL);
		this->pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		this->RenderTxt(Br.left+4, Br.top+4, L"txt", pTree->GetLoad());
	}
	return S_OK;
}
void Engine::SetFPS()
{
	this->FPS = FPSiter;
	FPSiter = 0;
}
