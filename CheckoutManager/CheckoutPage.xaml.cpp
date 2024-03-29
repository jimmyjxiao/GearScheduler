﻿//
// CheckoutPage.xaml.cpp
// Implementation of the CheckoutPage class
//

#include "pch.h"
#include "CheckoutPage.xaml.h"
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

CheckoutPage::CheckoutPage()
{
	InitializeComponent();
	Teams = database->getTeamsmap();
	deviceTypes = database->getdeviceTypes();
	Platform::Collections::Vector<Platform::String^>^ x = ref new Platform::Collections::Vector<Platform::String^>();
	for (auto&&z : Teams)
	{
		x->Append(ref new Platform::String((const wchar_t*)z.first.c_str()));
	}
	currentListview->ItemsSource = getCurrentcheckouts();
	overdueview->ItemsSource = getOverdue();
	teamSelector->ItemsSource = x;
}


Platform::Collections::Vector<overDueinfo, overDueequal>^ CheckoutManager::CheckoutPage::getOverdue()
{
	Platform::Collections::Vector<overDueinfo, overDueequal>^ returning = ref new Platform::Collections::Vector<overDueinfo, overDueequal>();
	const auto overdue = database->getOverdueCheckouts();
	for (auto &aeig : overdue)
	{
		overDueinfo e;
		e.itemType = Platform::StringReference((const wchar_t*)aeig.first.deviceType.data());
		e.user = Platform::StringReference((const wchar_t*)aeig.first.Team.data());
		e.itemID = aeig.second;
		e.checkedOutTime = Platform::StringReference(converters::shortDatetime(aeig.first.actualchktime).data());
		e.dueTime = Platform::StringReference(converters::shortDatetime(aeig.first.duedate).data());
		returning->Append(e);
	}
	return returning;
}

Platform::Collections::Vector<refCheckout, checkoutEqual>^ CheckoutManager::CheckoutPage::getCurrentcheckouts()
{
	Platform::Collections::Vector<refCheckout, checkoutEqual>^ returning = ref new Platform::Collections::Vector<refCheckout, checkoutEqual>();
	const auto currentcheckouts = database->getCheckouts(time(nullptr), time(nullptr) + 60);
	for (auto &aeg : currentcheckouts)
	{
		refCheckout z;
		z.checkedout = aeg.fullfilled; //xaml converters go the other way and I'm too lazy to do it any other way
		z.returned = ((aeg.fullfilled) && (aeg.actualreturntime != NULL));
		z.checkoutID = aeg.checkoutID;
		z.deviceType = Platform::StringReference((const wchar_t*)aeg.deviceType.data());
		z.team = Platform::StringReference((const wchar_t*)aeg.Team.data());
		z.CheckoutTime = Platform::StringReference(converters::shortDatetime(aeg.checkoutTime).data());
		z.returnTime = Platform::StringReference(converters::shortDatetime(aeg.duedate).data());
		returning->Append(z);
	}
	return returning;
}

void CheckoutManager::CheckoutPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto team = (const char16_t*)((Platform::String^)teamSelector->SelectedItem)->Data();
	const auto idstr = (const char16_t*)IDbox->Text->Data();
	
	try {
	
		warning->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		auto fulfilled = database->fullfillCheckout(team, (const char16_t*)password->Password->Data(), idstr);
		devTypeblock->Text = ref new Platform::String((const wchar_t*)fulfilled.deviceType.data());
		auto devit = deviceTypes.find(fulfilled.deviceType);
		devTypeblock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(devit->second);

		userblock->Text = ref new Platform::String((const wchar_t*)fulfilled.Team.data());
		auto teamit = Teams.find(fulfilled.Team);
		userblock->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(teamit->second);
		
		IDblock->Text = ref new Platform::String((const wchar_t*)idstr);

		

		dueblock->Text = ref new Platform::String(_wasctime(localtime(&fulfilled.duedate)));
		statusBlock->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	catch(char z)
	{
		if (z == 'P')
		{
			warning->Text = "Incorrect Password";
			
		}
		else if (z == 'N')
		{
			warning->Text = "Invalid Item ID";
		}
		else if (z == 'U')
		{
			warning->Text = "Does not match any scheduled checkout";
		}
		warning->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	catch (std::tuple<char , std::u16string ,std::vector<dataspace::dataManager::CheckoutInfo>> Conflicts)
	{
		if (std::get<2>(Conflicts).size() >= std::get <0>(Conflicts)) //More checkouts than devices
		{
			String^ msgstr = L"You do not have a scheduled checkout at this time for this item, and there are not enough for you to check this one out without interferring with other scheduled checkouts. Here are the scheduled checkouts for this time: \n";
			for (dataspace::dataManager::CheckoutInfo i : std::get<2>(Conflicts))
			{
				wchar_t tmformat[80];
				try
				{
					auto x = wcsftime(tmformat, 80, L"%c - ", localtime(&i.checkoutTime));
				}
				catch (std::exception e)
				{
					//__debugbreak();
				}
				msgstr = String::Concat(msgstr, ref new String(tmformat));
				//tmformat = nullptr;
				wcsftime(tmformat, 80, L"%c \n", localtime(&i.duedate));
				msgstr = String::Concat(msgstr, ref new String(tmformat));

			}
			//msgstr += (L"There are a total of " + numdevices.ToString() + L" " + v);
			auto msg = ref new Windows::UI::Popups::MessageDialog(msgstr);
			
			msg->Commands->Append(ref new Windows::UI::Popups::UICommand("Override", ref new Windows::UI::Popups::UICommandInvokedHandler([Conflicts, team, idstr](auto a) {
				
				auto allowedvec = ref new Platform::Collections::Vector<Platform::String^>();
				for (dataspace::dataManager::CheckoutInfo i : std::get<2>(Conflicts))
				{
				allowedvec->Append(ref new Platform::String((const wchar_t*)i.Team.data()));
				}
				auto signin = ref new AuthenticationDialog(allowedvec, database);

				signin->Authenticated += ref new CheckoutManager::AuthSucesshandler([team, idstr](Platform::String^ user, Windows::UI::Xaml::Controls::ContentDialogButtonClickDeferral^ def)
				{
				database->forceCheckout(idstr, team);
				});

				signin->ShowAsync();
				
			})));
			
			msg->Commands->Append(ref new Windows::UI::Popups::UICommand("Cancel"));
			msg->DefaultCommandIndex = 1;
			msg->CancelCommandIndex = 1;
		}
		else
		{
				
				
			warning->Text = "It looks like you don't have a scheduled checkout, but there are enough of these available for you to schedule a checkout right now and take it.";
				
			warning->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}
	}
}


void CheckoutManager::CheckoutPage::PasswordBox_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (password->Password->IsEmpty())
		checkoutbutton->IsEnabled = false;
	else
		checkoutbutton->IsEnabled = true;
}


void CheckoutManager::CheckoutPage::teamSelector_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	password->IsEnabled = true;
	warning->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}




void CheckoutManager::CheckoutPage::Returnbutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int id = std::stoi(returnBox->Text->Data());
	database->returndevice(id);
	Platform::String^ refz = Platform::StringReference((const wchar_t*)database->getdevicetypefromPubID(id).data());
	refz += L" (ID:"; 
	refz += id;
	refz += L") returned sucessfully and is now available";
	returnBlock->Text = refz;
	returnBox->Text = "";
}


void CheckoutManager::CheckoutPage::returnBox_TextChanging(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args)
{
	converters::textchangedNumberfilter(sender, args);
}
