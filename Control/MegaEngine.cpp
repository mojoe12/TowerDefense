#include "stdafx.h"
#include "MegaEngine.h"
#include <memory>
#include <thread>
#include "Machine.h"
#include "Coordinate.h"
#include "Werewolf.h"
#include "Wave.h"
#include "EngineRunner.h"
#include "LandmineBuilder.h"
#include "Map.h"


MegaEngine::MegaEngine() :
	ifplacing(false),
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL)
{

}

MegaEngine::~MegaEngine()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	t1.join();
}

void MegaEngine::RunMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

HRESULT MegaEngine::Initialize()
{

	HRESULT hr;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = MegaEngine::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"D2DMegaEngine";

		RegisterClassEx(&wcex);


		// Because the CreateWindow function takes its size in pixels,
		// obtain the system DPI and use it to scale the window size.
		FLOAT dpiX, dpiY;

		// The factory returns the current system DPI. This is also the value it will use
		// to create its own windows.
		m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);
		// dpi = dots per inch


		// Create the window.
		m_hwnd = CreateWindow(
			L"D2DMegaEngine",
			L"Direct2D MegaEngine",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}

	setup1();
	startThread();

	return hr;
}

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

	// com = component object model
	// binary format

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			MegaEngine app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}


HRESULT MegaEngine::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}

HRESULT MegaEngine::CreateDeviceResources()
{

	HRESULT hr = S_OK;
	
	if (!m_pRenderTarget)
	{
		RECT newrc;
		BOOL answer = IsWindow(m_hwnd);
		GetClientRect(m_hwnd, &newrc);

		D2D1_SIZE_U size = D2D1::SizeU(
			newrc.right - newrc.left,
			newrc.bottom - newrc.top
		);

		x = newrc.right - newrc.left;
		y = newrc.bottom - newrc.top;

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget
		);

		iwicig = NULL;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&iwicig
		);
	}


	return hr;
}

void MegaEngine::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
}

LRESULT CALLBACK MegaEngine::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		MegaEngine *pMegaEngine = (MegaEngine *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pMegaEngine)
		);

		result = 1;
	}
	else
	{
		MegaEngine *pMegaEngine = reinterpret_cast<MegaEngine *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));

		bool wasHandled = false;

		if (pMegaEngine)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pMegaEngine->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				pMegaEngine->OnRender();
				ValidateRect(hwnd, NULL);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_LBUTTONDOWN:
			{
				
				double x = GET_X_LPARAM(lParam);
				double y = GET_Y_LPARAM(lParam);

				const int xsidebar = 0; // EDIT
				const int yTimeButtonStart = 0; // EDIT
				const int yTower1Start = 0;

				if (x > xsidebar)
				{
					if (y > yTimeButtonStart)
					{
						Message m(true);
						pMegaEngine->msg = std::make_shared<Message> (m);
						pMegaEngine->ifplacing = false;
					}

					else if (y > yTower1Start) 
					{
						LogicLibrary::Coordinate<double> coord(0, 0);
						LogicLibrary::LandmineBuilder lmb (coord, pMegaEngine->eng->getMachine());
						std::shared_ptr<LogicLibrary::Tower> tower (&lmb);
						Message m(false, true, tower);
						pMegaEngine->msg = std::make_shared<Message>(m);
						pMegaEngine->ifplacing = true;
					}
				}

				else if (pMegaEngine->ifplacing) 
				{
					const double cellsToPixels = 1; // EDIT
					LogicLibrary::Coordinate<double> pos(x * cellsToPixels, y * cellsToPixels);
					pMegaEngine->msg->place(pos);
					
					std::lock_guard<std::mutex> lock(pMegaEngine->mq.getMutex());
					pMegaEngine->mq.push(*(pMegaEngine->msg));

				}

				// secondary:
				// upgrading >:(
				// weapon-related mouse input?

				InvalidateRect(hwnd, NULL, FALSE);

			}
			result = 0;
			wasHandled = true;
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}

HRESULT MegaEngine::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr) && m_pRenderTarget && gs && iwicig)
	{


		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		D2D1_RECT_F rect = D2D1::RectF(
			0,
			0,
			rtSize.width,
			rtSize.height
		);

		// road is on bottom, draw first

		for (int i = 0; ; i++) {
			ID2D1BitmapBrush* bmbrush = gs->getBrush(i);
			if (bmbrush == NULL) break;
			else {
				ID2D1Bitmap* bmp;
				bmbrush->GetBitmap(&bmp);
				auto a = bmp->GetSize();
				m_pRenderTarget->FillRectangle(&rect, bmbrush);
			}
		}

		m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}

	return hr;
}

void MegaEngine::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

void MegaEngine::setup1()
{
	using pair = std::pair<double, std::shared_ptr<LogicLibrary::Attacker>>;

	const int size = 5;
	
	GraphicLibrary::GraphicStorage* gsnew = new GraphicLibrary::GraphicStorage(m_pRenderTarget, iwicig, x, y);

	gs = std::shared_ptr<GraphicLibrary::GraphicStorage> (gsnew);
	auto brush = gs->getBrush(0);
	ID2D1Bitmap* bmp;
	brush->GetBitmap(&bmp);
	auto a = bmp->GetSize();

	LogicLibrary::Machine mach(size, gs);
	LogicLibrary::Coordinate<int> origin (0, 0);
	std::vector<LogicLibrary::Coordinate<int>> vec;
	vec.push_back(origin);
	LogicLibrary::PathObject po (vec);
	std::shared_ptr<LogicLibrary::PathObject> pop;
	pop = std::make_shared<LogicLibrary::PathObject> (po);
	std::vector<std::shared_ptr<LogicLibrary::PathObject>> pops;
	pops.push_back(pop);
	mach.setPaths(pops);

	auto machptr = std::make_shared<LogicLibrary::Machine>(mach);
	LogicLibrary::Map map(size, machptr);
	machptr->setMap(std::make_shared<LogicLibrary::Map> (map));

	LogicLibrary::Coordinate<double> coord(0, 0);
	LogicLibrary::Werewolf ww(coord, machptr);
	auto wwptr = std::make_shared<LogicLibrary::Werewolf>(ww);
	int timetostart = 2;
	pair pr = make_pair(timetostart, wwptr);
	std::vector<pair> waveinfo;
	waveinfo.push_back(pr);
	LogicLibrary::Wave myWave(machptr, waveinfo);
	auto waveptr = std::make_shared<LogicLibrary::Wave>(myWave);
	LogicLibrary::Engine engin(machptr, waveptr, 1, 1);
	engin.loadBrushSet(gs);
	eng = std::make_shared<LogicLibrary::Engine> (engin);

    brush = gs->getBrush(0);
	brush->GetBitmap(&bmp);
	a = bmp->GetSize();

}

void MegaEngine::startThread()
{
	auto brush = gs->getBrush(0);
	ID2D1Bitmap* bmp;
	brush->GetBitmap(&bmp);
	auto a = bmp->GetSize();

	t1 = std::thread (&MegaEngine::runThread, this);
}

void MegaEngine::runThread() 
{
	bool ifRunning = true;
	while (true) {
		if (ifRunning)
		{
			eng->Update();
		}

		{
			std::lock_guard<std::mutex> lock(mq.getMutex());
			while (mq.getsize()) 
			{
				Message m = mq.pop();
				if (m.ifChangeTime()) ifRunning = !ifRunning;
				else if (m.ifBuild())
				{
					auto tower = m.getTower();
					LogicLibrary::Coordinate<double> co (m.getPosition().X(), m.getPosition().Y());
					tower->changePosition(co);
					eng->getMachine()->addTower(tower);
				}
			}
		}
		
		/*{
			// lock gs (its a pointer?)
			OnRender();
		}*/
	}
}

/*
void MegaEngine::run(bool withInput)
{
	std::thread t1(input, messages);
	while (true) {
		engine.Update();
		{ // not necessary
			std::lock_guard<std::mutex> lock(messages.getMutex());
			
		}
	}
}*/