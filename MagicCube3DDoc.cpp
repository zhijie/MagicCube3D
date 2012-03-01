// MagicCube3DDoc.cpp : implementation of the CMagicCube3DDoc class
//

#include "stdafx.h"
#include "MagicCube3D.h"

#include "MagicCube3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMagicCube3DDoc

IMPLEMENT_DYNCREATE(CMagicCube3DDoc, CDocument)

BEGIN_MESSAGE_MAP(CMagicCube3DDoc, CDocument)
END_MESSAGE_MAP()


// CMagicCube3DDoc construction/destruction

CMagicCube3DDoc::CMagicCube3DDoc()
{
	// TODO: add one-time construction code here

}

CMagicCube3DDoc::~CMagicCube3DDoc()
{
}

BOOL CMagicCube3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMagicCube3DDoc serialization

void CMagicCube3DDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMagicCube3DDoc diagnostics

#ifdef _DEBUG
void CMagicCube3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMagicCube3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMagicCube3DDoc commands
