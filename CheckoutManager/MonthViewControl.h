#pragma once
#include "dataManager.h"
#include "CalInfo.h"
#include "converters.h"
#include "Calpage.xaml.h"
namespace CheckoutManager
{
	public delegate void switchView(bool month, CalInfo^ cal);
	public ref class MonthViewControl sealed :
		public Windows::UI::Xaml::Controls::CalendarView
	{
	public:
		
		MonthViewControl();
		property CalInfo^ cal
		{
			CalInfo^ get()
			{
				return calvar;
			}
			void set(CalInfo^ newset)
			{

				calvar = newset;

			}
		}
		property switchView^ switchHandler
		{
			void set(switchView^ z)
			{
				switchtoweek += z;
			}
		}
	private:
		event switchView^ switchtoweek;
		CalInfo^ calvar = nullptr;
		void CalendarView_CalendarViewDayItemChanging(Windows::UI::Xaml::Controls::CalendarView^ sender, Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs^ args);
		void OnSelectedDatesChanged(Windows::UI::Xaml::Controls::CalendarView ^sender, Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs ^args);
		void OnDoubleTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs ^e);
	};
	private struct MyEqual : public std::binary_function<const Windows::UI::Color, const Windows::UI::Color, bool>
	{
		bool operator()(const Windows::UI::Color& _Left, const Windows::UI::Color& _Right) const
		{

			if (_Left.A == _Right.A && _Left.R == _Right.R && _Left.G == _Right.G && _Left.B == _Right.B)
				return true;
			else return false;
		};
	};



}