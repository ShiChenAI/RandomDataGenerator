
// RandomDataGenerator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRandomDataGeneratorApp:
// See RandomDataGenerator.cpp for the implementation of this class
//

class CRandomDataGeneratorApp : public CWinApp
{
public:
	CRandomDataGeneratorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRandomDataGeneratorApp theApp;