#pragma once

#include "Renderer.h"

using namespace GyroSpace;
using namespace Windows::ApplicationModel::Core;
using namespace Microsoft::WRL;

ref class ImageLoader sealed
{
public:

internal:
	ImageLoader(IWICImagingFactory2* _wicFactory, ID2D1DeviceContext* _d2dContext);
	ID2D1Bitmap* LoadBitmap(Platform::String^ Filename);

private:
	Microsoft::WRL::ComPtr<ID2D1DeviceContext>			m_d2dContext;
	Microsoft::WRL::ComPtr<IWICImagingFactory2>			m_wicFactory;
	Microsoft::WRL::ComPtr<IWICBitmapDecoder>           m_wicDecoder;
    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode>       m_wicFrameDecode;
    Microsoft::WRL::ComPtr<IWICFormatConverter>         m_wicFormatConverter;
	ID2D1Bitmap* m_Bitmap;
};

