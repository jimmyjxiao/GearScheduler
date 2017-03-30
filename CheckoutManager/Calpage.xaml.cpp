//
// Calpage.xaml.cpp
// Implementation of the Calpage class
//

#include "pch.h"
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

Calpage::Calpage()
{
	InitializeComponent();
	currentcalendar = ref new CalInfo(database);
	monthView->switchHandler = ref new CheckoutManager::switchView(this, &CheckoutManager::Calpage::onswitch);
	devradio->IsChecked = true;
	refreshListbox(currentcalendar->ViewBy);
	list->SelectAll();
}


void CheckoutManager::Calpage::refreshListbox(bool viewby)
{
	std::map<std::u16string, Windows::UI::Color> colmap;
	if (viewby == ViewByDevice)
	{
		colmap = currentcalendar->datcon->getdeviceTypesmap();
	}
	else if (viewby == ViewByTeam)
	{
		colmap = currentcalendar->datcon->getTeamsmap();
	}
	Platform::Collections::Vector<Windows::UI::Xaml::Controls::TextBlock^>^ adding = ref new Platform::Collections::Vector<Windows::UI::Xaml::Controls::TextBlock^>();
	for (auto z : colmap)
	{
		auto text = ref new Windows::UI::Xaml::Controls::TextBlock();
		text->Text = ref new Platform::String((const wchar_t*)z.first.data());
		text->Foreground = ref new Windows::UI::Xaml::Media::SolidColorBrush(z.second);
		adding->Append(text);
	}
	list->ItemsSource = adding;
}

void CheckoutManager::Calpage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	((Windows::UI::Xaml::Controls::Frame^)Parent)->Navigate(AddCheckout::typeid);
}


void CheckoutManager::Calpage::RadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	bool newView;
	if(((Windows::UI::Xaml::Controls::RadioButton^)sender)->Tag->ToString() == L"dev")
	{
		newView = ViewByDevice;
	}
	else if (((Windows::UI::Xaml::Controls::RadioButton^)sender)->Tag->ToString() == L"team")
	{
		newView = ViewByTeam;
	}
	if (currentcalendar->ViewBy != newView)
	{
		refreshListbox(newView);
		currentcalendar->ViewBy = newView;
	}
}


void CheckoutManager::Calpage::AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	refreshListbox(currentcalendar->ViewBy);
}

void CheckoutManager::Calpage::onswitch(bool z, CalInfo ^ x)
{
	lengthPivot->SelectedIndex = 1;
}






void CheckoutManager::Calpage::list_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	
	weekview->selectionChanged(e->AddedItems, e->RemovedItems);
}


void CheckoutManager::Calpage::lengthPivot_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (lengthPivot->SelectedIndex == 0)
		list->IsEnabled = false;
	else list->IsEnabled = true;
}
