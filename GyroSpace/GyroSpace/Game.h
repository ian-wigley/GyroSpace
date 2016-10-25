#pragma once

#include "BasicTimer.h"
#include "Explosion.h"
#include "Fuel.h"
#include "ImageLoader.h"
#include "Meteor.h"
#include "MovingObjects.h"
#include "Planet.h"
#include "Renderer.h"
#include "Ship.h"
#include "Star.h"
#include <vector>

using namespace std;

ref class Game sealed
{
public:
	Game(ImageLoader^ _imageLoader, Renderer^ _renderer, BasicTimer^ _timer);

	boolean GameOn(void);
	boolean NextLevel(void);
	int GetScores(void);
	void StartGame(bool _gameOn);
	void Initialise(void);
	void Update(float _timeTotal, float _timeDelta);
	void UpdateShip(float _counter, int _angle);
	void ResetGame(void);
	void InitialiseMovingObjects(int _difficulty);
	void PauseGame(boolean _pause);

	// Methods to save and load state in response to suspend.
	void SaveInternalState(Windows::Foundation::Collections::IPropertySet^ state);
	void LoadInternalState(Windows::Foundation::Collections::IPropertySet^ state);

internal:
	void XAMLElements(Windows::UI::Xaml::Controls::TextBlock^ _scores, Windows::UI::Xaml::Controls::TextBlock^ _lives, Windows::UI::Xaml::Shapes::Rectangle^ _fuelLevelRect);

private:
	Windows::UI::Color UpdateBrushColour(byte _r, byte _g, byte _b);
	void DisplayToast(Platform::String^ _string);
	bool InterSectionCheck(D2D_RECT_F _ship, D2D_RECT_F _objects);

	ID2D1Bitmap* m_star;
	ID2D1Bitmap* m_explode;
	ID2D1Bitmap* m_fuels;
	ID2D1Bitmap* m_fuelGauge;
	ID2D1Bitmap* m_gameOver;
	ID2D1Bitmap* m_meteor0;
	ID2D1Bitmap* m_meteor1;
	ID2D1Bitmap* m_planet1;
	ID2D1Bitmap* m_planet2;
	ID2D1Bitmap* m_planet3;
	ID2D1Bitmap* m_ship;

	ID2D1Bitmap* m_meteorFrame0;
	ID2D1Bitmap* m_meteorFrame1;
	ID2D1Bitmap* m_explosionFrame;
	ID2D1Bitmap* m_shipFrame;

	D2D1_SIZE_F m_renderTargetSize;

	int m_lives;
	int* _lives;
	int m_scores;
	int m_difficultyLev;
	int m_planetNumber;
	int m_angle;
	float m_currentTime;

	// Class references
	BasicTimer^ m_timer;
	Explosion^ m_explosion;
	Fuel^ m_fuel;
	ImageLoader^ m_imageLoader;
	Meteor^ m_meteors;
	Planet^ m_planet;
	Star^ m_stars;
	Ship^ m_ships;
	Renderer^ m_renderer;

	// Class collections
	vector<Star^> m_starCollection;
	vector<Planet^> m_planetCollection;
	vector<MovingObjects^> m_movingObjects;
	vector<Platform::String^> m_planetNames;

	boolean m_nextLevel;
	boolean m_exploded;
	boolean m_cheat;
	boolean m_touchScreen;
	boolean m_planetDisplay;
	boolean m_paused;
	boolean m_gameOn;
	boolean m_toastSwitch;
	boolean m_updateFlag;

	D2D_RECT_F m_shipRect;
	D2D_RECT_F m_objects;

	Windows::UI::Xaml::Controls::TextBlock^ m_scoresTextBlock;
	Windows::UI::Xaml::Controls::TextBlock^ m_livesTextBlock;
	Windows::UI::Xaml::Shapes::Rectangle^ m_fuelLevelRect;
};

