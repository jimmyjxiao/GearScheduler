﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::CheckoutManager::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}


/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::MainPage::MainPage_obj1_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::NavItem>
{
public:
    MainPage_obj1_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 2: // MainPage.xaml line 25
                this->obj2 = safe_cast<::Windows::UI::Xaml::Controls::SymbolIcon^>(__target);
                break;
            case 3: // MainPage.xaml line 26
                this->obj3 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
        }
    }

    void DisconnectUnloadedObject(int connectionId)
    {
        throw ref new ::Platform::InvalidArgumentException("No unloadable elements to disconnect.");
    }

    void ResetTemplate()
    {
    }

    int ProcessBindings(::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
    {
        int nextPhase = -1;
        switch(args->Phase)
        {
            case 0:
                nextPhase = -1;
                this->SetDataRoot(static_cast<::CheckoutManager::NavItem^>(args->Item));
                if (this->_dataContextChangedToken.Value != 0)
                {
                    safe_cast<::Windows::UI::Xaml::FrameworkElement^>(args->ItemContainer->ContentTemplateRoot)->DataContextChanged -= this->_dataContextChangedToken;
                    this->_dataContextChangedToken.Value = 0;
                }
                this->_isInitialized = true;
                break;
        }
        this->Update_((::CheckoutManager::NavItem^) args->Item, (1 << args->Phase));
        return nextPhase;
    }
private:
    // Fields for each control that has bindings.
    ::Windows::UI::Xaml::Controls::SymbolIcon^ obj2;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj3;

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::NavItem^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_Symbol(obj->Symbol, phase);
                this->Update_Label(obj->Label, phase);
            }
        }
    }
    void Update_Symbol(::Windows::UI::Xaml::Controls::Symbol obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // MainPage.xaml line 25
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_SymbolIcon_Symbol(this->obj2, obj);
        }
    }
    void Update_Label(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // MainPage.xaml line 26
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj3, obj, nullptr);
        }
    }
};

void ::CheckoutManager::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
    case 4:
        {
            this->navMenu = safe_cast<::Windows::UI::Xaml::Controls::SplitView^>(__target);
        }
        break;
    case 5:
        {
            ::Windows::UI::Xaml::Controls::Button^ element5 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element5))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Button_Click);
        }
        break;
    case 6:
        {
            this->navigator = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::ListView^>(this->navigator))->SelectionChanged += ref new ::Windows::UI::Xaml::Controls::SelectionChangedEventHandler(this, (void (::CheckoutManager::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::Controls::SelectionChangedEventArgs^))&MainPage::ListView_SelectionChanged);
        }
        break;
    case 7:
        {
            this->zFrame = safe_cast<::Windows::UI::Xaml::Controls::Frame^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Frame^>(this->zFrame))->Navigated += ref new ::Windows::UI::Xaml::Navigation::NavigatedEventHandler(this, (void (::CheckoutManager::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::Navigation::NavigationEventArgs^))&MainPage::zFrame_Navigated);
            (safe_cast<::Windows::UI::Xaml::Controls::Frame^>(this->zFrame))->Loaded += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::MainPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::Page_Loaded);
        }
        break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::CheckoutManager::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    ::XamlBindingInfo::XamlBindings^ bindings = nullptr;
    switch (__connectionId)
    {
        case 1: // MainPage.xaml line 17
            {
                ::Windows::UI::Xaml::Controls::Grid^ element1 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                MainPage_obj1_Bindings* objBindings = new MainPage_obj1_Bindings();
                objBindings->SetDataRoot(element1->DataContext);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element1);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element1, bindings);
            }
            break;
    }
    return bindings;
}

#pragma warning(pop)


