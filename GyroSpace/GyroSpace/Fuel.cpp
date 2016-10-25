//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to display & update the Fuel objects

#include "pch.h"
#include "Fuel.h"

// Constructor
Fuel::Fuel(ID2D1Bitmap* _fuel,  D2D1_SIZE_F _renderTargetSize)
{
	this->m_bitmap = _fuel;

	this->m_screenHeight = (int)_renderTargetSize.height;
	this->m_screenWidth = (int)_renderTargetSize.width;

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();

	Reset();
}

// Update the position of the fuel
void Fuel::Update(void)
{
	this->m_speed += 0.1;
	this->m_angle += 0.01;

	this->m_xyPos.x = (float)(cos(this->m_angle) * this->m_speed) + this->m_xyPos.x;
	this->m_xyPos.y = (float)(sin(this->m_angle) * this->m_speed) + this->m_xyPos.y;

	//Update the Position the rectangle
	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + m_size.width + this->m_right;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + m_size.height + this->m_bottom;

	// Make the size "Grow" as it moves closer to the edge of the screen
	this->m_right += 0.3f;
	this->m_bottom += 0.3f;

	// If the Fuel goes off screen, reset the positions
	if (this->m_xyPos.x < 0 || this->m_xyPos.x > this->m_screenWidth || this->m_xyPos.y < 0 || this->m_xyPos.y > this->m_screenHeight)
	{
			Reset();
	}
}

// Reset the positions
void Fuel::Reset(void)
{
	this->m_angle = rand() % 360;
	this->m_speed = 0;
	this->m_xyPos.x = (float)this->m_screenWidth/2;
	this->m_xyPos.y = (float)this->m_screenHeight/2;
	this->m_right = 0;
	this->m_bottom = 0;
}

// Accessors
D2D_RECT_F Fuel::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Fuel::GetBitmap(void)
{
	return this->m_bitmap;
}


