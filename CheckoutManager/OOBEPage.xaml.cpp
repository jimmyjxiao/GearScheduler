//
// OOBEPage.xaml.cpp
// Implementation of the OOBEPage class
//

#include "pch.h"
#include "OOBEPage.xaml.h"
#include "WindowsNumerics.h"
#include "MainPage.xaml.h"
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

OOBEPage::OOBEPage()
{
	InitializeComponent();
	
}


void CheckoutManager::OOBEPage::gifboard_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//Storyboard->Begin();
	auto hostVisual = Windows::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(Shadowhost);
	auto compositor = hostVisual->Compositor;

	// Create a drop shadow
	auto dropShadow = compositor->CreateDropShadow();
	//dropShadow->Color = Windows::UI::ColorHelper::FromArgb(255, 75, 75, 80);
	dropShadow->Opacity = .35;
	dropShadow->BlurRadius = 15.0f;
	dropShadow->Offset = Windows::Foundation::Numerics::float3(-16.0f, 8.0f, 0.0f);
	// Associate the shape of the shadow with the shape of the target element
	dropShadow->Mask = gifboard->GetAlphaMask();

	// Create a Visual to hold the shadow
	auto shadowVisual = compositor->CreateSpriteVisual();
	shadowVisual->Shadow = dropShadow;
	//shadowVisual->Size = gifboard->RenderSize;
	// Add the shadow as a child of the host in the visual tree
	Windows::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(Shadowhost, shadowVisual);

	// Make sure size of shadow host and shadow visual always stay in sync
	auto bindSizeAnimation = compositor->CreateExpressionAnimation("hostVisual.Size");
	bindSizeAnimation->SetReferenceParameter("hostVisual", hostVisual);

	shadowVisual->StartAnimation("Size", bindSizeAnimation);

}





void CheckoutManager::OOBEPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto settings = Windows::Storage::ApplicationData::Current->LocalSettings;
	settings->Values->Insert("firstTimefinished", true);
	Window::Current->Content = ref new MainPage();
}
