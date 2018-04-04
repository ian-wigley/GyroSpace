//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to hold the Star information

#include "pch.h"
#include "Star.h"

Star::Star(ID2D1Bitmap* _star, D2D1_SIZE_F _renderTargetSize, double _speed)
{
	this->m_bitmap = _star;

	this->m_screenWidth = (int)_renderTargetSize.width;
	this->m_screenHeight = (int)_renderTargetSize.height;

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();
	this->m_starSpeed = _speed;
	this->m_rotation = 0;
	Reset();
}


// This method updates each stars position
void Star::Update(void)
{
	this->m_speed  += this->m_starSpeed;

	this->m_angle += this->m_rotation;

	this->m_xyPos.x = (float)(cos(this->m_angle) * this->m_speed) + this->m_xyPos.x;
	this->m_xyPos.y = (float)(sin(this->m_angle) * this->m_speed) + this->m_xyPos.y;

	//Update the Position the rectangle
	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + m_size.width;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + m_size.height;

	// If the Star goes off screen, reset the positions
	if (this->m_xyPos.x < 0 || this->m_xyPos.x > this->m_screenWidth || this->m_xyPos.y < 0 || this->m_xyPos.y > this->m_screenHeight)
	{
		Reset();
	}
}

// Reset the stars position as they go off screen
void Star::Reset(void)
{
	this->m_angle = rand() % 360;
	this->m_speed = 1;
	this->m_xyPos.x = (float)this->m_screenWidth/2;
	this->m_xyPos.y = (float)this->m_screenHeight/2;
}

// Accessors
D2D_RECT_F Star::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Star::GetBitmap(void)
{
	return this->m_bitmap;
}

// Set the Rotation amount
void Star::RotateStars(int _angle)
{
	_angle == 2 ? this->m_rotation = -0.02 : this->m_rotation = 0.02;
}

