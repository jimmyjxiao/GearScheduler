// BooleanToVisibilityConverter.cpp

#include "pch.h"
#include "converters.h"
#include <cwctype>
using namespace converters;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ BooleanToVisibilityConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	(void)targetType;  // Unused parameter
	(void)parameter;   // Unused parameter
	(void)language;    // Unused parameter

	auto boxedBool = dynamic_cast<Box<bool>^>(value);
	auto boolValue = (boxedBool != nullptr && boxedBool->Value);
	return (boolValue ? Visibility::Visible : Visibility::Collapsed);
}

Object^ BooleanToVisibilityConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	(void)targetType;  // Unused parameter
	(void)parameter;   // Unused parameter
	(void)language;    // Unused parameter

	auto visibility = dynamic_cast<Box<Visibility>^>(value);
	return (visibility != nullptr && visibility->Value == Visibility::Visible);
}

time_t converters::FoundationtoStdtime(const Windows::Foundation::DateTime* in)
{
	return (const time_t)((in->UniversalTime - 116444736000000000ULL) / 10000000);
}

void converters::textchangedNumberfilter(Windows::UI::Xaml::Controls::TextBox ^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs ^ args)
{

	
	std::wstring text = sender->Text->Data();
	text.erase(std::remove_if(text.begin(), text.end(), std::not1(std::ptr_fun((int(*)(int))std::iswdigit))), text.end());
	sender->Text = ref new Platform::String(text.data());

}

std::wstring converters::shortDatetime(time_t time)
{
	wchar_t buf[80]; //inefficient, but who cares;
	wcsftime(buf, 80, L"%D %I:%M%p", localtime(&time));
	return buf;
}
