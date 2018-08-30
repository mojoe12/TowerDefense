#include "stdafx.h"
//#include "DemoApp.h"
#include <windows.h>

#include <windowsx.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "GraphicStorage.h"
#include "Engine.h"
#include "MessageQueue.h"

#pragma comment(lib, "d2d1.lib")

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class MegaEngine
{
public:
	MegaEngine();
	~MegaEngine();
	HRESULT Initialize();
	void RunMessageLoop();

private:
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	static LRESULT CALLBACK WndProc(
		HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam
	);

	void setup1();
	void startThread();
	void runThread();

	std::shared_ptr<GraphicLibrary::GraphicStorage> gs;
	std::shared_ptr<LogicLibrary::Engine> eng;
	MessageQueue mq;

	bool ifplacing;
	std::shared_ptr<Message> msg;

	LONG x;
	LONG y;

	std::thread t1;

	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* iwicig;
};