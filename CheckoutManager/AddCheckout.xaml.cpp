//
// AddCheckout.xaml.cpp
// Implementation of the AddCheckout class
//

#include "pch.h"
#include "AddCheckout.xaml.h"

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

AddCheckout::AddCheckout()
{
	InitializeComponent();
	Windows::Foundation::DateTime now;
	now.UniversalTime = (time(0) * 10000000) + 116444736000000000ULL; //Convert time to the C++/CX datetime type. Converts the current unix time to nanoseconds and then adds 200 years
	startDate->Date = now;

	auto x = ref new Platform::Collections::Vector<Platform::String^>();
	for (auto&&z : database->getTeams())
	{
		x->Append(ref new Platform::String((const wchar_t*)z.first.c_str()));
	}
	teamSelector->ItemsSource = x;
	dataInstance = database;


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




void CheckoutManager::AddCheckout::AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	auto chktm = ref new Windows::Globalization::Calendar();
	chktm->SetDateTime(startDate->Date->Value);
	auto zeroday = [](Windows::Globalization::Calendar^ tmst)
	{
		tmst->Period = 1, tmst->Minute = 0, tmst->Second = 0, tmst->Nanosecond = 0, tmst->Hour = 12;
	};
	zeroday(chktm);
	Windows::Globalization::Calendar^ returntm;
	if (sameDay->IsOn)
	{
		returntm = chktm->Clone();
	}
	else
	{
		returntm->SetDateTime(returnDate->Date->Value);
		zeroday(returntm);
	}
	//chktm->AddNanoseconds(startTime->Time.Duration * 100);
	//returntm->AddNanoseconds(returnTime->Time.Duration * 100);
	auto chksec = chktm->GetDateTime();
	chksec.UniversalTime += startTime->Time.Duration;
	auto duesec = chktm->GetDateTime();
	duesec.UniversalTime += returnTime->Time.Duration;
	//save button


	auto timetconv = [](Windows::Foundation::DateTime *in) { return (const time_t)((in->UniversalTime - 116444736000000000ULL) / 10000000); };
	time_t z = (timetconv(&startDate->Date->Value)); //convert back to sanity units
	Platform::String^ v = devicepicker->SelectedValue->ToString();
	std::u16string devicestr = (const char16_t*)v->Data();
	const time_t timetchk = timetconv(&chksec);
	const time_t timetdue = timetconv(&duesec);
	try
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
			dataInstance->scheduleCheckout(addinfo);
			return true;
		};

		auto numdevices = dataInstance->getnumofdevices(devicestr);

		if (pconflict.empty() || pconflict.size() < numdevices)
		{
			schedule();
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
				catch(std::exception e)
				{
					__debugbreak();
				}
				msgstr = String::Concat(msgstr, ref new String(tmformat));
				//tmformat = nullptr;
				wcsftime(tmformat, 80, L"%c \n", localtime(&i.duedate));
				msgstr = String::Concat(msgstr, ref new String(tmformat));

			}
			msgstr += (L"There are a total of " + numdevices.ToString() + L" " + v);
			auto msg = ref new Windows::UI::Popups::MessageDialog(msgstr);



			msg->Commands->Append(ref new Windows::UI::Popups::UICommand("Double Schedule", ref new Windows::UI::Popups::UICommandInvokedHandler([pconflict, schedule, this](auto a)
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
	catch (std::exception e)
	{
		__debugbreak();
	}

}
Windows::Foundation::Collections::IVector<Platform::String^>^ CheckoutManager::AddCheckout::DeviceTypes::get()
{

	auto u16devices = dataInstance->getdeviceTypes();
	auto cxxstring = ref new Platform::Collections::Vector<Platform::String^>(); //convert u16string to Platform:;String
	for (auto& z : u16devices)
	{

		cxxstring->Append(ref new Platform::String((const wchar_t*)z.first.c_str()));
	}
	//__debugbreak();
	return cxxstring;

}
