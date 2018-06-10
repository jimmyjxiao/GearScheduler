//
// WeekViewControl.xaml.cpp
// Implementation of the WeekViewControl class
//

#include "pch.h"
#include "WeekViewControl.xaml.h"
#include "converters.h"
#include <ppl.h>
#include <set>
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

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

WeekViewControl::WeekViewControl()
{
	InitializeComponent();
	startofweek = ref new Windows::Globalization::Calendar();
	mainGrid->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler(this, &CheckoutManager::WeekViewControl::OnSizeChanged);
	for (byte i = 1; i <= 7; i++)
	{
		auto dayaddingCanvas = ref new Windows::UI::Xaml::Controls::Canvas();
		auto border = ref new  Windows::UI::Xaml::Controls::Border();
		border->BorderBrush = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Black);
		border->BorderThickness = 1;
		border->Child = dayaddingCanvas;
		dayCanvas[i - 1] = dayaddingCanvas;
		mainGrid->Children->Append(border);
		mainGrid->SetColumn(border, i);
		mainGrid->SetRow(border, 1);
		mainGrid->SetRowSpan(border, 3);
	}
	manuallyhidden = ref new Platform::Collections::Vector<WeekEvent^>();

}


void CheckoutManager::WeekViewControl::OnPropertyChanged(Platform::String ^ propertyName)
{
	PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}

void CheckoutManager::WeekViewControl::mainGrid_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}
void CheckoutManager::WeekViewControl::incrementweek(bool x)
{
	Windows::Foundation::DateTime newstart;
	if (x)
	{
		newstart.UniversalTime = cal->selectedDate.UniversalTime + 6.048e12;
	}
	else
	{
		newstart.UniversalTime = cal->selectedDate.UniversalTime - 6.048e12;
	}
	cal->selectedDate = newstart;
	updatecalendar(cal);
	OnPropertyChanged("dateRange");
}
void CheckoutManager::WeekViewControl::selectionChanged(Windows::Foundation::Collections::IVector<Platform::Object^>^ added, Windows::Foundation::Collections::IVector<Platform::Object^>^ removed)
{

	HyperlinkButton_Click(nullptr, nullptr);


	for (auto a : added)
	{
		auto xxz = (TextBlock^)static_cast<Object^>(a);
		auto iter = events.begin();
		for (auto b : events)
		{
			bool change;
			if (cal->ViewBy == ViewByDevice)
			{
				change = (xxz->Text == b->deviceStr);
			}
			else if (cal->ViewBy == ViewByTeam)
			{
				change = (xxz->Text == b->teamStr);
			}
			if(change)
				b->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}
	}
	for (auto a : removed)
	{
		auto xxz = (TextBlock^)static_cast<Object^>(a);
		auto iter = events.begin();
		for (auto b : events)
		{
			bool change;
			if (cal->ViewBy == ViewByDevice)
			{
				change = (xxz->Text == b->deviceStr);
			}
			else if (cal->ViewBy == ViewByTeam)
			{
				change = (xxz->Text == b->teamStr);
			}
			if (change)
				b->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		}
	}
}
CalInfo^ CheckoutManager::WeekViewControl::cal::get()
{
	return calvar;
}
void CheckoutManager::WeekViewControl::cal::set(CalInfo^ setting)
{
	calvar = setting;
	cal->updateCalendar += ref new CheckoutManager::update(this, &CheckoutManager::WeekViewControl::updatecalendar);
	cal->switchtoweek += ref new CheckoutManager::switchView(this, &CheckoutManager::WeekViewControl::switchtoweek);
}

void CheckoutManager::WeekViewControl::switchtoweek(bool, CalInfo ^)
{
	if (calvar->selectedDatechanged)
	{
		calvar->selectedDatechanged = false;
		if (firstTimeintialized)
		{
			auto newstart = ref new Windows::Globalization::Calendar();
			newstart->SetDateTime(calvar->selectedDate);
			newstart->Period = 1, newstart->Minute = 0, newstart->Second = 0, newstart->Nanosecond = 0, newstart->Hour = 12;
			newstart->AddDays((int)-newstart->DayOfWeek);
			if (newstart->GetDateTime().UniversalTime != startofweek->GetDateTime().UniversalTime)
			{
				startofweek = newstart;
				updatecalendar(calvar);
				OnPropertyChanged("dateRange");
			}


		}
	}
}

void CheckoutManager::WeekViewControl::updatecalendar(CalInfo^ calz)
{
	startofweek->SetDateTime(calvar->selectedDate);
	startofweek->Period = 1, startofweek->Minute = 0, startofweek->Second = 0, startofweek->Nanosecond = 0, startofweek->Hour = 12;
	startofweek->AddDays((int)-startofweek->DayOfWeek);
	if (firstTimeintialized)
	{
	
			events.clear();
			for (auto x : dayCanvas)
			{
				x->Children->Clear();
			}
	}


		auto formatter = Windows::Globalization::DateTimeFormatting::DateTimeFormatter::ShortDate;
		auto endDatetimerange = startofweek->Clone();
		endDatetimerange->AddWeeks(1);

		//currentRange->Text = (formatter->Format(startofweek->GetDateTime(), "America/Denver")) + " - " + (formatter->Format(endDatetimerange->GetDateTime(), "America/Denver"));
		double canvasHeight =
			(mainGrid->ActualHeight - mainGrid->RowDefinitions->GetAt(0)->ActualHeight);
		double columnwidth = dayCanvas[0]->ActualWidth;
		std::function<void()> updateFunc = [calz]() {calz->updateInfo(); };
		for (byte izp = 1; izp <= 7; izp++)
		{

			Windows::Globalization::Calendar^ day = startofweek->Clone();
			day->AddDays(izp - 1);
			const time_t starttime = converters::FoundationtoStdtime(&day->GetDateTime());
			day->AddDays(1);
			const time_t endtime = converters::FoundationtoStdtime(&day->GetDateTime());
			day->AddDays(-1);
			auto daycheckouts = cal->datcon->getCheckouts(starttime, endtime);
			
			for (const dataManager::CheckoutInfo z : daycheckouts)
			{

				double startprop;
				if (z.checkoutTime < starttime)
				{
					startprop = 0;

				}
				else
				{
					time_t seconds = (z.checkoutTime - starttime);
					startprop = (double)seconds / 86400.0;
				}
				std::unordered_map<std::u16string, Windows::UI::Color>::const_iterator it;
				if (cal->ViewBy == ViewByTeam)
					it = cal->colorMap.find(z.Team);
				else if (cal->ViewBy == ViewByDevice)
					it = cal->colorMap.find(z.deviceType);
				Platform::String^ eventTimestr = Platform::StringReference(converters::shortDatetime(z.checkoutTime).data());
				eventTimestr += L"\n";
				eventTimestr = Platform::String::Concat(eventTimestr, Platform::StringReference(converters::shortDatetime(z.duedate).data()));

				maxZindex[izp - 1] = 0;
				//test
				auto a = it->second;
				auto b = ref new Platform::String((const wchar_t*)z.deviceType.data());
				auto c = ref new Platform::String((const wchar_t*)z.Team.data());
				auto d = z.fullfilled;
				auto e = eventTimestr;
				auto f = &maxZindex[izp - 1];

				
				auto adding = ref new WeekEvent(it->second, ref new Platform::String((const wchar_t*)z.deviceType.data()), ref new Platform::String((const wchar_t*)z.Team.data()), z.fullfilled, eventTimestr, &maxZindex[izp - 1], z, updateFunc, z.actualchktime, z.actualreturntime, z.fullfilled);
				adding->chk = z.fullfilled;
				double top = startprop*canvasHeight;

				adding->Width = columnwidth;
				
				if (z.duedate < endtime)
				{
					////__debugbreak();
					float endprop;
					endprop = (z.duedate - z.checkoutTime) / 86400.0;
					adding->Height = (endprop*canvasHeight);
				}
				else
				{
					adding->Height = canvasHeight - top;
				}
				auto addingheight = adding->Height;
				////__debugbreak();

				dayCanvas[izp - 1]->Children->Append(adding);
				dayCanvas[izp - 1]->SetTop(adding, top);
				auto r2 = Windows::Foundation::Rect(0, dayCanvas[izp - 1]->GetTop(adding), 100, adding->Height);
				for (auto&& z : (dayCanvas[izp - 1]->Children))
				{
					if (!z->Equals(adding))
					{
						auto potentialintersect = dynamic_cast<WeekEvent^>(static_cast<Platform::Object^>(z));
						auto r1 = Windows::Foundation::Rect(0, dayCanvas[izp - 1]->GetTop(potentialintersect),100, potentialintersect->Height);
						if (r2.IntersectsWith(r1))
						{
							if (potentialintersect->intersectswith == nullptr)
							{
								auto vecptr = std::shared_ptr<std::vector<WeekEvent^>>(new std::vector<WeekEvent^>());
								vecptr->push_back(potentialintersect);
								vecptr->push_back(adding);
								adding->intersectswith = vecptr;
								potentialintersect->intersectswith = vecptr;
							}
							else
							{
								potentialintersect->intersectswith->push_back(adding);
								adding->intersectswith = potentialintersect->intersectswith;
							}
							double newWidth = (columnwidth / (potentialintersect->intersectswith->size()));
							unsigned char itzv = 0;
							for (auto &&v : *potentialintersect->intersectswith)
							{
								v->Width = newWidth;

								dayCanvas[izp - 1]->SetLeft(v, (newWidth * itzv));
								itzv++;

							}
						}
					}
				}

				adding->hide += ref new CheckoutManager::manualHide(this, &CheckoutManager::WeekViewControl::Onhide);
				adding->unhide += ref new CheckoutManager::manualunhide(this, &CheckoutManager::WeekViewControl::Onunhide);
				adding->deleted += ref new CheckoutManager::deleteEvent([this](WeekEvent^ l) {
					calvar->datcon->deleteCheckout(l->Checkout.checkoutID);
					for (auto &&a : dayCanvas)
					{
						unsigned int index = 0;
						bool found = false;
						for (auto &&control : a->Children)
						{
							if (dynamic_cast<WeekEvent^>((static_cast<Platform::Object^>(control)))->Checkout.checkoutID == l->Checkout.checkoutID)
							{
								found = true;
								break;
							}
						}
						if (found)
						{
							a->Children->RemoveAt(index);
						}
						
					}
					events.erase(std::remove(events.begin(), events.end(), l), events.end());
				});
				events.push_back(adding);
			}

			delete day;

		}

}

void CheckoutManager::WeekViewControl::HyperlinkButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (auto x : manuallyhidden)
	{
		x->Visibility = Windows::UI::Xaml::Visibility::Visible;
		x->manuallyhidden = false;
	}
	manuallyhidden->Clear();
	Partialnotification->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
}


void CheckoutManager::WeekViewControl::Onhide(CheckoutManager::WeekEvent ^listing)
{
	manuallyhidden->Append(listing);
	for (auto v : events)
	{
		if (v->Checkout.checkoutID == listing->Checkout.checkoutID)
			v->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		manuallyhidden->Append(v);
	}
	Partialnotification->Visibility = Windows::UI::Xaml::Visibility::Visible;
}


void CheckoutManager::WeekViewControl::Onunhide(CheckoutManager::WeekEvent ^listing)
{
	unsigned int index;
	if (manuallyhidden->IndexOf(listing, &index))
		manuallyhidden->RemoveAt(index);
	if (manuallyhidden->Size == 0)
		Partialnotification->Visibility = Windows::UI::Xaml::Visibility::Visible;


}



void CheckoutManager::WeekViewControl::back_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void CheckoutManager::WeekViewControl::OnSizeChanged(Platform::Object ^sender, Windows::UI::Xaml::SizeChangedEventArgs ^e)
{
	if (firstTimeintialized)
	{
		double columnwidth = dayCanvas[0]->ActualWidth;
		std::set<std::shared_ptr<std::vector<WeekEvent^>>> setdone;
		for (auto z : events)
		{
			if(z->intersectswith == nullptr)
				z->Width = columnwidth;
			else if ((setdone.find(z->intersectswith)) != (setdone.end()));
			else
			{
				auto newWidth = columnwidth / z->intersectswith->size();
				unsigned char itzv = 0;
				for (auto &&v : *z->intersectswith)
				{
					v->Width = newWidth;
					((Windows::UI::Xaml::Controls::Canvas^)v->Parent)->SetLeft(v, newWidth * itzv);
					itzv++;
				}
				setdone.insert(z->intersectswith);
			}
		}
	}
}


void CheckoutManager::WeekViewControl::UserControl_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	updatecalendar(cal);
	firstTimeintialized = true;
	OnPropertyChanged("dateRange");
}
