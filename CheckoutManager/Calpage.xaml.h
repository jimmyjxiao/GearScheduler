//
// Calpage.xaml.h
// Declaration of the Calpage class
//

#pragma once

#include "Calpage.g.h"
#include "WeekViewControl.xaml.h"
#include "MonthViewControl.h"
#include "AddCheckout.xaml.h"
using namespace Windows::UI::Xaml::Media::Imaging;
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Calpage sealed
	{
	public:


		Calpage();
		property CalInfo^ CurrentCalendar
		{
			CalInfo^ get()
			{
				return currentcalendar;
			}
		}
	private:

		CalInfo^ currentcalendar;
		void refreshListbox(bool viewby);
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void onswitch(bool z, CalInfo^ x);
		void list_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void lengthPivot_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void calendarback_click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void calendarforwad_click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnupdateCalendar(CheckoutManager::CalInfo ^);
		void AppBarButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AppBarButton_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AppBarToggleButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
