//
// WeekEvent.xaml.cpp
// Implementation of the WeekEvent class
//

#include "pch.h"
#include "WeekEvent.xaml.h"
#include <sstream>
#include "converters.h"
using namespace CheckoutManager;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

void CheckoutManager::WeekEvent::hideunhide(bool hideun)
{
	if (hideun)
	{
		hideinternal();
		hide(this);
	}
	else
	{
		unhideinternal();
		unhide(this);
	}
}


WeekEvent::WeekEvent(Windows::UI::Color color, Platform::String ^ devices, Platform::String^ teams, bool fullfilled, Platform::String^ timestr, int* maxzIndex, dataspace::dataManager::CheckoutInfo checkout)
{
	maxzindex = maxzIndex;
	manuallyhidden = false;
	groupColor = color;
	timetext = timestr;
	device = devices;
	team = teams;
	Checkout = checkout;
	InitializeComponent();

}


void CheckoutManager::WeekEvent::unhideinternal()
{
	Visibility = Windows::UI::Xaml::Visibility::Visible;
	manuallyhidden = false;
}

void CheckoutManager::WeekEvent::hideinternal()
{
	Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	manuallyhidden = true;
}

void CheckoutManager::WeekEvent::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	try
	{
		std::wstringstream pubID;
		pubID.str(DeviceID->Text->Data());
		int ID;
		if (pubID >> ID)
		{
			database->fullfillCheckout((const char16_t*)team->Data(), (const char16_t*)Password->Password->Data(), (const char16_t*)pubID.str().data());
			check->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}
		else
			throw 'D';
	}
	catch (char x)
	{
		if (x == 'P')
			Password->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
		else if (x == 'D')
			DeviceID->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);
		else
			throw x;
	}

}


void CheckoutManager::WeekEvent::UserControl_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	(*maxzindex)++;
	Windows::UI::Xaml::Controls::Canvas::SetZIndex(this, *maxzindex);
	FlyoutBase::ShowAttachedFlyout((FrameworkElement^)sender);
}


void CheckoutManager::WeekEvent::MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (manuallyhidden)
	{
		unhideinternal();
		unhide(this);
	}
	else
	{
		hideinternal();
		hide(this);
	}
}


void CheckoutManager::WeekEvent::DeviceID_TextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args)
{
	DeviceID->Background = ref new SolidColorBrush(Windows::UI::Colors::White);
	converters::textchangedNumberfilter(sender, args);
}





void CheckoutManager::WeekEvent::Password_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	((Windows::UI::Xaml::Controls::PasswordBox^)sender)->Background = ref new SolidColorBrush(Windows::UI::Colors::White);
}


void CheckoutManager::WeekEvent::MenuFlyoutItem_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	deleted(this);
}
