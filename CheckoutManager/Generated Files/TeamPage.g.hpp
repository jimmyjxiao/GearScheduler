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

#include "TeamPage.xaml.h"

void ::CheckoutManager::TeamPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///TeamPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}


/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::TeamPage::TeamPage_obj4_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::Team>
{
public:
    TeamPage_obj4_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 4: // TeamPage.xaml line 27
                this->obj4 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
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
                this->SetDataRoot(static_cast<::CheckoutManager::Team^>(args->Item));
                if (this->_dataContextChangedToken.Value != 0)
                {
                    safe_cast<::Windows::UI::Xaml::FrameworkElement^>(args->ItemContainer->ContentTemplateRoot)->DataContextChanged -= this->_dataContextChangedToken;
                    this->_dataContextChangedToken.Value = 0;
                }
                this->_isInitialized = true;
                break;
        }
        this->Update_((::CheckoutManager::Team^) args->Item, (1 << args->Phase));
        return nextPhase;
    }
private:
    // Fields for each control that has bindings.
    ::Platform::WeakReference obj4;

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::Team^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_teamName(obj->teamName, phase);
                this->Update_color(obj->color, phase);
            }
        }
    }
    void Update_teamName(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // TeamPage.xaml line 27
            if (this->obj4 != nullptr)
            {
                ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj4.Resolve<::Windows::UI::Xaml::Controls::TextBlock>(), obj, nullptr);
            }
        }
    }
    void Update_color(::Windows::UI::Xaml::Media::SolidColorBrush^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // TeamPage.xaml line 27
            if (this->obj4 != nullptr)
            {
                ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Foreground(this->obj4.Resolve<::Windows::UI::Xaml::Controls::TextBlock>(), obj, nullptr);
            }
        }
    }
};

/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::TeamPage::TeamPage_obj1_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::TeamPage>
{
public:
    TeamPage_obj1_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 3: // TeamPage.xaml line 22
                this->obj3 = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
                break;
        }
    }

    void DisconnectUnloadedObject(int connectionId)
    {
        throw ref new ::Platform::InvalidArgumentException("No unloadable elements to disconnect.");
    }
private:
    // Fields for each control that has bindings.
    ::Windows::UI::Xaml::Controls::ListView^ obj3;

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::TeamPage^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_bindTeams(obj->bindTeams, phase);
            }
        }
    }
    void Update_bindTeams(::Windows::Foundation::Collections::IVector<::CheckoutManager::Team^>^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // TeamPage.xaml line 22
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(this->obj3, obj, nullptr);
        }
    }
};

void ::CheckoutManager::TeamPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
    case 2:
        {
            this->stack = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
        }
        break;
    case 3:
        {
            this->teamslist = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::ListView^>(this->teamslist))->ContextRequested += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::UIElement^, ::Windows::UI::Xaml::Input::ContextRequestedEventArgs^>(this, (void (::CheckoutManager::TeamPage::*)
                (::Windows::UI::Xaml::UIElement^, ::Windows::UI::Xaml::Input::ContextRequestedEventArgs^))&TeamPage::ListView_ContextRequested);
        }
        break;
    case 5:
        {
            this->newTeambox = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    case 6:
        {
            this->Password = safe_cast<::Windows::UI::Xaml::Controls::PasswordBox^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::PasswordBox^>(this->Password))->PasswordChanged += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::TeamPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&TeamPage::Password_PasswordChanged);
        }
        break;
    case 7:
        {
            this->confirmpass = safe_cast<::Windows::UI::Xaml::Controls::PasswordBox^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::PasswordBox^>(this->confirmpass))->PasswordChanged += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::TeamPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&TeamPage::confirmpass_PasswordChanged);
        }
        break;
    case 8:
        {
            this->addbutton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->addbutton))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::TeamPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&TeamPage::Button_Click);
        }
        break;
    case 9:
        {
            this->addError = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
        }
        break;
    case 10:
        {
            this->addTypeWarning = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::CheckoutManager::TeamPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    ::XamlBindingInfo::XamlBindings^ bindings = nullptr;
    switch (__connectionId)
    {
        case 1: // TeamPage.xaml line 1
            {
                ::Windows::UI::Xaml::Controls::Page^ element1 = safe_cast<::Windows::UI::Xaml::Controls::Page^>(__target);
                TeamPage_obj1_Bindings* objBindings = new TeamPage_obj1_Bindings();
                objBindings->SetDataRoot(this);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                this->Bindings = bindings;
                element1->Loading += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::FrameworkElement^, ::Platform::Object^>(bindings, &::XamlBindingInfo::XamlBindings::Loading);
            }
            break;
        case 4: // TeamPage.xaml line 27
            {
                ::Windows::UI::Xaml::Controls::TextBlock^ element4 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                TeamPage_obj4_Bindings* objBindings = new TeamPage_obj4_Bindings();
                objBindings->SetDataRoot(element4->DataContext);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element4);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element4, bindings);
            }
            break;
    }
    return bindings;
}

#pragma warning(pop)


