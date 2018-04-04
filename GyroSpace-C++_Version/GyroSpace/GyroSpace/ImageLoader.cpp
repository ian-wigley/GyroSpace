//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Image Loader Class

#include "pch.h"
#include "ImageLoader.h"
#include "Game.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;

ImageLoader::ImageLoader(IWICImagingFactory2* _wicFactory, ID2D1DeviceContext* _d2dContext)
{
	m_wicFactory = _wicFactory;
	m_d2dContext = _d2dContext;
}

// Load a Bitmap image from file using the Windows Imaging Component and return it
ID2D1Bitmap* ImageLoader::LoadBitmap(Platform::String^ Filename)
{
	// Load the Image from the file system
	DX::ThrowIfFailed(m_wicFactory->CreateDecoderFromFilename(
		Filename->Data(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&m_wicDecoder));

	DX::ThrowIfFailed(m_wicDecoder->GetFrame(0, &m_wicFrameDecode));

	DX::ThrowIfFailed(m_wicFactory->CreateFormatConverter(&m_wicFormatConverter));

	DX::ThrowIfFailed(m_wicFormatConverter->Initialize(
		m_wicFrameDecode.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
		)
		);

	UINT imageWidth;
	UINT imageHeight;
	m_wicFormatConverter->GetSize(&imageWidth, &imageHeight);

	DX::ThrowIfFailed(m_d2dContext->CreateBitmapFromWicBitmap(m_wicFormatConverter.Get(),
		&m_Bitmap
		)
		);

	return m_Bitmap;
}