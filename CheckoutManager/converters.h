#pragma once
#include <time.h>
namespace CheckoutManager
{
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
		public ref class booltocolor  sealed : Windows::UI::Xaml::Data::IValueConverter, Windows::UI::Xaml::DependencyObject
		{
			// This converts the DateTime object to the Platform::String^ to display.
		public:
			virtual Platform::Object^ Convert(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
				Platform::Object^ parameter, Platform::String^ language)
			{
				auto bz = safe_cast<bool>(value);
				try
				{
					if (parameter != nullptr)
						bz = !bz;
				}
				catch (...) {}
				if (bz)
				{
					return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Green);
				}
				else
				{
					return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);

				}
			}

			// No need to implement converting back on a one-way binding 
			virtual Platform::Object^ ConvertBack(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
				Platform::Object^ parameter, Platform::String^ language)
			{
				throw ref new Platform::NotImplementedException();
			}
		};
		public ref class booltosymbol sealed : Windows::UI::Xaml::Data::IValueConverter
		{
		public:
			virtual Platform::Object^ Convert(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
				Platform::Object^ parameter, Platform::String^ language)
			{
				auto bz = safe_cast<bool>(value);
				if (bz)
				{
					return Windows::UI::Xaml::Controls::Symbol::Accept;
				}
				else
				{

					return Windows::UI::Xaml::Controls::Symbol::Cancel;
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
		std::wstring shortDatetime(time_t time);
	}
}