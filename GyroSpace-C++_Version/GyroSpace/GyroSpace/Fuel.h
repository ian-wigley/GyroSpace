#pragma once

#include "MovingObjects.h"

ref class Fuel sealed : MovingObjects
{
public:
	virtual void Update(void) override;
	virtual void Reset(void) override;

internal:
	Fuel(ID2D1Bitmap* _fuel,  D2D1_SIZE_F _renderTargetSize);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;

private:
	int m_currentFrame;
	int m_totalFrames;
	int m_animWidth;
	int m_width;
	int m_height;
	int m_fuelHeight;
	int m_fuelWidth;
	double m_speed;
	double m_angle;
	float m_right;
	float m_bottom;
	ID2D1Bitmap* m_fuel;
};

