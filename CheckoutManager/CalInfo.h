#pragma once
#include "dataManager.h"
using namespace dataspace;
using namespace Windows::UI::Xaml;
namespace CheckoutManager
{
	ref class CalInfo;
	public delegate void update(CalInfo^);
	public ref class CalInfo sealed
	{
	public:
		event update^ updateCalendar;
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
				updateCalendar(this);
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
				}
			}
		}
	internal:
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