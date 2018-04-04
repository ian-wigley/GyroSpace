#pragma once

#include "MovingObjects.h"

ref class Planet sealed  : MovingObjects
{
public:
        virtual void Update(void) override;
	void ResetPlanet(void);

internal:
	Planet(ID2D1Bitmap* _planet, D2D1_SIZE_F _renderTargetSize);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;
};

