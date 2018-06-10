//
// TrialExpired.xaml.h
// Declaration of the TrialExpired class
//

#pragma once

#include "TrialExpired.g.h"

namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class TrialExpired sealed
	{
	public:
		TrialExpired();
	private:
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
