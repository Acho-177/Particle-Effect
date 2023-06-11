
// TermProject.h : main header file for the TermProject application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTermProjectApp:
// See TermProject.cpp for the implementation of this class
//

class CTermProjectApp : public CWinApp
{
public:
	CTermProjectApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTermProjectApp theApp;
