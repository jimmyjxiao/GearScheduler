//
// DeviceViewPage.xaml.cpp
// Implementation of the DeviceViewPage class
//

#include "pch.h"
#include "DeviceViewPage.xaml.h"

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

DeviceViewPage::DeviceViewPage()
{
	InitializeComponent();

	data = database;
	

}

void CheckoutManager::DeviceViewPage::deleteGroup(devicesGroup ^ z)
{
	data->deleteDeviceType((const char16_t*)z->key->Data());
	unsigned int index;
	if (currentBinded->IndexOf(z, &index))
		currentBinded->RemoveAt(index);
	
}
Windows::UI::Xaml::Input::ICommand^ CheckoutManager::devicesGroup::deleteGroup::get()
{
	return ref new CommandDelegate::DelegateCommand(ref new CommandDelegate::ExecuteDelegate([this](Platform::Object^ param) {
		auto mainframe = (MainPage^)Windows::UI::Xaml::Window::Current->Content;
		auto current = (DeviceViewPage^)mainframe->AppFrame->Content;
		current->deleteGroup(this);
	}), nullptr);
}


void CheckoutManager::DeviceViewPage::AddDeviceType_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	try
	{
		if (!typeTextbox->Text->IsEmpty())
		{
			auto newgroup = ref new devicesGroup();
			newgroup->color = ref new Windows::UI::Xaml::Media::SolidColorBrush(dataManager::inttocolor(data->addDevicetype((const char16_t*)typeTextbox->Text->Data())));
			newgroup->key = typeTextbox->Text;
			currentBinded->Append(newgroup);
		}
	}
	catch (std::exception e)
	{
		__debugbreak();
	}
}
Windows::Foundation::Collections::IVector<devicesGroup^>^ CheckoutManager::DeviceViewPage::bindDevices::get()
{
	if (currentBinded == nullptr)
	{
		Platform::Collections::Vector<devicesGroup^>^ prepvec = ref new Platform::Collections::Vector<devicesGroup^>();
		try
		{
			auto x = data->getdeviceTypes();
			const auto v = data->getDevices();


			for (auto &z : x)
			{

				auto devtype = ref new devicesGroup();
				devtype->key = ref new Platform::String((const wchar_t*)z.first.c_str());
				devtype->color = ref new Windows::UI::Xaml::Media::SolidColorBrush(z.second);
				auto treetype = devtype->ToString();
				//__debugbreak();
				//devtype->color = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
				devtype->devices = ref new Platform::Collections::Vector<device^>();
				auto range = v.equal_range(z.first);

				if (range.first != v.end())
				{

					std::for_each(range.first, range.second, [devtype](std::pair<std::u16string, std::tuple<bool, std::u16string, std::u16string, int>> m)
					{

						auto appending = ref new device();
						appending->checkedOut = !std::get<0>(m.second);
						if (appending->checkedOut)
							appending->currentRentee = ref new Platform::String((const wchar_t*)std::get<1>(m.second).c_str());
						else appending->currentRentee = nullptr;
						appending->description = ref new Platform::String((const wchar_t*)(std::get<2>(m.second)).c_str());
						appending->deviceID = std::get<3>(m.second);
						devtype->devices->Append(appending);
					});
				}
				prepvec->Append(devtype);
			}
			currentBinded = prepvec;

		}
		catch (std::exception e)
		{
			__debugbreak();
		}
	}
	return currentBinded;
}




void CheckoutManager::DeviceViewPage::addDevicebutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto selectedType = (devicesGroup^)DeviceSelector->SelectedValue;
	if (selectedType == nullptr);
	else
	{
		try
		{
			data->addDevice((char16_t*)newdevdesc->Text->Data(), (char16_t*)selectedType->key->Data());
			device^ newdevice = ref new device();
			newdevice->checkedOut = false, newdevice->currentRentee = "", newdevice->description = newdevdesc->Text, newdevice->deviceID = 99;
			if (selectedType->devices == nullptr)
				selectedType->devices = ref new Platform::Collections::Vector<device^>();
			selectedType->devices->Append(newdevice);
		}
		catch (std::exception e)
		{
			__debugbreak();
		}

	}
	//__debugbreak();
}


void CheckoutManager::DeviceViewPage::Grid_ContextRequested(Windows::UI::Xaml::UIElement^ sender, Windows::UI::Xaml::Input::ContextRequestedEventArgs^ args)
{
	auto s = sender;
	auto a = args;
	//__debugbreak();
}


void CheckoutManager::DeviceViewPage::MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto s = e->ToString();
	auto a = e->OriginalSource;
	__debugbreak();
}


void CheckoutManager::DeviceViewPage::MenuFlyoutItem_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//I like ugly code!
	
}
