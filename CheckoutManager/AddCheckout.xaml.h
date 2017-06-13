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
	internal:
		AddCheckout(dataspace::dataManager::CheckoutInfo * editing, std::function<void()>editedfunc);
	public:
		AddCheckout();
		AddCheckout(Windows::Foundation::DateTime defaultTime);
		

	protected:
		 virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		 virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		Windows::Foundation::EventRegistrationToken cookie;
		std::function<void()> updatefunc;
		bool editmode = false;
		dataspace::dataManager::CheckoutInfo * edit;
		std::pair<bool, bool> selintial;
		bool isloaded = false;
		dataManager* dataInstance;
		std::vector<dataManager::CheckoutInfo> devicecheckoutcache;
		void AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void sameDay_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void teamSelector_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void OnBackRequested(Platform::Object ^sender, Windows::UI::Core::BackRequestedEventArgs ^args);
	};
}
