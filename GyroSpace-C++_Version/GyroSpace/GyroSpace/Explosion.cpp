//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Class to display & update the Explosion objects

#include "pch.h"
#include "Explosion.h"

Explosion::Explosion(ID2D1Bitmap* _explode, int _frames, ID2D1Bitmap* _explosionFrame, int _width)
{
	// Orinal Bitmap containing all the frames of animation
	this->m_bitmap = _explode;

	// Single Bitmap to conatin each frame of animation
	this->m_explode = _explosionFrame;

	this->m_xyPos.x = 0;
	this->m_xyPos.y = 0;

	// Get the size of the Bitmap
	this->m_size = m_bitmap->GetSize();

	this->m_totalFrames = _frames;
	this->m_currentFrame = 0;

	this->m_explodeRect.top = 0;
	this->m_explodeRect.bottom = (UINT)this->m_size.height;
	this->m_explodeRect.left = 0;
	this->m_explodeRect.right = _width;

	this->m_destPoint.x = 0;
	this->m_destPoint.y = 0;

	this->m_animWidth = _width;
}

// Update the explosion animation & rectangle position
int Explosion::UpdateExplosion(void)
{
	this->m_currentFrame = (this->m_currentFrame + 1) % this->m_totalFrames;
	this->m_explodeRect.left = this->m_currentFrame * this->m_animWidth;
	this->m_explodeRect.right = this->m_explodeRect.left + this->m_animWidth;

	this->m_explode->CopyFromBitmap(&m_destPoint, this->m_bitmap, &m_explodeRect);

	//Update the Position the rectangle
	this->m_rect.left = this->m_xyPos.x;
	this->m_rect.right = this->m_xyPos.x + this->m_size.width / m_totalFrames;;
	this->m_rect.top = this->m_xyPos.y;
	this->m_rect.bottom = this->m_xyPos.y + this->m_size.height;

	return this->m_currentFrame;
}

// Accessors
D2D_RECT_F Explosion::GetRect(void)
{
	return this->m_rect;
}

ID2D1Bitmap* Explosion::GetBitmap(void)
{
	return this->m_explode;
}

// Update the Position of the explosion
void Explosion::SetExplosionPosition(D2D_POINT_2F _xyPos)
{
	this->m_xyPos = _xyPos;
}