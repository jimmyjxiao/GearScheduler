﻿//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "OOBEPage.xaml.h"
#include "TrialExpired.xaml.h"
using namespace CheckoutManager;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
dataspace::dataManager * CheckoutManager::database = new dataspace::dataManager();
/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
	bool isintroed = false;
	auto settings = Windows::Storage::ApplicationData::Current->LocalSettings;
	if (settings->Values->HasKey("firstTimefinished"))
	{
		if(static_cast<bool>(settings->Values->Lookup("firstTimefinished")))
			isintroed = true;
	}
	if (Windows::ApplicationModel::Store::CurrentApp::LicenseInformation->IsActive)
	{
		if (!isintroed)
		{
			if (Window::Current->Content == nullptr)
				Window::Current->Content = ref new OOBEPage();
		}
		else
		{
			// Show graphics profiling information while debugging.
			auto shell = dynamic_cast<MainPage^>(Window::Current->Content);
			// Do not repeat app initialization when the Window already has content,
			// just ensure that the window is active
			if (shell == nullptr)
			{
				// Create a Frame to act as the navigation context and associate it with
				// a SuspensionManager key
				shell = ref new MainPage();

				shell->AppFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

				if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
				{
					// TODO: Restore the saved session state only when appropriate, scheduling the
					// final launch steps after the restore is complete

				}


			}
			Window::Current->Content = shell;
		}
	}
	else {
		Window::Current->Content = ref new TrialExpired();
	}
	Window::Current->Activate();

}

/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;  // Unused parameter
    (void) e;   // Unused parameter

    //TODO: Save application state and stop any background activity
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
    throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}