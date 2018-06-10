//
// TrialExpired.xaml.cpp
// Implementation of the TrialExpired class
//

#include "pch.h"
#include "TrialExpired.xaml.h"

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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

TrialExpired::TrialExpired()
{
	InitializeComponent();
	
}


void CheckoutManager::TrialExpired::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	concurrency::create_task(Windows::ApplicationModel::Store::CurrentApp::RequestAppPurchaseAsync(true));
}


void CheckoutManager::TrialExpired::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::System::Launcher::LaunchUriAsync(ref new Uri("mailto:gearSchedulerDev@outlook.com?Subject=Customized%20GearScheduler%20implementation%20inquiry"));
}
