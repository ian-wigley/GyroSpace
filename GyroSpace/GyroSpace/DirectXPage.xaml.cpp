//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
//
///////////////////////////////////////////////////

// Main entry class

#include "pch.h"
#include "amp.h"
#include "DirectXPage.xaml.h"
#include "Game.h"
#include "ImageLoader.h"

using namespace GyroSpace;
using namespace MenuComponents::Storage;

using namespace Platform;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Popups;
using namespace Concurrency;

using Windows::System::VirtualKey;

Game^ m_game;
ImageLoader^ m_imageLoader;

DirectXPage::DirectXPage() :
	m_renderNeeded(true),
	m_lastPointValid(false)
{
	InitializeComponent();
	FuelLevel->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	GameOverImage->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	ScoreTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	LivesTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	HighScores->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	Information->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	Options->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	InputName->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);

	m_gameOn = false;
	m_paused = false;
	m_scoresUpdate = false;
	m_displayGameOver = false;
	m_controlKeyboard =true;
	m_controlTouch = false;
	m_controlAccelerometer = false;
	m_updateFlag = true;
	
	m_difficulty = 1;
	m_currentTime = 0;

	m_renderer = ref new Renderer();

	m_renderer->Initialize(Window::Current->CoreWindow,	SwapChainPanel,	DisplayProperties::LogicalDpi );

	// Retrieve the WIC Factory from the DirectX Base Class
	IWICImagingFactory2* _wicFactory;
	_wicFactory = m_renderer->GetWICFactory();

	// Retrieve the D2D device context from the DirectX Base Class
	ID2D1DeviceContext* _d2dContext;
	_d2dContext = m_renderer->GetD2DContext();

	Window::Current->CoreWindow->SizeChanged +=
		ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &DirectXPage::OnWindowSizeChanged);

	DisplayProperties::LogicalDpiChanged +=
		ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnLogicalDpiChanged);

	DisplayProperties::OrientationChanged +=
        ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnOrientationChanged);

	DisplayProperties::DisplayContentsInvalidated +=
		ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnDisplayContentsInvalidated);

	m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &DirectXPage::OnRendering));

	m_timer = ref new BasicTimer();

	// Create a new Image Loader Class & pass in the WIC Factory
	m_imageLoader = ref new ImageLoader(_wicFactory, _d2dContext);

	m_game = ref new Game(m_imageLoader, m_renderer, m_timer);

	m_game->XAMLElements(ScoreTextBlock, LivesTextBlock, FuelLevelRectangle);

	m_TempStore = ref new TemporaryStorageAccess(Name1TextBlock, Name2TextBlock, Name3TextBlock, Name4TextBlock, Name5TextBlock, InputName);

	Accelerometer();
}

// Keyboard Event Handler
void GyroSpace::DirectXPage::keys(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (!m_game->NextLevel())
	{
		if (e->Key == VirtualKey::A)
		{
			//move right
			m_renderer->UpdateAngularPos(2);
			m_game->UpdateShip(0.0327f, 2);
		}

		if (e->Key == VirtualKey::S)
		{
			m_renderer->UpdateAngularPos(-2);
			m_game->UpdateShip(-0.0327f, -2);
		}
	}
}

// Touch Screen Event Handler
void DirectXPage::OnPointerMoved(Object^ sender, PointerRoutedEventArgs^ args)
{
	if (!m_game->NextLevel())
	{
		auto currentPoint = args->GetCurrentPoint(nullptr);
		if (currentPoint->IsInContact)
		{
			if (m_lastPointValid)
			{
				if(currentPoint->Position.X > m_lastPoint.X || currentPoint->Position.Y > m_lastPoint.Y)
				{
					//move left
					m_renderer->UpdateAngularPos(-2);
					m_game->UpdateShip(-0.0327f, -2);
				}
				else
				{
					//move right
					m_renderer->UpdateAngularPos(2);
					m_game->UpdateShip(0.0327f, 2);
				}
			}
			m_lastPoint = currentPoint->Position;
			m_lastPointValid = true;
		}
		else
		{
			m_lastPointValid = false;
		}
	}
}

void DirectXPage::OnPointerReleased(Object^ sender, PointerRoutedEventArgs^ args)
{
	m_lastPointValid = false;
}

void DirectXPage::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	m_renderer->UpdateForWindowSizeChange();
	m_renderNeeded = true;
}

void DirectXPage::OnLogicalDpiChanged(Object^ sender)
{
	m_renderer->SetDpi(DisplayProperties::LogicalDpi);
	m_renderNeeded = true;
}

void DirectXPage::OnOrientationChanged(Object^ sender)
{
	m_renderer->UpdateForWindowSizeChange();
	m_renderNeeded = true;
}

void DirectXPage::OnDisplayContentsInvalidated(Object^ sender)
{
	m_renderer->ValidateDevice();
	m_renderNeeded = true;
}

// Method to Render the game objects
void DirectXPage::OnRendering(Object^ sender, Object^ args)
{
	if (m_gameOn && !m_paused)
	{
		m_timer->Update();

		if (m_updateFlag)
		{
			// Get the current time
			m_currentTime = m_timer->Total;
			m_updateFlag = false;
		}

		// If the time has elapsed run the update
		if (m_timer->Total > m_currentTime + m_timer->Delta/2)
		{
			m_updateFlag = true;

			if (m_game->GameOn())
			{
				m_game->Update(m_timer->Total, m_timer->Delta);
				m_renderer->Render();
				m_renderer->Present();
			}
			else
			{
				// Game Over ! Clear the game objects & display the menu items
				this->m_renderer->ClearScreen();
				this->m_gameOn = false;
				this->m_displayGameOver = true;
				this->m_scoresUpdate = true;

				InitializeComponent();

				// Turn off the XAML game content off & Game Over Logo on.
				FuelLevel->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
				ScoreTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
				LivesTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
				GameOverImage->Visibility = (Windows::UI::Xaml::Visibility::Visible);

				m_timer->Reset();
			}
		}
	}

	// Timer to Display the Game Over Logo
	if (m_displayGameOver)
	{
		this->m_timer->Update();
		this->m_displayGameOver = m_TempStore->Delay(m_timer->Total, m_timer->Delta);
	}

	else if (!m_displayGameOver && m_scoresUpdate)
	{
		GameOverImage->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
		FuelLevel->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
		StartButton->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		HighScoreButton->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		InfoButton->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		OptionsButton->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		TitleImage->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		StartGameTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		HighScoresTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		InformationTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);
		OptionsTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);

		this->m_TempStore->UpdateScores(m_game->GetScores());
		this->m_scoresUpdate = false;
		m_game->ResetGame();
		this->m_timer->Reset();
	}
}

// App Bar Quit Event handler
void DirectXPage::OnQuitPressed(Object^ sender, RoutedEventArgs^ args)
{
	if (this->m_gameOn)
	{
		// Game Over ! Clear the game objects & display the menu items
		this->m_renderer->ClearScreen();
		this->m_gameOn = false;
		this->m_displayGameOver = true;
		this->m_scoresUpdate = true;

		InitializeComponent();

		// Turn off the XAML game content off & Game Over Logo on.
		FuelLevel->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
		ScoreTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
		LivesTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
		GameOverImage->Visibility = (Windows::UI::Xaml::Visibility::Visible);

		m_timer->Reset();
	}
}

// App Bar Pause Event handler
void GyroSpace::DirectXPage::OnPausePressed(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (this->m_gameOn)
	{
		// Create the message dialog and set its content and title
		auto messageDialog = ref new Windows::UI::Popups::MessageDialog("GyroSpace is paused, click Close to continue", "Game Paused");

		this->m_paused = true;
		this->m_timer->Paused(true);
		m_game->PauseGame(true);

		// Show the message dialog
		create_task(messageDialog->ShowAsync()).then([this](IUICommand^ command)
		{
			this->m_paused = false;
			this->m_timer->Paused(false);
			m_game->PauseGame(false);
		});
	}
}

void DirectXPage::SaveInternalState(IPropertySet^ state)
{
	m_game->SaveInternalState(state);
}

void DirectXPage::LoadInternalState(IPropertySet^ state)
{
	m_game->LoadInternalState(state);
}

// Method to turn off the Various XAML elements & start the game
void GyroSpace::DirectXPage::StartButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	StartButton->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	HighScoreButton->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	InfoButton->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	OptionsButton->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	TitleImage->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	StartGameTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	HighScoresTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	InformationTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	OptionsTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);

	Information->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	Options->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	HighScores->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
	InputName->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);

	FuelLevel->Visibility = (Windows::UI::Xaml::Visibility::Visible);
	ScoreTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);
	LivesTextBlock->Visibility = (Windows::UI::Xaml::Visibility::Visible);

	m_gameOn = true;
	m_game->InitialiseMovingObjects(m_difficulty);
	m_game->StartGame(true);
	m_timer->Reset();
}

void GyroSpace::DirectXPage::OptionsButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Options->Visibility = (Windows::UI::Xaml::Visibility::Visible);
	KeyBoardRadioButton->IsChecked = true;
}

void GyroSpace::DirectXPage::HighScoreButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	HighScores->Visibility = (Windows::UI::Xaml::Visibility::Visible);
}

void GyroSpace::DirectXPage::InfoButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Information->Visibility = (Windows::UI::Xaml::Visibility::Visible);
}

void GyroSpace::DirectXPage::CloseHighScorePanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	HighScores->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
}

void GyroSpace::DirectXPage::CloseInfoPanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Information->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
}

void GyroSpace::DirectXPage::CloseOptionsPanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Options->Visibility = (Windows::UI::Xaml::Visibility::Collapsed);
}

void GyroSpace::DirectXPage::KeyBoardRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_controlKeyboard = true;
	m_controlTouch = false;
	m_controlAccelerometer = false;
}

void GyroSpace::DirectXPage::TouchScreenRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_controlKeyboard = false;
	m_controlTouch = true;
	m_controlAccelerometer = false;
}

void GyroSpace::DirectXPage::AccelerometerRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_controlKeyboard = false;
	m_controlTouch = false;
	m_controlAccelerometer = true;
}

void GyroSpace::DirectXPage::DifficultySlider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	double m_oldValue = e->OldValue;
	double m_newValue = e->NewValue;
	if (m_oldValue > 0)
	{
		m_difficulty = (int)m_newValue;
	}
}

// Accelerometer Method that needs implementation and testing, I have no way of testing the functionality at this time, hence commenting out the code,
void GyroSpace::DirectXPage::Accelerometer(void)
{
	Windows::Devices::Sensors::Accelerometer^ accelerometer = Accelerometer::GetDefault();
    if (accelerometer != nullptr)
    {
		/*
        // Select a report interval that is both suitable for the purposes of the app and supported by the sensor.
        // This value will be used later to activate the sensor.
        uint32 minReportInterval = accelerometer->MinimumReportInterval;
        uint32 desiredReportInterval = minReportInterval > 16 ? minReportInterval : 16;

		// Re-enable sensor input (no need to restore the desired reportInterval... it is restored for us upon app resume)
        readingToken = accelerometer->ReadingChanged::add(ref new TypedEventHandler<Windows::Devices::Sensors::Accelerometer^, AccelerometerReadingChangedEventArgs^>(this, &GyroSpace::DirectXPage::ReadingChanged));
		*/
    }
    else
    {
		// Grey out the Accelerometer button
		AccelerometerRadioButton->IsEnabled = false;
    }
}

void GyroSpace::DirectXPage::ReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e)
{
	/*
    // We need to dispatch to the UI thread to display the output
    Dispatcher->RunAsync(
        CoreDispatcherPriority::Normal,
        ref new DispatchedHandler(
            [this, e]()
            {
                AccelerometerReading^ reading = e->Reading;

                ScenarioOutput_X->Text = reading->AccelerationX.ToString();
                ScenarioOutput_Y->Text = reading->AccelerationY.ToString();
                ScenarioOutput_Z->Text = reading->AccelerationZ.ToString();
            },
            CallbackContext::Any
            )
        );
		*/
}
