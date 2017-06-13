//
// DeviceViewPage.xaml.h
// Declaration of the DeviceViewPage class
//

#pragma once

#include "DeviceViewPage.g.h"
#include "dataManager.h"
#include "DelegateCommand.h"
#include "MainPage.xaml.h"
using namespace dataspace;
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>

	public value struct device sealed
	{

	public:
		Platform::String^ description;
		 bool checkedOut;
		 int deviceID;
		 Platform::String^ currentRentee;
	};
	struct deviceEqual : public std::binary_function<const device, const device, bool>
	{
		bool operator()(const device & left, const device & right) const
		{
			return (std::tie(left.checkedOut, left.currentRentee, left.deviceID, left.description) == std::tie(right.checkedOut, right.currentRentee, right.deviceID, right.description));
		};
	};
	[Windows::UI::Xaml::Data::Bindable]
	public ref struct devicesGroup sealed
	{
	public:
		property Windows::UI::Xaml::Media::SolidColorBrush^ color;
		property Platform::String^ key
		{
			Platform::String^ get()
			{


				return typeName;
			}
			void set(Platform::String^ in)
			{
				typeName = in;
			}
		}
		property Windows::UI::Xaml::Input::ICommand^ deleteGroup
		{
			Windows::UI::Xaml::Input::ICommand^ get();
		}
		
		property Windows::Foundation::Collections::IVector<device>^ devices;
	private:
		Platform::String^ typeName;


	};
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DeviceViewPage sealed
	{
	public:
		DeviceViewPage();
		void deleteGroup(devicesGroup^ z);
		property Windows::Foundation::Collections::IVector<devicesGroup^>^ bindDevices
		{
			Windows::Foundation::Collections::IVector<devicesGroup^>^ get();
		}

	private:
		dataManager * data;
		Platform::Collections::Vector<devicesGroup^>^ currentBinded = nullptr;
		std::unordered_map<std::u16string, Windows::UI::Color> * typemap;
		Windows::UI::Xaml::Input::ICommand^ deleteGroupcommand;
		void AddDeviceType_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void addDevicebutton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Grid_ContextRequested(Windows::UI::Xaml::UIElement^ sender, Windows::UI::Xaml::Input::ContextRequestedEventArgs^ args);
		void MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MenuFlyoutItem_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void MenuFlyoutItem_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
	public ref class grouptostr  sealed : Windows::UI::Xaml::Data::IValueConverter
	{
		// This converts the devicesGroup object to the name of the deviceType
	public:
		virtual Platform::Object^ Convert(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter, Platform::String^ language)
		{
			auto bz = safe_cast<devicesGroup^>(value);
			return bz->ToString();
		}

		// No need to implement converting back on a one-way binding 
		virtual Platform::Object^ ConvertBack(Platform::Object^ value, Windows::UI::Xaml::Interop::TypeName targetType,
			Platform::Object^ parameter, Platform::String^ language)
		{
			throw ref new Platform::NotImplementedException();
		}
	};
}
