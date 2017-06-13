//
// WeekViewControl.xaml.h
// Declaration of the WeekViewControl class
//

#pragma once

#include "WeekViewControl.g.h"
#include "CalInfo.h"
#include "WeekEvent.xaml.h"
#include "Calpage.xaml.h"
namespace CheckoutManager
{
	//[Windows::UI::Xaml::Data::Bindable]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class WeekViewControl sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	public:
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;
		WeekViewControl();
//		event switchView^ switchtomonth;
		property CalInfo^ cal
		{
			CalInfo^ get();
			void set(CalInfo^ setting);
		}
		property bool zoomed
		{
			bool get()
			{
				return zoomed;
			}
			void set(bool z)
			{
				if (z)
				{
					_zoomed = true;
					mainGrid->Width = (ActualWidth*7) + 99;
					scroll->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Visible;
					scroll->IsHorizontalRailEnabled = true;
				}
				else
				{
					mainGrid->Width = -NAN;
					scroll->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
					scroll->IsHorizontalRailEnabled = false;
				}
			}
		}
		property Platform::String^ dateRange
		{
			Platform::String^ get()
			{
				if(!firstTimeintialized)
					return nullptr;
				else
				{
					auto formatter = Windows::Globalization::DateTimeFormatting::DateTimeFormatter::ShortDate;
					auto startDatetime = startofweek->GetDateTime();
					auto endDatetime = startDatetime;
					endDatetime.UniversalTime += 6.048e12;
					Platform::String^ range = formatter->Format(startDatetime) + L" - " + formatter->Format(endDatetime);
					return range;
				}
			}
		}
	private:
		bool _zoomed;
		void OnPropertyChanged(Platform::String^ propertyName);
		CalInfo^ calvar;
		void mainGrid_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Windows::Globalization::Calendar^ startofweek;
		std::array<Windows::UI::Xaml::Controls::Canvas^, 7> dayCanvas;
		
		std::vector<WeekEvent^> events;
		std::array<int, 7> maxZindex;
		Platform::Collections::Vector<WeekEvent^>^ manuallyhidden;
	internal:
		void incrementweek(bool x);
		void selectionChanged(Windows::Foundation::Collections::IVector<Platform::Object^>^ added, Windows::Foundation::Collections::IVector<Platform::Object^>^ removed);
	private:
		void switchtoweek(bool,CalInfo^);
		void updatecalendar(CalInfo^ calz);
		bool firstTimeintialized = false;
		void HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Onhide(CheckoutManager::WeekEvent ^listing);
		void Onunhide(CheckoutManager::WeekEvent ^listing);
		void back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSizeChanged(Platform::Object ^sender, Windows::UI::Xaml::SizeChangedEventArgs ^e);
		void UserControl_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
