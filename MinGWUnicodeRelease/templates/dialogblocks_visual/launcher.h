/////////////////////////////////////////////////////////////////////////////
// Name:        Launcher.h
// Purpose:     
// Author:      Sergey Talipov
// Modified by: 
// Created:     03/11/2023 15:12:47
// RCS-ID:      
// Copyright:   15681627-3C745D8E-630127F2
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _Launcher_H_
#define _Launcher_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "mainform.h"
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
////@end control identifiers

/*!
 * Launcher class declaration
 */

class Launcher: public wxApp
{    
    DECLARE_CLASS( Launcher )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    Launcher();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin Launcher event handler declarations

////@end Launcher event handler declarations

////@begin Launcher member function declarations

////@end Launcher member function declarations

////@begin Launcher member variables
////@end Launcher member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(Launcher)
////@end declare app

#endif
    // _Launcher_H_
