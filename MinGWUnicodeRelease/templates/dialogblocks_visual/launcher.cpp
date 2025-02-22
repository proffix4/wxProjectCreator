/////////////////////////////////////////////////////////////////////////////
// Name:        Launcher.cpp
// Purpose:     
// Author:      Sergey Talipov
// Modified by: 
// Created:     03/11/2023 15:12:47
// RCS-ID:      
// Copyright:   15681627-3C745D8E-630127F2
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "Launcher.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( Launcher )
////@end implement app


/*
 * Launcher type definition
 */

IMPLEMENT_CLASS( Launcher, wxApp )


/*
 * Launcher event table definition
 */

BEGIN_EVENT_TABLE( Launcher, wxApp )

////@begin Launcher event table entries
////@end Launcher event table entries

END_EVENT_TABLE()


/*
 * Constructor for Launcher
 */

Launcher::Launcher()
{
    Init();
}


/*
 * Member initialisation
 */

void Launcher::Init()
{
////@begin Launcher member initialisation
////@end Launcher member initialisation
}

/*
 * Initialisation for Launcher
 */

bool Launcher::OnInit()
{    
////@begin Launcher initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	MainForm* mainWindow = new MainForm( NULL );
	mainWindow->Show(true);
////@end Launcher initialisation

    return true;
}


/*
 * Cleanup for Launcher
 */

int Launcher::OnExit()
{    
////@begin Launcher cleanup
	return wxApp::OnExit();
////@end Launcher cleanup
}

