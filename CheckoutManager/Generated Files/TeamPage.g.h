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
                ref class StackPanel;
                ref class GridView;
                ref class TextBox;
                ref class PasswordBox;
                ref class Button;
                ref class TextBlock;
            }
        }
    }
}

namespace CheckoutManager
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class TeamPage : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        void UnloadObject(::Windows::UI::Xaml::DependencyObject^ dependencyObject);
        void DisconnectUnloadedObject(int connectionId);
    
    private:
        bool _contentLoaded;
    
        class TeamPage_obj4_Bindings;
        class TeamPage_obj1_Bindings;
    
        ::XamlBindingInfo::XamlBindings^ Bindings;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ stack;
        private: ::Windows::UI::Xaml::Controls::GridView^ teamslist;
        private: ::Windows::UI::Xaml::Controls::TextBox^ newTeambox;
        private: ::Windows::UI::Xaml::Controls::PasswordBox^ Password;
        private: ::Windows::UI::Xaml::Controls::PasswordBox^ confirmpass;
        private: ::Windows::UI::Xaml::Controls::Button^ addbutton;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ addError;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ addTypeWarning;
    };
}

