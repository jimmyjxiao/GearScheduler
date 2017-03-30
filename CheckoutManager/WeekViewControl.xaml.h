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
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class WeekViewControl sealed
	{
	public:
		WeekViewControl();
//		event switchView^ switchtomonth;
		property CalInfo^ cal
		{
			CalInfo^ get();
			void set(CalInfo^ setting);
		}
	private:
		CalInfo^ calvar;
		void mainGrid_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Windows::Globalization::Calendar^ startofweek;
		std::array<Windows::UI::Xaml::Controls::Canvas^, 7> dayCanvas;
		
		std::vector<WeekEvent^> events;
		std::array<int, 7> maxZindex;
		Platform::Collections::Vector<WeekEvent^>^ manuallyhidden;
	internal:
		void selectionChanged(Windows::Foundation::Collections::IVector<Platform::Object^>^ added, Windows::Foundation::Collections::IVector<Platform::Object^>^ removed);
	private:
		void updatecalendar(CalInfo^ calz);
		bool firstTimeintialized = false;
		void HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Onhide(CheckoutManager::WeekEvent ^listing);
		void Onunhide(CheckoutManager::WeekEvent ^listing);
		void back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
