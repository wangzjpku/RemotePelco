
// test_pelco.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ctest_pelcoApp:
// See test_pelco.cpp for the implementation of this class
//

class Ctest_pelcoApp : public CWinApp
{
public:
	Ctest_pelcoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ctest_pelcoApp theApp;