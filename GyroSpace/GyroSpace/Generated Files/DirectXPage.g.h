﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class SwapChainBackgroundPanel;
                ref class TextBlock;
                ref class Canvas;
                ref class Button;
                ref class Image;
                ref class Grid;
                ref class Slider;
                ref class RadioButton;
            }
        }
    }
}
namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Shapes {
                ref class Rectangle;
            }
        }
    }
}

namespace GyroSpace
{
    partial ref class DirectXPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::SwapChainBackgroundPanel^ SwapChainPanel;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ ScoreTextBlock;
        private: ::Windows::UI::Xaml::Controls::Canvas^ TitleImage;
        private: ::Windows::UI::Xaml::Controls::Button^ OptionsButton;
        private: ::Windows::UI::Xaml::Controls::Button^ StartButton;
        private: ::Windows::UI::Xaml::Controls::Button^ HighScoreButton;
        private: ::Windows::UI::Xaml::Controls::Button^ InfoButton;
        private: ::Windows::UI::Xaml::Controls::Image^ GameOverImage;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ LivesTextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ StartGameTextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ HighScoresTextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ InformationTextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ OptionsTextBlock;
        private: ::Windows::UI::Xaml::Controls::Grid^ HighScores;
        private: ::Windows::UI::Xaml::Controls::Grid^ Information;
        private: ::Windows::UI::Xaml::Controls::Grid^ Options;
        private: ::Windows::UI::Xaml::Controls::Grid^ FuelLevel;
        private: ::Windows::UI::Xaml::Controls::Grid^ InputName;
        private: ::Windows::UI::Xaml::Shapes::Rectangle^ FuelLevelRectangle;
        private: ::Windows::UI::Xaml::Controls::Button^ CloseOptionsButton;
        private: ::Windows::UI::Xaml::Controls::Slider^ DifficultySlider;
        private: ::Windows::UI::Xaml::Controls::RadioButton^ KeyBoardRadioButton;
        private: ::Windows::UI::Xaml::Controls::RadioButton^ TouchScreenRadioButton;
        private: ::Windows::UI::Xaml::Controls::RadioButton^ AccelerometerRadioButton;
        private: ::Windows::UI::Xaml::Controls::Button^ CloseInfoPanelButton;
        private: ::Windows::UI::Xaml::Controls::Button^ CloseHighScorePanelButton;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Name1TextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Name2TextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Name3TextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Name4TextBlock;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ Name5TextBlock;
    };
}
