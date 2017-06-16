//
// TeamPage.xaml.cpp
// Implementation of the TeamPage class
//

#include "pch.h"
#include "TeamPage.xaml.h"

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

TeamPage::TeamPage()
{
	InitializeComponent();
	data = database;
}


void CheckoutManager::TeamPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto newteam = ref new Team();
	newteam->teamName = newTeambox->Text;
	newteam->color = ref new Windows::UI::Xaml::Media::SolidColorBrush(dataspace::dataManager::inttocolor(data->addTeam((const char16_t*)newTeambox->Text->Data(), (const char16_t*)confirmpass->Password->Data()))); //implement password hashing function later. Not really necessary right now; who's gonna bother to hack this?
	teamvec->Append(newteam);
}
Windows::Foundation::Collections::IVector<Team^>^ CheckoutManager::TeamPage::bindTeams::get()
{
	if (teamvec == nullptr)
	{
		Platform::Collections::Vector<Team^>^ intializevec = ref new Platform::Collections::Vector<Team^>();
		auto x = data->getTeams();
		for (auto v : x)
		{
			auto newstruct = ref new Team();
			newstruct->teamName = ref new Platform::String((const wchar_t*)v.first.c_str());
			newstruct->color = ref new Windows::UI::Xaml::Media::SolidColorBrush(v.second);
			intializevec->Append(newstruct);
		}
		teamvec = intializevec;
	}
	return teamvec;
}

void CheckoutManager::TeamPage::Password_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (Password->Password->IsEmpty())
		confirmpass->IsEnabled = false;
	else
		confirmpass->IsEnabled = true;
}


void CheckoutManager::TeamPage::confirmpass_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (confirmpass->Password->Equals(Password->Password))
		addbutton->IsEnabled = true;
	else
		addbutton->IsEnabled = false;
}


void CheckoutManager::TeamPage::ListView_ContextRequested(Windows::UI::Xaml::UIElement^ sender, Windows::UI::Xaml::Input::ContextRequestedEventArgs^ args)
{

	//Platform::String^ dighe = teamslist->Items->GetAt(1)->GetType()->FullName;
	//__debugbreak();

}
