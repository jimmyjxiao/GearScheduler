#pragma once
#include <time.h>

namespace converters
{
	public ref class BooleanToVisibilityConverter sealed : Windows::UI::Xaml::Data::IValueConverter
	{
	public:
		virtual Platform::Object^ Convert(
			Platform::Object^ value,
			Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter,
			Platform::String^ language);

		virtual Platform::Object^ ConvertBack(
			Platform::Object^ value,
			Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter,
			Platform::String^ language);
	};
	public ref class booltocolor  sealed : Windows::UI::Xaml::Data::IValueConverter
	{
		// This converts the DateTime object to the Platform::String^ to display.
	public:
		virtual Platform::Object^ Convert(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter, Platform::String^ language)
		{
			auto bz = safe_cast<bool>(value);
			if (bz)
			{
				return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
			}
			else
			{

				return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Green);
			}
		}

		// No need to implement converting back on a one-way binding 
		virtual Platform::Object^ ConvertBack(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter, Platform::String^ language)
		{
			throw ref new Platform::NotImplementedException();
		}
	};
	time_t FoundationtoStdtime(const Windows::Foundation::DateTime *in);
	void textchangedNumberfilter(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args);
}
