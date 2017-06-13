#include "pch.h"
#include "CalInfo.h"




CheckoutManager::CalInfo::CalInfo(dataManager * z)
{
	auto gcal = ref new Windows::Globalization::Calendar();
	_selectedDate = gcal->GetDateTime();
	date = selectedDate;
	colorMap = z->getdeviceTypes();
	offColor = z->getTeams();
	datcon = z;
}
