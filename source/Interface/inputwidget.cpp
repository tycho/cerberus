/*
 * Copyright (c) 2010 Steven Noonan <steven@uplinklabs.net>
 *                and Miah Clayton <miah@ferrousmoon.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "universal_include.h"

#include <typeinfo>

#include "App/app.h"
#include "Interface/interface.h"
#include "Interface/inputwidget.h"

InputWidget::InputWidget ( InputCallback _callback, Widget *_callbackParam,
                           Sint32 _x, Sint32 _y, Sint32 _w, Sint32 _h )
 : Widget ( _x, _y, _w, _h )
{
    m_widgetClass = WIDGET_INPUT;
    m_callback = _callback;
    m_callbackParam = _callbackParam;
}

int InputWidget::SendEnterKey ()
{
    if ( m_callback )
    {
        try {
            m_callback ( m_callbackParam );
        } catch ( std::exception &e ) {
            // TODO: Print out what 'e' provides.
            g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
            g_console->WriteLine ( "WARNING: InputWidget of type '%d' tried to use an invalid callback.", m_widgetClass );
            g_console->WriteLine ( "         m_callback threw exception '%s'", e.what() );
            g_console->SetColour ();
        }
        return -1;
    } else {
        // This widget has no callbacks defined.
        return 0;
    }
}

Widget *InputWidget::MouseUpdate ()
{
    if ( m_callback )
    {
        // It feels weird if it reacts on MouseDown instead of MouseUp
        if ( g_interface->MouseLeftEdge() && !g_interface->MouseLeft() )
        {
            try {
                m_callback ( m_callbackParam );
            } catch ( std::exception &e ) {
                // TODO: Print out what 'e' provides.
                g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
                g_console->WriteLine ( "WARNING: InputWidget of type '%s' tried to use an invalid callback.", m_widgetClass );
                g_console->WriteLine ( "         m_callback threw exception '%s'", e.what() );
                g_console->SetColour ();
            }
        }
        // Even if the click wasn't used, we return -1 because this
        // widget does have a callback defined for !_mouseDown calls.
        return this;
    } else {
        // This widget has no callbacks defined.
        return NULL;
    }
}
