#pragma once

#include "MovingObjects.h"

ref class Star sealed : MovingObjects
{
public:
	virtual void Update(void) override;
	virtual void Reset(void) override;
	void RotateStars(int _angle);

internal:
	Star(ID2D1Bitmap* _star, D2D1_SIZE_F _renderTargetSize, double _speed);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;

private:
	double m_rotation;
	double m_starSpeed;
};

