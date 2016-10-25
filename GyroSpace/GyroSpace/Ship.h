#pragma once

#include "AnimatedObjects.h"

ref class Ship sealed : AnimatedObjects
{
public:
    virtual void Update(void) override;
	void Update(float counter, int angle);
	void ResetShip(void);
	void FlyIntoPlanet(boolean _flyToPlanet);
    boolean ArrivedAtPlanet(void);

internal:
	Ship(ID2D1Bitmap* _ship, D2D1_SIZE_F _renderTargetSize, int _frames, ID2D1Bitmap* _shipFrame, int _width);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;
	D2D_POINT_2F GetCoords(void);

private:
	int m_x0;
	int m_x1;
	int m_y0;
	int m_y1;

	int m_screenCentreX;
	int m_screenCentreY;

	int m_circleHeight;
	int m_circleWidth;
	int m_shipSpeed;
	int m_distance;

	boolean m_flyToPlanet;
	boolean m_arrived;

	float m_right;
	float m_bottom;
	float m_time;
	float m_incrementer;

	#define PI 3.142

	D2D_RECT_U m_shipRect;
	D2D_RECT_F m_shipCollisionRect;
	ID2D1Bitmap* m_shipBitmap;
};

