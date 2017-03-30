//
// TeamPage.xaml.h
// Declaration of the TeamPage class
//

#pragma once

#include "TeamPage.g.h"
#include "dataManager.h"
namespace CheckoutManager
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref struct Team sealed
	{
		property Platform::String^ teamName;
		property Windows::UI::Xaml::Media::SolidColorBrush^ color;
	};
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class TeamPage sealed
	{
	public:
		TeamPage();
		property Windows::Foundation::Collections::IVector<Team^>^ bindTeams
		{
			Windows::Foundation::Collections::IVector<Team^>^ get();
		}
	private:
		dataspace::dataManager * data;
		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		Platform::Collections::Vector<Team^>^ teamvec = nullptr;
		void Password_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void confirmpass_PasswordChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
	
}
