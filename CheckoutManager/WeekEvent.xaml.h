//
// WeekEvent.xaml.h
// Declaration of the WeekEvent class
//

#pragma once

#include "WeekEvent.g.h"
#include "WeekViewControl.xaml.h"
#include "dataManager.h"
namespace CheckoutManager
{
	public delegate void manualHide(WeekEvent^ listing);
	public delegate void manualunhide(WeekEvent^ listing);
	public delegate void deleteEvent(WeekEvent^ listing);
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class WeekEvent sealed
	{
	internal:
		Windows::UI::Color groupColor;
		Platform::String^ timetext;
	public:
		void hideunhide(bool hideun);
		event manualHide^ hide;
		event manualunhide^ unhide;
		event deleteEvent^ deleted;
		property Platform::String^ teamStr
		{
			Platform::String^ get()
			{
				return team;
			}
		}
		property bool manuallyhidden;
		property Platform::String^ deviceStr
		{
			Platform::String^ get()
			{
				//auto zstr = u"Device:" + info->deviceType;
				//return ref new Platform::String((const wchar_t*)zstr.c_str());
				return device;
			}
		}
		property Platform::String^ timeStr
		{
			Platform::String^ get()
			{
				return timetext;
			}
		}
		property Windows::UI::Xaml::Media::SolidColorBrush^ background
		{
			Windows::UI::Xaml::Media::SolidColorBrush^ get()
			{
				return ref new Windows::UI::Xaml::Media::SolidColorBrush(groupColor);
			}
		}


	internal:
		WeekEvent(Windows::UI::Color color, Platform::String ^ devices, Platform::String^ teams, bool fullfilled, Platform::String^ timestr, int* maxzIndex, dataspace::dataManager::CheckoutInfo checkout, std::function<void()> editfunc);
		dataspace::dataManager::CheckoutInfo Checkout;
		std::shared_ptr<std::vector<WeekEvent^>> intersectswith;
	private:
		std::function<void()> updatefunc;
		Platform::String^ team;
		Platform::String^ device;
		int* maxzindex;
		void unhideinternal();
		void hideinternal();
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void UserControl_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DeviceID_TextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args);
		void Password_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MenuFlyoutItem_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void edit_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
