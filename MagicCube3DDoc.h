// MagicCube3DDoc.h : interface of the CMagicCube3DDoc class
//


#pragma once


class CMagicCube3DDoc : public CDocument
{
protected: // create from serialization only
	CMagicCube3DDoc();
	DECLARE_DYNCREATE(CMagicCube3DDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMagicCube3DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


