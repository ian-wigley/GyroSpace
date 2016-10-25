#pragma once

#include "AnimatedObjects.h"

ref class Explosion sealed : AnimatedObjects
{
public:
	int UpdateExplosion(void);

internal:
	Explosion(ID2D1Bitmap* _explode, int _frames, ID2D1Bitmap* _explosionFrame, int _width);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;
	void SetExplosionPosition(D2D_POINT_2F _xyPos);

private:
	ID2D1Bitmap* m_explode;
	D2D_RECT_U m_explodeRect;
};

