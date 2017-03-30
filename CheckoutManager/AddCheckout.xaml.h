//
// AddCheckout.xaml.h
// Declaration of the AddCheckout class
//

#pragma once

#include "AddCheckout.g.h"
#include "dataManager.h"
#include "AuthenticationDialog.xaml.h"

using namespace dataspace;
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AddCheckout sealed
	{

	public:
		AddCheckout();
		AddCheckout(Windows::Foundation::DateTime defaultTime);
		property Windows::Foundation::Collections::IVector<Platform::String^>^ DeviceTypes
		{
			Windows::Foundation::Collections::IVector<Platform::String^>^ get();

		}


	private:
		dataManager* dataInstance;
		std::vector<dataManager::CheckoutInfo> devicecheckoutcache;
		void AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
