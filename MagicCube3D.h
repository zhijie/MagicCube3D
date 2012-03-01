// MagicCube3D.h : main header file for the MagicCube3D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "OpenGL.h"

// CMagicCube3DApp:
// See MagicCube3D.cpp for the implementation of this class
//

class CMagicCube3DApp : public CWinApp
{
public:
	CMagicCube3DApp();
	
	COpenGL openGL;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CMagicCube3DApp theApp;