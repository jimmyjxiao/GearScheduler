//
// AuthenticationDialog.xaml.cpp
// Implementation of the AuthenticationDialog class
//

#include "pch.h"
#include "AuthenticationDialog.xaml.h"

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

// The Content Dialog item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238


CheckoutManager::AuthenticationDialog::AuthenticationDialog(Windows::Foundation::Collections::IVector <Platform::String^>^ allowedUsers, dataspace::dataManager* data)
{

	
	//Hasher = HashAlgorithmProvider::OpenAlgorithm(HashAlgorithmNames::Sha512);
	Database = data;
	InitializeComponent();
	user->ItemsSource = allowedUsers;
}




void CheckoutManager::AuthenticationDialog::ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	auto deferral = args->GetDeferral();

	Authenticated(currentloggedin, deferral);


}

void CheckoutManager::AuthenticationDialog::ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
	Hide();
}


void CheckoutManager::AuthenticationDialog::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	try
	{

		passbox->IsEnabled = false;
		loginbutton->IsEnabled = false;
		IsPrimaryButtonEnabled = false;
		currentloggedin = "";
		
			
			if (passbox->Password->IsEmpty())
			{
				passWarning->Text = L"Please enter password";
				IsPrimaryButtonEnabled = false;

				loginbutton->IsEnabled = true;
				logIndicator->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
				passbox->IsEnabled = true;
				currentloggedin = nullptr;
			}
			else
			{
				passWarning->Text = L"";
				//Platform::Array<unsigned char>^ x;
				//Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(Hasher->HashData(Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(passbox->Password, Windows::Security::Cryptography::BinaryStringEncoding::Utf16BE)), &x);
				//std::vector<unsigned char> hashvec(x->begin(), x->end());
				auto z = Database->passwordCheck((const char16_t*)user->SelectedValue->ToString()->Data(), (const char16_t*)passbox->Password->Data());
				if (z)
				{
					currentloggedin = user->SelectedValue->ToString();
					IsPrimaryButtonEnabled = true;
					loginbutton->IsEnabled = false;
					passbox->IsEnabled = false;
					logIndicator->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Green);

				}
				else
				{
					passWarning->Text = L"Wrong Password";
					IsPrimaryButtonEnabled = false;
					loginbutton->IsEnabled = true;
					logIndicator->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
					passbox->IsEnabled = true;
					currentloggedin = nullptr;
				}
			}	
			}
		
		
	catch (Exception^ e)
	{
		////__debugbreak();
	}
}


void CheckoutManager::AuthenticationDialog::user_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (user->SelectedValue != nullptr)
	{
		passWarning->Text = L"";
		IsPrimaryButtonEnabled = false;
		loginbutton->IsEnabled = true;
		logIndicator->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
		passbox->IsEnabled = true;
		currentloggedin = nullptr;

	}
}
