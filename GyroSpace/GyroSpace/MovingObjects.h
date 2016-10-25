#pragma once

ref class MovingObjects
{
public:
	virtual void Update(void){};
	virtual void Reset(void){};

internal:
	MovingObjects(void){};
	virtual D2D_RECT_F GetRect(void){return m_rect;};
	virtual ID2D1Bitmap* GetBitmap(void){return m_bitmap;};

	D2D1_SIZE_F m_size;
	D2D_POINT_2F m_xyPos;
	D2D_RECT_F m_rect;
	ID2D1Bitmap* m_bitmap;

	int m_screenHeight;
	int m_screenWidth;
	double m_speed;
	double m_angle;
};