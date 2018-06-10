#include "pch.h"
#include "MonthViewControl.h"


CheckoutManager::MonthViewControl::MonthViewControl()
{
	CalendarViewDayItemChanging += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::CalendarView ^, Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs ^>(this, &CheckoutManager::MonthViewControl::CalendarView_CalendarViewDayItemChanging);
	SelectionMode = Windows::UI::Xaml::Controls::CalendarViewSelectionMode::Single;
	SelectedDatesChanged += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::CalendarView ^, Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs ^>(this, &CheckoutManager::MonthViewControl::OnSelectedDatesChanged);
}

void CheckoutManager::MonthViewControl::CalendarView_CalendarViewDayItemChanging(Windows::UI::Xaml::Controls::CalendarView ^ sender, Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs ^ args)
{
	args->Item->DoubleTapped += ref new Windows::UI::Xaml::Input::DoubleTappedEventHandler(this, &CheckoutManager::MonthViewControl::OnDoubleTapped);

	auto zeroday = [](Windows::Globalization::Calendar^ tmst)
	{
		tmst->Period = 1, tmst->Minute = 0, tmst->Second = 0, tmst->Nanosecond = 0, tmst->Hour = 12;
	};
	auto dayItem = args->Item;

	auto fdate = ref new Windows::Globalization::Calendar();
	fdate->SetDateTime(args->Item->Date);
	zeroday(fdate);
	auto edate = fdate->Clone();
	edate->AddDays(1);
	auto startDay = fdate->GetDateTime();

	try
	{
		auto dayevents = cal->datcon->getCheckouts(converters::FoundationtoStdtime(&startDay), converters::FoundationtoStdtime(&edate->GetDateTime()));



		concurrency::create_task([dayevents, dayItem, this, startDay]()
		{
			Platform::Collections::Vector<Windows::UI::Color, MyEqual>^ daycolors = ref new Platform::Collections::Vector<Windows::UI::Color, MyEqual>();

			std::vector<dataManager::CheckoutInfo>::const_iterator endit;
			if (dayevents.size() < 9)
				endit = dayevents.end();
			else
				endit = dayevents.begin() + 9;

			std::for_each(dayevents.begin(), endit, [daycolors, this, startDay](const dataManager::CheckoutInfo n)
			{
				std::unordered_map<std::u16string, Windows::UI::Color>::const_iterator it;
				if (calvar->ViewBy == ViewByTeam)
					it = calvar->colorMap.find(n.Team);
				else if (calvar->ViewBy == ViewByDevice)
					it = calvar->colorMap.find(n.deviceType);
				daycolors->Append(it->second);
				
				//daycolors->Append(Windows::UI::Colors::Green);


			});
			std::function<void(Windows::Foundation::Collections::IIterable<Windows::UI::Color>^)> changefunc = [dayItem](Windows::Foundation::Collections::IIterable<Windows::UI::Color>^ z) {dayItem->SetDensityColors(z); };
			//dayItem info = { daycolors, changefunc, daycolors->GetView() };
			//allmap.insert(std::make_pair(startDay.UniversalTime, info));

			if (daycolors->Size > 0)
			{
				try
				{
					Dispatcher->RunAsync(
						Windows::UI::Core::CoreDispatcherPriority::Normal,
						ref new Windows::UI::Core::DispatchedHandler([dayItem, daycolors]()
					{

						dayItem->SetDensityColors(daycolors);
					}));

				}
				catch (Platform::Exception^ e)
				{
					//__debugbreak();
				}
			}
		});
	}
	catch (Platform::Exception^ e)
	{
		//__debugbreak();
	}

}


void CheckoutManager::MonthViewControl::OnSelectedDatesChanged(Windows::UI::Xaml::Controls::CalendarView ^sender, Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs ^args)
{
	if (args->AddedDates->Size != 0)
	{
		cal->selectedDate = args->AddedDates->GetAt(0);
		cal->selectedDatechanged = true;
	}
}


void CheckoutManager::MonthViewControl::OnDoubleTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs ^e)
{
	cal->monthtoweek();
}


void CheckoutManager::MonthViewControl::OnupdateCalendar(CheckoutManager::CalInfo ^)
{
	if (!removed)
	{
		auto newcontrol = ref new MonthViewControl();
		newcontrol->cal = calvar;
		newcontrol->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Stretch;
		newcontrol->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Stretch;
		calvar->updateCalendar -= cookie;
		auto x = ((Windows::UI::Xaml::Controls::PivotItem^)Parent);
		if (x != nullptr)
			x->Content = newcontrol;
		else
			replacewith = newcontrol;
		removed = true; 
	}
}
