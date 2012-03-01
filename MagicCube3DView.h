// MagicCube3DView.h : interface of the CMagicCube3DView class
//


#pragma once
#include "OpenGL.h"
#include "utilities.h"

class CMagicCube3DView : public CView
{
protected: // create from serialization only
	CMagicCube3DView();
	DECLARE_DYNCREATE(CMagicCube3DView)

// Attributes
public:
	CMagicCube3DDoc* GetDocument() const;	
	

	int shuffledNum;
	static const int timerRotate=1;//rotate timer index
	static const int timerShuffle=2;//shuffle timer index
	static const int totleShuffleNum=30;//shuffle number
	static const int rotateStep=3;//angle rotated every time
	static const int rotateStepInterval=10;//time needed for a rotate step
	//time needed for a rotate
	//that's 90/rotateStep*rotateStepInterval+surplus time
	static const int rotateInterval=90/rotateStep*rotateStepInterval+250;

	static const int timerRestore=3;//restore timer index
	int restoredPos;//use in timer during restoration
	CString restoreString;
	RotateInfo rotateInfo;

	int figurePtr;//pointer to figures
	
// Operations
public:
	void Restore_UpdateRotateInfo();
	void Executor();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMagicCube3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGameNew();
	afx_msg void OnShuffle();
	afx_msg void OnRestoreMagicCube();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnFigureCube();
};

#ifndef _DEBUG  // debug version in MagicCube3DView.cpp
inline CMagicCube3DDoc* CMagicCube3DView::GetDocument() const
   { return reinterpret_cast<CMagicCube3DDoc*>(m_pDocument); }
#endif

