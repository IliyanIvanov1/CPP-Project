
// Notifier_Interface.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNotifierInterfaceApp:
// See Notifier_Interface.cpp for the implementation of this class
//

class CNotifierInterfaceApp : public CWinApp
{
public:
	CNotifierInterfaceApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CNotifierInterfaceApp theApp;
