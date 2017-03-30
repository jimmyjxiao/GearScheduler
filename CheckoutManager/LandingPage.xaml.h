//
// LandingPage.xaml.h
// Declaration of the LandingPage class
//

#pragma once

#include "LandingPage.g.h"

namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class LandingPage sealed
	{
	public:
		LandingPage();
		property Platform::String^ datestr
		{
			Platform::String^ get()
			{
				Windows::Globalization::DateTimeFormatting::DateTimeFormatter^ dtformat = Windows::Globalization::DateTimeFormatting::DateTimeFormatter::LongDate;


				auto z = intcal->GetDateTime();
				return dtformat->Format(z);
			}
		}
		property Platform::String^ dtf
		{
			Platform::String^ get()
			{
				auto day = intcal->DayOfWeek;
				return ((int)(Windows::Globalization::DayOfWeek::Friday - day)).ToString();
			}
		}
		property Platform::String^ numdevices;
	private:
		Windows::Globalization::Calendar^ intcal;
	};
}
