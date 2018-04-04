//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to hold the Ship information

#include "pch.h"
#include "Ship.h"

Ship::Ship(ID2D1Bitmap* _ship, D2D1_SIZE_F _renderTargetSize, int _frames, ID2D1Bitmap* _shipFrame, int _width)
{
	this->m_totalFrames = _frames;
	this->m_bitmap = _ship;
	this->m_shipBitmap = _shipFrame;

	this->m_screenCentreX = (int)_renderTargetSize.width/2;
	this->m_screenCentreY = (int)_renderTargetSize.height/2;

	this->m_x0 = 0;
	this->m_x1 = 0;
	this->m_y0 = 0;
	this->m_y1 = 0;

	this->m_flyToPlanet = false;
	this->m_arrived = false;

	this->m_circleHeight = 135;
	this->m_circleWidth = 135;
	this->m_distance = 1000;
	this->m_time = 0;

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();

	this->m_shipRect.top = 0;
	this->m_shipRect.bottom = (UINT)this->m_size.height;
	this->m_shipRect.left = 0;
	this->m_shipRect.right = _width;

	this->m_destPoint.x = 0;
	this->m_destPoint.y = 0;

	this->m_animWidth = _width;

	ResetShip();
}

// Update the ships position through 360 degrees
void Ship::Update(float counter, int angle)
{
	this->m_incrementer += counter;
	this->m_angle += angle % 360;
	this->m_xyPos.x = (float)(m_circleWidth * 1.5 * cos(m_incrementer * m_shipSpeed * PI/180)) + this->m_screenCentreX;
	this->m_xyPos.y = (float)(m_circleHeight * 1.5 * sin(m_incrementer * m_shipSpeed * PI/180)) + this->m_screenCentreY;
}

// Update the ships animation frames
void Ship::Update(void)
{
	this->m_currentFrame = (this->m_currentFrame + 1) % this->m_totalFrames;
	this->m_shipRect.left = this->m_currentFrame * this->m_animWidth;
	this->m_shipRect.right = this->m_shipRect.left + this->m_animWidth;

	this->m_shipBitmap->CopyFromBitmap(&m_destPoint, this->m_bitmap, &m_shipRect);

	//Update the Position the rectangle
	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + this->m_size.width / m_totalFrames;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + this->m_size.height;

	// Move the ship into the centre of the screen using linear interpolation
	if (this->m_flyToPlanet)
	{
		// Shrink the ship rectangle as we approach the planet
		this->m_right -= 0.2f;
		this->m_bottom -= 0.2f;

		if ((int)this->m_xyPos.x != this->m_screenCentreX && (int)this->m_xyPos.y != this->m_screenCentreY)
		{
			this->m_x0 = (int)this->m_xyPos.x;
			this->m_x1 = this->m_screenCentreX;
			this->m_y0 = (int)this->m_xyPos.y;
			this->m_y1 = this->m_screenCentreY;
			this->m_xyPos.x += (this->m_x1 - this->m_x0) * (this->m_time / this->m_distance);
			this->m_xyPos.y += (this->m_y1 - this->m_y0) * (this->m_time / this->m_distance);
			this->m_time = this->m_time + 1 % this->m_distance;
		}
		else
		{
			this->m_arrived = true;
		}
	}
}

// Method to reset the ships position after losing a life
void Ship::ResetShip(void)
{
	this->m_right = 1;
	this->m_bottom = 1;

	this->m_xyPos.x = (float)this->m_screenCentreX;
	this->m_xyPos.y = (float)this->m_screenCentreY + 200;

	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + this->m_size.width / m_totalFrames;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + this->m_size.height;

	this->m_angle = 0;
	this->m_shipSpeed = 61;
	this->m_incrementer = 90;

	this->m_arrived = false;
	this->m_flyToPlanet = false;
}

// Accessors
D2D_RECT_F Ship::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Ship::GetBitmap(void)
{
	return this->m_shipBitmap;
}

D2D_POINT_2F Ship::GetCoords(void)
{
	return this->m_xyPos;
}

void Ship::FlyIntoPlanet(boolean _flyToPlanet)
{
	this->m_flyToPlanet = _flyToPlanet;
}

boolean Ship::ArrivedAtPlanet(void)
{
	return this->m_arrived;
}