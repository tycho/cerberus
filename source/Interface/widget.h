/*
 * Copyright (c) 2009 Steven Noonan <steven@uplinklabs.net>
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

#ifndef __included_widget_h
#define __included_widget_h

typedef enum
{
	WIDGET_UNKNOWN,
	WIDGET_WINDOW,
	WIDGET_BUTTON,
	WIDGET_INPUT,
	WIDGET_ERROR_WINDOW,
	WIDGET_TEXT
} WidgetClass;

class Widget
{
protected:
    WidgetClass m_widgetClass;

    SDL_Rect m_position;

    Uint32 m_cachedSurfaceID;
	bool   m_rebuildDisplayList;
	Uint32 m_displayList;

    Data::LList<Widget *> m_widgets;

    Widget *m_enterKeyDefault;

    bool m_expired;

public:
    Widget ();
    Widget ( Sint16 x, Sint16 y, Uint16 w, Uint16 h );
    virtual ~Widget();

    virtual bool HasEnterKeyDefault ();

    virtual void Expire ();
    virtual bool Expired ();

    virtual void AddWidget ( Widget *_widget );
    virtual void Update ();
	virtual void Initialise ();
    virtual void Render ();
    virtual void Render ( Sint16 _xOffset, Sint16 _yOffset );

    virtual void SetPosition ( Sint16 x, Sint16 y );
    virtual void SetSize ( Uint16 w, Uint16 h );

    virtual WidgetClass ClassID();

    virtual bool IsInsideWidget ( int _mouseX, int _mouseY );
    virtual int MouseDown ( bool _mouseDown, Sint32 _x, Sint32 _y ) = 0;
    virtual int SendEnterKey () = 0;

    virtual Data::LList<Widget *> *GetWidgetList();

    friend class Interface;
    friend class Window;
    friend class QuitWindow;
};

#endif
