//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to hold the Meteor information

#include "pch.h"
#include "Meteor.h"

// Constructor
Meteor::Meteor(ID2D1Bitmap* _meteor, D2D1_SIZE_F _renderTargetSize, int _frames, ID2D1Bitmap* _meteorFrame, int _width)
{
	this->m_bitmap  = _meteor;
	this->m_meteorBitmap = _meteorFrame;

	this->m_screenHeight = (int)_renderTargetSize.height;
	this->m_screenWidth = (int)_renderTargetSize.width;

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();

	this->m_totalFrames = _frames;
	this->m_currentFrame = 0;

	this->m_nextLevel = false;

	this->m_meteorRect.top = 0;
	this->m_meteorRect.bottom = (UINT)this->m_size.height;
	this->m_meteorRect.left = 0;
	this->m_meteorRect.right = 32;

	this->m_destPoint.x = 0;
	this->m_destPoint.y = 0;

	this->m_animWidth = _width;

	Reset();
}

// Update the meteor position & the rectangle
void Meteor::Update(void)
{
	this->m_currentFrame = (this->m_currentFrame + 1) % m_totalFrames;
	this->m_meteorRect.left = this->m_currentFrame * this->m_animWidth;
	this->m_meteorRect.right = this->m_meteorRect.left + this->m_animWidth;

	// Copy the relevent part of the spritesheet onto the render bitmap
	this->m_meteorBitmap->CopyFromBitmap(&m_destPoint, this->m_bitmap, &m_meteorRect);

	this->m_speed += 0.1;
	this->m_angle += 0.01;

	this->m_xyPos.x = (float)(cos(this->m_angle) * this->m_speed) + this->m_xyPos.x;
	this->m_xyPos.y = (float)(sin(this->m_angle) * this->m_speed) + this->m_xyPos.y;

	//Update the Position the rectangle
	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + m_size.width/m_totalFrames + this->m_right;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + m_size.height + this->m_bottom;

	this->m_right += 0.3f;
	this->m_bottom += 0.3f;

	// If the meteor goes off screen, reset the positions
	if (this->m_xyPos.x < 0 || this->m_xyPos.x > this->m_screenWidth || this->m_xyPos.y < 0 || this->m_xyPos.y > this->m_screenHeight)
	{
		if (!this->m_nextLevel)
		{
			Reset();
		}
	}
}

// Method to reset the Meteors to the centre of the screen
void Meteor::Reset(void)
{
	this->m_angle = rand() % 360;
	this->m_speed = 0;
	this->m_xyPos.x = (float)this->m_screenWidth/2;
	this->m_xyPos.y = (float)this->m_screenHeight/2;
	this->m_right = 0;
	this->m_bottom = 0;
}

// Accessors
D2D_RECT_F Meteor::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Meteor::GetBitmap(void)
{
	return this->m_meteorBitmap;
}