#pragma once
#include "dataManager.h"
using namespace dataspace;
using namespace Windows::UI::Xaml;
namespace CheckoutManager
{
	ref class CalInfo;
	public delegate void update(CalInfo^);
	public delegate void switchView(bool month, CalInfo^ cal);
	public ref class CalInfo sealed
	{
	public:
		event update^ updateCalendar;
		event switchView^ switchtoweek;
		property Windows::Foundation::DateTime date;
		property Windows::Foundation::DateTime selectedDate
		{
			Windows::Foundation::DateTime get()
			{
				return _selectedDate;
			}
			void set(Windows::Foundation::DateTime z)
			{
				_selectedDate = z;
				//updateCalendar(this);
			}
			
		}
		property bool ViewBy
		{
			bool get()
			{
				return view;
			}
			void set(bool a)
			{
				if (a != view)
				{
					std::swap(colorMap, offColor);
					view = a;
					updateCalendar(this);
				}
			}
		}
	internal:
		bool selectedDatechanged = false;
		void updateInfo()
		{
			updateCalendar(this);
		}
		void monthtoweek()
		{
			switchtoweek(false, this);
		}
		dataManager* datcon;
		CalInfo(dataManager* z);
		int debugvar = 0;
		std::unordered_map<std::u16string, Windows::UI::Color> colorMap;
		std::unordered_map<std::u16string, Windows::UI::Color> offColor;

	private:
		Windows::Foundation::DateTime _selectedDate;
		bool view = ViewByDevice;

	};
}