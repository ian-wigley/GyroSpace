//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// Main Game Class

#include "pch.h"
#include "Game.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::UI::Xaml::Media;

Game::Game(ImageLoader^ _imageLoader, Renderer^ _renderer, BasicTimer^ _timer)
{
	this->m_imageLoader = _imageLoader;
	this->m_renderer = _renderer;
	this->m_timer = _timer;

	this->m_planetNames.push_back("You have reached the Ice Planet !");
	this->m_planetNames.push_back("You have reached the Alien Planet !");
	this->m_planetNames.push_back("You have reached Earth !");

	this->m_planetNumber = 0;
	this->m_lives = 3;
	this->m_angle = 0;
	this->m_scores = 0;
	this->m_nextLevel = false;
	this->m_toastSwitch = false;
	this->m_exploded = false;
	this->m_planetDisplay = false;
	this->m_paused = false;
	this->m_gameOn = true;
	this->m_difficultyLev = 1;

	Initialise();
}

// This methods loads our bitmaps, creates the stars etc.
void Game::Initialise()
{
	this->m_star =  m_imageLoader->LoadBitmap(L"star.png");
	this->m_planet1 = m_imageLoader->LoadBitmap(L"ice.png");
	this->m_planet2 = m_imageLoader->LoadBitmap(L"alien.png");
	this->m_planet3 = m_imageLoader->LoadBitmap(L"earth.png");
	this->m_ship = m_imageLoader->LoadBitmap(L"ship.png");
	this->m_fuelGauge = m_imageLoader->LoadBitmap(L"fuelgauge.png");
	this->m_meteor0 = m_imageLoader->LoadBitmap(L"meteor0.png");
	this->m_meteor1 = m_imageLoader->LoadBitmap(L"meteor1.png");
	this->m_explode = m_imageLoader->LoadBitmap(L"explosion.png");
	this->m_fuels = m_imageLoader->LoadBitmap(L"fuel0.png");

	this->m_meteorFrame0 = m_imageLoader->LoadBitmap(L"bitmap.png");
	this->m_meteorFrame1 =  m_imageLoader->LoadBitmap(L"bitmap1.png");
	this->m_shipFrame = m_imageLoader->LoadBitmap(L"bitmap2.png");
	this->m_explosionFrame =  m_imageLoader->LoadBitmap(L"bitmap3.png");

	// Get the size of the render target
	this->m_renderTargetSize = m_renderer->GetRenderTargetSize();

	// Random Seed Generator
	unsigned seed = 0;
	srand(seed);

	// Create the Planets
	this->m_planet = ref new Planet(m_planet1, m_renderTargetSize);
	this->m_planetCollection.push_back(m_planet);
	this->m_planet = ref new Planet(m_planet2, m_renderTargetSize);
	this->m_planetCollection.push_back(m_planet);
	this->m_planet = ref new Planet(m_planet3, m_renderTargetSize);
	this->m_planetCollection.push_back(m_planet);

	// Create 80 stars
	for (int i = 0; i < 80; i++)
	{
		this->m_stars = ref new Star(m_star, m_renderTargetSize, 0.2);
		this->m_starCollection.push_back(m_stars);
	}

	// Create 40 faster moving stars
	for (int i = 0; i < 40; i++)
	{
		this->m_stars = ref new Star(m_star, m_renderTargetSize, 0.4);
		this->m_starCollection.push_back(m_stars);
	}
}

// This methods creates the Moving Objects.
void Game::InitialiseMovingObjects(int _difficulty)
{
	for (int i = 0; i < _difficulty * 2; i++)
	{
		this->m_meteors = ref new Meteor(m_meteor0, m_renderTargetSize, 16, m_meteorFrame0, 32);
		this->m_movingObjects.push_back(m_meteors);

		this->m_meteors = ref new Meteor(m_meteor1, m_renderTargetSize, 64, m_meteorFrame1, 44);
		this->m_movingObjects.push_back(m_meteors);
	}

	this->m_fuel = ref new Fuel(m_fuels, m_renderTargetSize);
	this->m_movingObjects.push_back(m_fuel);

	this->m_explosion = ref new Explosion(m_explode, 17, m_explosionFrame, 64);
	this->m_movingObjects.push_back(m_explosion);

	this->m_ships = ref new Ship(m_ship, m_renderTargetSize, 6, m_shipFrame, 22);

	// Pass the collection of objects to render to the Renderer class
	this->m_renderer->AddCollection(m_starCollection, m_movingObjects, m_planetCollection, m_ships);
}

// Method to update all of the in game objects & test for ship intersections
void Game::Update(float _timeTotal, float _timeDelta)
{
	if (m_lives > 0 && !this->m_paused)
	{
		this->m_ships->Update();

		double _time = floor(_timeTotal);

		this->m_scoresTextBlock->Text = "Score : " + this->m_scores.ToString();
		this->m_livesTextBlock->Text = "Lives : " + this->m_lives.ToString();

		Windows::UI::Color _newColour;

		this->m_fuelLevelRect->Width -= 0.5;

		if (this->m_fuelLevelRect->Width >= 160)
		{
			_newColour = UpdateBrushColour(0,255,0);
		}

		if (this->m_fuelLevelRect->Width >= 80 && this->m_fuelLevelRect->Width <= 160)
		{
			_newColour = UpdateBrushColour(255,255,0);
		}

		if (this->m_fuelLevelRect->Width > 1 && this->m_fuelLevelRect->Width <= 80)
		{
			_newColour = UpdateBrushColour(255,0,0);
		}

		else if (this->m_fuelLevelRect->Width == 1)
		{
			this->m_lives -= 1;
			this->m_fuelLevelRect->Width = 240;
			_newColour = UpdateBrushColour(0,255,0);
		}

		// Fill the Fuel level rectangle with the new colour
		this->m_fuelLevelRect->Fill = ref new SolidColorBrush(_newColour);

		// Timing to display Planets
		if (_time == 30.00)
		{
			this->m_planetDisplay = true;
			this->m_renderer->NextPlanet(this->m_planetDisplay, this->m_planetNumber);
		}

		if (_time == 150.00 && !m_toastSwitch)
		{
			this->DisplayToast(this->m_planetNames.at(this->m_planetNumber));
			this->m_ships->FlyIntoPlanet(true);
			this->m_nextLevel = true;
			this->m_toastSwitch = true;
		}
		else if (_time > 150.00)
		{
			this->m_toastSwitch = false;
		}

		// Has the Ship arrived at the planet yet ? If so reset the various values
		if (this->m_nextLevel && this->m_ships->ArrivedAtPlanet())
		{
			this->m_planetNumber = (this->m_planetNumber + 1) % 3;
			this->m_renderer->NextPlanet(this->m_planetDisplay, this->m_planetNumber);
			this->m_renderer->ResetShipAngularPosition();
			this->m_timer->Reset();
			this->m_nextLevel = false;
			this->m_ships->FlyIntoPlanet(false);
			this->m_planetDisplay = false;
			this->m_ships->ResetShip();
			this->DisplayToast("Next Level");

			for (UINT i = 0; i < this->m_planetCollection.size(); i++)
			{
				this->m_planetCollection.at(i)->ResetPlanet();		
			}
		}

		if (this->m_planetDisplay)
		{
			this->m_planetCollection.at(m_planetNumber)->Update();
		}

		// Update the Stars
		for (unsigned int i = 0; i < m_starCollection.size(); i++)
		{
			this->m_starCollection.at(i)->Update();
			this->m_starCollection.at(i)->RotateStars(m_angle);
		}

		// Update the Moving Objects
		for (unsigned int i = 0; i < m_movingObjects.size() -1; i++)
		{
			this->m_movingObjects.at(i)->Update();

			if (i < this->m_movingObjects.size() - 2 && !this->m_nextLevel)
			{
				this->m_shipRect = this->m_ships->GetRect();
				this->m_objects = this->m_movingObjects.at(i)->GetRect();

				// If the ship has collided with another object, remove a life
				if (InterSectionCheck(this->m_shipRect, this->m_objects))
				{
					// Position the explosion at the point of contact
					this->m_explosion->SetExplosionPosition(this->m_ships->GetCoords());
					this->m_lives -= 1;
					this->m_movingObjects.at(i)->Reset();

					// Explosion flag
					this->m_exploded = true;
				}

				this->m_objects = this->m_fuel->GetRect();

				// If the ship has collided with the fuel ?
				if (InterSectionCheck(this->m_shipRect, this->m_objects))
				{
					// Don't over fill the fuel level !
					if (this->m_fuelLevelRect->Width < 215)
					{
						this->m_fuelLevelRect->Width += 25;
					}
					this->m_fuel->Reset();
					this->m_scores += 50;
				}

				// Update the explosion running through the animation frames
				if (this->m_exploded)
				{
					if (this->m_updateFlag)
					{
						// Get the current time
						this->m_currentTime = this->m_timer->Total;
						this->m_updateFlag = false;
					}

					// If the time has elapsed run the update
					if (this->m_timer->Total > this->m_currentTime + this->m_timer->Delta)
					{
						this->m_updateFlag = true;

						// Increment through the frames of animation
						if(this->m_explosion->UpdateExplosion() != 16)
						{
							// Reset the Ships position
							this->m_ships->ResetShip();
							this->m_renderer->ResetShipAngularPosition();
						}
						else
						{
							this->m_exploded = false;
						}
					}
				}
			}
		}
	}
	else if(!this->m_paused)
	{
		this->m_gameOn = false;
	}
}

// Method to check if the Rectangles intersect
bool Game::InterSectionCheck(D2D_RECT_F _ship, D2D_RECT_F _objects)
{
	if (_ship.left < _objects.right && _ship.right > _objects.left && _ship.top < _objects.bottom && _ship.bottom > _objects.top)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Method to Update the Fuel Level rectangle colour
Windows::UI::Color Game::UpdateBrushColour(byte _r, byte _g, byte _b)
{
	Windows::UI::Color _colour;
	_colour.A = 255;
	_colour.R = _r;
	_colour.G = _g;
	_colour.B = _b;
	return _colour;
}

// Method to display toast Notifications
void Game::DisplayToast(Platform::String^ _string)
{
	ToastTemplateType toastTemplate = ToastTemplateType::ToastImageAndText01;
	XmlDocument^ toastXml = ToastNotificationManager::GetTemplateContent(toastTemplate);
	XmlNodeList^ toastTextElements = toastXml->GetElementsByTagName("text");
	toastTextElements->Item(0)->InnerText = _string;

	XmlNodeList^ toastImageAttributes = toastXml->GetElementsByTagName("image");
	IXmlNode^ toastNode = toastXml->SelectSingleNode("/toast");
	static_cast<XmlElement^>(toastNode)->SetAttribute("duration", "short");
	static_cast<XmlElement^>(toastNode)->SetAttribute("launch", "{\"type\":\"toast\",\"param1\":\"12345\",\"param2\":\"67890\"}");
	ToastNotification^ toast = ref new ToastNotification(toastXml);
	ToastNotificationManager::CreateToastNotifier()->Show(toast);
}

// Update the ship position
void Game::UpdateShip(float _counter, int _angle)
{
	this->m_ships->Update(_counter, _angle);
	this->m_angle = _angle;
}

boolean Game::GameOn(void)
{
	return this->m_gameOn;
}

// Save the games state
void Game::SaveInternalState(IPropertySet^ state)
{
	if (state->HasKey("m_lives"))
	{
		state->Remove("m_lives");
	}
	if (state->HasKey("m_scores"))
	{
		state->Remove("m_scores");
	}
	if (state->HasKey("m_paused"))
	{
		state->Remove("m_paused");
	}
	state->Insert("m_lives", PropertyValue::CreateInt32(this->m_lives));
	state->Insert("m_scores", PropertyValue::CreateInt32(this->m_scores));
	state->Insert("m_paused", PropertyValue::CreateBoolean(true));
}

// Load the games state
void Game::LoadInternalState(IPropertySet^ state)
{
	if (state->HasKey("m_lives") && state->HasKey("m_scores") && state->HasKey("m_paused"))
	{
		this->m_lives = safe_cast<IPropertyValue^>(state->Lookup("m_lives"))->GetInt32();
		this->m_scores = safe_cast<IPropertyValue^>(state->Lookup("m_scores"))->GetInt32();
		this->m_paused= safe_cast<IPropertyValue^>(state->Lookup("m_paused"))->GetBoolean();
	}
}

// Reset the Game ready for the next go
void Game::ResetGame(void)
{
	this->m_lives = 3;
	this->m_scores = 0;
	this->m_nextLevel = false;
	this->m_toastSwitch = false;
	this->m_exploded = false;
	this->m_ships->ResetShip();
	this->m_renderer->ResetShipAngularPosition();

	// Clear the Moving Objects collection
	this->m_movingObjects.clear();

	// Reset all the objects in the collection
	for (UINT i = 0; i < m_planetCollection.size(); i++)
	{
		this->m_planetCollection.at(i)->Reset();
	}
	this->m_fuelLevelRect->Width = 240;
}

void Game::PauseGame(boolean _pause)
{
	this->m_paused = _pause;
}

void Game::XAMLElements(Windows::UI::Xaml::Controls::TextBlock^ _scores, Windows::UI::Xaml::Controls::TextBlock^ _lives, Windows::UI::Xaml::Shapes::Rectangle^ _fuelLevelRect)
{
	this->m_scoresTextBlock = _scores;
	this->m_livesTextBlock = _lives;
	this->m_fuelLevelRect = _fuelLevelRect;
}

int Game::GetScores(void)
{
	return this->m_scores;
}

void Game::StartGame(bool _gameOn)
{
	this->m_gameOn = _gameOn;
}

boolean Game::NextLevel(void)
{
	return this->m_nextLevel;
}