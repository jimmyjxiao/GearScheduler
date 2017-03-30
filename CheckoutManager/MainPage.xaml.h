//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "converters.h"
#include "Calpage.xaml.h"
#include "DeviceViewPage.xaml.h"
#include "TeamPage.xaml.h"
#include "CheckoutPage.xaml.h"
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref struct NavItem sealed
	{

	public:
		NavItem(Platform::Type^ page, Platform::String^ label, Windows::UI::Xaml::Controls::Symbol sym);
		property bool selected;
		property Platform::String^ Label;
		property Windows::UI::Xaml::Controls::Symbol Symbol;
		property Windows::UI::Xaml::Interop::TypeName destPage;


	};
	public ref class MainPage sealed
	{
	public:
		MainPage();
		property Windows::UI::Xaml::Controls::Frame^ AppFrame
		{
			Windows::UI::Xaml::Controls::Frame^ get();

		}

	private:
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Windows::UI::Color GetNewColor();
		void ListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	internal:
		static MainPage^ current;
	};
}
