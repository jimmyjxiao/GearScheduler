//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//
// If you are reading this code right now I am so sorry. I know it's a huge steaming pile of shit.
#include "pch.h"
#include "MainPage.xaml.h"
using namespace CheckoutManager;
using namespace CheckoutManager::nav;
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{

	InitializeComponent();
	auto navlist = ref new Platform::Collections::Vector<NavItem^>();
	navlist->Append(ref new NavItem(
		Calpage::typeid, L"Schedule", Symbol::Calendar
	));
	navlist->Append(ref new NavItem(
		DeviceViewPage::typeid, L"Devices", Symbol::Library
	));
	navlist->Append(ref new NavItem(
		TeamPage::typeid, L"People/Teams", Symbol::People
	));
	navlist->Append(ref new NavItem(
		CheckoutPage::typeid, L"Checkout/Return/Status", Symbol::Bullets
	));
	navigator->ItemsSource = navlist;
	navigator->SelectedIndex = 0;
	//navigator->SelectedIndex = 0;
	//auto container = (Windows::UI::Xaml::Controls::ListViewItem^)navigator->ContainerFromIndex(0);
	//container->IsSelected = false;
	//zFrame->Navigate(OOBE::typeid);
	//OOBEDialog^ zeig = ref new OOBEDialog();
	//zeig->ShowAsync();
}

Windows::UI::Xaml::Controls::Frame^ CheckoutManager::MainPage::AppFrame::get()
{
	return zFrame;
}
void CheckoutManager::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	navMenu->IsPaneOpen = !navMenu->IsPaneOpen;
	/*
	Windows::Foundation::DateTime test = date->Date;


	auto reftm = ref new Windows::Globalization::Calendar();
	reftm->SetDateTime(date->Date);
	auto zeroday = [](Windows::Globalization::Calendar^ tmst)
	{
	tmst->Period = 1, tmst->Minute = 0, tmst->Second = 0, tmst->Nanosecond = 0, tmst->Hour = 12;
	};
	auto timetconv = [](Windows::Foundation::DateTime *in) { return (const time_t)((in->UniversalTime - 116444736000000000ULL) / 10000000); };
	zeroday(reftm);
	time_t x = (timetconv((&reftm->GetDateTime())));
	tm z;
	localtime_s(&z, &x);
	wchar_t buf[80];
	wcsftime(buf, 80, L"%c", &z);
	OutputDebugString(L"\n");
	OutputDebugString(reftm->Day.ToString()->Data());
	OutputDebugString(L"\n");

	auto formatter = ref new Windows::Globalization::DateTimeFormatting::DateTimeFormatter(L"longdate shorttime");
	auto str = formatter->Template;
	auto formated = formatter->Format(reftm->GetDateTime());
	//__debugbreak();
	*/

}

Windows::UI::Color CheckoutManager::MainPage::GetNewColor()
{
	return Windows::UI::Color();
}



void CheckoutManager::MainPage::ListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	auto topage = ((NavItem^)navigator->SelectedItem);
	zFrame->Navigate(topage->destPage);
}

CheckoutManager::nav::NavItem::NavItem(Platform::Type ^ page, Platform::String ^ label, Windows::UI::Xaml::Controls::Symbol sym)
{
	destPage = page;
	Label = label;
	Symbol = sym;
}


void CheckoutManager::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}


void CheckoutManager::MainPage::zFrame_Navigated(Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e)
{
	
	/*auto newpage = (Platform::Type^)(dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(sender)->SourcePageType);
	auto tn = AddCheckout::typeid;
	if (newpage == tn)
		//__debugbreak();*/
	
}
