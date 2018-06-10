//
// OOBEPage.xaml.h
// Declaration of the OOBEPage class
//

#pragma once

#include "OOBEPage.g.h"

namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class OOBEPage sealed
	{
	public:
		
		OOBEPage();
	private:
		void gifboard_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnTick(Platform::Object ^sender, Platform::Object ^args);
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
