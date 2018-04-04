//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
//
///////////////////////////////////////////////////

// Render Class

#include "pch.h"
#include "Renderer.h"

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;

Renderer::Renderer()
{
	m_planetDisplay = false;
}

// Method to Create the Device Independent Resources
void Renderer::CreateDeviceIndependentResources()
{
	DirectXBase::CreateDeviceIndependentResources();
}

// Method to Create the Device Resources
void Renderer::CreateDeviceResources()
{
	DirectXBase::CreateDeviceResources();
}

// Method to Create the Window Size Dependent Resources
void Renderer::CreateWindowSizeDependentResources()
{
	DirectXBase::CreateWindowSizeDependentResources();

	// Get the size of the render target
	m_renderTargetSize = this->GetRenderTargetSize();
	m_centre = D2D1::Point2F(m_renderTargetSize.width/2 ,m_renderTargetSize.height/2);
	m_angle = 0;
	m_planetNumber = 0;
}

// Method to Render the onscreen objects
void Renderer::Render()
{
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	// Draw the stars in the moving objects collection.
	for (unsigned int i = 0; i < m_starCollection.size(); i++)
	{
		m_d2dContext->DrawBitmap(m_starCollection.at(i)->GetBitmap(), m_starCollection.at(i)->GetRect());
	}

	// Display a planet
	if (m_planetDisplay)
	{
		m_d2dContext->DrawBitmap(m_planetCollection.at(m_planetNumber)->GetBitmap(),m_planetCollection.at(m_planetNumber)->GetRect());
	}

	// Draw the remaining objects in the moving objects collection.
	for (unsigned int i = 0; i < m_movingObjects.size(); i++)
	{
		m_d2dContext->DrawBitmap(m_movingObjects.at(i)->GetBitmap(), m_movingObjects.at(i)->GetRect());
	}

	// Get the Ship co-oridinates, position & rotate ship
	m_shipCoords = m_ships->GetCoords();
	m_d2dContext->SetTransform(D2D1::Matrix3x2F::Rotation((float)m_angle, m_shipCoords));
	m_d2dContext->DrawBitmap(m_ships->GetBitmap(), m_ships->GetRect());
	m_d2dContext->SetTransform(D2D1::Matrix3x2F::Rotation(0, m_shipCoords));

	// Ignore D2DERR_RECREATE_TARGET. This error indicates that the device
	// is lost. It will be handled during the next call to Present.
	HRESULT hr = m_d2dContext->EndDraw();
	if (hr != D2DERR_RECREATE_TARGET)
	{
		DX::ThrowIfFailed(hr);
	}
}

// Retrieve the size of the render target.
D2D1_SIZE_F Renderer::GetRenderTargetSize()
{
	return m_d2dContext->GetSize();
}

// Add the collections
void Renderer::AddCollection(vector<Star^> _starCollection, vector<MovingObjects^> _movingObjects, vector<Planet^> _planetCollection, Ship^ _ships)
{
	m_starCollection = _starCollection;
	m_movingObjects = _movingObjects;
	m_planetCollection = _planetCollection;
	m_ships = _ships;
}

// Update the ships Angular value of rotation
void Renderer::UpdateAngularPos(int _angle)
{
	this->m_angle += _angle % 360;
}

// Reset the ships Angular value of rotation
void Renderer::ResetShipAngularPosition(void)
{
	this->m_angle = 0;
}

// Check to see if it's time to display the Planets
boolean Renderer::DisplayPlanet(void)
{
	return m_planetDisplay;
}

// Clear the screen when game is over
void Renderer::ClearScreen(void)
{
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	m_d2dContext->EndDraw();
	m_swapChain->Present(2, 0);
}

// Display the next planet
void Renderer::NextPlanet(boolean _planetDisplay, int _planetNumber)
{
	this->m_planetDisplay = _planetDisplay;
	this->m_planetNumber = _planetNumber;
}