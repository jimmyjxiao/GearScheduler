//
// AuthenticationDialog.xaml.h
// Declaration of the AuthenticationDialog class
//

#pragma once

#include "AuthenticationDialog.g.h"
#include "dataManager.h"
using namespace dataspace;
using namespace Windows::Security::Cryptography::Core;
namespace CheckoutManager
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public delegate void AuthSucesshandler(Platform::String^ user, Windows::UI::Xaml::Controls::ContentDialogButtonClickDeferral^ def);
	public ref class AuthenticationDialog sealed
	{
	public:

		
		event AuthSucesshandler^ Authenticated;
	internal:
		AuthenticationDialog(Windows::Foundation::Collections::IVector<Platform::String^>^ allowedUsers, dataspace::dataManager * data);
		
	private:
		dataManager* Database;
		Platform::String^ currentloggedin;
		HashAlgorithmProvider^ Hasher;
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);


		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void user_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
	};
}
