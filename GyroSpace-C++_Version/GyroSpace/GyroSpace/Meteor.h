#pragma once

#include "AnimatedObjects.h"

ref class Meteor sealed : AnimatedObjects
{
public:
    virtual void Update(void) override;
	virtual void Reset(void) override;

internal:
	Meteor(ID2D1Bitmap* _meteor, D2D1_SIZE_F _renderTargetSize, int _frames, ID2D1Bitmap* _meteorFrame, int _width);
	virtual D2D_RECT_F GetRect(void) override;
	virtual ID2D1Bitmap* GetBitmap(void) override;

private:
	float m_right;
	float m_bottom;

	ID2D1Bitmap* m_meteorBitmap;
	D2D_RECT_U m_meteorRect;

	boolean m_nextLevel;
};