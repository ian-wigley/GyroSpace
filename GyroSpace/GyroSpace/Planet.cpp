//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to hold the Planet information

#include "pch.h"
#include "Planet.h"

// Constructor
Planet::Planet(ID2D1Bitmap* _planet, D2D1_SIZE_F _renderTargetSize)
{
	this->m_bitmap = _planet;

	this->m_xyPos = D2D1::Point2F(_renderTargetSize.width/2, _renderTargetSize.height/2);

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();

	ResetPlanet();
}

// Update the planet position & the rectangle
void Planet::Update(void)
{
	//Increase the Size of the rectangle
	this->m_rect.left -= 0.01f;
	this->m_rect.right += 0.01f;
	this->m_rect.top -= 0.01f;
	this->m_rect.bottom += 0.01f;
}

// Reset the planet size
void Planet::ResetPlanet(void)
{
	this->m_rect.left = this->m_xyPos.x - this->m_size.width/32;
	this->m_rect.right = this->m_xyPos.x + this->m_size.width/32;
	this->m_rect.top = this->m_xyPos.y - this->m_size.height/32;
	this->m_rect.bottom = this->m_xyPos.y + this->m_size.height/32;
}

// Accessors
D2D_RECT_F Planet::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Planet::GetBitmap(void)
{
	return this->m_bitmap;
}