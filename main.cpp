/////////////////////////////////////////////////////////////////////////////
// Name:        main.cpp
// Purpose:     
// Author:      Talipov S.N.
// Modified by: 
// Created:     12.06.2025 21:08:10
// RCS-ID:      
// Copyright:   @proffix4
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

#include "main.h"

////@begin XPM images

////@end XPM images


/*
 * Main type definition
 */

IMPLEMENT_CLASS( Main, wxFrame )


/*
 * Main event table definition
 */

BEGIN_EVENT_TABLE( Main, wxFrame )

////@begin Main event table entries
////@end Main event table entries

END_EVENT_TABLE()


/*
 * Main constructors
 */

Main::Main()
{
    Init();
}

Main::Main( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * Main creator
 */

bool Main::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin Main creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end Main creation
    return true;
}


/*
 * Main destructor
 */

Main::~Main()
{
////@begin Main destruction
////@end Main destruction
}


/*
 * Member initialisation
 */

void Main::Init()
{
////@begin Main member initialisation
////@end Main member initialisation
}


/*
 * Control creation for Main
 */

void Main::CreateControls()
{    
////@begin Main content construction
    Main* itemFrame1 = this;

////@end Main content construction
}


/*
 * Should we show tooltips?
 */

bool Main::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap Main::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin Main bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Main bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon Main::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin Main icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Main icon retrieval
}
