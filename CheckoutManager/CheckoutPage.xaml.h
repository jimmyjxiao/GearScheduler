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
	public value struct overDueinfo
	{
		Platform::String^ itemType;
		int itemID;
		Platform::String^ user;
		Platform::String^ checkedOutTime;
		Platform::String^ dueTime; 
	};
	public value struct refCheckout
	{
		Platform::String^ deviceType;
		Platform::String^ team;
		Platform::String^ CheckoutTime;
		Platform::String^ returnTime;
		bool returned;
		bool checkedout;
		int checkoutID;
	};
	struct checkoutEqual : public std::binary_function<const refCheckout, const refCheckout, bool>
	{
		bool operator()(const refCheckout & left, const refCheckout & right) const
		{
			return (left.checkoutID == right.checkoutID);
		};
	};
	struct overDueequal : public std::binary_function<const overDueinfo, const overDueinfo, bool>
	{
		bool operator()(const overDueinfo & left, const overDueinfo & right) const
		{
			return (left.itemType->Equals(right.itemType) && (left.itemID == right.itemID) && left.user->Equals(right.user) && left.checkedOutTime->Equals(right.checkedOutTime) && left.dueTime->Equals(right.dueTime));
		};
	};
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class CheckoutPage sealed
	{
	public:
		CheckoutPage();
	private:
		Platform::Collections::Vector<overDueinfo, overDueequal>^ getOverdue();
		Platform::Collections::Vector<refCheckout, checkoutEqual>^ getCurrentcheckouts();
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PasswordBox_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void teamSelector_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		std::map<std::u16string, Windows::UI::Color> Teams;
		std::unordered_map<std::u16string, Windows::UI::Color>  deviceTypes;
		void Returnbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void returnBox_TextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args);
	};
}
