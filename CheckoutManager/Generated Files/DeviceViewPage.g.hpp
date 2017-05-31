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

#include "DeviceViewPage.xaml.h"

void ::CheckoutManager::DeviceViewPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///DeviceViewPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}


/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::DeviceViewPage::DeviceViewPage_obj3_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::device>
    , public ::XamlBindingInfo::IXamlBindingTracking
{
            ::Windows::UI::Xaml::ResourceDictionary^ localResources;
            ::Platform::WeakReference converterLookupRoot;
public:
    DeviceViewPage_obj3_Bindings()
    {
        InitializeTracking(this);
    }

private:
    ~DeviceViewPage_obj3_Bindings()
    {
        ReleaseAllListeners();
    }

public:

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 3: // DeviceViewPage.xaml line 17
                this->obj3 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                break;
            case 4: // DeviceViewPage.xaml line 30
                this->obj4 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
            case 5: // DeviceViewPage.xaml line 27
                this->obj5 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
            case 6: // DeviceViewPage.xaml line 24
                this->obj6 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
        }
    }

    void DisconnectUnloadedObject(int connectionId)
    {
        throw ref new ::Platform::InvalidArgumentException("No unloadable elements to disconnect.");
    }

    void ResetTemplate()
    {
        ReleaseAllListeners();
    }

    int ProcessBindings(::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
    {
        int nextPhase = -1;
        switch(args->Phase)
        {
            case 0:
                nextPhase = -1;
                this->SetDataRoot(static_cast<::CheckoutManager::device^>(args->Item));
                if (this->_dataContextChangedToken.Value != 0)
                {
                    safe_cast<::Windows::UI::Xaml::FrameworkElement^>(args->ItemContainer->ContentTemplateRoot)->DataContextChanged -= this->_dataContextChangedToken;
                    this->_dataContextChangedToken.Value = 0;
                }
                this->_isInitialized = true;
                break;
        }
        this->Update_((::CheckoutManager::device^) args->Item, (1 << args->Phase));
        return nextPhase;
    }

    void SetConverterLookupRoot(::Windows::UI::Xaml::FrameworkElement^ rootElement)
    {
        this->converterLookupRoot = rootElement;
    }

    ::Windows::UI::Xaml::Data::IValueConverter^ LookupConverter(::Platform::String^ key)
    {
        if (this->localResources == nullptr)
        {
            this->localResources = this->converterLookupRoot.Resolve<::Windows::UI::Xaml::FrameworkElement>()->Resources;
            this->converterLookupRoot = nullptr;
            }
        return safe_cast<::Windows::UI::Xaml::Data::IValueConverter^>(this->localResources->HasKey(key) ? this->localResources->Lookup(key) : ::Windows::UI::Xaml::Application::Current->Resources->Lookup(key));
    }

private:
    // Fields for each control that has bindings.
    ::Platform::WeakReference obj3;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj4;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj5;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj6;
    
    // Fields for binding tracking.

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::device^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | DATA_CHANGED | (1 << 0))) != 0)
            {
                this->Update_checkedOut(obj->checkedOut, phase);
            }
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_deviceID(obj->deviceID, phase);
                this->Update_currentRentee(obj->currentRentee, phase);
                this->Update_description(obj->description, phase);
            }
        }
    }
    void Update_checkedOut(::Platform::Boolean obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED | DATA_CHANGED)) != 0)
        {
            // DeviceViewPage.xaml line 17
            if (this->obj3 != nullptr)
            {
                ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_Panel_Background(this->obj3.Resolve<::Windows::UI::Xaml::Controls::Grid>(), safe_cast<::Windows::UI::Xaml::Media::Brush^>(this->LookupConverter("availconverter")->Convert(obj, ::Windows::UI::Xaml::Media::Brush::typeid, nullptr, nullptr)), nullptr);
            }
        }
    }
    void Update_deviceID(::default::int32 obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 30
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj4, obj.ToString(), nullptr);
        }
    }
    void Update_currentRentee(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 27
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj5, obj, nullptr);
        }
    }
    void Update_description(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 24
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj6, obj, nullptr);
        }
    }

    virtual void ReleaseAllListeners() override
    {
    }

    virtual void PropertyChanged(Platform::Object^ sender, ::Windows::UI::Xaml::Data::PropertyChangedEventArgs^ e) override
    {
    }

    void CollectionChanged(::Platform::Object^ sender, ::Windows::UI::Xaml::Interop::NotifyCollectionChangedEventArgs^ e)
    {
    }

    void VectorChanged(::Platform::Object^ sender, ::Windows::Foundation::Collections::IVectorChangedEventArgs^ e)
    {
    }

    void MapChanged(::Platform::Object^ sender, ::Windows::Foundation::Collections::IMapChangedEventArgs<::Platform::String^>^ e)
    {
    }

    void DependencyPropertyChanged(::Windows::UI::Xaml::DependencyObject^ sender, ::Windows::UI::Xaml::DependencyProperty^ prop)
    {
        if (sender != nullptr)
        {
        }
    }
};

/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::DeviceViewPage::DeviceViewPage_obj8_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::devicesGroup>
{
public:
    DeviceViewPage_obj8_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 8: // DeviceViewPage.xaml line 79
                this->obj8 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
            case 9: // DeviceViewPage.xaml line 82
                this->obj9 = safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(__target);
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
                this->SetDataRoot(static_cast<::CheckoutManager::devicesGroup^>(args->Item));
                if (this->_dataContextChangedToken.Value != 0)
                {
                    safe_cast<::Windows::UI::Xaml::FrameworkElement^>(args->ItemContainer->ContentTemplateRoot)->DataContextChanged -= this->_dataContextChangedToken;
                    this->_dataContextChangedToken.Value = 0;
                }
                this->_isInitialized = true;
                break;
        }
        this->Update_((::CheckoutManager::devicesGroup^) args->Item, (1 << args->Phase));
        return nextPhase;
    }
private:
    // Fields for each control that has bindings.
    ::Platform::WeakReference obj8;
    ::Windows::UI::Xaml::Controls::MenuFlyoutItem^ obj9;

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::devicesGroup^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_key(obj->key, phase);
                this->Update_color(obj->color, phase);
                this->Update_deleteGroup(obj->deleteGroup, phase);
            }
        }
    }
    void Update_key(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 79
            if (this->obj8 != nullptr)
            {
                ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj8.Resolve<::Windows::UI::Xaml::Controls::TextBlock>(), obj, nullptr);
            }
        }
    }
    void Update_color(::Windows::UI::Xaml::Media::SolidColorBrush^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 79
            if (this->obj8 != nullptr)
            {
                ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Foreground(this->obj8.Resolve<::Windows::UI::Xaml::Controls::TextBlock>(), obj, nullptr);
            }
        }
    }
    void Update_deleteGroup(::Windows::UI::Xaml::Input::ICommand^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 82
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_MenuFlyoutItem_Command(this->obj9, obj, nullptr);
        }
    }
};

/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class CheckoutManager::DeviceViewPage::DeviceViewPage_obj1_Bindings 
    : public ::XamlBindingInfo::ReferenceTypeXamlBindings<::CheckoutManager::DeviceViewPage>
{
public:
    DeviceViewPage_obj1_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 2: // DeviceViewPage.xaml line 12
                this->obj2 = safe_cast<::Windows::UI::Xaml::Data::CollectionViewSource^>(__target);
                break;
            case 7: // DeviceViewPage.xaml line 68
                this->obj7 = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
                break;
            case 14: // DeviceViewPage.xaml line 46
                this->obj14 = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(__target);
                break;
        }
    }

    void DisconnectUnloadedObject(int connectionId)
    {
        throw ref new ::Platform::InvalidArgumentException("No unloadable elements to disconnect.");
    }
private:
    // Fields for each control that has bindings.
    ::Windows::UI::Xaml::Data::CollectionViewSource^ obj2;
    ::Windows::UI::Xaml::Controls::ListView^ obj7;
    ::Windows::UI::Xaml::Controls::ComboBox^ obj14;

    // Update methods for each path node used in binding steps.
    void Update_(::CheckoutManager::DeviceViewPage^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_bindDevices(obj->bindDevices, phase);
                this->Update_devicesGrouped(obj->devicesGrouped, phase);
            }
        }
    }
    void Update_bindDevices(::Windows::Foundation::Collections::IVector<::CheckoutManager::devicesGroup^>^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 12
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Data_CollectionViewSource_Source(this->obj2, obj, nullptr);
            // DeviceViewPage.xaml line 46
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(this->obj14, obj, nullptr);
        }
    }
    void Update_devicesGrouped(::Windows::UI::Xaml::Data::CollectionViewSource^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_devicesGrouped_View(obj->View, phase);
            }
        }
    }
    void Update_devicesGrouped_View(::Windows::UI::Xaml::Data::ICollectionView^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            // DeviceViewPage.xaml line 68
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(this->obj7, obj, nullptr);
        }
    }
};

void ::CheckoutManager::DeviceViewPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
    case 2:
        {
            this->devicesGrouped = safe_cast<::Windows::UI::Xaml::Data::CollectionViewSource^>(__target);
        }
        break;
    case 3:
        {
            ::Windows::UI::Xaml::Controls::Grid^ element3 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Grid^>(element3))->ContextRequested += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::UIElement^, ::Windows::UI::Xaml::Input::ContextRequestedEventArgs^>(this, (void (::CheckoutManager::DeviceViewPage::*)
                (::Windows::UI::Xaml::UIElement^, ::Windows::UI::Xaml::Input::ContextRequestedEventArgs^))&DeviceViewPage::Grid_ContextRequested);
        }
        break;
    case 9:
        {
            ::Windows::UI::Xaml::Controls::MenuFlyoutItem^ element9 = safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(element9))->Loaded += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::DeviceViewPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DeviceViewPage::MenuFlyoutItem_Loaded);
        }
        break;
    case 10:
        {
            this->typeTextbox = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    case 11:
        {
            ::Windows::UI::Xaml::Controls::Button^ element11 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element11))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::DeviceViewPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DeviceViewPage::AddDeviceType_Click);
        }
        break;
    case 12:
        {
            this->addDeviceTypeError = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
        }
        break;
    case 13:
        {
            this->addDeviceTypeWarning = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    case 14:
        {
            this->DeviceSelector = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(__target);
        }
        break;
    case 15:
        {
            this->newdevdesc = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
        }
        break;
    case 16:
        {
            this->addDevicebutton = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
            (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->addDevicebutton))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::CheckoutManager::DeviceViewPage::*)
                (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DeviceViewPage::addDevicebutton_Click);
        }
        break;
    case 17:
        {
            this->addDeviceError = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
        }
        break;
    case 18:
        {
            this->addDeviceWarning = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
        }
        break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::CheckoutManager::DeviceViewPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    ::XamlBindingInfo::XamlBindings^ bindings = nullptr;
    switch (__connectionId)
    {
        case 1: // DeviceViewPage.xaml line 1
            {
                ::Windows::UI::Xaml::Controls::Page^ element1 = safe_cast<::Windows::UI::Xaml::Controls::Page^>(__target);
                DeviceViewPage_obj1_Bindings* objBindings = new DeviceViewPage_obj1_Bindings();
                objBindings->SetDataRoot(this);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                this->Bindings = bindings;
                element1->Loading += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::FrameworkElement^, ::Platform::Object^>(bindings, &::XamlBindingInfo::XamlBindings::Loading);
            }
            break;
        case 3: // DeviceViewPage.xaml line 17
            {
                ::Windows::UI::Xaml::Controls::Grid^ element3 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                DeviceViewPage_obj3_Bindings* objBindings = new DeviceViewPage_obj3_Bindings();
                objBindings->SetDataRoot(element3->DataContext);
                objBindings->SetConverterLookupRoot(this);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element3);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element3, bindings);
            }
            break;
        case 8: // DeviceViewPage.xaml line 79
            {
                ::Windows::UI::Xaml::Controls::TextBlock^ element8 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                DeviceViewPage_obj8_Bindings* objBindings = new DeviceViewPage_obj8_Bindings();
                objBindings->SetDataRoot(element8->DataContext);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element8);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element8, bindings);
            }
            break;
    }
    return bindings;
}

#pragma warning(pop)


