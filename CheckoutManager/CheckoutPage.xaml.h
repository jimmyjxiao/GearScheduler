//
// CheckoutPage.xaml.h
// Declaration of the CheckoutPage class
//

#pragma once

#include "CheckoutPage.g.h"
#include "AuthenticationDialog.xaml.h"
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class CheckoutPage sealed
	{
	public:
		CheckoutPage();
	private:
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PasswordBox_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void teamSelector_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		std::map<std::u16string, Windows::UI::Color> Teams;
		std::unordered_map<std::u16string, Windows::UI::Color>  deviceTypes;
	};
}
