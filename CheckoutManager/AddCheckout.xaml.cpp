//
// AddCheckout.xaml.cpp
// Implementation of the AddCheckout class
//

#include "pch.h"
#include "AddCheckout.xaml.h"
#include "Calpage.xaml.h"
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

CheckoutManager::AddCheckout::AddCheckout(dataspace::dataManager::CheckoutInfo * editing, std::function<void()>editedfunc)
{
	updatefunc = editedfunc;
	InitializeComponent();
	dataInstance = database;
	Windows::Foundation::DateTime now;
	now.UniversalTime = (editing->checkoutTime * 10000000) + 116444736000000000ULL; //Convert time to the C++/CX datetime type. Converts the current unix time to nanoseconds and then adds 200 years
	Windows::Foundation::DateTime tommorow;
	tommorow.UniversalTime = now.UniversalTime + 8.64e11;
	startDate->Date = now;
	tm chkTime, returntm;
	localtime_s(&chkTime, &editing->checkoutTime);
	localtime_s(&returntm, &editing->duedate);
	chkTime.tm_hour = 0, chkTime.tm_min = 0, chkTime.tm_sec = 0;
	Windows::Foundation::TimeSpan startftime;
	time_t startsinceday = mktime(&chkTime);
	startftime.Duration = ((editing->checkoutTime-startsinceday) * 10000000) + 116444736000000000ULL;
	startTime->Time = startftime;
	returntm.tm_hour = 0, returntm.tm_min = 0, returntm.tm_sec = 0;
	time_t endsinceday = mktime(&returntm);
	Windows::Foundation::TimeSpan returnftime;
	returnftime.Duration = ((editing->duedate - endsinceday) * 10000000) + 116444736000000000ULL;
	returnTime->Time = returnftime;
	if (startsinceday == endsinceday)
	{
		sameDay->IsOn = true;
	}
	else 
	{
		sameDay->IsOn = false;
		tommorow.UniversalTime = (editing->duedate * 10000000) + 116444736000000000ULL;
	}
	returnDate->Date = tommorow;
	auto x = ref new Platform::Collections::Vector<Platform::String^>();
	Platform::String^ selteam;
	for (auto&&z : database->getTeams())
	{
		auto vvadi = Platform::StringReference((const wchar_t*)z.first.c_str());
		if (z.first == editing->Team)
			selteam = vvadi;
		x->Append(vvadi);
		
	}
	teamSelector->ItemsSource = x;
	teamSelector->SelectedItem = selteam;
	auto u16devices = dataInstance->getdeviceTypes();
	Platform::String^ seldevice;
	auto cxxstring = ref new Platform::Collections::Vector<Platform::String^>(); //convert u16string to Platform:;String
	for (auto& z : u16devices)
	{
		auto divjeig = Platform::StringReference((const wchar_t*)z.first.c_str());
		if (z.first == editing->deviceType)
			seldevice = divjeig;
		cxxstring->Append(divjeig);
	}
	devicepicker->ItemsSource = cxxstring;
	devicepicker->SelectedItem = seldevice;

	isloaded = true;
	edit = editing;
	editmode = true;
}

AddCheckout::AddCheckout()
{
	InitializeComponent();
	Windows::Foundation::DateTime now;
	now.UniversalTime = (time(0) * 10000000) + 116444736000000000ULL; //Convert time to the C++/CX datetime type. Converts the current unix time to nanoseconds and then adds 200 years
	Windows::Foundation::DateTime tommorow;
	tommorow.UniversalTime = now.UniversalTime + 8.64e11;
	startDate->Date = now;
	returnDate->Date = tommorow;
	auto x = ref new Platform::Collections::Vector<Platform::String^>();
	for (auto&&z : database->getTeams())
	{
		x->Append(ref new Platform::String((const wchar_t*)z.first.c_str()));
	}
	teamSelector->ItemsSource = x;
	dataInstance = database;
	auto u16devices = dataInstance->getdeviceTypes();
	auto cxxstring = ref new Platform::Collections::Vector<Platform::String^>(); //convert u16string to Platform:;String
	for (auto& z : u16devices)
	{
		cxxstring->Append(Platform::StringReference((const wchar_t*)z.first.c_str()));
	}
	devicepicker->ItemsSource = cxxstring;
	isloaded = true;
	
}

CheckoutManager::AddCheckout::AddCheckout(Windows::Foundation::DateTime defaultTime)
{
	startDate->Date = defaultTime;
	auto x = ref new Platform::Collections::Vector<Platform::String^>();
	for (auto&&z : database->getTeams())
	{
		x->Append(ref new Platform::String((const wchar_t*)z.first.c_str()));
	}
	teamSelector->ItemsSource = x;
	InitializeComponent();
}




void CheckoutManager::AddCheckout::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e)
{
	auto nav = Windows::UI::Core::SystemNavigationManager::GetForCurrentView();
	nav->AppViewBackButtonVisibility = Windows::UI::Core::AppViewBackButtonVisibility::Visible;
	cookie = (nav->BackRequested += ref new Windows::Foundation::EventHandler<Windows::UI::Core::BackRequestedEventArgs ^>(this, &CheckoutManager::AddCheckout::OnBackRequested));
}

void CheckoutManager::AddCheckout::OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	auto nav = Windows::UI::Core::SystemNavigationManager::GetForCurrentView();
	nav->AppViewBackButtonVisibility = Windows::UI::Core::AppViewBackButtonVisibility::Collapsed;
	nav->BackRequested -= cookie;
}

void CheckoutManager::AddCheckout::AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	auto chktm = ref new Windows::Globalization::Calendar();
	chktm->SetDateTime(startDate->Date->Value);
	chktm->Period = 1, chktm->Minute = 0, chktm->Second = 0, chktm->Nanosecond = 0, chktm->Hour = 12;
	Windows::Globalization::Calendar^ returntm = ref new Windows::Globalization::Calendar();
	if (sameDay->IsOn)
	{
		returntm = chktm->Clone();
	}
	else
	{
		returntm->SetDateTime(returnDate->Date->Value);
		returntm->Period = 1, returntm->Minute = 0, returntm->Second = 0, returntm->Nanosecond = 0, returntm->Hour = 12;
	}
	//chktm->AddNanoseconds(startTime->Time.Duration * 100);
	//returntm->AddNanoseconds(returnTime->Time.Duration * 100);
	auto chksec = chktm->GetDateTime();
	chksec.UniversalTime += startTime->Time.Duration;
	auto duesec = returntm->GetDateTime();
	duesec.UniversalTime += returnTime->Time.Duration;
	//save button


	auto timetconv = [](Windows::Foundation::DateTime *in) { return (const time_t)((in->UniversalTime - 116444736000000000ULL) / 10000000); };
	time_t z = (timetconv(&startDate->Date->Value)); //convert back to sanity units
	Platform::String^ v = devicepicker->SelectedValue->ToString();
	std::u16string devicestr = (const char16_t*)v->Data();
	const time_t timetchk = timetconv(&chksec);
	const time_t timetdue = timetconv(&duesec);

		if (timetdue <= timetchk)
		{
			auto message = ref new Windows::UI::Popups::MessageDialog("Return time must be after Checkout time.");
			message->ShowAsync();
		}
		else
		{
			auto pconflict = dataInstance->getCheckouts(timetchk, timetdue, devicestr);


			auto schedule = [this, timetchk, timetdue, devicestr]() {
				dataManager::CheckoutInfo addinfo;
				addinfo.Team = (const char16_t*)teamSelector->SelectedValue->ToString()->Data();
				addinfo.deviceType = devicestr;
				addinfo.checkoutTime = timetchk;
				addinfo.duedate = timetdue;
				addinfo.actualchktime = NULL;
				addinfo.actualreturntime = NULL;
				if (editmode)
				{
					if (dataspace::dataManager::CheckoutInfo::isSameNotfulfilled(addinfo, *edit))
					{
						addinfo.checkoutID = edit->checkoutID;
						addinfo.actualchktime = edit->actualchktime;
						addinfo.actualreturntime = edit->actualreturntime;
						addinfo.fullfilled = edit->fullfilled;
						dataInstance->editCheckout(addinfo);
						updatefunc();
					}
					((Windows::UI::Xaml::Controls::ContentDialog^)Parent)->Hide();
				}
				else
					dataInstance->scheduleCheckout(addinfo);
				return true;
			};

			auto numdevices = dataInstance->getnumofdevices(devicestr);
			if (editmode)
			{
				pconflict.erase(std::remove_if(pconflict.begin(), pconflict.end(), [this](dataspace::dataManager::CheckoutInfo asdhe) {
					return (edit->checkoutID == asdhe.checkoutID);
				}), pconflict.end());
			}
			if (pconflict.empty() || pconflict.size() < numdevices)
			{
				schedule();
				if(!editmode)
					((Windows::UI::Xaml::Controls::Frame^)Parent)->GoBack();
			}
			else
			{
				auto formatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter(L"longdate shorttime");

				String^ msgstr = L"Your checkout on " + formatter->Format(chksec) + L" - " + formatter->Format(duesec) + L" of " + v + L" conflicts with the checkout(s) from: \n ";
				for (dataManager::CheckoutInfo i : pconflict)
				{
					wchar_t tmformat[80];
					try
					{
						auto x = wcsftime(tmformat, 80, L"%c - ", localtime(&i.checkoutTime));
					}
					catch (std::exception e)
					{
						__debugbreak();
					}
					msgstr = String::Concat(msgstr, StringReference(tmformat));
					//tmformat = nullptr;
					wcsftime(tmformat, 80, L"%c \n", localtime(&i.duedate));

					msgstr = String::Concat(msgstr, StringReference(tmformat));
					msgstr += L"By: ";
					msgstr += Platform::StringReference((const wchar_t*)i.Team.data());

				}
				msgstr += (L"There are a total of " + numdevices.ToString() + L" " + v);
				auto msg = ref new Windows::UI::Popups::MessageDialog(msgstr);



				msg->Commands->Append(ref new Windows::UI::Popups::UICommand("OverSchedule", ref new Windows::UI::Popups::UICommandInvokedHandler([pconflict, schedule, this](auto a)
				{
					auto allowedusers = ref new Platform::Collections::Vector<Platform::String^>();
					for (dataManager::CheckoutInfo i : pconflict)
					{
						allowedusers->Append(ref new Platform::String((const wchar_t*)i.Team.c_str()));
					}
					auto signin = ref new AuthenticationDialog(allowedusers, this->dataInstance);

					signin->Authenticated += ref new CheckoutManager::AuthSucesshandler([schedule, this](Platform::String^ user, Windows::UI::Xaml::Controls::ContentDialogButtonClickDeferral^ def)
					{

						schedule();
						def->Complete();
						((Windows::UI::Xaml::Controls::Frame^)Parent)->GoBack();
					});
					signin->ShowAsync();
				})));
				msg->Commands->Append(ref new Windows::UI::Popups::UICommand("Cancel"));


				msg->DefaultCommandIndex = 1;
				msg->CancelCommandIndex = 1;
				msg->ShowAsync();
			}
		}
		

}



void CheckoutManager::AddCheckout::sameDay_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (isloaded)
	{
		if (sameDay->IsOn)
			returnDate->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		else
			returnDate->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void CheckoutManager::AddCheckout::teamSelector_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (sender->Equals(teamSelector))
		selintial.first = true;
	else
		selintial.second = true;
	if ((selintial.first == true) && (selintial.second == true))
		savebutton->IsEnabled = true;
}


void CheckoutManager::AddCheckout::OnBackRequested(Platform::Object ^sender, Windows::UI::Core::BackRequestedEventArgs ^args)
{
	Windows::Foundation::Collections::IKeyValuePair<bool, time_t>^ backinfo;
	((Windows::UI::Xaml::Controls::Frame^)Parent)->Navigate(Calpage::typeid, backinfo);
	((Windows::UI::Xaml::Controls::Frame^)Parent)->GoBack();
}
