﻿/*====================================================================
Copyright(c) 2016 Adam Rankin


Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and / or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
====================================================================*/

#pragma once

// Local includes
#include "IGTLConnectorPage.g.h"

namespace WF = Windows::Foundation;
namespace WFC = WF::Collections;
namespace WFM = WF::Metadata;
namespace WUX = Windows::UI::Xaml;
namespace WUXC = Windows::UI::Xaml::Controls;
namespace WUXM = Windows::UI::Xaml::Media;

namespace UWPOpenIGTLinkUI
{

  /// <summary>
  /// An empty page that can be used on its own or navigated to within a Frame.
  /// </summary>
  public ref class IGTLConnectorPage sealed
  {
  public:
    IGTLConnectorPage();

  private:
    void onUITimerTick( Platform::Object^ sender, Platform::Object^ e );
    void serverPortTextBox_TextChanged( Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e );
    void serverHostnameTextBox_TextChanged( Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e );
    void connectButton_Click( Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e );
    void processConnectionResult( bool result );

  protected private:
    UWPOpenIGTLink::IGTLinkClient^ IGTClient;

    WUX::DispatcherTimer^ UITimer;
  };

}