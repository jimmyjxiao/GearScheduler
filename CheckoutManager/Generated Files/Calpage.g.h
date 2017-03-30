﻿#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

#include "XamlBindingInfo.g.h"

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Pivot;
                ref class ListView;
                ref class RadioButton;
            }
        }
    }
}
namespace CheckoutManager {
    ref class WeekViewControl;
    ref class MonthViewControl;
}

namespace CheckoutManager
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class Calpage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
        class Calpage_obj1_Bindings;
    
        ::XamlBindingInfo::XamlBindings^ Bindings;
        private: ::Windows::UI::Xaml::Controls::Pivot^ lengthPivot;
        private: ::Windows::UI::Xaml::Controls::ListView^ list;
        private: ::Windows::UI::Xaml::Controls::RadioButton^ devradio;
        private: ::CheckoutManager::WeekViewControl^ weekview;
        private: ::CheckoutManager::MonthViewControl^ monthView;
    };
}

