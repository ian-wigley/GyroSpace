#pragma once

#include "MovingObjects.h"

ref class AnimatedObjects : MovingObjects
{
internal:
	AnimatedObjects(void){};

	int m_currentFrame;
	int m_totalFrames;
	int m_animWidth;

	ID2D1Bitmap* m_bitmap;
	D2D1_POINT_2U m_destPoint;
};

