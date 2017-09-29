#pragma once

#include <vector>
#include "stdafx.h"
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <memory>

#pragma comment(lib, "d2d1.lib")

namespace GraphicLibrary
{

	class GraphicStorage
	{
	public:
		GraphicStorage();
		GraphicStorage(ID2D1HwndRenderTarget* m_pRenderTarget, IWICImagingFactory* iwicig, LONG, LONG);
		GraphicStorage(const GraphicStorage&) = default;
		~GraphicStorage();
		ID2D1BitmapBrush* getBrush(int);

	private:
		HRESULT LoadBitmapFromFile(
			ID2D1RenderTarget *pRenderTarget,
			IWICImagingFactory *pIWICFactory,
			PCWSTR uri,
			UINT destinationWidth,
			UINT destinationHeight,
			ID2D1Bitmap **ppBitmap
		);

		ID2D1HwndRenderTarget* m_pRenderTarget;
		IWICImagingFactory* iwicig;
		std::vector<ID2D1BitmapBrush*> brushes;
		// some sort of ordering system

	};

	template<class Interface>
	inline void SafeRelease(Interface ** ppInterfaceToRelease)
	{
		if (*ppInterfaceToRelease != NULL)
		{
			(*ppInterfaceToRelease)->Release();
			(*ppInterfaceToRelease) = NULL;
		}
	}

}
