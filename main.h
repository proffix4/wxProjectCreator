/////////////////////////////////////////////////////////////////////////////
// Name:        main.h
// Purpose:     
// Author:      Talipov S.N.
// Modified by: 
// Created:     12.06.2025 21:08:10
// RCS-ID:      
// Copyright:   @proffix4
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H_
#define _MAIN_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MAIN 10000
#define SYMBOL_MAIN_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_MAIN_TITLE _("Main")
#define SYMBOL_MAIN_IDNAME ID_MAIN
#define SYMBOL_MAIN_SIZE wxSize(400, 300)
#define SYMBOL_MAIN_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * Main class declaration
 */

class Main: public wxFrame
{    
    DECLARE_CLASS( Main )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    Main();
    Main( wxWindow* parent, wxWindowID id = SYMBOL_MAIN_IDNAME, const wxString& caption = SYMBOL_MAIN_TITLE, const wxPoint& pos = SYMBOL_MAIN_POSITION, const wxSize& size = SYMBOL_MAIN_SIZE, long style = SYMBOL_MAIN_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAIN_IDNAME, const wxString& caption = SYMBOL_MAIN_TITLE, const wxPoint& pos = SYMBOL_MAIN_POSITION, const wxSize& size = SYMBOL_MAIN_SIZE, long style = SYMBOL_MAIN_STYLE );

    /// Destructor
    ~Main();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin Main event handler declarations
////@end Main event handler declarations

////@begin Main member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Main member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin Main member variables
////@end Main member variables
};

#endif
    // _MAIN_H_
