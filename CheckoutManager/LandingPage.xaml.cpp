//
// LandingPage.xaml.cpp
// Implementation of the LandingPage class
//

#include "pch.h"
#include "LandingPage.xaml.h"

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

LandingPage::LandingPage()
{
	intcal = ref new Windows::Globalization::Calendar();
	intcal->SetToNow();
	InitializeComponent();
}
