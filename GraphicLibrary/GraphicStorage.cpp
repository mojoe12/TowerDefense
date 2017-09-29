#include "stdafx.h"
#include "GraphicStorage.h"

namespace GraphicLibrary
{

	GraphicStorage::GraphicStorage() : 
		m_pRenderTarget(NULL),
		iwicig(NULL)
	{
	}

	GraphicStorage::GraphicStorage(ID2D1HwndRenderTarget* m_pRenderTargeti, IWICImagingFactory* iwicigi, LONG x, LONG y) :
		m_pRenderTarget(m_pRenderTargeti),
		iwicig(iwicigi)
	{
		const int numBrushes = 4;
		PWSTR names [numBrushes] = { 
			LR"(C:\Users\thisisjo\Pictures\Saved Pictures\roadterrain.png)",
			LR"(C:\Users\thisisjo\Pictures\Saved Pictures\werewolf.png)",
			LR"(C:\Users\thisisjo\Pictures\Saved Pictures\towers.png)",
			LR"(C:\Users\thisisjo\Pictures\Saved Pictures\landmine.png)"
		};
		//LR"(C:\Users\thisisjo\Pictures\Saved Pictures\landmine.png)",

		std::vector<PWSTR> imageNames (names, names + numBrushes);

		brushes = std::vector<ID2D1BitmapBrush*>();
		
		for (int i = 0; i < numBrushes; i++) {
			ID2D1Bitmap* m_pBitmap = NULL;
			HRESULT hr = LoadBitmapFromFile(
				m_pRenderTarget,
				iwicig,
				imageNames[i],
				x,
				y,
				&m_pBitmap
			);

			ID2D1BitmapBrush* m_pBitmapBrush = NULL;

			if (SUCCEEDED(hr))
			{
				hr = m_pRenderTarget->CreateBitmapBrush(
					m_pBitmap,
					&m_pBitmapBrush
				);
			}

			if (SUCCEEDED(hr)) 
			{
				ID2D1Bitmap* bmp;
				m_pBitmapBrush->GetBitmap(&bmp);
				auto a = bmp->GetSize();
				brushes.push_back(m_pBitmapBrush);
			}

			ID2D1Bitmap* bmp;
			brushes[0]->GetBitmap(&bmp);
			auto a = bmp->GetSize();
			a = a;
		}
	}


	GraphicStorage::~GraphicStorage()
	{
		for (auto bmbrush : brushes) {
			SafeRelease(&bmbrush);
		}
	}

	ID2D1BitmapBrush* GraphicStorage::getBrush(int i)
	{
		ID2D1BitmapBrush* retval = NULL;
		size_t index = 1;
		index *= i;
		if (index < brushes.size()) retval = brushes[i];
//		ID2D1Bitmap* bmp;
//		retval->GetBitmap(&bmp);
//		auto a = bmp->GetSize();
		return retval;
	}

	HRESULT GraphicStorage::LoadBitmapFromFile(
		ID2D1RenderTarget *pRenderTarget,
		IWICImagingFactory *pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap **ppBitmap
	)
	{
		IWICBitmapDecoder *pDecoder = NULL;
		IWICBitmapFrameDecode *pSource = NULL;
		IWICStream *pStream = NULL;
		IWICFormatConverter *pConverter = NULL;
		IWICBitmapScaler *pScaler = NULL;

		HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
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
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
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
}