#pragma once

#include <vector>
#include "DirectXBase.h"
#include "MovingObjects.h"
#include "Planet.h"
#include "Ship.h"
#include "Star.h"

using namespace std;

// This class renders our Objects
ref class Renderer : public DirectXBase
{
internal:
	Renderer();
	D2D1_SIZE_F GetRenderTargetSize();
	void AddCollection(vector<Star^> _starCollection, vector<MovingObjects^> _movingObjects, vector<Planet^> _planetCollection, Ship^ _ships);

public:
	virtual void CreateDeviceIndependentResources() override;
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	void ResetShipAngularPosition(void);

	void NextPlanet(boolean _planetDisplay, int _planetNumber);
	void UpdateAngularPos(int _angle);
	void ClearScreen(void);
	boolean DisplayPlanet(void);

private:
	ID2D1Bitmap* m_bitMap;
	D2D_RECT_F m_rect;
	D2D1_POINT_2F m_centre;
	D2D_POINT_2F m_shipCoords;
	D2D1_SIZE_F m_renderTargetSize;

	vector<MovingObjects^> m_movingObjects;
	vector<Star^> m_starCollection;
	vector<Planet^>m_planetCollection;

	Ship^ m_ships;

	boolean m_planetDisplay;
	int m_planetNumber;
	int m_angle;
};
