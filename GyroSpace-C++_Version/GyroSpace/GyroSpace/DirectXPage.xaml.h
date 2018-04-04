//
// BlankPage.xaml.h
// Declaration of the BlankPage.xaml class.
//

#pragma once

#include "DirectXPage.g.h"
#include "Renderer.h"
#include "BasicTimer.h"

using namespace MenuComponents::Storage;

namespace GyroSpace
{
	/// <summary>
	/// A DirectX page that can be used on its own.  Note that it may not be used within a Frame.
	/// </summary>
    [Windows::Foundation::Metadata::WebHostHidden]
	public ref class DirectXPage sealed
	{
	public:
		DirectXPage();
		void OnQuitPressed(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnPausePressed(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SaveInternalState(Windows::Foundation::Collections::IPropertySet^ state);
		void LoadInternalState(Windows::Foundation::Collections::IPropertySet^ state);

	private:
		void keys(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnLogicalDpiChanged(Platform::Object^ sender);
		void OnOrientationChanged(Platform::Object^ sender);
		void OnDisplayContentsInvalidated(Platform::Object^ sender);
		void OnRendering(Object^ sender, Object^ args);
		void OnUpdating(Object^ sender, Object^ args);
		void Accelerometer(void);

		Windows::Foundation::EventRegistrationToken m_eventToken;
		Windows::Foundation::Point m_lastPoint;

		Renderer^ m_renderer;
		BasicTimer^ m_timer;
		TemporaryStorageAccess^ m_TempStore;
		
		int m_difficulty;
		float m_currentTime;

		bool m_updateFlag;
		bool m_renderNeeded;
		bool m_lastPointValid;
		bool m_gameOn;
		bool m_scoresUpdate;
		bool m_displayGameOver;
		bool m_controlKeyboard;
		bool m_controlTouch;
		bool m_controlAccelerometer;
		bool m_paused;

		void ReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e);
		void Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OptionsButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void StartButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void HighScoreButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InfoButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CloseHighScorePanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CloseInfoPanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void CloseOptionsPanel(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RadioButton_Checked_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void KeyBoardRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TouchScreenRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AccelerometerRadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DifficultySlider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void CloseName(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void StartButton_Hover(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	};
}
